#include "MyList.h"
#include<string>
#include<vector>
using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary {
	MyList<string> *words;				//The master list of words

	MyList<string> top100[20][26];		//
	MyList<string> top1000[20][26];		//Temporary lists to build words
	MyList<string> theRest[20][26];		//

	Mark<string> top100Mark[20][26];	//
	Mark<string> top1000Mark[20][26];	//Indexed pointers [x][y] pointing to first member of words with length x+1 and starting character y + 'a'
	Mark<string> theRestMark[20][26];	//

	int compares;			//Number of compares on current word being checked
	int foundCompares;		//Total number of compares on words that were found
	int notFoundCompares;	//Total number of compares on words that were not found


public:
	Dictionary(string filename);	//Constructor takes filename of file to be read into dictionary
	bool inTop100(string word);		//Returns true if word is in the top 100 english words used
	bool inTop1000(string word);	//Returns true if word is in the top 101 - 1000 english words used
	bool inTheRest(string word);	//Returns true if word is any other word in the dictionary
	bool inDictionary(string word);	//Returns true if one of the above three are true. Adds compares to foundCompares if true, otherwise adds to notFoundCompares.
	bool find(string *word, int start, int end);	//Returns true if the word is between indexes start and end. Performs recursive binary search. Increments compares with each use of string.compare(string)
	void insertAlpha(string *word, MyList<string> *list);	//Inserts word into list alphabetically, if it is already there, does nothing. Calls the function below
	void insertAlpha(string* word, int start, int end, MyList<string>* list);	//Called from above. Performs recursive binary search to find position of correct alphabetic insertion
	static void cleanWord(string &word);	//Removes all characters except letters, numbers, and apostrophes. Converts captial letters to lowercase
	static void toLower(char &c);			//Converts a char to lowercase
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
