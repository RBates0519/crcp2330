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
        string asmFile;
        string jackFile;
    public:
        Parser();
        Parser(string);
        ~Parser();
        void translate();
        void decode();

};

#endif // PARSER_H
