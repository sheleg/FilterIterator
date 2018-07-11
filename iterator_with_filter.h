#pragma once
#include <iostream>

template<typename InputIterator, typename Filter, typename LessRelation = std::less<decltype(*(std::declval<InputIterator>()))>>
class iterator_with_filter
{
	using Data = decltype(*(std::declval<InputIterator>()));
	using SmartIterator = iterator_with_filter<InputIterator, Filter, LessRelation>;

	InputIterator iterator_;
	Filter filter_;
	LessRelation less_;

public:
	iterator_with_filter();

	Data SmartIterator::operator * (const SmartIterator& filtered_iterator); 
	SmartIterator SmartIterator::operator ++ (int);
	SmartIterator SmartIterator::operator ++ ();

};