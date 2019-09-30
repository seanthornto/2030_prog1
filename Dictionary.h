#include "MyList.h"
#include<string>
#include<vector>
using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary {
	MyList<string> *words;
	MyList<string> top100[20];
	MyList<string> top1000[20];
	MyList<string> theRest[20];


public:
	Dictionary(string filename);
	//~Dictionary();	
	//bool inTop100(string word);
	//bool inTop1000(string word);
	//bool inTheRest(string word);
	//bool inDictionary(string word);
	void insertAlpha(string *word, MyList<string> *list);
	void insertAlpha(string* word, int start, int end, MyList<string>* list);
	string toLower(string word);
	char toLower(char c);
	void print();



};

#endif
