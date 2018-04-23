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
	string asmName = ".asm";
	//Make sure we have received a .asm file
	if(fileName.find(asmName) != std::string::npos)
	{
		asmFile = fileName;
		cout << "ASM file to translate: " << asmFile << endl;

		input.open(asmFile,ifstream::in);
		if(!input)
		{
			cout << asmFile << " could not be opened." << endl;
			exit(0);
		}
	}
	//If not a .asm file
	else
	{
		cout << "Not a valid file type." << endl;
		exit(0);
	}
}

Parser::~Parser()
{
    input.close();
}

void Parser::translate()
{
    while(true)
    {
        if( input.eof() ) break;
        decode();
    }
}


void Parser::decode()
{
}
