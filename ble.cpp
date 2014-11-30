#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<vector>
#include<list>
#include<iterator>
#include "ble.h"
using namespace std;

void OC::open(const char* filename) {
	ifstream in(filename);
	string line;
	int i=1;
	
	this->resize(1);
	this->reserve(100000);

	for(iterator w=begin();getline(in, line);w++){
		this->resize(i++);
		istringstream iss(line);
		string word;
		while(iss >> word) {
			(*w).emplace_back(word);
		}
	}
};
void OC::write(ostream& out) {
	int i=0;
	for(iterator w=begin();w!=end();w++){
		int j=0;
		out<<">>"<<i++<<"<<\n";
		for(list<string>::iterator ite=w->begin();ite != w->end();ite++){
			out<<j++<<": "<<*ite<<'\n';
		}
	}
};
void OC::execute(){
	for(iterator w=begin();w!=end();w++){
		(*w).sort(GS());
	}
}
bool GS::operator()(const std::string& x, const std::string& y) const {
		return x.size()<y.size();
};