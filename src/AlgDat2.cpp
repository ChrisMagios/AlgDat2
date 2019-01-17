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
		string word = "";
		string trans = "";
		stringstream stream;
		stream.str(input);
		stream >> word >> trans;
		cout << trans << endl;

		if (trans == "") {

			if (word == "fill") {

				for (wordpair x : preList) {
					tree.insert(wordpair(x.first, x.second), &tree.getRoot());
				}

			} else if (word == "show") {
				cout << tree.toString() << endl;

			} else if (word == "clear") {
				tree.clear();
				cout << "XX" << tree.getRoot().getSonKnots().size() << endl;
			} else if (word == "testfind") {

				tree.insert(wordpair("erstens", "erstens"), &tree.getRoot());
				tree.insert(wordpair("ersti", "ersti"), &tree.getRoot());
				tree.insert(wordpair("ehsan", "ehsan"), &tree.getRoot());
				tree.insert(wordpair("einsam", "einsam"), &tree.getRoot());
				cout << "Test find einsam" << endl;
				tree.find("einsam");
				cout << "Test find troll" << endl;
				tree.find("troll");
			}

			else if (word == "end") {
				isDone = true;
				cout << tree.toString() << endl;
			} else if (word != "") {
				cout << "sorry I don't understand" << endl;
			}

			input.clear();
			cin.clear();
		} else {

			if (word == "find") {
				tree.find(trans);
			} else if (word == "erase") {
				tree.erase(trans);
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
	}
	return 0;
}
