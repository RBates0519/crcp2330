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

    public:
        Parser();
        Parser(string);
        ~Parser();
};

#endif // PARSER_H
