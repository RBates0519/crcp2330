#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "translator.h"

using namespace std;

class Parser
{
    private:
        fstream input;
        fstream output;
        Translator translator;

        uint16_t stack_pointer_;
        unordered_map<string, string> 	symbol_table_;
        vector<string> symbol_names_;
    public:
        //Constructors
        Parser();
        Parser(string);
        ~Parser();

        //Reading functions
        void translate();
        void decode();

        void rmvWhiteSpace(string&);
        bool isComment(string&) const;

        bool isSymbol(string s);

};

#endif // PARSER_H
