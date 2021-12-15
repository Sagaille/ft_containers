/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_original.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:40:39 by ldavids           #+#    #+#             */
/*   Updated: 2021/12/15 13:48:22 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <stack>


int main()
{
	std::vector<int>		test0;
	std::vector<int>		test1(10, 10);
	std::vector<int>		test2(test1);
	std::vector<int>		test3;
	std::vector<int>		test5;

	std::cout << "size() + constructors" << std::endl << "-------------" << std::endl;
	std::cout << "test0.size == " <<  test0.size() << std::endl;
	std::cout << "test1.size == " << test1.size() << std::endl;
	std::cout << "test0 = test1; " << std::endl;
	test0 = test1;
	std::cout << "test0.size == " <<  test0.size() << std::endl;
	std::cout << "test1.size == " << test1.size() << std::endl;
	std::cout << "test2.size == " << test2.size() << std::endl;

	test0 = test3;
	test3.push_back(3);
	test3.push_back(2);
	test3.push_back(1);
	test3.push_back(0);
	std::cout << test0[0] << std::endl;
	std::vector<int>::iterator	it1 = test3.begin();
	std::vector<int>::iterator	it2 = test3.end();
	std::cout << "constructor by range test4(it1, it2)" << std::endl;
	std::vector<int>		test4(it1, it2);
	while (it1 != it2)
	{
		std::cout << *it1 << std::endl;
		it1++;
	}
	std::cout << std::endl;
	std::cout << "iterators" << std::endl << "-------------" << std::endl;
	std::cout << "begin()" << std::endl;
	it1 = test3.begin();
	std::cout << "*it1 == " << *it1 << std::endl;
	it2 = test3.end();
	--it2;
	std::cout << "*it2 == " << *it2 << std::endl;

	std::cout << "begin() with const_iterator" << std::endl;
	for( std::vector<int>::const_iterator it3 = test3.begin() ; it3 != test3.end() ; ++it3 )
		{ std::cout << *it3 << std::endl; }

	std::cout << "rbegin() with reverse_iterator" << std::endl;
	std::vector<int>::reverse_iterator	it4 = test3.rbegin();
	std::cout << "*it4 == " << *it4 << std::endl;
	std::cout << "rend() with reverse_iterator" << std::endl;
	std::vector<int>::reverse_iterator	it5 = test3.rend();
	it5--;
	std::cout << "*it5 == " << *it5 << std::endl;

	std::cout << "rbegin() with const_reverse_iterator" << std::endl;
	std::vector<int>::const_reverse_iterator	it6 = test3.rbegin();
	std::cout << "*it6 == " << *it6 << std::endl;
	std::cout << "rend() with const_reverse_iterator" << std::endl;
	std::vector<int>::reverse_iterator	it7 = test3.rend();
	it7--;
	std::cout << "*it7 == " << *it7 << std::endl;

	std::cout << std::endl;
	std::cout << "capapity" << std::endl << "-------------" << std::endl;

	std::cout << "test3.max_size() == " << test3.max_size() << std::endl;
	std::cout << "test0.max_size() == " << test0.max_size() << std::endl;

	test3.resize(3);
	it1 = test3.begin();
	it2 = test3.end();
	std::cout << "test3.resize(3)" << std::endl;
	while (it1 != it2)
	{
		std::cout << *it1 << std::endl;
		it1++;
	}
	std::cout << "test3.resize(10, 5)" << std::endl;
	test3.resize(10, 5);
	it1 = test3.begin();
	it2 = test3.end();
	while (it1 != it2)
	{
		std::cout << *it1 << std::endl;
		it1++;
	}
	std::cout << "test3.capacity() == " << test3.capacity() << std::endl;
	std::cout << "test0.capacity() == " << test0.capacity() << std::endl;
	std::cout << "test1.capacity() == " << test1.capacity() << std::endl;
	std::cout << "test2.capacity() == " << test2.capacity() << std::endl;
	std::cout << "test5.capacity() == " << test5.capacity() << std::endl;

	std::cout << "test2.empty() == " << test2.empty() << std::endl;
	std::cout << "test5.empty() == " << test5.empty() << std::endl;

	std::cout << std::endl;
	std::cout << "reserve" << std::endl << "-------------" << std::endl;
	std::cout << "test5.reserve(5)" << std::endl;
	test5.reserve(5);
	std::cout << "test5.capacity() == " << test5.capacity() << std::endl;
	std::cout << "test5.size() == " << test5.size() << std::endl;

	std::cout << std::endl;
	std::cout << "element access" << std::endl << "-------------" << std::endl;
	std::cout << "test3[0] == " << test3[0] << std::endl;
	std::cout << "test3[1] == " << test3[1] << std::endl;
	std::cout << "test3[2] == " << test3[2] << std::endl;
	std::cout << "test3[3] == " << test3[3] << std::endl;
	std::cout << "test3.at(0) == " << test3.at(0) << std::endl;
	std::cout << "test3.at(1) == " << test3.at(1) << std::endl;
	std::cout << "test3.at(2) == " << test3.at(2) << std::endl;
	std::cout << "test3.at(3) == " << test3.at(3) << std::endl;
	try
	{
		std::cout << "test3.at(-1) == " << test3.at(-1) << std::endl;
	}
	catch (std::exception(&e))
	{
		std::cout << "out of range exception" << std::endl;
	}
	std::cout << "test3.front() == " << test3.front() << std::endl;
	std::cout << "test3.back() == " << test3.back() << std::endl;

	std::cout << std::endl;
	std::cout << "modifiers" << std::endl << "-------------" << std::endl;
	std::vector<int>		test6;
	std::cout << "test6.capacity() == " << test6.capacity() << std::endl;
	std::cout << "test6.assign(6, 5);" << std::endl;
	test6.assign(6, 5);
	it1 = test6.begin();
	it2 = test6.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << "test5.capacity() == " << test5.capacity() << std::endl;
	std::cout << "test5.assign(6, 5);" << std::endl;
	test5.assign(3, 5);
	it1 = test5.begin();
	it2 = test5.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << "test5.pop_back();\ntest5.pop_back();" << std::endl;
	test5.pop_back();
	test5.pop_back();
	it1 = test5.begin();
	it2 = test5.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << "test5.capacity() == " << test5.capacity() << std::endl;
	std::cout << "test5.size() == " << test5.size() << std::endl;


	std::cout << std::endl;
	std::cout << "insert" << std::endl << "-------------" << std::endl;
	std::cout << std::endl;
	it2 = test5.begin();
	std::cout << "test5.insert(test5.begin(), 4); == " << *(test5.insert(it2, 4)) << std::endl;
	std::cout << "test5.size(); == " << test5.size() << std::endl;
	std::cout << "test5.capacity() == " << test5.capacity() << std::endl;
	it1 = test5.begin();
	it2 = test5.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << std::endl;
	it2 = test5.end();
	std::cout << "test5.insert(test5.end(), 2); == " << *(test5.insert(it2, 2)) << std::endl;
	std::cout << "test5.size(); == " << test5.size() << std::endl;
	std::cout << "test5.capacity() == " << test5.capacity() << std::endl;
	it1 = test5.begin();
	it2 = test5.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << std::endl;
	it2 = test5.end();
	--it2;
	std::cout << "test5.insert(test5.end() - 1, 10, 10);" << std::endl;
	test5.insert(it2, 10, 10);
	std::cout << "test5.size(); == " << test5.size() << std::endl;
	std::cout << "test5.capacity() == " << test5.capacity() << std::endl;
	it1 = test5.begin();
	it2 = test5.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << std::endl;
	it2 = test5.end();
	std::cout << "test5.insert(test5.end(), test3.begin(), test3.end());" << std::endl;
	test5.insert(it2, test3.begin(), test3.end());
	std::cout << "test5.size(); == " << test5.size() << std::endl;
	std::cout << "test5.capacity() == " << test5.capacity() << std::endl;
	it1 = test5.begin();
	it2 = test5.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << std::endl;
	it2 = test5.end();
	std::cout << "test5.insert(test5.end(), test3.begin(), test3.end());" << std::endl;
	std::cout << "test5.size(); == " << test5.size() << std::endl;
	std::cout << "test5.capacity() == " << test5.capacity() << std::endl;
	test5.insert(it2, test3.begin(), test3.end());
	std::cout << "test5.size(); == " << test5.size() << std::endl;
	it1 = test5.begin();
	it2 = test5.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << std::endl;
	std::vector<int>		test7;
	std::cout << "test7.reserve(20);" << std::endl;
	std::cout << "test7.capacity() == " << test7.capacity() << std::endl;
	test7.reserve(20);
	std::cout << "test7.capacity() == " << test7.capacity() << std::endl;
	it2 = test7.begin();
	test7.insert(it2, test3.begin(), test3.end());
	it1 = test7.begin();
	it2 = test7.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << std::endl;
	std::cout << "test7.erase(test7.end() - 1);" << std::endl;
	std::cout << "test7.erase(test7.begin());" << std::endl;
	test7.erase(test7.end() - 1);
	test7.erase(test7.begin());
	it1 = test7.begin();
	it2 = test7.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << "test7.erase(test7.begin());" << std::endl;
	test7.erase(test7.begin(), test7.end());
	it1 = test7.begin();
	it2 = test7.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << std::endl;
	std::cout << "test5.clear();" << std::endl;
	test5.clear();
	it1 = test5.begin();
	it2 = test5.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}

	std::cout << std::endl;
	std::cout << "test5.swap(test3);" << std::endl;
	test5.swap(test3);
	it1 = test5.begin();
	it2 = test5.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}
	std::cout << std::endl;
	std::cout << "std::swap(test5, test3) -- NON MEMBER;" << std::endl;
	std::swap(test5, test3);
	it1 = test3.begin();
	it2 = test3.end();
	while (it1 != it2)
	{
		std::cout <<"*it == " << *it1 << std::endl;
		it1++;
	}

	std::cout << std::endl;
	std::cout << "COMPARISON - NON-MEMBER" << std::endl << "-------------" << std::endl;

	if (test5 < test3)
	{
		std::cout << "test5 is lexicographically less then test3" << std::endl;
	}
	if (test3 > test5)
	{
		std::cout << "test3 is lexicographically greater then test5" << std::endl;
	}
	std::cout << "test5 = test3;" << std::endl;
	test5 = test3;
	if (test3 == test5)
	{
		std::cout << "test3 is lexicographically equal to test5" << std::endl;
	}
	if (test3 >= test5)
	{
		std::cout << "test3 is lexicographically equal or greater then test5" << std::endl;
	}
	test3.push_back(510);
	std::cout << "test3.push_back(510);" << std::endl;
	if (test3 > test5)
	{
		std::cout << "test3 is lexicographically greater then test5" << std::endl;
	}
	if (test3 != test5)
	{
		std::cout << "test3 is lexicographically different then test5" << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Vector Iterator" << std::endl << "-------------" << std::endl;
	it2 = test3.end();
	--it2;
	std::cout << "*it2 == " << *it2 << std::endl;
	--it2;
	std::cout << "*it2 == " << *it2 << std::endl;
	it2--;
	std::cout << "*it2 == " << *it2 << std::endl;
	it2++;
	std::cout << "*it2 == " << *it2 << std::endl;
	++it2;
	std::cout << "*it2 == " << *it2 << std::endl;
	it2--;
	std::cout << "*it2 == " << *it2 << std::endl;
	it2 -= 2;
	std::cout << "*it2 == " << *it2 << std::endl;
	it2 += 3;
	std::cout << "*it2 == " << *it2 << std::endl;

	std::cout << std::endl;
	std::cout << "std::vector<int>::iterator it3 = it2;" << std::endl;
	std::vector<int>::iterator it3 = it2;
	std::cout << "*it3 == " << *it3 << std::endl;
	std::vector<int>::iterator it8(it2);
	std::cout << "*it8 == " << *it8 << std::endl;
	std::cout << "it8[-1] == " << it8[-1] << std::endl;
	if (it8 == it2)
	{
		std::cout << "it8 == it2" << std::endl;
	}
	--it8;
	std::cout << "--it8" << std::endl;
	if (it8 < it2)
	{
		std::cout << "it8 < it2" << std::endl;
	}
	if (it8 <= it2)
	{
		std::cout << "it8 <= it2" << std::endl;
	}
	if (it8 != it2)
	{
		std::cout << "it8 != it2" << std::endl;
	}
	std::vector<int>::reverse_iterator it9 = test3.rbegin();
	std::vector<int>::iterator it10 = test3.end();
	std::cout << "reverse_iterator it9 == " << *it9 << std::endl;
	it10--;
	std::cout << "iterator it10 == " << *it10 << std::endl;
	if (*it10 == *it9)
		std::cout << "equality" << std::endl;


	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	std::vector<int>::reverse_iterator r_it = v.rbegin();
	std::vector<int>::const_reverse_iterator c_r_it = v.rbegin() + 1;
	std::cout << *r_it << std::endl;
	std::cout << *c_r_it << std::endl;
	std::cout << "(c_r_it == r_it): " << (c_r_it == r_it) << std::endl;
	std::cout << "(c_r_it >= r_it): " << (c_r_it >= r_it) << std::endl;
}
