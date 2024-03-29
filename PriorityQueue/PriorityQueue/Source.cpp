#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

#include "PriorityQueue.h"
#include <iomanip>

class Program {  // NOLINT(hicpp-special-member-functions, cppcoreguidelines-special-member-functions)
public:
	explicit Program(std::istream & is = std::cin, std::ostream & os = std::cout)
		: menu_option_(0)
		, is_running_(true)
		, is_(is)
		, os_(os)
	{
		// empty body
	}

	virtual ~Program() = default;

	bool is_running() const { return is_running_; }

	virtual void print_menu() = 0;

	void read_menu_option() {
		is_ >> menu_option_;
	}

	virtual void execute_option() = 0;

protected:
	int menu_option_;
	bool is_running_;
	std::istream & is_;
	std::ostream & os_;
};



class PriorityQueueProgram : public Program {
public:
	explicit PriorityQueueProgram(std::istream & is = std::cin, std::ostream & os = std::cout)
		: Program(is, os) 
	{
		// empty body
	}

	void print_menu() override;
	void execute_option() override;

private:
	static const int menu_options = 7;
	std::string menu_options_msgs_[menu_options] =
	{
		"Exit program",
		"Create priority queue",
		"Check if priority queue is empty",
		"Get top element of priority queue",
		"Pop element from priority queue",
		"Push element to priority queue",
		"Convert heap"
	};
	std::string menu_msg_ = "Select menu option: ";

	PriorityQueue<int> pq_min_;
	PriorityQueue<int, std::greater<>> pq_max_;
	bool is_min_heap_ = true;
	bool is_made_heap_ = false;
};

void PriorityQueueProgram::print_menu() {
	for (auto i = 1; i < menu_options; i++) {
		os_ << i << ". " << menu_options_msgs_[i] << std::endl;
	}

	os_ << "0. " << menu_options_msgs_[0] << std::endl;
	os_ << menu_msg_;
}


void PriorityQueueProgram::execute_option() {
	try {
		switch (menu_option_) {
		case 1:	// Create (new) pq (delete old)
			pq_min_.clear();
			pq_max_.clear();
			os_ << "Select type of heap (1 for min, 0 for max): ";
			is_ >> is_min_heap_;
			is_made_heap_ = true;
			break;
		case 2:	// pq.empty()
			if (is_made_heap_) {
				os_ << "Heap empty: " << std::boolalpha;
				if (is_min_heap_) {
					os_ << pq_min_.empty();
				}
				else {
					os_ << pq_max_.empty();
				}

				os_ << std::endl;
			}

			break;
		case 3:	// pq.top()
			if (is_made_heap_) {
				os_ << "Top element is: ";
				if (is_min_heap_) {
					os_ << pq_min_.top();
				}
				else {
					os_ << pq_max_.top();
				}

				os_ << std::endl;
			}

			break;
		case 4:	// pq.pop()
			if (is_made_heap_) {
				if (is_min_heap_) {
					pq_min_.pop();
				}
				else {
					pq_max_.pop();
				}

			}

			break;
		case 5:	// pq.push()
			if (is_made_heap_) {
				os_ << "Input int: ";
				int temp;
				is_ >> temp;
				if (is_min_heap_) {
					pq_min_.push(temp);
				}
				else {
					pq_max_.push(temp);
				}

			}

			break;
		case 6:	// convert heap
			if (is_made_heap_) {
				if (is_min_heap_) {
					is_min_heap_ = false;
					while (!pq_min_.empty()) {
						pq_max_.push(pq_min_.top());
						pq_min_.pop();
					}

				}
				else {
					is_min_heap_ = true;
					while (!pq_max_.empty()) {
						pq_min_.push(pq_max_.top());
						pq_max_.pop();
					}

				}

			}

			break;
		case 0:
			// deallocation of lists is implicit and implemented in STL
			is_running_ = false;
			break;
		default:
			break;
		}

		os_ << std::endl;
	}
	catch (PriorityQueueEmpty & ex) {
		os_ << ex.what() << std::endl << std::endl;
	}

}



void load_test_ints_from_file(std::vector<int> & vec, const std::string & path_to_file, const int number_of_ints) {
	std::ifstream is;
	is.open(path_to_file);
	vec.reserve(number_of_ints);
	for (auto i = 0; i < number_of_ints; i++) {
		int temp;
		is >> temp;
		vec.push_back(temp);
	}

	is.close();
}

