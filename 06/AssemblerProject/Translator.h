#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_

#include <string>
#include <unordered_map>
#include <cassert>
#include <iostream>
using namespace std;

class Translator {
private:
	unordered_map<string, uint16_t> 	opcodes_;
	unordered_map<string, uint16_t> 	jumps_;
	unordered_map<string, uint16_t> 	dests_;
	uint16_t 						stack_pointer_;
	unordered_map<string, uint16_t> 	symbol_table_;
public:
	Translator();
	virtual ~Translator();
	int comp(const string&) const;
	int dest(const string&) const;
	int jump(const string&) const;
};

#endif /* TRANSLATOR_H_ */
