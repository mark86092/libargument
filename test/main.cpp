#include <iostream>
#include "argument.hpp"

using namespace std;

class Parameter: public ArgParser {
	public:
		int value;
		double sum;
	public:
		Parameter() {
			add_o("--value", [this](string arg){this->value = stoi(arg);}, "10");
			add_o("--sum", [this](string arg){this->sum = stod(arg);});
		}
};
int main(int argc, const char * argv[]) {
	Parameter param;
	param.parse(argc, argv);
	cout << param.value;
	cout << param.sum;
}
