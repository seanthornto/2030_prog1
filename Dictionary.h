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
	Mark<string> top100Mark[20];
	Mark<string> top1000Mark[20];
	Mark<string> theRestMark[20];
	int compares;
	int foundCompares;
	int notFoundCompares;


public:
	Dictionary(string filename);
	//~Dictionary();	
	bool inTop100(string word);
	bool inTop1000(string word);
	bool inTheRest(string word);
	bool inDictionary(string word);
	bool find(string *word, int start, int end);
	void insertAlpha(string *word, MyList<string> *list);
	void insertAlpha(string* word, int start, int end, MyList<string>* list);
	static void cleanWord(string &word);
	static void toLower(char &c);
	void print()
	{
		words->print();
	}
	int getFoundCompares() 
	{
		return foundCompares;
	}
	int getNotFoundCompares()
	{
		return notFoundCompares;
	}
	int getSize()
	{
		return words->getSize();
	}
};

#endif
