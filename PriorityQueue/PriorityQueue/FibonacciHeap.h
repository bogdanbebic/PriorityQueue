#pragma once
#ifndef _FIBONACCI_HEAP_H_
#define _FIBONACCI_HEAP_H_
#include <functional>

#include "PriorityQueue.h"

template<typename T, class Compare = std::less<T>>
class FibonacciHeap : public PriorityQueue<T, Compare> {
public:
	FibonacciHeap()
		: PriorityQueue<T, Compare>()
	{
		// TODO: implement
	}

	~FibonacciHeap() = default;	// TODO: implement

	FibonacciHeap(const FibonacciHeap& other) = default;	// TODO: implement
	FibonacciHeap(FibonacciHeap&& other) = default;	// TODO: implement

	FibonacciHeap & operator=(const FibonacciHeap& other) = default;	// TODO: implement
	FibonacciHeap & operator=(FibonacciHeap&& other) = default;	// TODO: implement

	T top() const override;

	bool empty() const override { return size_ == 0; }
	int size() const override { return size_; }

	void push(const T& elem) override;
	void push(T&& elem) override;
	void pop() override;

	void merge(FibonacciHeap<T, Compare>& other);

	void clear() override;

private:
	int size_ = 0;
	// TODO: implementation structure of heap
};


template <typename T, class Compare>
T FibonacciHeap<T, Compare>::top() const {
	return T();	// TODO: implement
}

template <typename T, class Compare>
void FibonacciHeap<T, Compare>::push(const T& elem) {
	// TODO: implement
}

template <typename T, class Compare>
void FibonacciHeap<T, Compare>::push(T&& elem) {
	// TODO: implement
}

template <typename T, class Compare>
void FibonacciHeap<T, Compare>::pop() {
	// TODO: implement
}

template <typename T, class Compare>
void FibonacciHeap<T, Compare>::merge(FibonacciHeap<T, Compare>& other) {
	// TODO: implement
	size_ += other.size();
}

template <typename T, class Compare>
void FibonacciHeap<T, Compare>::clear() {
	// TODO: implement
	size_ = 0;
}

#endif
