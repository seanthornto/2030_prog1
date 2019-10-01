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
	int i = 0;
	file.open("top100.txt");
	if (file.is_open()) {
		getline(file, line);
		while (!file.eof())
		{
			cleanWord(line);
			length = line.length();
			if (length > 20) length = 20;
			insertAlpha(&line, &top100[length - 1]);
			getline(file, line);
		}
		cleanWord(line);
		length = line.length();
		if (length > 20) length = 20;
		insertAlpha(&line, &top100[length - 1]);
	}
	
	file.close();
	for (int i = 0; i < 20; i++) {
		top100Mark[i].index = words->getSize();
		if (!top100[i].isEmpty()) {
			top100Mark[i].point = top100[i].getHead();
			words->addList(&top100[i]);
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
			insertAlpha(&line, &top1000[length - 1]);
			getline(file, line);
		}
		cleanWord(line);
		length = line.length();
		if (length > 20) length = 20;
		insertAlpha(&line, &top1000[length - 1]);
	}
	file.close();

	for (int i = 0; i < 20; i++) {
		top1000Mark[i].index = words->getSize();
		if (!top1000[i].isEmpty()) {
			top1000Mark[i].point = top1000[i].getHead();
			words->addList(&top1000[i]);
		}
	}


	file.open(filename);
	if (file.is_open()) {
		getline(file, line);
		
		while (!file.eof())
		{
			cleanWord(line);
			length = line.length();
			if (length > 20) length = 20;
			if (!inTop100(line) && !inTop1000(line)) insertAlpha(&line, &theRest[length - 1]);
			getline(file, line);
		}
		cleanWord(line);
		length = line.length();
		if (length > 20) length = 20;
		if (!inTop100(line) && !inTop1000(line)) insertAlpha(&line, &theRest[length - 1]);
	}
	file.close();
	

	for (int i = 0; i < 20; i++) {
		theRestMark[i].index = words->getSize();
		if (!theRest[i].isEmpty()) {
			theRestMark[i].point = theRest[i].getHead();
			words->addList(&theRest[i]);
		}
	}
	
	foundCompares = 0;
	notFoundCompares = 0;
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
	int start = top100Mark[length - 1].index;
	int end;
	if (length < 20) end = top100Mark[length].index - 1;
	else end = 99;
	if (end < start) return false;
	words->moveCursorTo(top100Mark[length - 1]);
	return find(&word, start, end);
}

bool Dictionary::inTop1000(string word)
{
	int length = word.length();
	if (length > 20) length = 20;
	int start = top1000Mark[length - 1].index;
	int end;
	if (length < 20) end = top1000Mark[length].index - 1;
	else end = 999;
	if (end < start) return false;
	words->moveCursorTo(top1000Mark[length - 1]);
	return find(&word, start, end);
}

bool Dictionary::inTheRest(string word)
{
	int length = word.length();
	if (length > 20) length = 20;
	int start = theRestMark[length - 1].index;
	int end;
	if (length < 20) end = theRestMark[length].index - 1;
	else end = words->getSize() - 1;
	if (end < start) return false;
	words->moveCursorTo(theRestMark[length - 1]);
	return find(&word, start, end);
}

bool Dictionary::inDictionary(string word)
{
	return inTop100(word) || inTop1000(word) || inTheRest(word);
}

bool Dictionary::find(string *word, int start, int end)
{
	int mid = (start + end) / 2;
	int range = end - start;
	
	words->moveCursorTo(mid);
	Mark<string> cursor = words->getCursor();
	
	int compare = word->compare(cursor.point->data);
	compares++;
	
	if (range > 3) {
		if (compare < 0) return find(word, start, mid - 1);
		else if (compare > 0) return find(word, mid + 1, end);
		else {
			foundCompares += compares;
			compares = 0;
			return true;
		}
	}

	else if (range == 3) {
		if (compare < 0) {
			compare = word->compare(cursor.point->prev->data);
			compares++;
			if (compare == 0) {
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
		else if (compare > 0) return find(word, mid + 1, end);
		else {
			foundCompares += compares;
			compares = 0;
			return true;
		}
	}

	else if (range == 2) {
		if (compare < 0) {
			compare = word->compare(cursor.point->prev->data);
			compares++;
			if (compare == 0) {
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
		else if (compare > 0) {
			compare = word->compare(cursor.point->next->data);
			compares++;
			if (compare == 0) {
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
		else {
			foundCompares += compares;
			compares = 0;
			return true;
		}
	}

	else if (range == 1) {
		if (compare == 0) {
			foundCompares += compares;
			compares = 0;
			return true;
		}
		else {
			compare = word->compare(cursor.point->next->data);
			compares++;
			if (compare == 0) {
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
	}
	else return compare == 0;
}