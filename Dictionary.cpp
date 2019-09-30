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
	

	file.open("top100.txt");
	if (file.is_open()) {
		while (!file.eof())
		{
			getline(file, line);
			line = toLower(line);
			length = line.length();
			if (length > 20) length = 20;
			insertAlpha(&line, &top100[length - 1]);
		}
	}
	
	file.close();
	
	for (int i = 0; i < 20; i++) {
		words->addList(&top100[i]);
	}

	file.open("top1000.txt");
	if (file.is_open()) {
		while (!file.eof())
		{
			getline(file, line);
			line = toLower(line);
			length = line.length();
			if (length > 20) length = 20;
			insertAlpha(&line, &top1000[length - 1]);
		}
	}

	file.close();

	for (int i = 0; i < 20; i++) {
		words->addList(&top1000[i]);
	}

	
	

	//file.open("top1000.txt");
	//	if (file.is_open()) {
	//		while (!file.eof()) {
	//			getline(file, line);
	//			line = toLower(line);
	//			insertAlpha(line, 100);
	//		}
    //	}
	//file.close();
	
	//file.open(filename);
	//if (file.is_open()) {
	//	while (!file.eof()) {
	//		getline(file, line);
	//		line = toLower(line);
	//		if (!inTop100(line) && !inTop1000(line)) insertAlpha(line, 1000);
	//	}
	//}
}

string Dictionary::toLower(string word)
{
	for (char &c : word) c = toLower(c);
	return word;
}

char Dictionary::toLower(char c)
{
	if (c >= 'A' && c <= 'Z') c += 32;
	return c;
}

void Dictionary::insertAlpha(string *word, MyList<string> *list)
{
	if (list->isEmpty()) list->pushNode(*word);
	else insertAlpha(word, 0, list->getSize() - 1, list);
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

void Dictionary::print()
{
	words->print();
}