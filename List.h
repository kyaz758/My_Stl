/******************************************************************************
 ***** File Name : List.h
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2016-11-27 15:53
 * Last Modified : 2016-11-30 20:27
 ******************************************************************************/
#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <malloc.h>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

namespace mylist
{
    template <typename _Ty>
    class list
    {
    protected:
        struct _Node;
        typedef struct _Node * _Nodeptr;
        struct _Node
        {
            _Nodeptr _Prev, _Next; _Ty _Value;
        };
        struct _Acc;
        struct _Acc
        {
            typedef _Node *& _Nodepref;
            typedef _Ty &    _Vref;
            static _Nodepref _Prev(_Nodeptr _P)
            {
                return (*_P)._Prev;
            }
            static _Nodepref _Next(_Nodeptr _P)
            {
                return (*_P)._Next;
            }
            static _Vref _Value(_Nodeptr _P)
            {
                return (*_P)._Value;
            }
        };
    public:
        typedef list<_Ty>       _Myt;
        typedef _Ty             value_type;
        typedef _Ty *           _Tptr;
        typedef const _Ty *     _Ctptr;
        typedef _Ty &           reference;
        typedef const _Ty &     const_reference;
        typedef int             difference_type;
        typedef unsigned int    size_type;
    public:
        class const_iterator;
        class iterator;
        class const_iterator
        {
        public:
            const_iterator(_Nodeptr _P = NULL):_Ptr(_P) {}
            const_reference operator*() const
            {
                return _Acc::_Value(_Ptr);
            }
            _Ctptr operator->()
            {
                return &**this;
            }
            const_iterator & operator++()
            {
                _Ptr = _Acc::_Next(_Ptr);
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
                _Ptr = _Acc::_Prev(_Ptr);
                return *this;
            }
            const_iterator operator--(int)
            {
                const_iterator _tmp = *this;
                --*this;
                return _tmp;
            }
            bool operator==(const_iterator &_X)
            {
                return _Ptr == _X._Ptr;
            }
            bool operator!=(const_iterator &_X)
            {
                return !(*this == _X);
            }
            _Nodeptr _MyNode() const
            {
                return _Ptr;
            }
        protected:
            _Nodeptr _Ptr;
        };
        class iterator : public const_iterator
        {
        public:
            iterator(_Nodeptr _P = NULL):const_iterator(_P), _Ptr(_P) {}
            reference operator*() const 
            {
                return _Acc::_Value(_Ptr);
            }
            _Tptr operator->() const 
            {
                return &**this;
            }
            iterator & operator++()
            {
                _Ptr = _Acc::_Next(_Ptr);
                return *this;
            }
            iterator operator++(int)
            {
                iterator _tmp = *this;
                ++*this;
                return _tmp;
            }
            iterator & operator--()
            {
                _Ptr = _Acc::_Prev(_Ptr);
                return *this;
            }
            iterator operator--(int)
            {
                iterator _tmp = *this;
                --*this;
                return _tmp;
            }
            bool operator==(const iterator &_X)
            {
                return _Ptr == _X._Ptr;
            }
            bool operator!=(const iterator &_X)
            {
                return !(*this == _X);
            }
            _Nodeptr _MyNode() const
            {
                return _Ptr;
            }
        private:
            _Nodeptr _Ptr;
        };
    public:
	    list():_Size(0)
        {
            _Head = _Create_Node(0);
        }
        list(const list<_Ty>& _X)
        {
            _Head = _Create_Node(0);
            iterator mit = begin();
            iterator yit = _X.begin();
            while (yit != _X.end())
            {
                insert(mit, *yit);
            }
        }
        list<_Ty> & operator=(const list<_Ty>& _X)
        {
            _Head = _Create_Node(0);
            iterator mit = begin();
            iterator yit = _X.begin();
            while (yit != _X.end())
            {
                insert(mit, *yit);
            }
        }
        ~list()
        {
             while(_Size != 0)
            {
	           pop_back();
	        }
	        _Destory_Node(_Head);
        }
        iterator begin()
        {
            iterator it = _Head->_Next;//_Acc::_Next(_Head);
            return it;//_Acc::_Next(_Head);
        }
        iterator end()
        {
        	return _Head;
        }
        const_iterator begin() const
        {
            const_iterator cit = _Head;
            return cit;
        }
        const_iterator end() const
        {
            return _Head;
        }
        void resize(size_type _N, const _Ty& _X=_Ty())
        {
            if (_Size < _N)
            {
                iterator it = begin();
                for (int i=0; i<_N; ++i)
                {
                    ++it;
                }
                while(it != end())
                {
                    erase(it);
                }
            }
            else
            {
                iterator it = end();
                for (int i=_N-_Size; i<_N; ++i)
                {
                    insert(it, _X);
                }
            }
        }
        size_type size() const
        {
            return _Size;
        }
        bool empty() const
        {
            return _Size == 0;
        }
        iterator front()
        {
            return begin();
        }
        const_iterator front() const
        {
            return begin();
        }
        iterator back()
        {
            iterator it = end();
            return --it;
        }
        const_iterator back() const
        {
            iterator it = end();
            return --it;
        }
        void push_front(const _Ty& _X)
        {
            insert(begin(), _X);
        }
        void push_back(const _Ty& _X)
        {
            insert(end(), _X);
        }
        void pop_front()
        {
            erase(begin());
        }
        void pop_back()
        {
	        iterator _tmp = end();
            erase(--_tmp);
        }
        
