
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
		temp+="siema jest blad, rozmiar jest ";
		temp+=amount;
		temp+="za pewne zostal on przepelniony";
		return temp;
	}
	string blad2(){
		string temp;
		temp+="siema jest blad, rozmiar jest ";
		temp+=amount;
		temp+="pewnie probowales wyjmowac z pustego stosu";
		return temp;
	}
};

template<typename T, int rozmiar>
class SzablonStosu{ 
	T stos[rozmiar];
	int top;
public:
	SzablonStosu() : top(0) {}
	void push(const T& i) {
		try{
			if(top==rozmiar)
				throw pierwszy(top);
		}catch(pierwszy arg){
			cout<<arg.blad();
		}
		stos[top++] = i;
	}
	T pop() {
		try{
			if(top==0)
				throw pierwszy(top);
		}catch(pierwszy arg){
			cout<<arg.blad2();
		}
		return stos[--top];
	}
};
template<typename T, int rozmiar>
class SzablonSprytnegoStosu {
	SzablonStosu<T, rozmiar> *sp;
public:
	SzablonSprytnegoStosu<T,rozmiar> *nast;

	SzablonSprytnegoStosu (): sp(0), nast(0) { };
	void push(const T& i) {
		try{
		}
		if (!sp) 
			sp = new SzablonStosu<T,rozmiar>;
		sp->push(i);
	};
	T pop() {
		if (sp)
			return sp->pop();
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

		// ... 
	};
	T pop() {
		// ...
		return T(); // ta linijka to "zaœlepka"
	};
};
int main() {

	//KontenerStos<string,100> K;
	SzablonStosu<string,100> K;
	ifstream fi("qv.txt");
	K.pop();
	// zape³nianie stosu
	string s;
	while (fi) {
		fi >> s; 
		K.push(s);
		fi.seekg(ios::beg);
		fi.clear();
	};

	// opró¿nianie stosu
	while (true)
		K.pop();

	system("pause");
	return 0;
}
