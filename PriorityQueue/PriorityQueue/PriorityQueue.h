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
	PriorityQueue() = default;

	~PriorityQueue() = default;

	PriorityQueue(const PriorityQueue & other) = default;
	PriorityQueue(PriorityQueue && other) = default;

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

	void merge(const PriorityQueue & other) {
		fibonacci_heap_.merge(other.fibonacci_heap_);
	}

	void merge(PriorityQueue && other) {
		fibonacci_heap_.merge(other.fibonacci_heap_);
	}
	
	void clear() {
		fibonacci_heap_.clear();
	}
	
private:

	class FibonacciHeap {  // NOLINT(hicpp-special-member-functions, cppcoreguidelines-special-member-functions)
	public:
		FibonacciHeap() = default;

		~FibonacciHeap() {
			clear();
		}

		FibonacciHeap(const FibonacciHeap& other) = default;
		FibonacciHeap(FibonacciHeap&& other) = default;

		T top() const {
			if (min_ == roots_.end()) {
				throw PriorityQueueEmpty();
			}

			return (*min_)->data;
		}

		bool empty() const { return size_ == 0; }

		int size() const { return size_; }

		void push(const T& elem) {
			auto *new_node = new Node(elem);
			roots_.insert(min_, new_node);
			size_++;
			if (roots_.size() == 1) {
				min_ = roots_.begin();
				return;
			}

			if (cmp_(elem, (*min_)->data)) {
				--min_;
			}

		}

		void push(T&& elem) {
			auto *new_node = new Node(elem);
			roots_.insert(min_, new_node);
			size_++;
			if (roots_.size() == 1) {
				min_ = roots_.begin();
				return;
			}

			if (cmp_(elem, min_->data)) {
				--min_;
			}

		}

		void pop() {
			if (min_ == roots_.end()) {
				throw PriorityQueueEmpty();
			}

			roots_.splice(min_, (*min_)->children);
			min_ = roots_.erase(min_);
			if (!roots_.empty()) {
				consolidate();
			}

			size_--;
		}

		void merge(FibonacciHeap& other) {
			auto it_min_old = min_;
			if (min_ != roots_.end() || (other.min_ != other.roots_.end() && cmp_(min_->data, other.min_->data))) {
				min_ = other.min_;
			}

			size_ += other.size();

			roots_.splice(it_min_old, other.roots_);
			other.size_ = 0;
			other.min_ = other.roots_.end();
		}

		void clear() {
			for (auto & root : roots_) {
				delete root;
			}

			roots_.clear();
			size_ = 0;
			min_ = roots_.end();
		}

	private:

		struct Node {  // NOLINT(cppcoreguidelines-special-member-functions, hicpp-special-member-functions)
			explicit Node(T value) : data(value) {}

			~Node() {
				for (auto & child : children) {
					delete child;
				}

			}

			T data;
			std::list<Node*> children;
			// typename std::list<Node>::iterator father;	// not used (possible implementation later)
			// bool mark = false;	// not used (possible implementation later)
		};

		void consolidate() {
			std::vector<typename std::list<Node*>::iterator> arr;
			auto size = static_cast<int>(log2(size_) + 2);
			arr.reserve(size);
			for (auto i = 0; i < size; i++) {
				arr.push_back(roots_.end());
			}

			for (auto it = roots_.begin(); it != roots_.end(); ++it) {
				auto x = it;
				int degree = (*it)->children.size();
				while (arr[degree] != roots_.end()) {
					auto y = arr[degree];
					if (cmp_((*y)->data, (*x)->data)) {
						std::swap(*x, *y);
					}

					(*x)->children.insert((*x)->children.begin(), *y);
					roots_.erase(y);

					arr[degree] = roots_.end();
					degree++;
				}

				arr[degree] = x;
			}
			
			min_ = roots_.begin();
			for (auto it = roots_.begin(); it != roots_.end(); ++it) {
				if (cmp_((*it)->data, (*min_)->data)) {
					min_ = it;
				}

			}
			
		}

		Compare cmp_ = Compare();

		int size_ = 0;

		std::list<Node*> roots_;
		typename std::list<Node*>::iterator min_ = roots_.end();

	}; // end class FibonacciHeap

	FibonacciHeap fibonacci_heap_;

};	// end class PriorityQueue

#endif
