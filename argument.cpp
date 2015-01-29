#include <functional>
#include <vector>
#include <iostream>
#include "argument.hpp"

using namespace std;

void ArgParser::print_help() const {
	cout << "USAGE: main";
	for (const ArgComponent & arg: p_arglist) {
		cout << " " << arg.keyword;
	}
	for (const pair<string, ArgComponent> & arg: o_arglist) {
		if (arg.second.setDefault) {
			cout << " [" << arg.second.keyword << " " << arg.second.defaultValue << "]";
		} else {
			cout << " " << arg.second.keyword;
		}
	}
	cout << endl;
}
void ArgParser::parse(int argc, const char * argv[]) {
	try {
		__parse(argc, argv);
	} catch (const string & message) {
		print_help();
		cout << message << endl;
		exit(1);
	}
}

void ArgParser::__parse(int argc, const char * argv[]) {
	unsigned int p_arglist_parsed = 0;
	for (int i = 1; i < argc; i++) {
		const string temp(argv[i]);
		if (o_arglist.find(temp) != o_arglist.end()) {
			if (i + 1 >= argc) {
				throw temp + " require argument";
			}
			o_arglist[temp].isActive = true;
			o_arglist[temp].handler(string(argv[i+1]));
		} else {
			if (p_arglist_parsed == p_arglist.size()) {
				throw "exceed positional argument limit";
			}
			p_arglist[p_arglist_parsed].isActive = true;
			p_arglist[p_arglist_parsed].handler(temp);
			p_arglist_parsed += 1;
		}
	}

	for (const ArgComponent & arg: p_arglist) {
		if (!arg.isActive) {
			throw "positional argument " + arg.keyword + " required";
		}
	}
	for (const pair<string, ArgComponent> & arg: o_arglist) {
		if (!arg.second.isActive) {
			if (arg.second.setDefault) {
				arg.second.handler(arg.second.defaultValue);
			} else {
				throw "keyword arguemnt " + arg.second.keyword + " required";
			}
		}
	}
}
void ArgParser::add_p(const string & keyword, const ParameterHandler & handler) {
	ArgComponent a;
	a.handler = handler;
	a.keyword = keyword;
	p_arglist.push_back(a);
}
void ArgParser::add_o(const string & keyword, const ParameterHandler & handler) {
	ArgComponent a;
	a.keyword = keyword;
	a.handler = handler;
	o_arglist.insert({keyword, a});
}
void ArgParser::add_o(const string & keyword, const ParameterHandler & handler, const string & defaultValue) {
	ArgComponent a;
	a.keyword = keyword;
	a.handler = handler;
	a.defaultValue = defaultValue;
	a.setDefault = true;
	o_arglist.insert({keyword, a});
}
