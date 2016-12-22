/******************************************************************************
 ***** File Name : Alloc.h
 **** Created By : kyaz758
 *** Description : STL之空间配置器Alloc
 * Creation Date : 2016-12-18 15:12
 * Last Modified : 2016-12-22 15:16
 ******************************************************************************/
#ifndef ALLOC_H
#define ALLOC_H 

#include <cstring>
#include <malloc.h>
namespace kyaz
{
#if 0
#inlude <new>
#define __THROW_BAD_ALLOC throw std::bad_alloc();
#elif !define (__THROW_BAD_ALLOC)
#include <iostream>
#define __THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1);
#endif

    template <int inst>
    class __malloc_alloc_template
    {
    private:
        /*
         * 函数作用：用于空间正常获取失败后的情况
         *           默认行为：首先回调用函数指针释放用户预留的备用空间，
         *                     若失败，则直接exit
         */
        static void *oom_malloc(size_t n);
        static void *oom_realloc(void *, size_t n);
        static void (*__malloc_alloc_oom_handler) ();
    public:
        static void *allocate(size_t n)
        {
            void *result = malloc(n);
            if (NULL == result)
            {
                result = oom_malloc(n);
            }
            return result;
        }
        static void deallocate(void *p, size_t)
        {
            free(p);
        }
        static void * reallocate(void *p, size_t, size_t new_sz)
        {
            void *result = realloc(p, new_sz);
            if (NULL == result)
            {
                result = oom_realloc(p, new_sz);
            }
            return result;
        }
        static void ( *set_malloc_handler( void (*f)() ) ) ()
        {
            void (*old)() = __malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = f;
            return old;
        }
        
    };
    template <int inst>
    void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = NULL;

