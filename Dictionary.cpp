#include "MyList.h"
#include "Dictionary.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

Dictionary::Dictionary(string filename)
{
	words = new MyList<string>();
	string line;
	ifstream file;
	int length;
	foundCompares = 0;
	notFoundCompares = 0;
	compares = 0;

	file.open("top100.txt");
	if (file.is_open()) {
		getline(file, line);			// Read each line and insert word into list according to length and first charcter
		while (!file.eof())
		{
			cleanWord(line);
			length = line.length();
			if (length > 20) length = 20;
			insertAlpha(&line, &top100[length - 1][line.at(0) - 97]);
			getline(file, line);
		}
		cleanWord(line);
		length = line.length();
		if (length > 20) length = 20;
		insertAlpha(&line, &top100[length - 1][line.at(0) - 97]);
	}
	file.close();

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 26; j++) {
			top100Mark[i][j].index = words->getSize();   //Set the corresponding marks to the heads of each list and add
			if (!top100[i][j].isEmpty()) {				 //each list to words.
				top100Mark[i][j].point = top100[i][j].getHead();
				words->addList(&top100[i][j]);
			}
		}
	}

	file.open("top1000.txt");
	if (file.is_open()) {
		getline(file, line);
		while (!file.eof())
		{
			cleanWord(line);
			length = line.length();
			if (length > 20) length = 20;
			insertAlpha(&line, &top1000[length - 1][line.at(0) - 97]);
			getline(file, line);
		}
		cleanWord(line);
		length = line.length();
		if (length > 20) length = 20;
		insertAlpha(&line, &top1000[length - 1][line.at(0) - 97]);
	}
	file.close();

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 26; j++) {
			top1000Mark[i][j].index = words->getSize();
			if (!top1000[i][j].isEmpty()) {
				top1000Mark[i][j].point = top1000[i][j].getHead();
				words->addList(&top1000[i][j]);
			}
		}
	}

	file.open(filename);
	if (file.is_open()) {
		getline(file, line);
		while (!file.eof())
		{
			cleanWord(line);
			length = line.length();						//Do as above but only insert word if it is not already in top100 or top1000
			if (length > 20) length = 20;
			if (!inTop100(line) && !inTop1000(line)) insertAlpha(&line, &theRest[length - 1][line.at(0) - 97]);
			getline(file, line);
		}
		cleanWord(line);
		length = line.length();
		if (length > 20) length = 20;
		if (!inTop100(line) && !inTop1000(line)) insertAlpha(&line, &theRest[length - 1][line.at(0) - 97]);
	}
	file.close();

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 26; j++) {
			theRestMark[i][j].index = words->getSize();
			if (!theRest[i][j].isEmpty()) {
				theRestMark[i][j].point = theRest[i][j].getHead();
				words->addList(&theRest[i][j]);
			}
		}
	}

	compares = 0;	//Resets compare value, since this will have changed from using find when constructing
}

void Dictionary::cleanWord(string &word)
{
	string result = "";
	for (char &c : word) {
		if ('a' <= c && c <= 'z') result += c;
		else if (c < 'A') {
			if ((c == 39) || ('0' <= c && c <= '9')) result += c;
		}
		else if (c <= 'Z') {
			toLower(c);
			result += c;
		}
	}
	word = result;
}

void Dictionary::toLower(char &c)
{
	c += 32;
}

void Dictionary::insertAlpha(string *word, MyList<string> *list)
{
	if (list->isEmpty()) list->pushNode(*word);
	else insertAlpha(word, 0, list->getSize() - 1, list);
	list->resetCursor();
}

void Dictionary::insertAlpha(string *word, int start, int end, MyList<string> *list)
{
	int compare;
	if (start < end) {
		int midpoint = (end + start) / 2;
		list->moveCursorTo(midpoint);
		compare = word->compare(list->getCursor().point->data);
		compares++;
		if (compare < 0)
		{
			return insertAlpha(word, start, midpoint - 1, list);
		}
		else if (compare > 0)
		{
			return insertAlpha(word, midpoint + 1, end, list);
		}
	}
	else {
		list->moveCursorTo(start);
		compare = word->compare(list->getCursor().point->data);
		compares++;
		if (compare < 0) {
			list->insertBefore(list->getCursor().point, *word);
		}
		else if (compare > 0) {
			list->insertAfter(list->getCursor().point, *word);
		}
	}
}

bool Dictionary::inTop100(string word)
{
	int length = word.length();
	if (length > 20) length = 20;
	if (top100[length - 1][word.at(0) - 97].isEmpty()) return false;
	int start = top100Mark[length - 1][word.at(0) - 97].index;
	int end;
	if (length < 20 || word.at(0) != 'z') end = top100Mark[length - 1][word.at(0) - 96].index - 1;
	else end = 99;
	if (end < start) return false;
	words->moveCursorTo(top100Mark[length - 1][word.at(0) - 97]);
	return find(&word, start, end);
	
}

bool Dictionary::inTop1000(string word)
{

	int length = word.length();
	if (length > 20) length = 20;
	if (top1000[length - 1][word.at(0) - 97].isEmpty()) return false;
	int start = top1000Mark[length - 1][word.at(0) - 97].index;
	int end;
	if (length < 20 || word.at(0) != 'z') end = top1000Mark[length - 1][word.at(0) - 96].index - 1;
	else end = 999;
	if (end < start) return false;
	words->moveCursorTo(top1000Mark[length - 1][word.at(0) - 97]);
	return find(&word, start, end);
}

bool Dictionary::inTheRest(string word)
{
	int length = word.length();
	if (length > 20) length = 20;
	if (theRest[length - 1][word.at(0) - 97].isEmpty()) return false;
	int start = theRestMark[length - 1][word.at(0) - 97].index;
	int end;
	if (length < 20 || word.at(0) != 'z') end = theRestMark[length - 1][word.at(0) - 96].index - 1;
	else end = words->getSize() - 1;
	if (end < start) return false;
	words->moveCursorTo(theRestMark[length - 1][word.at(0) - 97]);
	return find(&word, start, end);
}

bool Dictionary::inDictionary(string word)
{
	if (inTop100(word) || inTop1000(word) ||inTheRest(word)) {
		foundCompares += compares;
		compares = 0;
		return true;
	}
	else {
		notFoundCompares += compares;
		compares = 0;
		return false;
	}
}

bool Dictionary::find(string *word, int start, int end)
{
	int mid = (start + end) / 2;
	int range = end - start;
	Mark<string> cursor = words->getCursor();
	words->moveCursorTo(mid);
	cursor = words->getCursor();
	
	
	int compare = word->compare(cursor.point->data);
	compares++;

	if (range > 3) {
		if (compare > 0) return find(word, mid + 1, end);
		else if (compare < 0) return find(word, start, mid - 1);
		else return true;
	}

	else if (range == 3) {
		if (compare > 0) return find(word, mid + 1, end);
		else if (compare < 0) {
			compare = word->compare(cursor.point->prev->data);
			compares++;
			return (compare == 0);
		}
		else return true;
	}

	else if (range == 2) {
		if (compare > 0) {
			compare = word->compare(cursor.point->next->data);
			compares++;
			return (compare == 0);
		}
		else if (compare < 0) {
			compare = word->compare(cursor.point->prev->data);
			compares++;
			return (compare == 0);
		}
		else return true;
	}

	else if (range == 1) {
		if (compare == 0) return true;
		else {
			compare = word->compare(cursor.point->next->data);
			compares++;
			return (compare == 0);
		}
	}

	else return (compare == 0);
}