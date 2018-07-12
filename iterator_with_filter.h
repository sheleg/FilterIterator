#pragma once
#include <iostream>
#include <iterator>

template<typename BaseIterator, typename Filter>
class iterator_with_filter : public BaseIterator
{
	using ItemT = decltype(*(std::declval<BaseIterator>()));
	using IteratorT = iterator_with_filter<BaseIterator, Filter>;

	BaseIterator current_;
	BaseIterator end_;
	Filter filter_;

	void forward()
	{
		do
		{
			++current_;
		} while (current_ != end_ && !filter_(*(current_)));
	}

public:
	iterator_with_filter()
		: current_(nullptr)
		, end_(nullptr)
		, filter_([]() { return nullptr; }) {}

	iterator_with_filter(BaseIterator iterator, BaseIterator container_end, Filter filter)
		: current_(iterator)
		, end_(container_end)
		, filter_(filter) 
	{
		if (current_ != end_ && !filter_(*current_))
			forward();
	}

	iterator_with_filter(const IteratorT& iterator)
		: current_(iterator.current_)
		, end_(iterator.end_)
		, filter_(iterator.filter_) {}

	ItemT operator * ()
	{
		return *current_;
	}

	BaseIterator operator -> ()
	{
		return current_;
	}

	IteratorT& operator ++ ()
	{
		forward();
		return *this;
	}

	IteratorT operator ++ (int)
	{
		IteratorT temp_iterator(*this);
		forward();
		return temp_iterator;
	}

	IteratorT& operator = (const IteratorT& sm_iterator)
	{
		current_ = sm_iterator.current_;
		end_ = sm_iterator.end_;
		filter_ = sm_iterator.filter_;
		return *this;
	}

	bool operator == (const IteratorT& sm_iterator)
	{
		return current_ == sm_iterator.current_;
	}

	bool operator != (const IteratorT& sm_iterator)
	{
		return current_ != sm_iterator.current_;
	}
};