        iterator insert(iterator _P, const _Ty & _X)
        {
            _Nodeptr _tmp = _Create_Node(_X);
            _Acc::_Next(_tmp) = _P._MyNode();
	        _Acc::_Prev(_tmp) = _Acc::_Prev(_P._MyNode());
	        _Acc::_Next(_Acc::_Prev(_P._MyNode())) = _tmp;
	        _Acc::_Prev(_P._MyNode()) = _tmp;
            ++_Size;
            return _tmp;
        }
        iterator erase(iterator _P)
        {
            _Nodeptr _next = _Acc::_Next(_P._MyNode());
            _Nodeptr _prev = _Acc::_Prev(_P._MyNode());
            _Acc::_Next(_prev) = _next;
            _Acc::_Prev(_next) = _prev;
            _Destory_Node(_P._MyNode());
            --_Size;
            return iterator(_next);
        }
        void clear()
        {
            _Nodeptr _P = _Head;
            while(_P != NULL)
            {
                _Nodeptr _tmp = _P;
                _P = _Acc::_Next(_P);
                _Destory_Node(_tmp);
            }
        }
        void swap(const list<_Ty>& _X)
        {
            _Nodeptr _tmp = _Head;
            size_type tmp = _Size;
            _Head = _X._Head;
            _Size = _X._Size;
            _X._Head = _tmp;
            _X._Size = tmp;
        }
        void unique()
        {
            iterator first = begin();
            iterator last = end();
            if (first == last)
                return ;
            iterator next = first;
            while (++next != last)
            {
                if (*first == *next)
                    erase(next);
                else
                    first = next;
                next = first;
            }
        }
        void reverse()
        {
            if (_Size == 0 || _Size == 1)
                return ;
            iterator first = begin();
            iterator last = end();
            while (first++ != --last)
            {
                iterator tmp = first;
                first = last;
                last = tmp;
            }
        }
    private:
        _Nodeptr _Head;
        size_type _Size;
        _Nodeptr _Create_Node(const _Ty& _X)
        {
            _Nodeptr _S = (_Nodeptr)malloc(sizeof(_Node));
            if (NULL == _S) exit(0);
            memset(_S, 0, sizeof(_Node));
	        _Acc::_Next(_S) = _Acc::_Prev(_S) = _S;
            //_Acc::_Value(_S) = _X;
            new(&_Acc::_Value(_S)) _Ty(_X);
            return _S;
        }
        void _Destory_Node(_Nodeptr _P)
        {
            free(_P);
         	//_P = NULL;
        }
    };
}
#endif /* ifndef LIST_H */
