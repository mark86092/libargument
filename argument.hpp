#ifndef __ARGUMENT_HPP__
#define __ARGUMENT_HPP__

#include <functional>
#include <vector>
#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef function<void(string)> ParameterHandler;
struct ArgComponent {
	// the argument keyword, eg: --sum, input ...
	string keyword;
	// the handler function void(string)
	ParameterHandler handler;
	// check whether active after parse
	bool isActive;
	// the default value
	string defaultValue;
	// whether enable default value
	bool setDefault;
	string description = "";
	ArgComponent() {
		isActive = false;
		setDefault = false;
	}
};
class ArgParser {
	private:
		vector<ArgComponent> p_arglist;
		map<string, ArgComponent> o_arglist;
		void __parse(int argc, const char * argv[]);
	public:
		void print_help() const;
		void parse(int argc, const char * argv[]);
		// a positional argument
		void add_p(const string & keyword, const ParameterHandler & handler);
		// a keyword argument
		void add_o(const string & keyword, const ParameterHandler & handler);
		// a keyword argument with default
		void add_o(const string & keyword, const ParameterHandler & handler, const string & defaultValue);
};

#endif