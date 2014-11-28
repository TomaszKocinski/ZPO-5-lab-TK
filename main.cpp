
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<vector>
#include<list>
#include "ble.h"
int main(int argc, char* argv[]) {
	OC my_list;
	std::ofstream myfile ("example.txt");
	my_list.open("qv.txt");
	my_list.execute();
	my_list.write(myfile);

}
