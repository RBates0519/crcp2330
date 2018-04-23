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
//	asmFile = jackFile= "AssemblerFiles/";


	string asmName = ".asm";
	string jackName = ".jack";
	//Make sure we have received a .asm file
//	if(fileName.find(asmName) != std::string::npos)
//	{
		//Save param fileName into class var asmFile
		asmFile = fileName;
		cout << "ASM file to translate: " << asmFile << endl;

		//Open fstream for input
		input.open(asmFile,ifstream::in);
		if(!input)
		{
			cout << asmFile << " could not be opened." << endl;
			exit(0);
		}

		//Save Prog.jack into jackFile from Prog.asm
//		jackFile = fileName.erase(fileName.find(asmName),string::npos);
//		jackFile.append(jackName);

		//Open fstream for output
		output.open(jackFile,ofstream::out);
		if(!output)
		{
			cout << jackFile << " could not be opened." << endl;
			exit(0);
		}
//	}
	//If not a .asm file
//	else
//	{
//		cout << "Not a valid file type." << endl;
//		exit(0);
//	}
}

Parser::~Parser()
{
    input.close();
}

void Parser::translate()
{
	cout << "Now translating " << asmFile << endl;
    while(true)
    {
        if( input.eof() ) break;
        decode();
    }
    cout << "Finished reading file!" << endl;
}


void Parser::decode()
{
	string field;
	getline(input,field);
	cout << "Read: " << field << endl;

}
