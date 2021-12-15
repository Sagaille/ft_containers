/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:37:31 by ldavids           #+#    #+#             */
/*   Updated: 2021/12/14 18:12:52 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "../utils/utility.hpp"
#include "../utils/iterator.hpp"
#include "../utils/algorithm.hpp"
#include "tree.hpp"

// map containers keep their keys ordered at all times
// these keys are ordered on a red black tree

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > > // if no given compare class, use the default less compare for the key class
	class map
	{
		////////////////MEMBER TYPES\\\\\\\\\\\\\\\\\\\\/
		public :
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<const Key, T>							value_type;
			typedef size_t										size_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

		private :
			typedef tree<key_type, value_type, key_compare, allocator_type>			tree_type;

		public :
			typedef typename tree_type::value_compare					value_compare;
			typedef typename tree_type::iterator						iterator;
			typedef typename tree_type::const_iterator					const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type	difference_type;


		private :
			key_compare			_key_comp;
			value_compare		_value_comp;
			tree_type			_tree;

		//////////////////MEMBER FUNCTIONS\\\\\\\\\\\\\\\\\\\\/
		public :
			explicit map(const Compare &comp = key_compare(), const Allocator &alloc = Allocator())
			: _key_comp(comp), _value_comp(comp), _tree(comp, alloc)
			{
			}
			template <class InputIt>
			map(InputIt first, InputIt last, const key_compare &comp = key_compare(), const Allocator &alloc = Allocator())
			: _key_comp(comp), _value_comp(comp), _tree(comp, alloc)
			{
				insert(first, last);
			}
			map(const map &src)
			: _key_comp(src._key_comp), _value_comp(src._value_comp), _tree(src._tree)
			{
				insert(src.begin(), src.end());
			}
			~map()
			{
			}
			map&	operator=(const map &src)
			{
				_tree = src._tree;
				return (*this);
			}

			//////////////////Iterators\\\\\\\\\\\\\\\\\\\\\\/
			iterator	begin()
			{
				return (_tree.begin());
			}
			const_iterator	begin() const
			{
				return (_tree.begin());
			}
			iterator	end()
			{
				return (_tree.end());
			}
			const_iterator	end() const
			{
				return (_tree.end());
			}
			reverse_iterator	rbegin()
			{
				return reverse_iterator(end());
			}
			const_reverse_iterator	rbegin() const
			{
				return const_reverse_iterator(end());
			}
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			//////////////////Capacity\\\\\\\\\\\\\\\\\\\\\\/
			bool empty() const
			{
				if (_tree.size() == 0)
					return (1);
				else
					return (0);
			}
			size_type size() const
			{
				return (_tree.size());
			}
			size_type max_size() const
			{
				return (_tree.max_size());
			}

			////////////////Element access\\\\\\\\\\\\\\\\\\\\/
			// if k matches the key of an element in the container, the function returns a reference to its mapped value.
			// If k does not match the key of any element in the container, the function inserts a new element with that key.
			mapped_type		&operator[](const key_type &k)
			{
				return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second);
			}

			///////////////////Modifiers\\\\\\\\\\\\\\\\\\\\\\/
			void clear()
			{
				_tree.clear();
			}
			// if inserts fails (key already used), returns iterator pair with false as sec and position as first
			pair<iterator, bool> insert(const value_type &val)
			{
				return (_tree.insert(val));
			}
			iterator insert(iterator position, const value_type &val)
			{
				return (_tree.insert(position, val));
			}
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					_tree.insert(*first);
					++first;
				}
			}
			void		erase(iterator position)
			{
				_tree.erase(position);
			}
			size_type	erase(const key_type &k)
			{
				return (_tree.erase(k));
			}
			void		erase(iterator first, iterator last)
			{
				_tree.erase(first, last);
			}
			void	swap(map &src)
			{
				_tree.swap(src._tree);
			}

			///////////////////Allocator\\\\\\\\\\\\\\\\\\\\\\/
			allocator_type	get_allocator() const
			{
				return (std::allocator<pair<const Key, T> >());
			}

			///////////////////Operations\\\\\\\\\\\\\\\\\\\\\\/
			size_type	count(const Key &k) const
			{
				return (_tree.count(k));
			}
			iterator find( const Key &k)
			{
				return (_tree.find(k));
			}
			const_iterator find(const Key &k) const
			{
				return (_tree.find(k));
			}

			// Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
			// Because the elements in a map container have unique keys, the range returned will contain a single element at most.
			// First iterator is the lower bound and second is the upper boun.
			ft::pair<iterator,iterator>	equal_range(const Key &k)
			{
				return (_tree.equal_range(k));
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const Key &k) const
			{
				return (_tree.equal_range(k));
			}
			iterator lower_bound(const Key &k) // return first iterator that goes after or is equivalent
			{
				return (_tree.lower_bound(k));
			}
			const_iterator lower_bound(const Key &k) const
			{
				return (_tree.lower_bound(k));
			}
			iterator upper_bound(const Key &k)
			{
				return (_tree.upper_bound(k));
			}
			const_iterator upper_bound(const Key &k) const
			{
				return (_tree.upper_bound(k));
			}

			///////////////////Observers\\\\\\\\\\\\\\\\\\\\\\/
			key_compare key_comp() const
			{
				return (_key_comp);
			}
			value_compare value_comp() const
			{
				return (_value_comp);
			}

			///////////////////Tree_printer\\\\\\\\\\\\\\\\\\\\\\/
		/*private :
			void	print_map()
			{
				_tree.print_tree();
			}
			void	print_map2()
			{
				_tree.print_tree_two();
			}*/
	};
	////////////////NON MEMBER FUNCTIONS\\\\\\\\\\\\\\\\\\\\/
	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key,T,Compare,Alloc> &lhs,
					const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key,T,Compare,Alloc> &lhs,
					const map<Key,T,Compare,Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key,T,Compare,Alloc> &lhs,
					const map<Key,T,Compare,Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key,T,Compare,Alloc> &lhs,
					const map<Key,T,Compare,Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key,T,Compare,Alloc> &lhs,
					const map<Key,T,Compare,Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key,T,Compare,Alloc> &lhs,
					const map<Key,T,Compare,Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc> &x, map<Key,T,Compare,Alloc> &y)
	{
		x.swap(y);
	}
} // namespace ft

#endif
