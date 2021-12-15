/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:17:40 by ldavids           #+#    #+#             */
/*   Updated: 2021/12/15 13:22:21 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "type_traits.hpp"
#include "iterator_traits.hpp"
#include <iterator>

namespace ft
{
	template <class T>
	class reverse_iterator : public std::iterator<typename std::iterator_traits<T>::iterator_category,   //check iterator category
												 typename std::iterator_traits<T>::value_type,
												 typename std::iterator_traits<T>::difference_type,
												 typename std::iterator_traits<T>::pointer,
												 typename std::iterator_traits<T>::reference>
	{
		public :
			typedef T													type;
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;
		protected :
																type	_ptr;
		public :
			/////////////////////CONSTRUCTOR\\\\\\\\\\\\\\\\\\\\\\/
			reverse_iterator() : _ptr()
			{
			}
			explicit reverse_iterator(type x) : _ptr(x)
			{
			}
			template<class U>
			reverse_iterator(const reverse_iterator<U> &other)
			{
				_ptr = other.base();
			}
			/////////////////////MEMBER\\\\\\\\\\\\\\\\\\\\\\/
			template<class U>
			reverse_iterator &operator=(const reverse_iterator<U> &other)
			{
				_ptr = other.base();
				return (*this);
			}
			type base() const
			{
				return _ptr;
			}
			reference operator*() const
			{
				type	tmp = _ptr;
				return *(--tmp);
			}
			pointer operator->() const
			{
				return (&(operator*()));
			}
			reference operator[](difference_type n) const
			{
				return (base()[-n-1]);
			}
			reverse_iterator &operator++()
			{
				--_ptr;
				return (*this);
			}
			reverse_iterator &operator--()
			{
				++_ptr;
				return (*this);
			}
			reverse_iterator operator++( int )
			{
				reverse_iterator	tmp = *this;
				--_ptr;
				return (tmp);
			}
			reverse_iterator operator--( int )
			{
				reverse_iterator	tmp = *this;
				++_ptr;
				return (tmp);
			}
			reverse_iterator operator+( difference_type n ) const
			{
				/*reverse_iterator	tmp = *this;
				tmp._ptr += n;*/
				return (reverse_iterator(base() - n));
			}
			reverse_iterator operator-( difference_type n ) const
			{
				reverse_iterator	tmp = *this;
				tmp._ptr -= n;
				return (tmp);
			}
			reverse_iterator& operator+=( difference_type n )
			{
				_ptr -= n;
				return (*this);
			}
			reverse_iterator& operator-=( difference_type n )
			{
				_ptr += n;
				return (*this);
			}
	};
	/////////////////////NON_MEMBER\\\\\\\\\\\\\\\\\\\\\\/
	template<class Iterator1, class Iterator2>
	bool operator==( const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator!=( const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() < lhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() > lhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() <= lhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() >= lhs.base());
	}
	template<class Iter>
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &it)
	{
		return (reverse_iterator<Iter>(it.base() - n));
	}
	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> &lhs,
																	 const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs )
	{
		return (rhs.base() - lhs.base());
	}
} // namespace ft

#endif
