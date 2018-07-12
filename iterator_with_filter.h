#pragma once
#include <iostream>
#include <iterator>

template<typename InputIterator, typename Filter>
class iterator_with_filter
{
	using Data = decltype(*(std::declval<InputIterator>()));
	using SmartIterator = iterator_with_filter<InputIterator, Filter>;

	InputIterator current_iterator_;
	InputIterator end_iterator_;
	Filter filter_;

	void get_next_filtered()
	{
		do
		{
			++current_iterator_;
		} while (current_iterator_ != end_iterator_ && !filter_(*(current_iterator_)));
	}

public:
	iterator_with_filter(InputIterator iterator, InputIterator container_end, Filter filter)
		: current_iterator_(iterator)
		, end_iterator_(container_end)
		, filter_(filter) 
	{
		if (!filter_(*current_iterator_))
			get_next_filtered();
	}

	iterator_with_filter(const SmartIterator& iterator)
		: current_iterator_(iterator.current_iterator_)
		, end_iterator_(iterator.end_iterator_)
		, filter_(iterator.filter_) {}

	//InputIterator operator * ()
	//{
	//	return iterator_;
	//}

	Data operator * ()
	{
		return *current_iterator_;
	}

	InputIterator operator -> ()
	{
		return current_iterator_;
	}

	SmartIterator operator ++ ()
	{
		get_next_filtered();
		return *this;
	}

	SmartIterator operator ++ (int)
	{
		SmartIterator temp_iterator(*this);
		get_next_filtered();
		return temp_iterator;
	}

	SmartIterator& operator = (const SmartIterator& sm_iterator)
	{
		current_iterator_ = sm_iterator.current_iterator_;
		end_iterator_ = sm_iterator.end_iterator_;
		filter_ = sm_iterator.filter_;
		return *this;
	}

	bool operator == (const SmartIterator& sm_iterator)
	{
		return current_iterator_ == sm_iterator.current_iterator_;
	}

	bool operator != (const SmartIterator& sm_iterator)
	{
		return current_iterator_ != sm_iterator.current_iterator_;
	}

	//friend void swap(const SmartIterator& sm_iterator1, const SmartIterator& sm_iterator2) {
	//	std::swap(sm_iterator1.current_iterator_, sm_iterator2.current_iterator_);
	//}
};