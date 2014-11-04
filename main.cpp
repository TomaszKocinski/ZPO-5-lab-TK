
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class pierwszy:public exception{
public:
	int amount;
	pierwszy(int arg){
		amount=arg;
	}
	string blad(){
		string temp;
		temp+="siema jest blad, rozmiar jest";
		temp+=amount;
		temp+="za pewne zostal on przepelniony\n";
		return temp;
	}
	string blad2(){
		string temp;
		temp+="siema jest blad, rozmiar jest";
		temp+=amount;
		temp+="pewnie probowales wyjmowac z pustego stosu\n";
		return temp;
	}
};
class nextstack:public exception{public:nextstack(){}};
class closestack:public exception{public:closestack(){}};
class koniec:public exception{public:koniec(){}};

template<typename T, int rozmiar>
class SzablonStosu{ 
	T stos[rozmiar];
	int top;
public:
	SzablonStosu() : top(0) {}
	void push(const T& i) {
		if(top==rozmiar)
			throw pierwszy(top);
		stos[top++] = i;
	}
	T pop() {
		if(top==0)
			throw pierwszy(top);
		return stos[--top];
	}
};
template<typename T, int rozmiar>
class SzablonSprytnegoStosu {
	SzablonStosu<T, rozmiar> *sp;
public:
	SzablonSprytnegoStosu<T,rozmiar> *nast;
	SzablonSprytnegoStosu<T,rozmiar> *poprz;
	SzablonSprytnegoStosu (): sp(0), nast(0), poprz(0) { };
	void push(const T& i) {
		if (!sp) 
			sp = new SzablonStosu<T,rozmiar>;
		try{
			sp->push(i);
		}catch(pierwszy arg){
			cout<<arg.blad();
			throw nextstack();
		}
	};
	T pop() {
		try{
			if (sp)
				return sp->pop();
		}
		catch(pierwszy arg){
			cout<<arg.blad2();
			throw closestack();
		}
	};
	~SzablonSprytnegoStosu() {      
		delete sp; 
	};
};
template<typename T, int rozmiar>
class KontenerStos {
	SzablonSprytnegoStosu<T,rozmiar> *glowa;
	SzablonSprytnegoStosu<T,rozmiar> *wsk;
public:
	KontenerStos(): wsk(0) {
		glowa = new SzablonSprytnegoStosu<T,rozmiar>;
		wsk=glowa;
	};
	~KontenerStos() {
		wsk=glowa;
		while (wsk->nast!=NULL) {
			glowa=wsk->nast;
			delete wsk;
		};
		delete glowa;
	};
	void push(const T& i) {
		try{
			wsk->push(i);
		}
		catch(nextstack){
			wsk->nast=new SzablonSprytnegoStosu<T,rozmiar>;
			wsk->nast->poprz=wsk;
			wsk=wsk->nast;
			wsk->push(i);
		}
	};
	T pop() {
		try{
			wsk->pop();
		}
		catch(closestack){
			if(wsk->poprz){
				wsk=wsk->poprz;
				delete wsk->nast;
				wsk->nast=0;
				wsk->pop();
			}else{
				cout<<"probujesz pop przy pustym pustym stosie\n";
				throw koniec();
			}
		}
		return T(); 
	};
};
int main() {
	KontenerStos<string,3> K;
	ifstream fi("qv.txt");
	string s,t;
	try {
		while (fi) {
			fi >> s;
			t+=s;
			K.push(t);
			fi.seekg(ios::beg);
			fi.clear();
		}
	}
	catch (std::bad_alloc &ba) {
		cout << "bad_alloc caught: " << ba.what() << endl;
		cout << "Press ENTER to continue" << endl;
		cin.ignore();
	}
 
	fi.seekg(ios::beg);
	fi.clear();
	while (true)
		try{K.pop();
	}
	catch(...){
		break;
	}
	system("pause");
	return 0;
}
