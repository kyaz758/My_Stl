/******************************************************************************
 ***** File Name : Construct.h
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2016-12-18 14:47
 * Last Modified : 2016-12-18 15:11
 ******************************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#ifndef CONSTRUCT_H
#define CONSTRUCT_H 

#include "../My_Stl/Iterator.h"
#include "../My_Stl/Type_traits.h"

namespace kyaz
{
    template <typename T1, typename T2>
    inline void construct(T1 *p, const T2 &value)
    {
        new (p) T1(value);
    }
    template <typename T>
    inline void construct(T *p)
    {
        new (p) T();
    }
    
    template <typename T>
    inline void destory(T *pointer)
    {
        pointer->~T();
    }
    template <typename _FI>
    inline void destory(_FI _F, _FI _L)
    {
        __destory(_F, _L, value_type(_F));
    }

    template <typename _FI, typename T>
    inline void __destory(_FI _F, _FI _L, T*)
    {
        typedef typename __type_traits<T>::has_trivial_destructor 
            trivial_destructor;
        __destory_aux(_F, _L, trivial_destructor());
    }
    template <typename _FI>
    inline void __destory_aux(_FI _F, _FI _L, __false_type)
    {
        while (_F++ != _L)
        {
            destory(&*_F);
        }
    }
    template <typename _FI>
    inline void __destory_aux(_FI _F, _FI _L, __true_type) {}
    inline void destory(char *, char *) {}
    inline void destory(wchar_t *, wchar_t *) {}
};


#endif /* ifndef CONSTRUCT_H */
