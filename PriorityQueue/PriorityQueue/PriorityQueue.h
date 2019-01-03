#pragma once
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
#include <functional>
#include <exception>
#include <list>

class PriorityQueueEmpty : public std::exception {
public:
	char const* what() const override {
		return "*** Priority queue is empty! ***";
	}

};


/**
 * \brief Implementation of a priority queue using a Fibonacci heap
 * \tparam T Type of stored elements
 * \tparam Compare Compare function object used in comparing elements
 */
template<typename T, class Compare = std::less<T>>
class PriorityQueue {  // NOLINT(hicpp-special-member-functions, cppcoreguidelines-special-member-functions)
public:
	T top() const {
		return fibonacci_heap_.top();
	}

	bool empty() const {
		return fibonacci_heap_.empty();
	}

	int size() const {
		return fibonacci_heap_.size();
	}

	void push(const T & elem) {
		fibonacci_heap_.push(elem);
	}

	void push(T && elem) {
		fibonacci_heap_.push(elem);
	}

	void pop() {
		fibonacci_heap_.pop();
	}
	
	void clear() {
		fibonacci_heap_.clear();
	}
	
private:

	class FibonacciHeap {
	public:
		FibonacciHeap() = default;

		~FibonacciHeap() = default;	// TODO: implement

		FibonacciHeap(const FibonacciHeap& other) = default;	// TODO: implement
		FibonacciHeap(FibonacciHeap&& other) = default;	// TODO: implement

		FibonacciHeap & operator=(const FibonacciHeap& other) = default;	// TODO: implement
		FibonacciHeap & operator=(FibonacciHeap&& other) = default;	// TODO: implement

		T top() const {
			if (min_ == roots_.end()) {
				throw PriorityQueueEmpty();
			}

			return min_->data;
		}

		bool empty() const { return size_ == 0; }
		int size() const { return size_; }

		void push(const T& elem) {}	// TODO: implement
		void push(T&& elem) {}	// TODO: implement
		void pop() {
			if (min_ == roots_.end()) {
				throw PriorityQueueEmpty();
			}

			// TODO: pop min_
		}

		void merge(FibonacciHeap& other) {}	// TODO: implement

		void clear() {}	// TODO: implement

	private:

		struct Node {
			T data = T();
			std::list<Node> children;
			typename std::list<Node>::iterator current = children.end();
			typename std::list<Node>::iterator father = children.end();
		};

		int size_ = 0;

		std::list<Node> roots_;
		typename std::list<Node>::iterator min_ = roots_.end();

	}; // end class FibonacciHeap

	FibonacciHeap fibonacci_heap_;

};	// end class PriorityQueue

#endif
