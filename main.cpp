
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<vector>
#include<list>
#include "ble.h"
int main(int argc, char* argv[]) {
	/*TaskAdapter<LoggingTask<TimingTask<OC>>> my_list;

	std::ofstream myfile ("example.txt");
	my_list.open("qv.txt");
	my_list->execute();
	my_list.write(myfile);*/

	
	
	typedef public TaskAdapter<LoggingTask<TimingTask<OC > > > task;
	task t;
	ITask* it = &t;
	std::ofstream myfile ("example.txt");
	t.open("quovadis.txt");
	it->execute();
	t.write(myfile);
	
	
	
	
	return 0;

}
