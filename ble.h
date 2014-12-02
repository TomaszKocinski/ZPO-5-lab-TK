#ifndef ble_cpp
#define ble_cpp
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<iterator>
class OC:public std::vector<std::list<std::string>>{
public:
	void open(const char* filename);
	OC(const char* filename){
		open(filename);
	};
	OC() {};
	void write(std::ostream& out = std::cout);
	void execute();
	~OC();
};
struct GS {
	bool operator() (const std::string&, const std::string&) const;
};
#endif
