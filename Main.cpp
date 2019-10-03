#include "MyList.h"
#include "Dictionary.h"
#include "timer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

int foundWords = 0;
int notFoundWords = 0;
int skippedWords = 0;
int foundCompares = 0;
int notFoundCompares = 0;

Dictionary *dictionary;

vector<string> splitString(string line, char delim)
{
	vector<string> splitStrings;
	string word = "";
	for (char &c : line) {
		if (c == delim) {
			if (word != "") {
				splitStrings.push_back(word);
				word = "";
			}
		}
		else word += c;
	}
	if (word != "") splitStrings.push_back(word);
	return splitStrings;
}

bool startsLetter(string word)
{
	char firstChar = word.at(0);
	if ('a' <= firstChar && firstChar <= 'z') return true;
	return false;
}

void checkLine(vector<string> line)
{
	for (string str : line) {
		Dictionary::cleanWord(str);
		if (str == "");											//Do nothing if string is empty
		else if (!startsLetter(str)) skippedWords++;			//Skip word if string starts with a number
		else if (dictionary->inDictionary(str)) foundWords++;	//Check if word is in dictionary, increment values accordingly.
		else notFoundWords++;
	}
}

int main()
{
	Timer time;
	dictionary = new Dictionary("dict.random2.nodop");
	cout << endl << "dictionary size " << dictionary->getSize() << endl;

	ifstream file;
	string line;
	string word;
	vector<string> splitLine;

	time.Start(); 

	// ----------- SPELLCHECKING BEGINS HERE -----------
	file.open("book.txt");
	if (file.is_open()) {
		getline(file, line);
		while (!file.eof()) {
			splitLine = splitString(line, ' ');
			checkLine(splitLine);
			getline(file, line);
		}
		splitLine = splitString(line, ' ');
		checkLine(splitLine);
	}
	file.close();
	// ----------- SPELLCHECKING ENDS HERE -----------

	time.Stop();

	foundCompares = dictionary->getFoundCompares();
	notFoundCompares = dictionary->getNotFoundCompares();

	cout << "Done checking and these are the results" << endl;
	cout << "finished in time: " << time.Time() << endl;
	cout << "There are " << foundWords << " words found in the dictionary" << endl;
	cout << "     " << foundCompares << " compares. Average: " << foundCompares / foundWords << endl;
	cout << "There are " << notFoundWords << " words NOT found in the dictionary" << endl;
	cout << "     " << notFoundCompares << " compares. Average: " << notFoundCompares / notFoundWords << endl;
	cout << "There are " << skippedWords << " words not checked." << endl;



	return 0;
}