    typedef __malloc_alloc_template<0> malloc_alloc;
    ///////////////////////////////////////////////////////////////////////////
    enum { __ALIGN = 8 };
    enum { __MAX_BYTES = 128 };
    enum { __NFREELISTS = __MAX_BYTES / __ALIGN };
    template <bool threads, int inst>
    class __default_alloc_template
    {
    private:
        union obj
        {
            union obj * next;
            char client_data[1];
        };
        static obj * volatile free_list[__NFREELISTS];
        static char * start_free;
        static char * end_free;
        static size_t heap_size;
    public:
        static size_t ROUND_UP(size_t bytes)
        {
            return (bytes + __ALIGN - 1) & ~(__ALIGN - 1);
        }
        static size_t FREELIST_INDEX(size_t bytes)
        {
            return ((bytes + __ALIGN - 1) / __ALIGN - 1);
        }
        /*
         * 函数名称：chunk_alloc
         * 返回结果：char类型指针
         * 传入参数：size申请的空间大小， nobjs申请空间个数（默认20）
         * 函数作用：从自建的heap取空间给用户，当池子空时，给内存池"注水"
         */
        static char * chunk_alloc(size_t size, int &nobjs)
        {
            char * result = NULL;
            size_t total_bytes = size * nobjs;  //计算结果为总计申请空间大小
            size_t bytes_left = end_free - start_free;  //计算结果为内存池可用
            if (bytes_left >= total_bytes)  //剩余空间足够此次申请
            {
                result = start_free;
                start_free += total_bytes;
                return result;
            }
            //足够申请一个以上不够nobjs个，则申请byte_left/size个
            else if (bytes_left >= size)  
            {
                result = start_free;
                nobjs = bytes_left/size;
                total_bytes = nobjs * size;
                start_free += total_bytes;
                return result;
            }
            //当heap空间不够一个size大小，先将剩余空间链接入相应的free_list
            //再调用malloc申请空间，即”注水”，×递归× 
            else 
            {
                size_t bytes_to_get = 2*total_bytes + ROUND_UP(heap_size>>4);
                if (bytes_left > 0)  //即当heap有剩余空间，现将其链入
                {
                }
                start_free = (char *)malloc(bytes_to_get);
                //malloc申请空间失败，采取方案：
                //首先遍历free_list，若其后有未用空间，则将其放入heap，×递归×，
                //若无，则调用一级空间配置器处理
                if (NULL == start_free)
                {
                    obj * volatile * my_free_list = NULL;
                    obj * p = NULL;
                    size_t i = size;
                    while (i < __MAX_BYTES)
                    {
                        my_free_list = free_list + FREELIST_INDEX(i);
                        p = *my_free_list;
                        if (p != NULL)
                        {
                            *my_free_list = p->next;
                            start_free = (char *)p;
                            end_free = start_free + i;
                            return chunk_alloc(size, nobjs);
                        }
                        i += __ALIGN;
                    }
                    start_free = (char *)malloc_alloc::allocate(bytes_to_get);
                }
                heap_size += bytes_to_get; 
                end_free = start_free + bytes_to_get;
                return chunk_alloc(size, nobjs);
            }
        }
        /*
         * 函数名称：refill
         * 返回结果：void类型指针，填充内存池后申请到空间的地址（20-1）
         * 传入参数：size填充内存池元素大小
         * 函数作用：使用malloc申请空间，将申请到空间首个的地址返回
         *           供用户使用，其余链接入内存池中
         */
        static void * refill(size_t n)
        {
            int nobjs = 20;
            char *chunk = chunk_alloc(n, nobjs);
            if (nobjs == 1)
                return chunk;
            obj * volatile * my_free_list = free_list + FREELIST_INDEX(n); 
            obj * current_obj, next_obj;
            next_obj = *my_free_list = (obj *)(chunk+n);
            while (1) 
            {
                current_obj = next_obj;
                next_obj = (obj *)((char *)next_obj + n);
                if (current_obj == chunk+n*nobjs)
                {
                    current_obj->next == NULL;
                    break;
                }
                else 
                {
                    current_obj = next_obj;
                }
            }
            obj * result = (obj *)chunk;
            return result;
        }
    public:
        static void * allocate(size_t n)
        {
            obj * volatile * my_free_list = NULL;
            obj * result = NULL;
            if (n > (size_t)__MAX_BYTES)
            {
                return malloc_alloc::allocate(n);
            }
            my_free_list = free_list + FREELIST_INDEX(n);
            result = *my_free_list;
            if (NULL == result)
            {
                void *r = refill(ROUND_UP(n));
                return r;
            }
            *my_free_list = result->next;
            return result;
        }
        static void deallocate(void *p, size_t n)
        {
            obj *q = (obj *)p;
            obj * volatile * my_free_list = NULL;
            if (n > (size_t)__MAX_BYTES)
            {
                malloc_alloc::deallocate(p, n);
                return ;
            }
            *my_free_list = free_list + FREELIST_INDEX;
            q->next = *my_free_list;
            *my_free_list = q;    
        }
        static void * reallocate(void *p, size_t old_sz, size_t new_sz);
    };
    template <bool threads, int inst>
    typename __default_alloc_template<threads, inst>::obj * volatile
    __default_alloc_template<threads, inst>::free_list[__NFREELISTS] = {NULL};

    template <bool threads, int inst>
    char * __default_alloc_template<threads, inst>::start_free = NULL;
    template <bool threads, int inst>
    char * __default_alloc_template<threads, inst>::end_free = NULL;
    template <bool threads, int inst>
    size_t __default_alloc_template<threads, inst>::heap_size = 0;
    ///////////////////////////////////////////////////////////////////////////
    
    //#define __USE_MALLOC 
    #ifdef __USE_MALLOC
    typedef __malloc_alloc_template<0> malloc_alloc;
    typedef malloc_alloc alloc;
    #else
    typedef __default_alloc_template<0, 0> alloc; 
    #endif /* ifdef __USE_MALLOC */ 
    template <class T, class Alloc>
    class simple_alloc
    {
    private:
        static T * allocate(size_t n)   //一组T类型对象的空间
        {
            return 0==n?NULL:(T *)Alloc::allocate(n * sizeof(T));
        }
        static T * allocate()   //一个T类型对象的空间
        {
            return (T *)Alloc::allocate(sizeof(T));
        }
        static void deallocate(T *p, size_t n)
        {
            if (p == NULL || n <= 0) return ;
            Alloc::deallocate(p, sizeof(T)*n);
        }
        static void deallocate(T *p)
        {
            if (p == NULL) return ;
            return Alloc::deallocate(p, sizeof(T));
        }
    };
};
#endif /* ifndef ALLOC_H */
