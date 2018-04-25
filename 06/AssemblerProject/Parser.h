#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

class Parser
{
    private:
        fstream input;
        fstream output;
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

};

#endif // PARSER_H
