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
    unordered_map<string, uint16_t> 	opcodes_;
    unordered_map<string, uint16_t> 	jumps_;
    unordered_map<string, uint16_t> 	dests_;
    uint16_t stack_pointer_;
    unordered_map<string, uint16_t> 	symbol_table_;
public:
    Translator();
    ~Translator();
    string transA_Command(string param);
    string transC_Command();
    int comp(const string&) const;
    int dest(const string&) const;
    int jump(const string&) const;
    string intToStr(int i);
};

#endif /* TRANSLATOR_H_ */
