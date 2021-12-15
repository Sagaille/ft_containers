/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:37:53 by ldavids           #+#    #+#             */
/*   Updated: 2021/12/14 22:12:17 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "../utils/iterator_traits.hpp"
#include <iterator>

namespace	ft
{
	template <class T>
	class random_access_iterator : public std::iterator<std::random_access_iterator_tag, T>
	// https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
	{
		public :
			typedef T												type;
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;

		private :
			type					_ptr;

		public :
		/////////////////////CANONICAL FORM////////////////////////
									random_access_iterator() : _ptr(NULL)
									{
									}
									explicit random_access_iterator(type ptr) : _ptr(ptr)
									{
									}
									template <class Iter>	//template class so we can build const iterators
									random_access_iterator(const random_access_iterator<Iter> &src)
									{
										*this = src;
									}
			template <class Iter>		//template class so we can assign const iterators
			random_access_iterator	&operator=(const random_access_iterator<Iter> &src)
			{
				_ptr = src.base();
				return (*this);
			}
			type	base() const
			{
				return _ptr;
			}
			/////////////////////PROPERTY////////////////////////
			// dereference operator
			reference				operator*() const
			{
				return (*_ptr);
			}
			pointer					operator->() const
			{
				return (_ptr);
			}
			reference				&operator[](difference_type n) const
			{
				return *(_ptr + n);
			}
			// pre-post inc/decrement
			random_access_iterator			&operator++()
			{
				_ptr++;
				return (*this);
			}
			random_access_iterator			operator++(int)
			{
				random_access_iterator	temp(*this);
				_ptr++;
				return (temp);
			}
			random_access_iterator			&operator--()
			{
				_ptr--;
				return (*this);
			}
			random_access_iterator			operator--(int)
			{
				random_access_iterator	temp(*this);
				_ptr--;
				return (temp);
			}
			// arithmetic op
			random_access_iterator			operator+(difference_type n) const
			{
				return (random_access_iterator(_ptr + n));
			}
			random_access_iterator			operator-(difference_type n) const
			{
				return (random_access_iterator(_ptr - n));
			}
			random_access_iterator			&operator+=(difference_type n)
			{
				_ptr += n;
				return (*this);
			}
			random_access_iterator			&operator-=(difference_type n)
			{
				_ptr -= n;
				return (*this);
			}
	};

	// NON-MEMBER (necessary to use some external functions)

	template <class Iterator1, class Iterator2>
	bool operator==(const random_access_iterator<Iterator1> &lhs, const random_access_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!=(const random_access_iterator<Iterator1> &lhs, const random_access_iterator<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator<(const random_access_iterator<Iterator1> &lhs, const random_access_iterator<Iterator2> &rhs)
	{
	return (lhs.base() < rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator<=(const random_access_iterator<Iterator1> &lhs, const random_access_iterator<Iterator2> &rhs)
	{
	return (lhs.base() <= rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>(const random_access_iterator<Iterator1> &lhs, const random_access_iterator<Iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>=(const random_access_iterator<Iterator1> &lhs, const random_access_iterator<Iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	random_access_iterator<Iterator> operator+(typename
		random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator> &it)
	{
		return (random_access_iterator<Iterator>(it.base() + n));
	}
	template <class Iterator1, class Iterator2>
	typename random_access_iterator<Iterator1>::difference_type
	operator-(const random_access_iterator<Iterator1> &lhs, const random_access_iterator<Iterator2> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif
