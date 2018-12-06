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
#include "Trie.h"
using namespace std;
typedef pair<string, string> wordpair;

wordpair preList[] = {wordpair("distel", "cool"),wordpair("distanz", "distance"),wordpair("du","you"),wordpair("durch", "through"),};


void preFill(){

	for(wordpair x : preList){


		// insert x

	}
}



int main() {

	//Stuff I need in the Main

	Trie<string, string> tree;
	bool isDone = false;
	string input;


	//------------------------


	cout << "Welcome to the World trie?" << endl;
	cout << "	  /\_/\  (" << endl;
	cout << "	 ( ^.^ ) _)" << endl;
	cout << "	   \"/  (" << endl;
	cout << "	 ( | | )" << endl;
	cout << "	(__d b__)" << endl;

	cout << "To fill in a set of word type: fill" << endl;
	cout << "To enter a word pair do as following:" << endl;
	cout << "Example: welt world" << endl;
	cout << "Use the command show to have a visual of the trie" << endl;



	while(!isDone){

		std::getline(cin,input);
		input = std::transform(input.begin(), input.end(),input.begin(), ::tolower);
		// muss das verhalten von kuhaku pruefen wegen lowercase

		switch(input){

		case "fill":
			preFill();
			break;

		case "show":
			tree.toString();
			break;

		case "end" :
			isDone = true;
			tree.toString();
			break;

		default:
			string word;
			string trans;
			stringstream stream;
			stream.str(input);
			stream >> word >> trans;


			tree.insert(wordpair(word,trans));

			stream.clear();
			word.clear();
			trans.clear();
			cin.clear();

			break;

		}


	}






	while(!isDone){
		cout << "Please enter word pairs." << endl;
		string word;
		string trans;
		cin >> word >> trans;

		tree.insert(wordpair(word, trans));
		//deckt keinen flaschen input ab
		//insert()


	}



	return 0;
}
