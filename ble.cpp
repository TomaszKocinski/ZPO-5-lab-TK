#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<vector>
#include<list>
#include<iterator>
#include<windows.h>
#include "ble.h"
using namespace std;

void OC::open(const char* filename) {
	ifstream in(filename);
	string line;
	int i=1;
	

	this->resize(1);
	this->reserve(100000);
	iterator w=begin();

	while(getline(in, line)){
		if(line==""){ 
			continue;
		}
		this->resize(i++);
		istringstream iss(line);
		string word;
		while(iss >> word) {
			(*w).push_back(word);
		}
		w++;
	}
	w--;
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
OC::~OC(){
	cout<<"siemahh";
	vector::~vector();
	cout<<"shh";

	/// tak jak na dole jest chujowo, bo tylko element listy sie usuwaja, a potem jak sie chce wywolac destruktor wektora to jest blad bo chce jeszcze raz liste wywalic i ma blad dostepu
	/*iterator w=begin();
	list<string>::iterator ite=(*w).begin();;
	for(int i=0;w!=end();w++){
		(*w).~list();
	}*/
}
bool GS::operator()(const std::string& x, const std::string& y) const {
	return x.size()<y.size();
};