void load_test_ints_to_vecs(
	std::vector<int> & vec10, 
	std::vector<int> & vec100, 
	std::vector<int> & vec1000, 
	std::vector<int> & vec10000, 
	std::vector<int> & vec100000) 
{
	load_test_ints_from_file(vec10, "./test_ints/test_10.txt", 10);
	load_test_ints_from_file(vec100, "./test_ints/test_100.txt", 100);
	load_test_ints_from_file(vec1000, "./test_ints/test_1000.txt", 1000);
	load_test_ints_from_file(vec10000, "./test_ints/test_10000.txt", 10000);
	load_test_ints_from_file(vec100000, "./test_ints/test_100000.txt", 100000);
}



std::chrono::duration<double> measure_time_push(PriorityQueue<int> & pq, std::vector<int> vec) {
	const auto start = std::chrono::system_clock::now();
	for (auto & elem : vec) {
		pq.push(elem);
	}
	
	const auto end = std::chrono::system_clock::now();
	const std::chrono::duration<double> elapsed = end - start;
	return elapsed;
}

std::chrono::duration<double> measure_time_pop(PriorityQueue<int> & pq) {
	const auto start = std::chrono::system_clock::now();
	while (!pq.empty()) {
		pq.pop();
	}

	const auto end = std::chrono::system_clock::now();
	const std::chrono::duration<double> elapsed = end - start;
	return elapsed;
}

int measure_steps_push(PriorityQueue<int> & pq, std::vector<int> vec) {
	auto steps = 0;

	for (auto & elem : vec) {
		pq.push(elem, steps);
	}

	return steps;
}

int measure_steps_pop(PriorityQueue<int> & pq) {
	auto steps = 0;

	while (!pq.empty()) {
		pq.pop(steps);
	}

	return steps;
}

void print_performance_table() {
	PriorityQueue<int> pq; // min pq
	std::vector<int> vec10, vec100, vec1000, vec10000, vec100000;
	load_test_ints_to_vecs(vec10, vec100, vec1000, vec10000, vec100000);

	std::cout << std::setprecision(7) << std::fixed;

	std::cout << "Elems  | sec(push) |  sec(pop)  | steps(push) | steps(pop)" << std::endl;
	std::cout << 10 << "     | " << measure_time_push(pq, vec10).count();
	std::cout << " |  " << measure_time_pop(pq).count();
	std::cout << " | " << measure_steps_push(pq, vec10);
	std::cout << "          | " << measure_steps_pop(pq);
	std::cout << std::endl;

	std::cout << 100 << "    | " << measure_time_push(pq, vec100).count();
	std::cout << " |  " << measure_time_pop(pq).count();
	std::cout << " | " << measure_steps_push(pq, vec100);
	std::cout << "         | " << measure_steps_pop(pq);
	std::cout << std::endl;

	std::cout << 1000 << "   | " << measure_time_push(pq, vec1000).count();
	std::cout << " |  " << measure_time_pop(pq).count();
	std::cout << " | " << measure_steps_push(pq, vec1000);
	std::cout << "        | " << measure_steps_pop(pq);
	std::cout << std::endl;

	std::cout << 10000 << "  | " << measure_time_push(pq, vec10000).count();
	std::cout << " |  " << measure_time_pop(pq).count();
	std::cout << " | " << measure_steps_push(pq, vec10000);
	std::cout << "       | " << measure_steps_pop(pq);
	std::cout << std::endl;

	std::cout << 100000 << " | " << measure_time_push(pq, vec100000).count();
	std::cout << " |  " << measure_time_pop(pq).count();
	std::cout << " | " << measure_steps_push(pq, vec100000);
	std::cout << "      | " << measure_steps_pop(pq);
	std::cout << std::endl;
}


int main() {
	std::cout << "Hello, World!" << std::endl;

	// Testing part
	PriorityQueueProgram program;
	while (program.is_running()) {
		program.print_menu();
		program.read_menu_option();
		program.execute_option();
	}

	// Bencmarking part
	print_performance_table();
	
	system("pause");
	return 0;
}
