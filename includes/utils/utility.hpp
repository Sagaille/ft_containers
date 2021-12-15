/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:31:33 by ldavids           #+#    #+#             */
/*   Updated: 2021/12/10 15:41:39 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "algorithm.hpp"

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		/////////////////////MEMBER\\\\\\\\\\\\\\\\\\\\\\/
		pair() : first(), second()
		{
		}
		pair(const first_type &x, const second_type &y) : first(x), second(y)
		{
		}
		template<class U1, class U2>
		pair(const pair<U1, U2> &p) : first(p.first), second(p.second)
		{
		}
		virtual ~pair()
		{
		}
		pair &operator=(const pair& other)
		{
			first = other.first;
			second = other.second;
			return (*this);
		}
	};
	/////////////////////NON_MEMBER\\\\\\\\\\\\\\\\\\\\\\/
	template<class T1, class T2>
	pair<T1,T2> make_pair(T1 t, T2 u)
	{
		return (pair<T1, T2>(t, u));
	}
	template<class T1, class T2>
	bool operator==(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template<class T1, class T2>
	bool operator!=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (!(lhs == rhs));
	}
	template<class T1, class T2>
	bool operator<(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		if (lhs.first < rhs.first)
			return (true);
		if (rhs.first < lhs.first)
			return (false);
		if (lhs.second < rhs.second)
			return (true);
		return (false);
	}
	template<class T1, class T2>
	bool operator>(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (rhs < lhs);
	}
	template<class T1, class T2>
	bool operator<=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (!(rhs < lhs));
	}
	template<class T1, class T2>
	bool operator>=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
