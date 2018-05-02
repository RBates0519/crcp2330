#include "Translator.h"
#include <iostream>
#include <string>
using namespace std;

//initialize translator maps with opcods, jump,
//and dest symbols
Translator::Translator() :
opcodes_({
	{"0",		0101010},
	{"1",		0111111},
	{"-1", 		0111010},
	{"D",		0001100},
	{"A",		0110000},
	{"!D", 		0001101},
	{"!A", 		0110001},
	{"-D", 		0001111},
	{"-A", 		0110011},
	{"D+1", 		0011111},
	{"A+1", 		0110111},
	{"D-1", 		0001110},
	{"A-1", 		0110010},
	{"D+A", 		0000010},
	{"D-A", 		0010011},
	{"A-D", 		0000111},
	{"D&A", 		0000000},
	{"D|A", 		0010101},
	// Comp. (a=1)
	{"M",		1110000},
	{"!M", 		1110001},
	{"-M", 		1110011},
	{"M+1", 		1110111},
	{"M-1", 		1110010},
	{"D+M", 		1000010},
	{"D-M", 		1010011},
	{"M-D", 		1000111},
	{"D&M", 		1000000},
	{"D|M", 		1010101}
}),

jumps_({
	{"", 	000},
	{"JGT", 	001},
	{"JEQ", 	010},
	{"JGE", 	011},
	{"JLT", 	100},
	{"JNE", 	101},
	{"JLE", 	110},
	{"JMP",	111}
}),

dests_({ 	// d1 d2 d3 0 0 0
	{"", 		000},
	{"M", 		001},
	{"D", 		010},
	{"MD", 		011},
	{"A", 		100},
	{"AM", 		101},
	{"AD", 		110},
	{"AMD",		111}
})
{
	//constructor body
}

Translator::~Translator() {
	// TODO Auto-generated destructor stub
}

int Translator::comp(const string& s) const {
	if (opcodes_.count(s))
		return opcodes_.at(s);
	cerr << "Error: '" << s << "' invalid operation." << endl;
	throw std::runtime_error("Invalid operation");
}

int Translator::dest(const string& s) const {
	if (dests_.count(s))
		return dests_.at(s);
	std::cerr << "Error: '" << s << "' invalid destination operand.";
	std::cerr << std::endl;
	throw std::runtime_error("Invalid destination");
}

int Translator::jump(const string& s) const {
	if (jumps_.count(s))
		return jumps_.at(s);
	std::cerr << "Error: '" << s << "' invalid jump mnemonic.";
	std::cerr << std::endl;
	throw std::runtime_error("Invalid jump");
}

