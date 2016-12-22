/******************************************************************************
 ***** File Name : Iterator.h
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2016-12-11 16:00
 * Last Modified : 2016-12-22 12:41
 ******************************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#ifndef ITERATOR_H
#define ITERATOR_H
namespace kyaz 
{
    /*
     * 迭代器之型别：
     * input               read-only
     * output              write-only 
     * forward             read&write
     * bidirectional       read&write&++&--
     * random_access       read&write&++&--&+&-
     */
    typedef int ptrdiff_t;
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag :public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag :public bidirectional_iterator_tag {};

    template <typename _Cate, typename _Ty, typename _Dist=int, 
             typename _P=_Ty *, typename _Ref=_Ty &>
    class Iterator
    {
        typedef _Cate   iterator_category;
        typedef _Ty     value_type;
        typedef _Dist   difference_type;
        typedef _P      pointer;
        typedef _Ref    reference;
    };
    /*
     * 迭代器萃取型别：
     * _Cate 迭代器之型别
     * _Ty   迭代器所指之物之型别
     * _Dist 迭代器所指之物的差值型别
     * _P    迭代器所指之物之指针型别
     * _Ref  迭代器所指之物之引用型别
     */

    // VC P.J
    template <typename _Cate, typename _Ty, typename _Dist, 
             typename _P, typename _Ref>
    _Cate _Iter_cat(const Iterator<_Cate, _Ty, _Dist, _P, _Ref> &)
    {
        return _Cate();
    }
    template <typename T>
    random_access_iterator_tag _Iter_cat(const T *)
    {
        return random_access_iterator_tag();
    }

    // Traits-----SGI
    template <typename Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };
    template <typename T>
    struct iterator_traits<T *>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type; 
        typedef int                        difference_type;
        typedef T *                        pointer;
        typedef T &                        reference;
    };
    template <typename T>
    struct iterator_traits<const T *>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type; 
        typedef int                        difference_type;
        typedef T *                        pointer;
        typedef T &                        reference;
    };
    
    template <typename Iterator>
    typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator &)
    {
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();
    }
    template <typename Iterator>
    typename iterator_traits<Iterator>::value_type *
    value_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
    }
    template <typename Iterator>
    typename iterator_traits<Iterator>::difference_type *
    difference_type(const Iterator &)
    {
        return static_cast
            <typename iterator_traits<Iterator>::difference_type *>(0);
    }
    
    template <typename _Ty, typename _D>
    struct _Bidit : public Iterator<bidirectional_iterator_tag, _Ty, _D> {};

    template <typename _Ty, typename _D>
    struct _Ranit : public Iterator<random_access_iterator_tag, _Ty, _D> {};

    template <typename _II>
    typename iterator_traits<_II>::difference_type
    __distance(_II _F, _II _L, input_iterator_tag)
    {
        typename iterator_traits<_II>::difference_type n = 0;
        while (_F++ != _L) ++n;
        return n;
    }

    template <typename _II>
    typename iterator_traits<_II>::difference_type
    __distance(_II _F, _II _L, random_access_iterator_tag)
    {
        return _L - _F;
    }

    template <typename _II>
    typename iterator_traits<_II>::difference_type
    distance(_II _F, _II _L)
    {
        return __distance(_F, _L, iterator_category(_F));
    }



    template <typename _II, typename _Dist>
    void __advance(_II &i, _Dist n, input_iterator_tag)
    {
        while (n--) ++i;
    }
    template <typename _FI, typename _Dist>
    void __advance(_FI &i, _Dist n, forward_iterator_tag)
    {
        __advance(i, n, input_iterator_tag());
    }
    template <typename _BI, typename _Dist>
    void __advance(_BI &i, _Dist n, bidirectional_iterator_tag)
    {
        if (n >= 0)
            while (n--) ++i;
        else
            while (n++) --i;
    }
    template <typename _RAI, typename _Dist>
    void __advance(_RAI &i, _Dist n, random_access_iterator_tag)
    {
        i += n;
    }

    template <typename _II, typename _Dist>
    void advance(_II &i, _Dist n)
    {
        typedef typename iterator_traits<_II>::iterator_category cate;
        __advance(i, n, cate());
        //__advance(i, n, _Iter_cat(i));
    }
}; 
#endif
