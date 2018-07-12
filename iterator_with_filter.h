#pragma once
#include <iostream>

template<typename InputIterator, typename Filter>
class iterator_with_filter
{
	using Data = decltype(*(std::declval<InputIterator>()));
	using SmartIterator = iterator_with_filter<InputIterator, Filter>;

	InputIterator iterator_;
	Filter filter_;

public:
	iterator_with_filter(InputIterator iterator, Filter filter)
		: iterator_(iterator)
		, filter_(filter) {}

	InputIterator SmartIterator::operator * (const SmartIterator& filtered_iterator)
	{
		return iterator_;
	}

	SmartIterator SmartIterator::operator ++ (int) {}
	SmartIterator SmartIterator::operator ++ () {}

};