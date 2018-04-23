using namespace std;
#include <clocale>
#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include <dirent.h>

#include "parser.h"

Parser::Parser()
{
}

Parser::Parser(string fileName)
{
	input.open(fileName,ifstream::in);
	if(!input)
	{
		cout << fileName << " could not be opened." << endl;
		exit(0);
	}
}

Parser::~Parser()
{
    input.close();
}
