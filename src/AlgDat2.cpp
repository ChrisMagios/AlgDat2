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

wordpair preList[] = { wordpair("durch", "through"), wordpair("distel",
		"distel"), wordpair("duda", "you"), wordpair("distanz", "distance"), };

int main() {

	//Stuff I need in the Main

	Trie<string> tree;
	bool isDone = false;
	string input;

	//------------------------

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
			for (wordpair x : preList) {
				tree.insert(wordpair(x.first, x.second), &tree.getRoot());
			}
			input.clear();
			cin.clear();
		}
		if (input == "show") {
			cout << tree.toString() << endl;
			input.clear();
			cin.clear();
		}
//		if (input == "clear") {
//			tree.clear();
//			if (tree.getRoot().getSonKnots().empty()) {
//				cout << "I erased all!!" << endl;
//			} else {
//				cout << "something went wrong.. erase no no" << endl;
//			}
//		}
		if (input == "testfind") {

			tree.insert(wordpair("erstens", "erstens"), &tree.getRoot());
			tree.insert(wordpair("ersti", "ersti"), &tree.getRoot());
			tree.insert(wordpair("ehsan", "ehsan"), &tree.getRoot());
			tree.insert(wordpair("einsam", "einsam"), &tree.getRoot());

			cout << "Test find einsam" << endl;
			tree.find("einsam");

			cout << "Test find troll" << endl;
			tree.find("troll");
			input.clear();
			cin.clear();
		}
		else if (input == "end") {
			isDone = true;
			cout << tree.toString() << endl;
		} else {
			string word = "";
			string trans = "";
			stringstream stream;
			stream.str(input);
			cout
					<< "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
					<< input << endl;
			stream >> word >> trans;

			if (word == "find") {
				tree.find(trans);
				input.clear();
				word.clear();
				trans.clear();
				stream.clear();
				cin.clear();
			} else if (word == "erase") {

				cout << "Erased? " << tree.erase(trans) << endl;
				cout << true << endl;
				tree.find(trans);
			} else if (word != "" && trans != "") {
				tree.insert(wordpair(word, trans), &tree.getRoot());
			} else {
				cout << "upps, somthing went wrong" << endl;
			}

			stream.clear();
			word.clear();
			trans.clear();
			cin.clear();

		}

		cin.clear();

	}
	return 0;
}
