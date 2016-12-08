/******************************************************************************
 ***** File Name : Vector.h
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2016-11-30 12:43
 * Last Modified : 2016-12-04 10:34
 ******************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

namespace myvector
{
    template <typename _Ty>
    class vector
    {
    public:
        typedef vector<_Ty> _Myt;
        typedef _Ty         value_type;
        typedef _Ty *       _Tptr;
        typedef const _Ty * _Ctptr;
        typedef _Ty &       reference;
        typedef const _Ty & const_reference;
        typedef size_t      size_type;
        typedef int         difference_type;
    public:
        class const_iterator;
        class iterator;
        class const_iterator
        {
        public:
            const_iterator(_Tptr _P = NULL):_Ptr(_P) {}
            const_reference operator*() const
            {
                return *_Ptr;
            }
            _Ctptr operator->()
            {
                return _Ptr;
            }
            const_iterator & operator++()
            {
                ++_Ptr;
                return *this;
            }
            const_iterator operator++(int)
            {
                const_iterator _tmp = *this;
                ++*this;
                return _tmp;
            }
            const_iterator & operator--()
            {
                --_Ptr;
                return *this;
            }
            const_iterator operator--(int)
            {
                const_iterator _tmp = *this;
                --*this;
                return _tmp;
            }
            const_iterator operator+(int n) const
            {
                const_iterator _tmp = _Ptr += n;
                return _tmp; 
            }
            const_iterator operator+(iterator & _X) const
            {
                const_iterator _tmp = _Ptr + _X._Ptr;
                return _tmp;
            }
            const_iterator operator-(int n) const
            {
                const_iterator _tmp = _Ptr -= n;
                return _tmp;
            }
            const_iterator operator-(iterator & _X) const
            {
                const_iterator _tmp = _Ptr - _X._Ptr;
                return _tmp;
            }
            const_iterator& operator+=(difference_type n)
            {
                _Ptr += n;
                return *this;
            }
            const_iterator operator-=(difference_type n)
            {
                _Ptr -= n;
                return *this;
            }
            _Ty & operator[](difference_type n)
            {
                return *(_Ptr+n);
            }
            bool operator==(const_iterator & _X) const
            {
                return _Ptr == _X._Ptr;
            }
            bool operator!=(const_iterator & _X) const
            {
                return !(*this == _X);
            }
            bool operator>(const_iterator & _X) const
            {
                return _Ptr > _X._Ptr;
            }
            bool operator<(const_iterator & _X) const
            {
                return _Ptr < _X._Ptr;
            }
            bool operator>=(const_iterator & _X) const
            {
                return !(*this<_X);
            }
            bool operator<=(const_reference & _X) const
            {
                return !(*this>_X);
            }
        private:
            _Tptr _Ptr;
        };
        class iterator : public const_iterator
        {
        public:
            iterator(_Tptr _P = NULL):_Ptr(_P) {}
            reference operator*() const
            {
                return *_Ptr;
            }
            _Tptr operator->()
            {
                return &**this;
            }
            iterator & operator++()
            {
                ++_Ptr;
                return *this;
            }
            iterator operator++(int)
            {
                const_iterator _tmp = *this;
                ++*this;
                return _tmp;
            }
            iterator & operator--()
            {
                --_Ptr;
                return *this;
            }
            iterator operator--(int)
            {
                const_iterator _tmp = *this;
                --*this;
                return _tmp;
            }
            iterator operator+(int n)
            {
                const_iterator _tmp = _Ptr += n;
                return _tmp; 
            }
            iterator operator+(iterator & _X)
            {
                const_iterator _tmp = _Ptr + _X._Ptr;
                return _tmp;
            }
            iterator operator-(int n)
            {
                const_iterator _tmp = _Ptr -= n;
                return _tmp;
            }
            iterator operator-(iterator & _X)
            {
                const_iterator _tmp = _Ptr - _X._Ptr;
                return _tmp;
            }
            iterator& operator+=(int n)
            {
                _Ptr += n;
                return *this;
            }
            iterator operator-=(int n)
            {
                _Ptr -= n;
                return *this;
            }
        private:
            _Tptr _Ptr;
        };
    public:
        typedef const_iterator _It;
        explicit vector():_First(NULL), _Last(NULL), _End(NULL) {}
        explicit vector(size_type _N, const _Ty & _V = _Ty())
        {
            _First = _Buynode(_N);
            _Last = _End = _First + _N;
            _Ufill(_First, _N, _V);
        }
        vector(const _Myt & _X)
        {
            size_type _N = _X._Last - _X._First;
            _First = _Buynode(_N);
            _Last = _End = _First + _N;
            _Ucopy(_First, _Last, _X._First);
        }
        vector(_It _F, _It _L)
        {
            size_type _N = _L - _F;
            _First = _Buynode(_N);
            _Last = _End = _First + _N;
            _Ucopy(_First, _Last, _F);
        }
        ~vector()
        {
            _Destory(_First, _Last);
        }
        _Myt & operator=(const _Myt& _X)
        {
            size_type _N = _X._Last - _X._First;
            _First = _Buynode(_N);
            _Last = _End = _First + _N;
            _Ucopy(_First, _Last, _X._First);
        }
        bool empty() const 
        {
            return size() == 0;
        }
        reference operator[](size_type _N)
        {
            return *(_First+_N);
        }
        const_reference operator[](size_type _N) const;
        
        reference front() 
        {
            return *_First;
        }
        const_reference front() const
        {
            return *_First;
        }
        reference back()
        {
            return *(_Last - 1);
        }
        const_reference back() const
        {
            return *(_Last - 1);
        }
        size_type size() const
        {
            return _Last - _First;
        } 
        size_type max_size() const
        {
            return _End - _First;
        }
        iterator begin()
        {
            return _First;
        }
        iterator end()
        {
            return _Last;
        }
        void reserve(size_type _N);
        void push_back() {}
        void assign(_It _F, _It _L);
        void assign(size_type _N, const _Ty & _X = _Ty());
        iterator insert(iterator _P, const _Ty & _X = _Ty())
        {
            iterator _F = _First;
            iterator _L = _Last;
            while (_F != _P)
                ++_F; 
            while (_L != _First)
                *--_L = *_L;
            new(&*_P) _Ty(_X);
            return _P;
        }
        void insert(iterator _P, size_type _N, const _Ty & _X)
        {
            while (_N > 0)
            {
                insert(_P, _X);
                --_N;
            }
        }
        void insert(iterator _P, _It _F, _It _L)
        {
            while (_F != _L)
                insert(_P, *_F++);
        }
        iterator erase(iterator _P)
        {
            iterator _F = _First;
            iterator _L = _Last;
            while (_F != _P)
                ++_F;
            _F->~Ty();
            while (_F != _L)
                *_F = *++_F;
            return _P;
        }
        iterator erase(iterator _F, iterator _L)
        {
            iterator it = _First;
            while (it != _F)
            {
                ++it;
            }
            while (_Last != _F)
            {
                *--_Last = *_F++; 
            }
        }
        void clear()
        {
            erase(_First, _Last);
        }
        bool _Eq(const _Myt & _X) const;
        bool _Lt(const _Myt & _X) const;
        void swap(_Myt & _X);
        friend void swap(_Myt & _X, _Myt & _Y);
        reference at(size_type _N);
        const_reference at(size_type _N) const;
        size_type capacity() const;
        void resize()
        {
            size_type _N = size();
            iterator _tmp = _First;
            _First = _Buynode(2*_N);
        }
    private:
        _Tptr _Buynode(size_type n)
        {
            _Tptr _S = (_Tptr)malloc(sizeof(_Ty)*n);
            return _S;
        }
        void _Destory(iterator _F, iterator _L)
        {
            while (_F != _L)
            {
                _F++->~_Ty();
            }
        }
        iterator _Ucopy(const_iterator _F, const_iterator _L, iterator _P)
        {
            while (_F != _L)
            {
                new(&*_P++) _Ty(*_F++);
            }
            return _P;
        }
        void _Ufill(iterator _F, size_type _N, const _Ty &_X)
        {
            while (0 < _N--)
            {
                new(&*_F++) _Ty(_X);
            }
        }
    protected:
        iterator _First, _Last, _End;
    };
};

#endif
