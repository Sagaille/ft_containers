#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "includes/utils/type_traits.hpp"
#include "includes/utils/iterator.hpp"
#include "includes/map/map.hpp"
#include <map>


int main()
{
	std::map<int, std::string> test01;
	test01.insert(std::pair<int, std::string>(0, "lol"));

	std::map<int, std::string>::iterator it = test01.begin();
	std::cout << it->first << " and " << it->second <<std::endl;

	std::map<int, std::string> test00;
	test00.insert(std::pair<int, std::string>(33, "hj"));
	test00.insert(std::pair<int, std::string>(13, "dfza"));
	test00.insert(std::pair<int, std::string>(53, "lol"));
	test00.insert(std::pair<int, std::string>(21, "lol"));
	test00.insert(std::pair<int, std::string>(11, "lol"));
	test00.insert(std::pair<int, std::string>(15, "lol"));
	test00.insert(std::pair<int, std::string>(31, "lol"));
	test00.insert(std::pair<int, std::string>(53, "lol"));
	test00.insert(std::pair<int, std::string>(41, "lol"));
	test00.insert(std::pair<int, std::string>(61, "lol"));
	std::map<int, std::string>::iterator it2 = test00.begin();
	std::map<int, std::string>::iterator it3 = test00.end();
	while (it2 != it3)
	{
		std::cout << it2->first << " and " << it2->second <<std::endl;
		++it2;
	}
	it2 = test00.begin();
	it2++;
	it2++;
	it2++;
	std::cout << it2->first <<std::endl;
	test00.insert(it2, std::pair<int, std::string>(54, "lol"));
	it2 = test00.begin();
	it2++;
	it2++;
	it2++;
	std::cout << it2->first <<std::endl;
	test00.insert(it2, std::pair<int, std::string>(53, "lol"));
	it2 = test00.begin();
	it2++;
	it2++;
	it2++;
	it2++;
	it2++;
	it2++;
	it2++;
	it2++;
	it2++;
	it3 = test00.lower_bound(40);
	std::cout << "lower bound == " << it3->first <<std::endl;
	it3 = test00.upper_bound(40);
	std::cout << "upper bound == " << it3->first <<std::endl;
	std::cout << "jere" << it2->first <<std::endl;
	test00.insert(it2, std::pair<int, std::string>(75, "lol"));
	test00.insert(std::pair<int, std::string>(10, "lol"));
	/*test00.print_map();
	test00.print_map2();*/
}
