#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "PriorityQueue.h"
#include "FibonacciHeap.h"

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
	static const int menu_options = 6;
	std::string menu_options_msgs_[menu_options] =
	{
		"Exit program",
		"Create priority queue",
		"Check if priority queue is empty",
		"Get top element of priority queue",
		"Pop element from priority queue",
		"Push element to priority queue"
	};
	std::string menu_msg_ = "Select menu option: ";

	// TODO: pq with compare function

};

void PriorityQueueProgram::print_menu() {
	for (auto i = 1; i < menu_options; i++) {
		os_ << i << ". " << menu_options_msgs_[i] << std::endl;
	}

	os_ << "0. " << menu_options_msgs_[0] << std::endl;
	os_ << menu_msg_;
}

void PriorityQueueProgram::execute_option() {
	switch (menu_option_) {
	case 1:	// TODO: Create (new) pq (delete old)
		break;
	case 2:	// TODO: pq.empty()
		break;
	case 3:	// TODO: pq.top()
		break;
	case 4:	// TODO: pq.pop()
		break;
	case 5:	// TODO: pq.push()
		break;
	case 0:
		// TODO: deallocation of pq_
		is_running_ = false;
		break;
	default:
		break;
	}

	os_ << std::endl;
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



int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;

	// Testing part
	PriorityQueueProgram program;
	while (program.is_running()) {
		program.print_menu();
		program.read_menu_option();
		program.execute_option();
	}

	// Bencmarking part
	PriorityQueue<int> *pq = new FibonacciHeap<int>; // min pq
	std::vector<int> vec10, vec100, vec1000, vec10000, vec100000;
	load_test_ints_to_vecs(vec10, vec100, vec1000, vec10000, vec100000);
	// TODO: implement benchmarking

	delete pq;

	system("pause");
	return 0;
}
