#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_

#include <string>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

class Translator {
private:
    unordered_map<string, string> 	opcodes_;
    unordered_map<string, string> 	jumps_;
    unordered_map<string, string> 	dests_;
    uint16_t stack_pointer_;
    unordered_map<string, string> 	symbol_table_;
public:
    Translator();
    ~Translator();
    string transA_Command(string);
    string transC_Command(string);
    string getComp(const string&) const;
    string getDest(const string&) const;
    string getJump(const string&) const;
    string getSymbolVal(string s);
    string intToStr(int i);
    uint16_t immediate(string s);
};

#endif /* TRANSLATOR_H_ */
