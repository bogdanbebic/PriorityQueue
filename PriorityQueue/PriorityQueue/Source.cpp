#include <iostream>
#include <string>
#include "PriorityQueue.h"



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

	PriorityQueue<int> pq_;

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



int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;
	
	PriorityQueueProgram program;

	while (program.is_running()) {
		program.print_menu();
		program.read_menu_option();
		program.execute_option();
	}

	system("pause");
	return 0;
}
