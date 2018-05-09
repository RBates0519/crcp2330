#include <clocale>
#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include <dirent.h>

#include "parser.h"

using namespace std;

Parser::Parser():
stack_pointer_(0x0010),

// Predefined symbols:
symbol_table_({
    {"SP",      "0x0"},
    {"LCL",     "0x1"},
    {"ARG",     "0x2"},
    {"THIS",    "0x3"},
    {"THAT",    "0x4"},
    {"R0",      "0x0"},
    {"R1",      "0x1"},
    {"R2",      "0x2"},
    {"R3",      "0x3"},
    {"R4",      "0x4"},
    {"R5",      "0x5"},
    {"R6",      "0x6"},
    {"R7",      "0x7"},
    {"R8",      "0x8"},
    {"R9",      "0x9"},
    {"R10",     "0xA"},
    {"R11",     "0xB"},
    {"R12",     "0xC"},
    {"R13",     "0xD"},
    {"R14",     "0xE"},
    {"R15",     "0xF"},
    {"SCREEN",  "0x4000"},
    {"KBD",     "0x6000"}
}),
symbol_names_({
    {"SP"},
    {"LCL"},
    {"ARG"},
    {"THIS"},
    {"THAT"},
    {"R0"},
    {"R1"},
    {"R2"},
    {"R3"},
    {"R4"},
    {"R5"},
    {"R6"},
    {"R7"},
    {"R8"},
    {"R9"},
    {"R10"},
    {"R11"},
    {"R12"},
    {"R13"},
    {"R14"},
    {"R15"},
    {"SCREEN"},
    {"KBD"}
})
{
}

Parser::Parser(string fileName):
stack_pointer_(0x0010),

// Predefined symbols:
symbol_table_({
    {"SP",      "0x0"},
    {"LCL",     "0x1"},
    {"ARG",     "0x2"},
    {"THIS",    "0x3"},
    {"THAT",    "0x4"},
    {"R0",      "0x0"},
    {"R1",      "0x1"},
    {"R2",      "0x2"},
    {"R3",      "0x3"},
    {"R4",      "0x4"},
    {"R5",      "0x5"},
    {"R6",      "0x6"},
    {"R7",      "0x7"},
    {"R8",      "0x8"},
    {"R9",      "0x9"},
    {"R10",     "0xA"},
    {"R11",     "0xB"},
    {"R12",     "0xC"},
    {"R13",     "0xD"},
    {"R14",     "0xE"},
    {"R15",     "0xF"},
    {"SCREEN",  "0x4000"},
    {"KBD",     "0x6000"}
}),
symbol_names_({
    {"SP"},
    {"LCL"},
    {"ARG"},
    {"THIS"},
    {"THAT"},
    {"R0"},
    {"R1"},
    {"R2"},
    {"R3"},
    {"R4"},
    {"R5"},
    {"R6"},
    {"R7"},
    {"R8"},
    {"R9"},
    {"R10"},
    {"R11"},
    {"R12"},
    {"R13"},
    {"R14"},
    {"R15"},
    {"SCREEN"},
    {"KBD"}
})
{
        cout << "\e[1m\e[34mASM file to translate: \e[0m" << fileName << endl;

        //Open fstream for input
        input.open(fileName,ifstream::in);
        if(!input)
        {
            cout << fileName << " could not be opened." << endl;
            exit(0);
        }

        //Save Prog.jack into jackFile from Prog.asm
        string outFile = fileName.erase(fileName.find(".txt"),string::npos);
        outFile.append(".jack");

        //Open fstream for output
        output.open(outFile,ofstream::out);
        if(!output)
        {
            cout << outFile << " could not be opened." << endl;
            exit(0);
        }
        else
            cout << "\e[1m\e[34mJack output file: \e[0m" << outFile << endl;
}

Parser::~Parser()
{
    input.close();
    output.close();
}

void Parser::translate()
{

    // Running through input file once to populate symbol table with user defined jump symbols
    int PC = 0;
    int RAMLocation = 16;
    string sym;
    while (getline(input, sym))
    {
        if ((sym.substr(0, 1) == "(") && !(isSymbol(sym.substr(1, sym.find(")", 0) - 1))))
        {
            symbol_table_[sym.substr(1, sym.find(")", 0) - 1)] = PC;
            symbol_names_.push_back(sym.substr(1, sym.find(")", 0) - 1));
        }
        if (sym.substr(0, 1) != "/" && sym.substr(0, 1) != "(" && sym.substr(0, 1) != "")
            PC++;
    }
    input.clear(); // clear bad state after eof
    input.seekg( 0 );

    // Running through input file again to populate symbol table with user defined variable symbols
    while (getline(input, sym))
    {
        if (sym.substr(0, 1) == "@")
        {
            bool first_is_dig = (sym.find_first_of( "0123456789" ) == 1);
            if (!(first_is_dig) && !(isSymbol(sym.substr(1, sym.find(" ", 0) - 1))))
            {
                symbol_table_[sym.substr(1, sym.length() - 1)] = RAMLocation;
                RAMLocation++;
                symbol_names_.push_back(sym.substr(1, sym.length() - 1));
            }
        }
    }
    input.clear(); // clear bad state after eof
    input.seekg( 0 );

    cout << "\e[1m\e[33mNow translating!\e[0m\n" << endl;
    while(true)
    {
        if( input.eof() ) break;
        decode();
    }
    cout << "\n\e[1m\e[33mFinished reading file!\e[0" << endl;
}


void Parser::decode()
{
    string command, hack_command;
    getline(input,command);

    rmvWhiteSpace(command);
    cout << "\n\e[1mInstruction is: \e[0m" << command << endl;

    // comments, blank line, or labels do nothing
    if (command.substr(0, 1) == "/" || command.substr(0, 1) == "" || command.substr(0, 1) == "(")
    {
        ;
    }
    // A command, call the A translation function
    else if (command.substr(0, 1) == "@")
    {
        bool has_only_digits = (command.find_first_not_of( "0123456789" ) == string::npos);
        //Ex: @17 or some number
        if (isdigit(command[1]))
        {
            //translate A command
            hack_command = translator.transA_Command(command.substr(1, command.length() - 1));
            output << hack_command << endl;
        }
        //@var
        else //user defined symbol
        {
            //translate
            string symbol = symbol_table_[(command.substr(1, command.length() - 1))];
            hack_command = translator.transA_Command(symbol);
            output << hack_command << endl;
        }
    }
    // C command, call the C translation function
    else
    {
        hack_command = translator.transC_Command(command);
        output << hack_command << endl;
    }

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

bool Parser::isComment(string& line) const {
    if (line.find("//") == 0)
        return true;
    else
        return false;
}

bool Parser::isSymbol(string s)
{
    for (int i = 0; i<symbol_names_.size(); i++) // linear search for the string, return 1 if it exists, return 0 if it doesn't
    {
        if (symbol_names_[i] == s)
            return 1;
    }
    return 0;
}
