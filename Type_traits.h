/******************************************************************************
 ***** File Name : Type_traits.h
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2016-12-16 11:22
 * Last Modified : 2016-12-22 12:13
 ******************************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H 
namespace kyaz
{
    struct __true_type {};
    struct __false_type {};
    
    /*
     * 类型萃取模板：define其内各种函数的必要性
     * 作用：提升调用时的效率，减少不必要的析构赋值操作
     */
    template <typename type>
    struct __type_traits
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<char>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<unsigned char>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<signed char>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<short>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<unsigned short>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<int>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<unsigned int>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<long>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<unsigned long>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<float>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<double>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<long double>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <>
    struct __type_traits<bool>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    template <typename T>
    struct __type_traits<const T *>
    {
        typedef __true_type this_dummy_member_must_be_first;
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type is_POD_type;
    };
    
};
#endif /* ifndef TYPE_TRAITS_H */
