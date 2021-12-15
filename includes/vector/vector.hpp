/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:45:01 by ldavids           #+#    #+#             */
/*   Updated: 2021/12/15 13:59:10 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../utils/iterator_traits.hpp"
#include "random_access_iterator.hpp"
#include "../utils/type_traits.hpp"
#include "../utils/algorithm.hpp"
#include "../utils/iterator.hpp"
#include "../utils/utility.hpp"

#include <iostream>
#include <exception>
#include <memory>
#include <limits>
#include <algorithm>
#include <iterator>

namespace ft
{
	template <class T, class A = std::allocator<T> >
	class vector
	{
		////////////////MEMBER TYPES\\\\\\\\\\\\\\\\\\\\/
		public :
			typedef	T 													value_type;
			typedef A													allocator_type;
			// https://www.cplusplus.com/reference/memory/allocator_traits/
			// use of allocator_type typedef to ensure we use the correct definition defined by allocator
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef	ft::random_access_iterator<pointer>							iterator;
			typedef	ft::random_access_iterator<const_pointer>					const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type	difference_type;
			typedef	size_t												size_type;

		//////////////////ATTRIBUTES\\\\\\\\\\\\\\\\\\\\\/
		private :
			allocator_type						_allocator;
			pointer								_capacity_last;
			pointer								_first;
			pointer								_last;

		public :
		////////////////CONSTUCTOR\\\\\\\\\\\\\\\\\\\\/
		explicit vector(const allocator_type &alloc = allocator_type())
		 : _allocator(alloc), _capacity_last(NULL), _first(NULL), _last(NULL)
		{
		}
		explicit vector(size_type n, const_reference val = value_type(), const allocator_type &alloc = allocator_type())
		 : _allocator(alloc), _capacity_last(NULL), _first(NULL), _last(NULL)
		{
			if (n > 0)
			{
				_first = _allocator.allocate(n);
				_last = _first + n;
				_capacity_last = _last;
				std::uninitialized_fill_n(_first, n, val);
			}
		}
		template<class InputIt>
		vector(InputIt first,
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last,
			 const allocator_type &alloc = allocator_type())
		 : _allocator(alloc), _capacity_last(NULL), _first(NULL), _last(NULL)
		{
			size_type	range = std::distance(first, last);
			_first = _allocator.allocate(range);
			_last = _first + range;
			_capacity_last = _last;
			std::uninitialized_copy(first, last, _first);
		}
		vector(const vector &src)
		 : _allocator(src._allocator), _capacity_last(NULL), _first(NULL), _last(NULL)
		{
			size_type range = src.size();
			if (range > 0)
			{
				_first = _allocator.allocate(range);
				_last = _first + range;
				_capacity_last = _last;
				std::uninitialized_copy(src._first, src._last, _first);
			}
		}
		vector					&operator=(const vector &src)
		{
			assign(src._first, src._last);
			return (*this);
		}
		////////////////DESTRUCTOR\\\\\\\\\\\\\\\\\\\\/
		~vector()
		{
			clear();
			_allocator.deallocate(_first, capacity());
		};
		////////////////ITERATORS\\\\\\\\\\\\\\\\\\\\/
		iterator				begin()
		{
			return (iterator(_first));
		}
		const_iterator			begin() const
		{
			return (const_iterator(_first));
		}
		iterator				end()
		{
			return (iterator(_last));
		}
		const_iterator			end() const
		{
			return (const_iterator(_last));
		}
		reverse_iterator		rbegin()
		{
			return (reverse_iterator(end()));
		}
		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(end()));
		}
		reverse_iterator		rend()
		{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(begin()));
		}
		////////////////CAPACITY\\\\\\\\\\\\\\\\\\\\/
		size_type			size() const
		{
			return (_last - _first);
		}
		size_type			max_size() const
		{
			return (std::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()), _allocator.max_size()));
		}
		void				resize (size_type n, value_type val = value_type())
		{
			while (n < size())
				pop_back();
			if (n > size())
				insert(end(), n - size(), val);
		}
		size_type			capacity() const
		{
			return (_capacity_last - _first);
		}
		bool				empty() const
		{
			if (begin() == end())
				return (1);
			return (0);
		}
		void				reserve (size_type n)
		{
			if (n > max_size())
				throw std::length_error("size requested is greater than the maximum size (vector::max_size)\n");
			if (n > capacity())
			{
				size_type		old_cap = capacity();
				size_type		old_size = size();
				pointer			new_first = _allocator.allocate(n);

				std::uninitialized_copy(_first, _last, new_first);
				clear();
				_allocator.deallocate(_first, old_cap);
				_first = new_first;
				_last = _first + old_size;
				_capacity_last = _first + n;
			}
		}
		/////////////ELEMENT ACCESS\\\\\\\\\\\\\\\\\/
		reference 			operator[](size_type n)
		{
			return (_first[n]);
		}
		const_reference		operator[](size_type n) const
		{
			return (_first[n]);
		}
		reference			at(size_type n)
		{
			if (n >= size() || n < 0)
				throw std::out_of_range("Accessing out of range element in vector\n");
			else
				return (_first[n]);
		}
		const_reference		at(size_type n) const
		{
			if (n >= size() || n < 0)
				throw std::out_of_range("Accessing out of range element in vector\n");
			else
				return (_first[n]);
		}
		reference			front()
		{
			return (_first[0]);
		}
		const_reference		front() const
		{
			return (_first[0]);
		}
		reference			back()
		{
			return (_first[size() - 1]);
		}
		const_reference		back() const
		{
			return (_first[size() - 1]);
		}
		///////////////MODIFIERS\\\\\\\\\\\\\\\\\\/
		// If a reallocation happens,the storage needed is allocated using the internal allocator.
		// Any elements held in the container before the call are destroyed and replaced by newly constructed elements (no assignments of elements take place).
		// This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.

		template <class InputIterator>
		void				assign(InputIterator first, typename ft::enable_if<
						!ft::is_integral<InputIterator>::value, InputIterator>::type last)
		{
			size_type new_size = std::distance(first, last);
			if (new_size > capacity())
			{
				clear();
				reserve(new_size);
				std::uninitialized_copy(first, last, _first);
			}
			else
			{
				pointer now = _last;
				if (_first != _last)
				{
					while (now != _first + new_size)
						_allocator.destroy(--now);
				}
				std::copy(first, last, _first);
			}
			_last = _first + new_size;
		}
		void				assign(size_type n, const value_type &val)
		{
			if (n > capacity())
			{
				clear();
				reserve(n);
				std::uninitialized_fill_n(_first, n, val);
			}
			else
			{
				pointer now = _last;
				if (_first != _last)
				{
					while (now != (_first + n))
						_allocator.destroy(--now);
				}
				std::fill_n(_first, n, val);
			}
			_last = _first + n;
		}
		void				push_back(const value_type& val)
		{
			size_type new_size = size() + 1;
			if (new_size > capacity())
				reserve(new_capacity(new_size));
			_allocator.construct(_last, val);
			++_last;
		}
		void				pop_back()
		{
			pointer		temp = _last;

			if (size() > 0)
			{
				_last--;
				_allocator.destroy(temp);
			}
		}
		// INSERT
		// dixit cppreference "Causes reallocation if the new size() is greater than the old capacity().
		// If the new size() is greater than capacity(), all iterators and references are invalidated.
		// Otherwise, only the iterators and references before the insertion point remain valid.
		// The past-the-end iterator is also invalidated."
		iterator			insert(iterator position, const value_type &val)
		{
			size_type	diff = position - begin();
			insert(position, 1, val);
			return (begin()) + diff;
		}
		void				insert(iterator position, size_type n, const value_type &val)
		{
			size_type	new_size = size() + n;
			size_type	diff = position - begin();

			if (new_size > capacity())
			{
				if (new_size > max_size())
					throw std::exception();
				new_size = new_capacity(new_size);
				size_type	old_capa = capacity();
				size_type	old_size = size();
				pointer		new_first = _allocator.allocate(new_size);
				std::uninitialized_copy(begin(), position, new_first);
				std::uninitialized_fill_n(new_first + diff, n, val);
				std::uninitialized_copy(position, end(), new_first + diff + n);
				clear();
				_allocator.deallocate(_first, old_capa);
				_first = new_first;
				_last = _first + old_size + n;
				_capacity_last = _first + new_size;
			}
			else
			{
				move_range(diff, n);
				size_t		i = 0;
				while (i < n)
				{
					if (diff + i >= size())
						_allocator.construct(&_first[diff + i], val);
					else
						_first[diff + i] = val;
					i++;
				}
				_last += n;
			}
		}
		template <class InputIterator>
		void				insert(iterator position, InputIterator first_it, typename ft::enable_if<
							!ft::is_integral<InputIterator>::value, InputIterator>::type last_it)
		{
			size_type	range = std::distance(first_it, last_it);
			size_type	new_size = size() + range;
			size_type	diff = position - begin();
			if (new_size > capacity())
			{
				new_size = new_capacity(new_size);
				size_type	old_capa = capacity();
				size_type	old_size = size();
				pointer		new_first = _allocator.allocate(new_size);
				std::uninitialized_copy(begin(), position, new_first);
				std::uninitialized_copy(first_it, last_it, new_first + diff);
				std::uninitialized_copy(position, end(), new_first + diff + range);
				clear();
				_allocator.deallocate(_first, old_capa);
				_first = new_first;
				_last = _first + old_size + range;
				_capacity_last = _first + new_size;
			}
			else
			{
				size_t		i = 0;
				move_range(diff, range);
				while (i < range)
				{
					if (diff + i >= size())
						_allocator.construct(_first + diff + i, *first_it);
					else
						_first[diff + i] = *first_it;
					++i;
					++first_it;
				}
				_last += range;
			}
		}
		iterator			erase(iterator position)
		{
			return (erase(position, position + 1));
		}
		iterator			erase(iterator first_it, iterator last_it)
		{
			difference_type		range = std::distance(first_it, last_it);
			iterator		temp = first_it;
			while (temp + range != end())
			{
				*temp = *(temp + range);
				temp++;
			}
			pointer			old_last = _last;
			_last -= range;
			while (old_last != _last)
			{
				_allocator.destroy(old_last);
				old_last--;
			}
			return (first_it);
		}

		void				clear()
		{
			pointer	temp = _first;
			while (temp != _last)
			{
				_allocator.destroy(temp);
				++temp;
			}
			_last = _first;
		}
		void				swap(vector &x)
		{
			pointer		temp_first = _first;
			pointer		temp_last = _last;
			pointer		temp_capa = _capacity_last;

			_first = x._first;
			_last = x._last;
			_capacity_last = x._capacity_last;

			x._first = temp_first;
			x._last = temp_last;
			x._capacity_last = temp_capa;
		}
		allocator_type		get_allocator() const
		{
			return (_allocator);
		}
	private :
		size_type new_capacity(size_type new_cap)
		{
			size_type max_cap = max_size();
			if (new_cap > max_cap)
				throw std::exception();
			size_type cap = capacity();
			if (cap >= max_cap / 2)
				return max_cap;
			return std::max(cap * 2, new_cap);
		}
		void move_range(size_type diff, size_type count)
		{
			size_type now_size = size();
			size_type new_size = now_size + count;

			for (size_t i = 0; i < now_size - diff; i++)
			{
				if (new_size - i > now_size)
					_allocator.construct(&_first[new_size - i - 1], _first[now_size - i - 1]);
				else
					_first[new_size - i - 1] = _first[now_size - i - 1];
			}
		}
	};
	///////////////NON MEMBER\\\\\\\\\\\\\\\\\\/
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		size_t	i = 0;
		while (i < lhs.size())
		{
			if (lhs[i] != rhs[i])
				return (false);
			i++;
		}
		return (true);
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}
	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}; // namespace ft

#endif
