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
 * \brief Abstract implementation of a priority queue
 * \tparam T Type of stored elements
 * \tparam Compare Compare function object used in comparing elements
 */
template<typename T, class Compare = std::less<T>>
class PriorityQueue {  // NOLINT(hicpp-special-member-functions, cppcoreguidelines-special-member-functions)
public:
	virtual T top() const = 0;

	virtual bool empty() const = 0;
	virtual int size() const = 0;

	virtual void push(const T & elem) = 0;
	virtual void push(T && elem) = 0;
	virtual void pop() = 0;
	
	virtual void clear() = 0;

	virtual ~PriorityQueue() = 0;

};

template <typename T, class Compare>
PriorityQueue<T, Compare>::~PriorityQueue() = default;


#endif
