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
	top100 = *new vector<Mark<string>>(20);
	top1000 = *new vector<Mark<string>>(20);
	theRest = *new vector<Mark<string>>(20);
	string line;
	ifstream file;
	

	file.open("top100.txt");
	if (file.is_open()) {
		while (!file.eof())
		{
			getline(file, line);
			line = toLower(line);
			cout << line << endl;
			insertAlpha(line, 0);
			
		}
	}
	file.close();

	file.open("top1000.txt");
		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, line);
				line = toLower(line);
				insertAlpha(line, 100);
			}
		}
	file.close();
	
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

void Dictionary::insertAlpha(string word, int after)
{
	Mark<string>* mark = new Mark<string>();
	int length = word.length();
	if (length > 20) length = 20;
	Node<string>* temp;
	bool found = false;
	int index = -1;
	if (after == 0) {
		cout << top100[length - 1].index << endl;
		if (words->isEmpty()) {
			temp = words->pushNode(word);
			index = 0;
			mark = new Mark<string>(temp, 0);
			top100[length - 1] = *mark;
		}
		else if (top100[length - 1].index == -1) {
			for (int i = length - 2; i >= 0; i--) {
				if (top100[i].index != -1) {
					words->moveCursorTo(top100[i]);
					while (true) {
						if (words->getCursor().point->data.length() > (unsigned) (i + 1)) {
							temp = words->insertBefore(words->getCursor().point, word);
							index = words->getCursor().index - 1;
							mark = new Mark<string>(temp, index);
							top100[length - 1] = *mark;
							
							break;
						}
						if (words->getCursor().point == words->getTail()) {
							temp = words->appendNode(word);
							index = words->getCursor().index + 1;
							mark = new Mark<string>(temp, index);
							top100[length - 1] = *mark;
							break;
						}
						words->moveCursorRight(1);
					}
					found = true;
					break;
				}
			}
			if (!found) {
				temp = words->pushNode(word);
				index = 0;
				mark = new Mark<string>(temp, index);
				top100[length - 1] = *mark;
			}
		}
		else {
			int end;
			if (top100[length].index == -1) {
				while (words->moveCursorRight(1)) {
					if (words->getCursor().point->data.length() != length - 1) {
						words->moveCursorLeft(1);
						break;
					}
				}
				end = words->getCursor().index;
			}
			else end = top100[length].index;
			if (insertAlpha(&word, top100[length - 1].index, end)) {
				Mark<string> cursor = words->getCursor();
				index = cursor.index - 1;
				if (cursor.point == top100[length - 1].point) {
					top100[length - 1].point = cursor.point->prev;
					top100[length - 1].index = index;
				}
			}
			else index = words->getCursor().index + 1;
		}
		cout << index << endl;
		
		for (Mark<string> m : top100) if (m.index > index) m.index++;
	}
	if (after = 100) {
		if (top1000[length - 1].index == -1)	{
			for (int i = length - 2; i >= 0; i--) {
				if (!(top1000[i].index == -1)) {
					words->moveCursorTo(top1000[i]);
					while (true) {
						if (words->getCursor().point->data.length() > (unsigned)(i + 1)) {
							temp = words->insertBefore(words->getCursor().point, word);
							index = words->getCursor().index - 1;
							mark = new Mark<string>(temp,index);
							top1000[length - 1] = *mark;
							break;
						}
						if (words->getCursor().point == words->getTail()) {
							temp = words->appendNode(word);
							index = words->getCursor().index + 1;
							mark = new Mark<string>(temp,index);
							top1000[length - 1] = *mark;
							break;
						}
						words->moveCursorRight(1);
					}
					found = true;
					break;
				}	
			}
			if (!found) {
				temp = words->appendNode(word);
				index = words->getSize() - 1;
				mark = mark = new Mark<string>(temp, index);
				top1000[length - 1] = *mark;
			}
		}
		else {
			int end;
			if (top1000[length].index == -1) {
				while (words->moveCursorRight(1)) {
					if (words->getCursor().point->data.length() != length - 1) {
						words->moveCursorLeft(1);
						break;
					}
				}
				end = words->getCursor().index;
			} 
			else end = top1000[length].index;

			if (insertAlpha(&word, top1000[length - 1].index, end)) {
				Mark<string> cursor = words->getCursor();
				index = cursor.index - 1;
				if (cursor.point == top100[length - 1].point) {
					top1000[length - 1].point = cursor.point->prev;
					top1000[length - 1].index = cursor.index - 1;
				}
			}
			else index = words->getCursor().index + 1;
		}

		for (Mark<string> m : top1000) if (m.index > index) m.index++;
	}

	if (after = 1000) {
		if (theRest[length - 1].index == -1) {
			for (int i = length - 2; i >= 0; i--) {
				if (!(theRest[i].index == -1)) {
					words->moveCursorTo(theRest[i]);
					while (true) {
						if (words->getCursor().point->data.length() > (unsigned)(i + 1)) {
							temp = words->insertBefore(words->getCursor().point, word);
							index = words->getCursor().index - 1;
							mark = new Mark<string>(temp, index);
							theRest[length - 1] = *mark;
							break;
						}
						if (words->getCursor().point == words->getTail()) {
							temp = words->appendNode(word);
							index = words->getCursor().index + 1;
							mark = new Mark<string>(temp, index);
							theRest[length - 1] = *mark;
							break;
						}
						words->moveCursorRight(1);
					}
					found = true;
					break;
				}
			}
			if (!found) {
				temp = words->appendNode(word);
				index = words->getSize() - 1;
				mark = mark = new Mark<string>(temp, index);
				theRest[length - 1] = *mark;
			}
		}
		else {
			int end;
			if (theRest[length].index == -1) {
				while (words->moveCursorRight(1)) {
					if (words->getCursor().point->data.length() != length - 1) {
						words->moveCursorLeft(1);
						break;
					}
				}
				end = words->getCursor().index;
			}
			else end = theRest[length].index;
			if (insertAlpha(&word, theRest[length - 1].index, end)) {
				Mark<string> cursor = words->getCursor();
				index = cursor.index - 1;
				if (cursor.point == top100[length - 1].point) {
					theRest[length - 1].point = cursor.point->prev;
					theRest[length - 1].index = cursor.index - 1;
				}
			}
			else index = words->getCursor().index + 1;
		}
	}
}

bool Dictionary::insertAlpha(string *word, int start, int end)
{
	int compare;
	if (start != end) {
		int midpoint = (end + start) / 2;
		words->moveCursorTo(midpoint);
		compare = word->compare(words->getCursor().point->data);
		if (compare < 0)
		{
			return insertAlpha(word, start, midpoint - 1);
		}
		else if (compare > 0)
		{
			return insertAlpha(word, midpoint + 1, end);
		}
	}
	else {
		words->moveCursorTo(start);
		compare = word->compare(words->getCursor().point->data);
		if (compare < 0) {
			words->insertBefore(words->getCursor().point, *word);
			return true;
		}
		else if (compare > 0) {
			words->insertAfter(words->getCursor().point, *word);
			return false;
		}
	}
	return false;
}

void Dictionary::print()
{
	words->print();
}