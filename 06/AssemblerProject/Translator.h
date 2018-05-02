#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_

#include <unordered_map>
#include <string>
using namespace std;

class Translator {
private:
	unordered_map<string, int> opcodes_;
	unordered_map<string, int> jumps_;
	unordered_map<string, int> dests_;
public:
	Translator();
	virtual ~Translator();
	int comp(const string&) const;
	int dest(const string&) const;
	int jump(const string&) const;
};

#endif /* TRANSLATOR_H_ */
