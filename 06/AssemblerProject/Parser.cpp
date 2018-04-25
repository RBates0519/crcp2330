using namespace std;
#include <clocale>
#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include <dirent.h>

#include "Parser.h"

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
		cout << "ASM file to translate: " << fileName << endl;

		//Open fstream for input
		input.open(fileName,ifstream::in);
		if(!input)
		{
			cout << fileName << " could not be opened." << endl;
			exit(0);
		}

		//Save Prog.jack into jackFile from Prog.asm
//		string outFile = fileName.erase(fileName.find(asmName),string::npos);
		string outFile = fileName.erase(fileName.find(".txt"),string::npos);
		outFile.append(jackName);

		//Open fstream for output
		output.open(outFile,ofstream::out);
		if(!output)
		{
			cout << outFile << " could not be opened." << endl;
			exit(0);
		}
		else
			cout << "Opened: " << outFile << " for output!" << endl;
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
	cout << "////Now translating!\\\\\\\\\n" << endl;
    while(true)
    {
        if( input.eof() ) break;
        decode();
    }
    cout << "\\\\\\\\Finished reading file!////" << endl;
}


void Parser::decode()
{
	string field;
	getline(input,field);
	cout << "Read: " << field;

	rmvWhiteSpace(field);
	cout << "Line now holds: " << field << "\n" << endl;

}

void Parser::rmvWhiteSpace(string &line)
{
	const string blank_spaces = " \t\v\n\f\r";

	// Remove left white spaces
	line.erase(0, line.find_first_not_of(blank_spaces));

	// Remove right white spaces and comments
	size_t comment_pos = line.find("//");
	if (comment_pos != 0 && comment_pos != std::string::npos) {
			// There is a comment following a command.
			line.erase(line.find_first_of("//"), std::string::npos);
	}

	line.erase(line.find_last_not_of(blank_spaces)+1, std::string::npos);
}
