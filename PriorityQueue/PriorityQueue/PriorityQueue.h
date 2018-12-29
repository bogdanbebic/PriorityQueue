#pragma once
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
#include <functional>
#include <exception>

class PriorityQueueEmpty : public std::exception {
public:
	char const* what() const override {
		return "*** Priority queue is empty! ***";
	}

};


/**
 * \brief Implementation of a priority queue
 * \tparam T Type of stored elements
 * \tparam Compare Compare function object used in comparing elements
 */
template<typename T, class Compare = std::less<T>>
class PriorityQueue {	// TODO: implementation
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue & other);
	PriorityQueue(PriorityQueue && other);

	~PriorityQueue() = default;	// TODO: deallocation of implementation structures

	PriorityQueue & operator=(const PriorityQueue & other);
	PriorityQueue & operator=(PriorityQueue && other);

	T top() const;

	bool empty() const { return size_ == 0; }
	int size() const { return size_; }

	void push(const T & elem);
	void push(T && elem);
	void pop();

private:
	int size_;
};

template <typename T, class Compare>
PriorityQueue<T, Compare>::PriorityQueue()
	: size_(0)
{
	// empty body // TODO: init of implementation structures
}

#endif
