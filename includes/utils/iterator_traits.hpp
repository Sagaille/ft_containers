/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:02:42 by ldavids           #+#    #+#             */
/*   Updated: 2021/11/25 23:02:28 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		ITERATOR_TRAITS_HPP
#define		ITERATOR_TRAITS_HPP

#include <iterator>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <algorithm>

namespace	ft
{
	// check this = https://www.lix.polytechnique.fr/~liberti/public/computing/prog/libstdc++/iterator_traits.html

	//generic template struct
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category		iterator_category;
		typedef typename Iterator::value_type				value_type;
		typedef typename Iterator::difference_type			difference_type;
		typedef typename Iterator::pointer					pointer;
		typedef typename Iterator::reference				reference;
	};

	// This template struc is done for ordinary pointers that also can be used as iterators
	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef ptrdiff_t							difference_type;
		typedef T									*pointer;
		typedef T									&reference;
	};

	// https://www.oreilly.com/library/view/c-in-a/059600298X/re675.html
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef ptrdiff_t							difference_type;
		typedef const T								*pointer;
		typedef const T								&reference;
	};

	// IS_INTEGRAL
	// see https://www.sandordargo.com/blog/2021/04/07/what-are-type-traits for the best implementation tuto
	///

	// first remove_cv template to remove the const or volatile
	// NB : The volatile keyword is intended to prevent the compiler
	// from applying any optimizations on objects that can change in ways that cannot be determined by the compiler.
	template <class T>
	struct remove_cv
	{
		typedef T type;
	};

	template <class T>
	struct remove_cv<const T>
	{
		typedef T type;
	};

	template <class T>
	struct remove_cv<volatile T>
	{
		typedef T type;
	};

	template <class T>
	struct remove_cv<const volatile T>
	{
		typedef T type;
	};


	template<class Tp, Tp v>
	struct integral_constant
	{
		enum									{ value = v };
		typedef Tp								value_type;
		typedef integral_constant<Tp, v>		type;
		operator value_type() const
		{
			return value;
		}
		value_type operator()()
		{
			return value;
		}
	};

	//So true_type is an integral_constant where type is bool and value is true.
	typedef integral_constant<bool, true>		true_type;
	typedef integral_constant<bool, false>		false_type;

	template<class Tp>
	struct _is_integral_helper : public false_type
	{
	};
	template<>
	struct _is_integral_helper<bool> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<char> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<signed char> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<unsigned char> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<wchar_t> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<short> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<unsigned short> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<int> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<unsigned int> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<long> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<unsigned long> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<long long> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<unsigned long long> : public true_type
	{
	};

	// is_integral class inherits from the false or true type, wich is an integral constant
	template<class Tp>
	struct is_integral : public _is_integral_helper<typename remove_cv<Tp>::type>::type
	{
	};
}

#endif
