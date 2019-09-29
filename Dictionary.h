#include "MyList.h"
#include<string>
#include<vector>
using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary {
	MyList<string> *words;
	vector<Mark<string>> top100;
	vector<Mark<string>> top1000;
	vector<Mark<string>> theRest;


public:
	Dictionary(string filename);
	//~Dictionary();
	//bool inTop100(string word);
	//bool inTop1000(string word);
	//bool inTheRest(string word);
	//bool inDictionary(string word);
	void insertAlpha(string word, int after);
	bool insertAlpha(string *word, int after, int before);
	string toLower(string word);
	char toLower(char c);
	void print();



};

#endif
