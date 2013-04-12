#ifndef FILES_H
#define FILES_H
#include "ht.h"
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::endl;
using std::boolalpha;

class files {
private:
	ofstream out;
	ifstream in;
	string command;
	string temp;
	ht<string>* hash;
public:
	files(const char* inName, const char* outName) {
		in.open(inName);
		out.open(outName);
		hash = new ht<string>();
	}
	~files() {
		in.close();
		out.close();
		delete hash;
	}
	void init() {
		while(in >> command)
			run(command);
	}
	void run(string command) {
		if(command == "clear") {
			clear();
		}
		else if(command == "add") {
			insert();
		}
		else if(command == "find") {
			find();
		}
		else if(command == "remove") {
			fremove();
		}
		else if(command == "print") {
			print();
		}
	}
	void clear() {
		delete hash;
		hash = new ht<string>();
		out << "clear" << endl;
	}
	void insert() {
		in >> temp;
		hash->add(temp);
		out << "add " << temp << endl;
	}
	void find() {
		in >> temp;
		out << "find " << temp << " " << boolalpha << hash->find(temp) << endl;
	}
	void fremove() {
		in >> temp;
		hash->remove(temp);
		out << "remove " << temp << endl;
	}
	void print() {
		out << "print" << endl << hash->print();
	}
};
#endif
