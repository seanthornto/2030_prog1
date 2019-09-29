#include <iostream>
#include "MyList.h"
#include "Dictionary.h"
using std::cin;
using std::cout;
using std::endl;

double avgComp(int size)
{
	if (size > 1) {
		if (size % 2 == 1) {
			return (1.0 / size) + ((size - 1.0) / size) * (avgComp((size - 1) / 2) + 1);
		}
		else {
			return (1.0 / size) + .5 * (avgComp(size / 2) + 1)  +  (.5 - (1.0 / size)) * (avgComp(size / 2 - 1) + 1);
		}
	}
	else return size;
		
}

int main()
{
	Dictionary *dictionary = new Dictionary("dictionary.txt");
	dictionary->print();
	return 0;
}