/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:51:20 by ldavids           #+#    #+#             */
/*   Updated: 2021/12/15 13:53:11 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "../utils/iterator.hpp"
#include "../utils/utility.hpp"
#include <stdlib.h>
#include <stdexcept>
#include <limits>

namespace ft
{
	template <class T>
	class node
	{
		public :
			node		*parent;
			node		*left;
			node		*right;
			bool		color;
			T			value;

			static const bool		Black = 1;
			static const bool		Red = 0;

			node()
			: parent(NULL), left(NULL), right(NULL), color(Black)
			{
			}
			node(node *nil, const T &value)
			: parent(nil), left(nil), right(nil), color(Red), value(value)
			{
			}
	};

	template <class T>
	class node_tools
	{
		public :
			node<T>		*search_min(node<T> *no, node<T> *nil) const
			{
				while (no->left != nil)
				{
					no = no->left;
				}
				return (no);
			}
			node<T>		*search_max(node<T> *no, node<T> *nil) const
			{
				while (no->right != nil)
				{
					no = no->right;
				}
				return (no);
			}
			bool	is_left_child(node<T> *no) const
			{
				return (no == no->parent->left);
			}
			bool	is_right_child(node<T> *no) const
			{
				return (no == no->parent->right);
			}
			// ref : https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/
			// If right subtree of node is not NULL, then succ lies in right subtree.
			// Go to right subtree and return the node with minimum key value in the right subtree.
			// Else, then next is one of the ancestors. Do the following.
			// Travel up using the parent pointer until you see a node which is left child of its parent.
			// CAN RETURN THE END NODE WITH HIGHEST KEY AS ARG (because _end is root->parent)
			node<T>		*next_node(node<T> *no, node<T> *nil) const
			{
				if (no->right != nil)
				{
					return (search_min(no->right, nil));
				}
				while (!is_left_child(no))
					no = no->parent;
				return (no->parent);
			}
			// CAN RETURN THE HIGHEST KEY WITH END NODE AS ARG (because _end is root->parent)
			node<T>		*prev_node(node<T> *no, node<T> *nil) const
			{
				if (no->left != nil)
				{
					return (search_max(no->left, nil));
				}
				while (!is_right_child(no))
					no = no->parent;
				return (no->parent);
			}
	};

	template <class T> //class T is pair<key, mapped>
	class tree_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
		public :
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;

		private :
			typedef node<value_type>								*node_type;		// is the pointer to the class node<pair<key, mapped>> which are linked

		private :
			node_type					_current;		// get access to the key or mapped through (&current_->value)->first or (&current_->value)->second !! usefull for _comp
			node_type					_nil;
			node_tools<value_type>		_tools;

		public :
			tree_iterator()
			: _current(NULL)
			{
			}
			explicit tree_iterator(node_type ptr, node_type nil)  // _nil as arg so we can keep track of the endpoint pointer
			: _current(ptr), _nil(nil)
			{
			}
			template <class Iter>
			tree_iterator(const tree_iterator<Iter> &src)
			{
				*this = src;
			}
			template <class Iter>
			tree_iterator		&operator=(const tree_iterator<Iter> &src)
			{
				if (*this == src)
					return (*this);
				_current = src.getBase();
				_nil = src.get_nil();
				return (*this);
			}

			reference	operator*() const
			{
				return (_current->value);
			}
			pointer		operator->() const
			{
				return (&_current->value);
			}
			tree_iterator		&operator++()
			{
				_current = _tools.next_node(_current, _nil);
				return (*this);
			}
			tree_iterator		operator++(int)
			{
				tree_iterator		tmp(*this);
				++(*this);
				return (tmp);
			}
			tree_iterator		&operator--()
			{
				_current = _tools.prev_node(_current, _nil);
				return (*this);
			}
			tree_iterator		operator--(int)
			{
				tree_iterator		tmp(*this);
				--(*this);
				return (tmp);
			}
			node_type		get_current() const
			{
				return (_current);
			}
			node_type		get_nil() const
			{
				return (_nil);
			}
			node_type		getBase() const
			{
				return (_current);
			}
	};
	// Non-member functions
	// Relational Operators: Bidirectional iterators can be used with equality operator (==),
	// but it can not be used with other relational operators like <=.
	// https://www.geeksforgeeks.org/bidirectional-iterators-in-cpp/
	template <class It1, class It2>
	bool	operator==(const ft::tree_iterator<It1> &lhs, const ft::tree_iterator<It2> &rhs)
	{
		return (lhs.get_current() == rhs.get_current());
	}
	template <class It1, class It2>
	bool	operator!=(const ft::tree_iterator<It1> &lhs, const ft::tree_iterator<It2> &rhs)
	{
		return (lhs.get_current() != rhs.get_current());
	}

	template <class Key, class T, class Compare, class Allocator = std::allocator<T> >
	class tree
	{
		public :
			typedef tree_iterator<T *>					iterator;
			typedef tree_iterator<const T *>			const_iterator;

		private :
			typedef Key															key_type;
			typedef T															value_type;  // pair<key, mapped> ----> std::cout << val.first shows the key
			typedef node<T>														*node_type;
			typedef const node<T>												*const_node_type;
			typedef typename Allocator::size_type								size_type;
			typedef	Compare														key_compare;

			//  had to rebind the allocator to the node class to alloc and construct nodes.
			typedef typename Allocator::template rebind<node<T> >::other		node_allocator_type;
			typedef typename node_allocator_type::difference_type				difference_type;

		private :
			node_type			_begin;  //first sorted key
			node_type			_end;   //post last key iterator, linked to root (end->left is root)
			node_type			_nil;  //leafs (like the \0 in a string == endpoint)
			key_compare			_compare;
			size_type			_size;
			node_tools<T>		_tools;
			node_allocator_type	_alloc;

		public:

		class value_compare : public std::binary_function<value_type, value_type, bool>  // in C++98, it is required to inherit
		{
			// https://www.cplusplus.com/reference/map/map/value_comp/
			// Returns a comparison object that can be used to compare two pairs to get
			// whether the key of the first one goes before the second. The mapped value is not relevant.
			class tree;
			private:
				key_compare comp;
			public:
				value_compare() : comp() {}
				value_compare(const key_compare &x) : comp(x) {}
				bool operator()(const value_type &x, const value_type &y) const
				{
					return comp(x.first, y.first);
				}
		};

		public :
			tree(const key_compare &compare = key_compare(), const Allocator &alloc = Allocator())
			: _compare(compare), _size(0), _alloc(node_allocator_type(alloc))
			{
				init();
			}
			tree(const tree &src)
			: _compare(src._compare), _size(0), _alloc(src._alloc)
			{
				init();
			}
			~tree()
			{
				destroy(get_root());
				delete_node(_nil);
				delete_node(_end);
			}
			tree		&operator=(const tree &src)
			{
				clear();
				_compare = src._compare;
				iterator	it1 = src.begin();
				iterator	it2 = src.end();
				while (it1 != it2)
				{
					insert(*it1);
					++it1;
				}
				return (*this);
			}
			iterator	begin()
			{
				return (iterator(_begin, _nil));
			}
			const_iterator	begin() const
			{
				return (const_iterator(_begin, _nil));
			}
			iterator	end()
			{
				return (iterator(_end, _nil));
			}
			const_iterator	end() const
			{
				return (const_iterator(_end, _nil));
			}
			size_type	size() const
			{
				return (_size);
			}
			size_type	max_size() const
			{
				return (std::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()), _alloc.max_size()));
			}

			// https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
			pair<iterator, bool>	insert(const value_type &value)
			{
				node_type	insert_place = search_insert_place(value);
				return (insert_node(insert_place, value));
			}

			// Hint for the position where the element can be inserted.
			// Must still follow rules of the tree and doesnt force the insertion
			// Time complexity: log(n) (n is the size of the map), if the hint is optimal then O(1)
			// Hinting on either side (prev or next position the value should be) gives about the same result, and is always better than no hint at all.
			// Choosing a poor hint position is worse than no hint at all.
			// Could be better coded with upper and lower bound?
			iterator		insert(iterator position, const value_type &val)
			{
				if (position == end())
				{
					iterator max = end();
					--max;
					if (_size > 0 && _compare(*(&max.get_current()->value.first), val.first))  //  check if the position hint is valid
						return (insert_node(max.getBase(), val).first);
					else										//  else we search for the opti insert place
						return (insert(val).first);
				}
				if (_compare(val.first, *(&position.get_current()->value.first))) //  value < pos
				{
					if (position == begin())  //  no need to check further, insert
						return (insert_node(_begin, val).first);
					iterator prev = position;
					--prev;
					if (_compare(*(&prev.get_current()->value.first), val.first)) //  if prev node is less then val, we are in the correct subtree
					{
						if (prev.getBase()->right == _nil)		//  if right node of the previous key is free, go there
							return (insert_node(prev.getBase(), val).first);
						else
							return (insert_node(position.getBase(), val).first);
					}
					return (insert(val).first); //  hint was not good, we need a new position
				}
				if (_compare(*(&position.get_current()->value.first), val.first)) // pos < value
				{
					iterator max = end();
					--max;
					if (position == max)
						return (insert_node(max.getBase(), val).first);
					iterator next = position;
					++next;
					if (_compare(val.first, *(&next.get_current()->value.first)))
					{
						if (position.getBase()->right == _nil)
							return (insert_node(position.getBase(), val).first);
						else
							return (insert_node(next.getBase(), val).first);
					}
					return (insert(val).first);
				}
				return (position);
			}

			//  https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
			//  https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
			//  http://ion.uwinnipeg.ca/~ychen2/advancedAD/Red-black%20Tree.pdf
			void erase(iterator position)
			{
				if (position == end())
					return ;
				if (position == begin())
					_begin = _tools.next_node(_begin, _nil);
				bool deleted_color;
				node_type replaced = replace_node(position.getBase(), deleted_color);
				if (deleted_color == node<T>::Black)
					delete_fixup(replaced);  // check if replaced node breaks no rule and fix it
				delete_node(position.getBase()); // alloc.destroy + deallocate
				--_size;
			}

			size_type erase(const Key &key)
			{
				iterator it = find(key);
				if (it == end())
					return (0);
				erase(it);
				return (1);
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			}

			void clear()
			{
				destroy(get_root());  // erase everything from root till nil
				_begin = _end;
				_end->left = _nil;
				_size = 0;
			}

			void swap(tree &src)
			{
				node_type temp = _nil;
				_nil = src._nil;
				src._nil = temp;

				temp = _begin;
				_begin = src._begin;
				src._begin = temp;

				temp = _end;
				_end = src._end;
				src._end = temp;

				Compare temp2 = _compare;
				_compare = src._compare;
				src._compare = temp2;

				node_allocator_type temp3 = _alloc;
				_alloc = src._alloc;
				src._alloc = temp3;

				size_type temp4 = _size;
				_size = src._size;
				src._size = temp4;
			}

			iterator lower_bound(const key_type &key)
			{
				node_type node = lower_bound_node(key);
				return (iterator(node, _nil));
			}

			const_iterator lower_bound(const key_type &key) const
			{
				node_type node = lower_bound_node(key);
				return (const_iterator(node, _nil));
			}

			iterator upper_bound(const key_type &key)
			{
				node_type node = upper_bound_node(key);
				return (iterator(node, _nil));
			}

			const_iterator upper_bound(const key_type &key) const
			{
				node_type node = upper_bound_node(key);
				return (const_iterator(node, _nil));
			}

			pair<iterator, iterator> equal_range(const key_type &key)
			{
				pair<node_type, node_type> range = equal_range_node(key);
				return (ft::make_pair(iterator(range.first, _nil), iterator(range.second, _nil)));
			}

			pair<const_iterator, const_iterator> equal_range(const key_type &key) const
			{
				pair<node_type, node_type> range = equal_range_node(key);
				return (ft::make_pair(const_iterator(range.first, _nil), const_iterator(range.second, _nil)));
			}

			iterator find(const key_type &key)
			{
				node_type node = find_node(key);
				return (iterator(node, _nil));
			}
			const_iterator find(const key_type &key) const
			{
				node_type node = find_node(key);
				return (const_iterator(node, _nil));
			}

			size_type count(const key_type &key) const
			{
				if (find(key) != end())
					return (1);
				return (0);
			}

		private :
			// utility tree manip
			void		init()
			{
				_nil = _alloc.allocate(1);
				node<T> empty;
				_alloc.construct(_nil, empty);  // create empty node then construct the pointer to it
				_nil->left = _nil;	// same pointer for each leaf, instead of allocating each
				_nil->right = _nil;

				_end = _alloc.allocate(1);		// root parent but also position after last/highest key (see next_node & prev_node)
				_alloc.construct(_end, empty);
				_end->left = _nil;		//root
				_begin = _end;
			}
			void		destroy(node_type no)
			{
				if (no != _nil)
				{
					destroy(no->left);
					destroy(no->right);
					delete_node(no);	//alloc.destroy + alloc.deallocate
				}
			}

			void		set_root(node_type	no)
			{
				_end->left = no;
				no->parent = _end;
			}

			node_type	get_root() const
			{
				return (_end->left);
			}
			node_type	create_node(const value_type &val)
			{
				node_type new_no = _alloc.allocate(1);
				node<T> simple_node(_nil, val);  // fist create a node, then construct the pointer to the node
				_alloc.construct(new_no, simple_node);
				return (new_no);
			}
			void		delete_node(node_type no)
			{
				_alloc.destroy(no);
				_alloc.deallocate(no, 1);
			}
			void rotate_left(node_type no)
			{
				node_type y = no->right;
				no->right = y->left;
				if (y->left != _nil)
					y->left->parent = no;
				y->parent = no->parent;
				if (no->parent == _end)
					set_root(y);
				else if (_tools.is_left_child(no))
					no->parent->left = y;
				else
					no->parent->right = y;
				y->left = no;
				no->parent = y;
			}
			void	rotate_right(node_type no)
			{
				node_type y = no->left;
				no->left = y->right;
				if (y->right != _nil)
					y->right->parent = no;
				y->parent = no->parent;
				if (no->parent == _end)
					set_root(y);
				else if (_tools.is_right_child(no))
					no->parent->right = y;
				else
					no->parent->left = y;
				y->right = no;
				no->parent = y;
			}
			node_type	search_insert_place(const value_type &value)
			{
				node_type prev_node = _nil;  // in case now_node == _nil -----> return _nil
				node_type now_node = get_root();
				while (now_node != _nil)
				{
					prev_node = now_node;
					if (_compare(value.first, now_node->value.first))
						now_node = now_node->left;
					else if (_compare(now_node->value.first, value.first))
						now_node = now_node->right;
					else
						return now_node;
				}
				return (prev_node);
			}

			// Perform standard BST insertion and make the colour of newly inserted nodes as RED.
			// If x is the root, change the colour of x as BLACK (Black height of complete tree increases by 1).
			pair<iterator, bool>	insert_node(node_type insert_position, const value_type &val)
			{
				node_type	node = create_node(val);
				node->parent = insert_position;
				if (node->parent == _nil)
					set_root(node);
				else if (_compare(node->value.first, insert_position->value.first))
					insert_position->left = node;
				else if (_compare(insert_position->value.first, node->value.first))
					insert_position->right = node;
				else		// inserted key is already taken
				{
					delete_node(node);
					return (ft::make_pair(iterator(insert_position, _nil), false));
				}
				insert_fixup(node);
				check_begin(node);
				++_size;
				return (ft::make_pair(iterator(node, _nil), true));
			}

			void insert_fixup(node_type no)
			{
				// Do the fixup if the color of nodes parent is not BLACK and node is not the root.
				// if node is the root, parent is black by def
				// The main property that violates after insertion is two consecutive reds
				while (no->parent->color == node<T>::Red)
				{
					if (_tools.is_left_child(no->parent))
						insert_fixup_left(no);
					else
						insert_fixup_right(no);
				}
				get_root()->color = node<T>::Black;
			}

			void insert_fixup_left(node_type &no)
			{
				node_type y = no->parent->parent->right;
				if (y->color == node<T>::Red)
				//  If x’s uncle is RED : Change the colour of parent and uncle as BLACK.
				//							Colour of a grandparent as RED.
				{
					no->parent->color = node<T>::Black;
					y->color = node<T>::Black;
					no->parent->parent->color = node<T>::Red;
					no = no->parent->parent;
				}
				else
				{
					//  If x’s uncle is BLACK :
					//  If left left case : right rotate grandparent and swap colours of grandpa and parent
					//  If left right case : left rotate parent then aply left left case
					if (_tools.is_right_child(no))
					{

						no = no->parent;
						rotate_left(no);
					}
					no->parent->color = node<T>::Black;
					no->parent->parent->color = node<T>::Red;
					rotate_right(no->parent->parent);
				}
			}

			void insert_fixup_right(node_type &no)
			{
				node_type y = no->parent->parent->left;
				if (y->color == node<T>::Red)
				//  If x’s uncle is RED : Change the colour of parent and uncle as BLACK.
				//							Colour of a grandparent as RED.
				{
					no->parent->color = node<T>::Black;
					y->color = node<T>::Black;
					no->parent->parent->color = node<T>::Red;
					no = no->parent->parent;
				}
				else
				{
					//  If x’s uncle is BLACK :
					//  If right right case : left rotate grandparent and swap colours of grandpa and parent
					//  If right left case : right rotate parent then aply right right case
					if (_tools.is_left_child(no))
					{
						no = no->parent;
						rotate_right(no);
					}
					no->parent->color = node<T>::Black;
					no->parent->parent->color = node<T>::Red;
					rotate_left(no->parent->parent);
				}
			}

			void delete_fixup(node_type no)  // used in erase()
			{
				// double black
				while (no != get_root() && no->color == node<T>::Black)
				{
					if (_tools.is_right_child(no))
						delete_fixup_right(no);
					else
						delete_fixup_left(no);
				}
				no->color = node<T>::Black;
			}

			void delete_fixup_left(node_type &no)
			{
				node_type sibling = no->parent->right;
				if (sibling->color == node<T>::Red)
				{
					sibling->color = node<T>::Black;
					no->parent->color = node<T>::Red;
					rotate_left(no->parent);
					sibling = no->parent->right;
				}
				if (sibling->left->color == node<T>::Black && \
					sibling->right->color == node<T>::Black)
				{
					sibling->color = node<T>::Red;
					no = no->parent;
				}
				else
				{
					if (sibling->right->color == node<T>::Black)
					{
						sibling->left->color = node<T>::Black;
						sibling->color = node<T>::Red;
						rotate_right(sibling);
						sibling = no->parent->right;
					}
					sibling->color = no->parent->color;
					no->parent->color = node<T>::Black;
					sibling->right->color = node<T>::Black;
					rotate_left(no->parent);
					no = get_root();
				}
			}

			void delete_fixup_right(node_type &no)
			{
				node_type sibling = no->parent->left;
				if (sibling->color == node<T>::Red)
				{
					sibling->color = node<T>::Black;
					no->parent->color = node<T>::Red;
					rotate_right(no->parent);
					sibling = no->parent->left;
				}
				if (sibling->right->color == node<T>::Black && \
					sibling->left->color == node<T>::Black)
				{
					sibling->color = node<T>::Red;
					no = no->parent;
				}
				else
				{
					if (sibling->left->color == node<T>::Black)
					{
						sibling->right->color = node<T>::Black;
						sibling->color = node<T>::Red;
						rotate_left(sibling);
						sibling = no->parent->left;
					}
					sibling->color = no->parent->color;
					no->parent->color = node<T>::Black;
					sibling->left->color = node<T>::Black;
					rotate_right(no->parent);
					no = get_root();
				}
			}

			// https://stackoverflow.com/questions/18646471/can-somebody-explain-me-this-binary-tree-transplant-algorithm
			void transplant(node_type x, node_type y)
			{
				if (x->parent == _end)
					set_root(y);
				else if (_tools.is_left_child(x))
					x->parent->left = y;
				else
					x->parent->right = y;
				if (y->parent != _nil)
					y->parent = x->parent;
			}

			node_type replace_node(node_type node, bool &deleted_color)
			{
				deleted_color = node->color;
				node_type replaced_node;
				// Node to be deleted has only one child: Copy the child to the node and delete the child
				if (node->left == _nil)
				{
					replaced_node = node->right;
					transplant(node, node->right);
				}
				else if (node->right == _nil)
				{
					replaced_node = node->left;
					transplant(node, node->left);
				}
				else  //  Node to be deleted has two children: Find inorder successor of the node. Copy contents of the inorder successor to the node and delete the inorder successor
				{
					node_type y = _tools.search_min(node->right, _nil);
					deleted_color = y->color;
					replaced_node = y->right;
					if (y->parent == node)
					{
						replaced_node->parent = y;
					}
					else
					{
						transplant(y, y->right);
						y->right = node->right;
						y->right->parent = y;
					}
					transplant(node, y);
					y->left = node->left;
					y->left->parent = y;
					y->color = node->color;
				}
				return replaced_node;
			}

			void check_begin(node_type node)
			{
				if (_begin == _end || _compare(node->value.first, _begin->value.first))
				{
					_begin = node;
				}
			}

			node_type lower_bound_node(const key_type &key) const
			{
				node_type result = _end;
				node_type node = get_root();
				while (node != _nil)
				{
					if (!_compare(node->value.first, key)) // node >= key (mind the !)
					{
						result = node;
						node = node->left;
					}
					else
						node = node->right;
				}
				return (result);
			}

			node_type upper_bound_node(const key_type &key) const
			{
				node_type result = _end;
				node_type node = get_root();
				while (node != _nil)
				{
					if (_compare(key, node->value.first))
					{
						result = node;
						node = node->left;
					}
					else
						node = node->right;
				}
				return (result);
			}

			pair<node_type, node_type> equal_range_node(const key_type &key) const
			{
				node_type lower = get_root();
				node_type upper = _end;
				while (lower != _nil)
				{
					if (_compare(key, lower->value.first))
					{
						upper = lower;
						lower = lower->left;
					}
					else if (_compare(lower->value.first, key))
					{
						lower = lower->right;
					}
					else
					{
						if (lower->right != _nil)
							upper = _tools.search_min(lower->right, _nil);
						return ft::make_pair(lower, upper);
					}
				}
				return (ft::make_pair(lower, upper));
			}

			node_type find_node(const key_type &key) const
			{
				node_type node = lower_bound_node(key);  // use lower bound to check
				if (node != _end && !_compare(key, node->value.first))  // use the "is not less" in case upper bound
					return (node);
				return (_end);
			}

			/*void	print_tab(int lvl)
			{
				int i = 0;

				while (i < lvl)
				{
					std::cout << "\t";
					i++;
				}
			}

			void	print_tree_rec(node_type root, int lvl)
			{
				if (root == _nil)
				{
					print_tab(lvl);
					std::cout << "nil" <<std::endl;
					return ;
				}
				print_tab(lvl);
				std::cout << (&root->value)->first <<std::endl;
				print_tab(lvl);
				std::cout << "left" <<std::endl;
				print_tree_rec(root->left, lvl + 1);
				print_tab(lvl);
				std::cout << "right" <<std::endl;
				print_tree_rec(root->right, lvl + 1);
			}

			void	another_print_tree(node_type root, int lvl)
			{
				int i;
				if (root != _nil)
				{
					another_print_tree(root->right, ++lvl);
					std::cout << std::endl;
					if (root == get_root())
						std::cout << "Root -> ";
					for (i = 0; i < lvl && root != get_root(); i++)
						std::cout << "        ";
					std::cout << (&root->value)->first;
					another_print_tree(root->left, ++lvl);
				}
			}

			void printBT(const std::string& prefix, node_type node, bool isLeft)
			{
				if(node != _nil)
				{
					std::cout << prefix;

					std::cout << (isLeft ? "├──" : "└──" );

					// print the value of the node
					if ((node->color) == 0)
						std::cout << "\x1B[31m" << (&node->value)->first << "\033[0m" << std::endl;
					else
						std::cout << (&node->value)->first << std::endl;
					std::cout << "\033[0m";
					// enter the next tree level - left and right branch
					printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
					printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
				}
			}

		public :
			void	print_tree()		// check and must be private
			{
				print_tree_rec(get_root(), 0);
			}

			void	print_tree_two()		// check and must be private
			{
				printBT("", get_root(), false);
			}*/
	};
}


#endif
