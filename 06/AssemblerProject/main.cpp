#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <string>

#include "parser.h"
using namespace std;

/*
 * @project Project 6 - Assembler
 * @file    main.cpp
 * @author  Riley Bates
 * @brief   Translates assembly language into binary code.
 *
 * @date    4/2018
 */

/* Prog.asm file containing a valid Hack assembly language program
 * should be translated into the correct Hack binary code and stored in a Prog.hack file. */


// arg 1 - Prog.asm file to be assembled into binary code
int main(int argc, char **argv)
{
    if (argc < 1)
    {
            cout << "Error: no file is specified." << endl;
    }
    else
    {
        string inputFile = argv[1];
        Parser parser(inputFile);
        parser.translate();
    }

    return 0;
}
