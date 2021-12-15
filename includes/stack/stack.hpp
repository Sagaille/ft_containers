/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:42:49 by ldavids           #+#    #+#             */
/*   Updated: 2021/12/14 22:03:39 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

// LIFO
// https://www.softwaretestinghelp.com/stack-in-cpp/
// Uses of Stack :
//		-Infix To Postfix Expressions
//		-Expression Parsing/Evaluation
//		-Tree Traversals
//		-Sorting Algorithms (like quicksort)
//		-Towers Of Hanoi

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		////////////////MEMBER TYPES\\\\\\\\\\\\\\\\\\\\/
		public :
			typedef T				value_type;
			typedef Container		container_type;
			typedef size_t			size_type;

		//////////////////ATTRIBUTES\\\\\\\\\\\\\\\\\\\\\/
		protected :
			Container				c;

		////////////////MEMBER FUNCTIONS\\\\\\\\\\\\\\\\\\\\/
		public :
			explicit stack (const container_type& ctnr = container_type())
			 : c(ctnr)
			{
			}
			bool	empty() const
			{
				return (c.empty());
			}
			size_type	size() const
			{
				return (c.size());
			}
			value_type	&top()
			{
				return (c.back());
			}
			const value_type	&top() const
			{
				return (c.back());
			}
			void push(const value_type &val)
			{
				c.push_back(val);
			}
			void pop()
			{
				c.pop_back();
			}

			////////////////NON MEMBER FUNCTIONS\\\\\\\\\\\\\\\\\\\\/
			// friend so we can use the operators from the underlying containers

			friend bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs.c == rhs.c);
			}
			friend bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs.c != rhs.c);
			}
			friend bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs.c < rhs.c);
			}
			friend bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs.c <= rhs.c);
			}
			friend bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs.c > rhs.c);
			}
			friend bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs.c >= rhs.c);
			}
	};
} // namespace ft

#endif
