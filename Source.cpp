#include "iterator_with_filter.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

bool isEvenCheck(int n)
{
	return n % 2 == 0;
}

int main()
{
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	iterator_with_filter<decltype(vec.begin()), bool(*)(int)> iter1(vec.begin(), vec.end(), isEvenCheck);
	iterator_with_filter<decltype(vec.begin()), bool(*)(int)> iter2(vec.begin(), vec.end(), isEvenCheck);
	std::cout << *(++iter1);
	std::cout << *iter2;
	//std::cout << (iter1 != iter2);
	swap(iter1, iter2);
	std::cout << *iter1++;
	std::cout << *iter2;
	//std::min_element(iter, iter);
	return 0;
}
