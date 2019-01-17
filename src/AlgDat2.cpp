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

	cout << "      ." << endl;
	cout << "   _/ \\_" << endl;
	cout << "   \\     /" << endl;
	cout << "   /.'o'.\\" << endl;
	cout << "    .o.'." << endl;
	cout << "   .'.'o'." << endl;
	cout << "  o'.o.'.o." << endl;
	cout << " .'.o.'.'.o." << endl;
	cout << ".o.'.o.'.o.'." << endl;
	cout << "   [___]" << endl;
	cout << "    \\___/    " << endl;


	cout << "______________" << endl;
	cout << "To enter a word pair do as following:" << endl;
	cout << "Example: welt world" << endl;
	cout << "Use the command help to see all commands" << endl;
	cout << "______________" << endl;

	while (!isDone) {

		std::getline(cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		string word = "";
		string trans = "";
		stringstream stream;
		stream.str(input);
		stream >> word >> trans;

		if (trans == "") {

			if (word == "fill") {

				for (wordpair x : preList) {
					tree.insert(wordpair(x.first, x.second));
				}
				tree.print();
			} else if (word == "help") {

				cout << "[fill] -> for a prefilled list" << endl;
				cout
						<< "[word translation] -> to insert a word and a translation to the trie"
						<< endl;
				cout << "[show] -> for a visual of the trie" << endl;
				cout << "[clear] -> to erase all elements of the trie" << endl;
				cout << "[erase word] -> to erase a word and its translation"
						<< endl;
				cout << "[find word] -> to get the translation of the word"
						<< endl;
				cout << "[testfind] -> to test the find method" << endl;
				cout << "[end] -> to end the Programm without exception"
						<< endl;
				cout << "______________" << endl;

			} else if (word == "show") {
				cout << tree.toString() << endl;

			} else if (word == "clear") {
				tree.clear();
				if(tree.empty()){
					cout << "All elements have been erased from the trie!" << endl;
					cout << "The trie is empty now!!" << endl;
				}
				else {
					cout << "If you see this, something went worng. The trie isn't empty... sry..." << endl;
				}

			} else if (word == "testfind") {

				tree.insert(wordpair("erstens", "erstens"));
				tree.insert(wordpair("ersti", "ersti"));
				tree.insert(wordpair("ehsan", "ehsan"));
				tree.insert(wordpair("einsam", "einsam"));
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
				//tree.find(trans);
				cout << "Searching for the word " << "\"" << trans << "\"" << "..." << endl;

				if(tree.find(trans).getCurrent()->getvalueLeaf() == tree.begin().getCurrent()->getvalueLeaf()){
					cout << "closer" << endl;
				}



//				if(tree.find(trans).getCurrent()->getvalueLeaf() != trans){
//					cout << trans << endl;
//					cout << tree.find(trans).getCurrent()->getvalueLeaf() << endl;
//					cout << "I didn't find it. The Word \"" << trans << "\" does not exist within the trie!" << endl;
//				}
				cout << "This is what I found: " << tree.find(trans).getCurrent()->getvalueLeaf() << endl;
//				else{
//					cout << "This is what I found: " << tree.find(trans).getCurrent()->getvalueLeaf() << endl;
//				}
			} else if (word == "erase") {
				if(tree.erase(trans)){
					cout << "The word: " << trans << " has been erased!" << endl;
				}
				else {
					if(tree.find(trans).getCurrent()->getvalueLeaf() == trans){
						cout << "if you see this we messed up" << endl;
					}
					else{
						cout << "The word " << "\""<< trans << "\"" <<  " does not exist!!" << endl;
					}
				}

			} else if (word != "" && trans != "") {
				tree.insert(wordpair(word, trans));
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
