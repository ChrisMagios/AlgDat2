//============================================================================
// Name        : AlgDat2.cpp
// Author      : Chris Magios, Alex Diekhof
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include "Trie.h"
using namespace std;
typedef pair<string, string> wordpair;

wordpair preList[] = { wordpair("distel", "cool"), wordpair("distanz",
		"distance"), wordpair("du", "you"), wordpair("durch", "through"), };

void preFill() {

	for (wordpair x : preList) {



	}
}

int main() {

	//Stuff I need in the Main

	Trie<string> tree;
	bool isDone = false;
	string input;

	//------------------------

	cout << "Welcome to the World trie?" << endl;
	cout << "	  /\\_/\\  (" << endl;
	cout << "	 ( ^.^ ) _)" << endl;
	cout << "	   \\\"/  (" << endl;
	cout << "	 ( | | )" << endl;
	cout << "	(_d b_)" << endl;

	cout << "To fill in a set of word type: fill" << endl;
	cout << "Type end to end the program" << endl;
	cout << "Type show, to see the trie" << endl;
	cout << "To enter a word pair do as following:" << endl;
	cout << "Example: welt world" << endl;
	cout << "Use the command show to have a visual of the trie" << endl;

	while (!isDone) {

		std::getline(cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);

		if (input == "fill") {
			preFill();
		} else if (input == "show") {
			tree.toString();
		} else if (input == "end") {
			isDone = true;
			tree.toString();
		} else {
			string word = "";
			string trans = "";
			stringstream stream;
			stream.str(input);
			stream >> word >> trans;

			if (word == "" || trans == "") {
				cout << "upps, somthing went wrong" << endl;
				//savety first
				stream.clear();
				word.clear();
				trans.clear();
				cin.clear();
				//------------

			}

			tree.insert(wordpair(word, trans), &tree.getRoot());

			stream.clear();
			word.clear();
			trans.clear();
			cin.clear();

		}

	}
	return 0;
}
