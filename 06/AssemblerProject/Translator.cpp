#include "translator.h"
using namespace std;

//initialize translator maps with opcods, jump,
//and dest symbols
Translator::Translator() :
opcodes_({
    {"0",		"0101010"},
    {"1",		"0111111"},
    {"-1", 		"0111010"},
    {"D",		"0001100"},
    {"A",		"0110000"},
    {"!D", 		"0001101"},
    {"!A", 		"0110001"},
    {"-D", 		"0001111"},
    {"-A", 		"0110011"},
    {"D+1", 	"0011111"},
    {"A+1", 	"0110111"},
    {"D-1", 	"0001110"},
    {"A-1", 	"0110010"},
    {"D+A", 	"0000010"},
    {"D-A", 	"0010011"},
    {"A-D", 	"0000111"},
    {"D&A", 	"0000000"},
    {"D|A", 	"0010101"},
    {"M",       "1110000"},
    {"!M",      "1110001"},
    {"-M",      "1110011"},
    {"M+1", 	"1110111"},
    {"M-1", 	"1110010"},
    {"D+M",		"1000010"},
    {"D-M",		"1010011"},
    {"M-D",		"1000111"},
    {"D&M",		"1000000"},
    {"D|M",		"1010101"}
}),

jumps_({
    {"",        "000"},
    {"JGT", 	"001"},
    {"JEQ", 	"010"},
    {"JGE", 	"011"},
    {"JLT", 	"100"},
    {"JNE", 	"101"},
    {"JLE", 	"110"},
    {"JMP",     "111"}
}),

dests_({ 	// d1 d2 d3
    {"", 		"000"},
    {"M", 		"001"},
    {"D", 		"010"},
    {"MD", 		"011"},
    {"A", 		"100"},
    {"AM", 		"101"},
    {"AD", 		"110"},
    {"AMD",		"111"}
})
{
    //constructor body
}

Translator::~Translator()
{
}

string Translator::transA_Command(string a_com)
{
    int val = stoi(a_com);
    string out = "0";

    if ((val - 16384) >= 0)
    {
        val -= 16384;
        out += "1";
    }
    else
        out += "0";

    if ((val - 8192) >= 0)
    {
        val -= 8192;
        out += "1";
    }
    else
        out += "0";

    if ((val - 4096) >= 0)
    {
        val -= 4096;
        out += "1";
    }
    else
        out += "0";

    if ((val - 2048) >= 0)
    {
        val -= 2048;
        out += "1";
    }
    else
        out += "0";

    if ((val - 1024) >= 0)
    {
        val -= 1024;
        out += "1";
    }
    else
        out += "0";

    if ((val - 512) >= 0)
    {
        val -= 512;
        out += "1";
    }
    else
        out += "0";

    if ((val - 256) >= 0)
    {
        val -= 256;
        out += "1";
    }
    else
        out += "0";

    if ((val - 128) >= 0)
    {
        val -= 128;
        out += "1";
    }
    else
        out += "0";

    if ((val - 64) >= 0)
    {
        val -= 64;
        out += "1";
    }
    else
        out += "0";

    if ((val - 32) >= 0)
    {
        val -= 32;
        out += "1";
    }
    else
        out += "0";

    if ((val - 16) >= 0)
    {
        val -= 16;
        out += "1";
    }
    else
        out += "0";

    if ((val - 8) >= 0)
    {
        val -= 8;
        out += "1";
    }
    else
        out += "0";

    if ((val - 4) >= 0)
    {
        val -= 4;
        out += "1";
    }
    else
        out += "0";

    if ((val - 2) >= 0)
    {
        val -= 2;
        out += "1";
    }
    else
        out += "0";

    if ((val - 1) >= 0)
    {
        val -= 1;
        out += "1";
    }
    else
        out += "0";

    cout << "\e[1m\e[32mA command in binary is: \e[0m" << out << endl;
    return out;
}

string Translator::transC_Command(string c_com)
{
    c_com=c_com.substr(0,c_com.find(" ",0));
    string out = "111";
    string curr;
    string comp;
    string dest;
    string jump;

    //get opcode
    int equalSign = c_com.find("=", 0);
    int semi = c_com.find(";", 0);
    int len = semi - equalSign;
    curr = c_com.substr(equalSign + 1,len);
    comp = getComp(curr);
    cout << "\t\e[1mOpcode: \e[0m" << curr << endl;
    cout << "\t\e[1mComp bits are: \e[0m" << comp << endl;

    //get dest
    curr = c_com.substr(0, equalSign);
    dest = getDest(curr);
    cout << "\t\e[1mDest: \e[0m" << curr << endl;
    cout << "\t\e[1mDest bits are: \e[0m" << dest << endl;

    //get jump
    curr = c_com.substr(semi + 1, 3);

    int posOfSemi = c_com.find_first_of(";");
    //no semicolon in instruction
    if(posOfSemi == string::npos)
        curr = "";
    cout << "\t\e[1mJump: \e[0m" << curr << endl;
    jump = getJump(curr);
    cout << "\t\e[1mJump bits are: \e[0m" << jump << endl;


    out = out + comp + dest + jump;
    cout << "\e[1m\e[32mC command in binary is: \e[0m" << out << endl;
    return out;
}

string Translator::getComp(const string& s) const {
    if (opcodes_.count(s))
        return opcodes_.at(s);
    cerr << "Error: '" << s << "' invalid operation." << endl;
    throw runtime_error("Invalid operation");
}

string Translator::getDest(const string& s) const {
    if (dests_.count(s))
        return dests_.at(s);
    cerr << "Error: '" << s << "' invalid destination operand.";
    cerr << endl;
    throw runtime_error("Invalid destination");
}

string Translator::getJump(const string& s) const {
    if (jumps_.count(s))
        return jumps_.at(s);
    cerr << "Error: '" << s << "' invalid jump mnemonic.";
    cerr << endl;
    throw runtime_error("Invalid jump");
}
