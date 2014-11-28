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
	int i=0,j=1;
	
	this->resize(1);
	this->reserve(100000);

	for(iterator w=begin();getline(in, line);w++,i++){
		this->resize(j++);
		list<string>::iterator ite=w._Ptr->begin();
		istringstream iss(line);
		string word;
		while(iss >> word) {
			(*this)[i].insert(ite,word);
		}
	}
};
void OC::write(ostream& out) {
	int i=0;
	for(iterator w=begin();w!=end();w++){
		int j=0;
		out<<">>"<<i++<<"<<\n";
		for(list<string>::iterator ite=w._Ptr->begin(), end =w._Ptr->end() ; ite != end;ite++){
			out<<j++<<": ";
			out<<ite._Ptr->_Myval<<'\n';
		}
	}
};
void OC::execute(){
	int i=0;
	for(iterator w=begin();w!=end();w++,i++){
		(*this)[i].sort(GS());
	}
}
bool GS::operator()(const std::string& x, const std::string& y) const {
		return x.size()<y.size();
};