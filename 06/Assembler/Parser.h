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

        //Input/output file names
        string asmFile;
        string jackFile;
    public:
        //Constructors
        Parser();
        Parser(string);
        ~Parser();

        //Reading functions
        void translate();
        void decode();

};

#endif // PARSER_H
