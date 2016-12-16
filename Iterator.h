/******************************************************************************
 ***** File Name : Iterator.h
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2016-12-11 16:00
 * Last Modified : 2016-12-15 23:02
 ******************************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

namespace kyaz 
{
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
        __advance(i, n, cate());
    }

}
