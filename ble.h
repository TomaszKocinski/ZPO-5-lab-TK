#ifndef ble_cpp
#define ble_cpp
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<iterator>
#include<Windows.h>
class OC:public std::vector<std::list<std::string>>{
public:
	void open(const char* filename);
	OC(const char* filename){
		open(filename);
	};
	OC() {};
	void write(std::ostream& out = std::cout);
	virtual void execute();
	~OC();
	virtual std::string GetName() {
		return "siema";
	}
};
struct GS {
	bool operator() (const std::string&, const std::string&) const;
};
using namespace std;

struct Timer
{
	Timer() 
	{
		Reset();
	}

	double GetElapsedTimeSecs()
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter( &now );

		LARGE_INTEGER span;
		span.QuadPart = now.QuadPart - m_startTime.QuadPart;

		LARGE_INTEGER freq;
		QueryPerformanceFrequency( &freq ) ;
		return (double)span.QuadPart /(double)freq.QuadPart;
	}

	void Reset()
	{
		QueryPerformanceCounter(&m_startTime);
	}

private:

	LARGE_INTEGER m_startTime;
};

struct ITask
{
	virtual ~ITask(){};
	virtual std::string GetName() = 0;
	virtual void execute() = 0;
};

template< class T >
class TimingTask : public T
{
	Timer timer_;
public:
	void execute() {
		timer_.Reset();
		T::execute();
		double t = timer_.GetElapsedTimeSecs();
		std::cout << "Task Duration: " << t << " seconds" << std::endl;
	}
};



template< class T >
class TaskAdapter : public ITask, public T {
public:
	virtual void execute() {
		T::execute();
	}
	virtual std::string GetName() {
		return T::GetName();
	}
};

template< class T >
class LoggingTask : public T {
public:
	void execute() {
		std::cout << "LOG: The task is starting - " << GetName().c_str() << std::endl;
		T::execute();
		std::cout << "LOG: The task has completed - " << GetName().c_str() << std::endl;
	}
};

#endif
