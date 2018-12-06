//============================================================================
// Name        : AlgDat2.cpp
// Author      : Chris Magios, Alex Diekhof
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <tuple>
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
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	cout << "your a cunt. So lets start" << endl;
	Trie<string, string> tree;

	bool isDone = false;

	cout << "Example: welt world" << endl;
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
