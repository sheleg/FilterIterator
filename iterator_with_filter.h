#pragma once
#include <iostream>
#include <iterator>

template <class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T * , class Reference = T & >
	struct MyIterator {
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
};

template<typename BaseIterator, typename Filter>
class iterator_filtering : public MyIterator<std::forward_iterator_tag, BaseIterator>/* : public BaseIterator*/
{
	using ItemT = decltype(*(std::declval<BaseIterator>()));
	using IteratorT = iterator_filtering<BaseIterator, Filter>;

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
	iterator_filtering()
		: current_(nullptr)
		, end_(nullptr)
		, filter_([]() { return false; }) {}

	iterator_filtering(BaseIterator iterator, BaseIterator container_end, Filter filter)
		: current_(iterator)
		, end_(container_end)
		, filter_(filter) 
	{
		if (current_ != end_ && !filter_(*current_))
			forward();
	}

	iterator_filtering(const IteratorT& iterator)
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

	friend bool operator == (const IteratorT& first, const IteratorT& second)
	{
		return first.current_ == second.current_;
	}

	friend bool operator != (const IteratorT& first, const IteratorT& second)
	{
		return first.current_ == second.current_;
	}

	friend void swap(IteratorT& first, IteratorT& second)
	{
		std::swap(first.current_, second.current_);
	}
};


