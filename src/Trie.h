/*
 * Trie.h
 *
 *  Created on: 30.11.2018
 *      Author: Chris
 */

#ifndef TRIE_H_
#define TRIE_H_
#include <stdio.h>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <list>
#include <vector>

class InnerKnot;
class TrieIterator;
class AbstractKnot;
using namespace std;
template<class T, class E = char>
class Trie {

	typedef basic_string<E> key_type; // string=basic_string<char>
	typedef pair<string, T> value_type;
	typedef T mapped_type;

public:

	Trie() {

	}

	// AbstractKnot class for easier inheritance
	class AbstractKnot {
	private:
		map<E, AbstractKnot*> son_knots;
	public:

		virtual void print(int level) = 0;
		virtual string toString(int level) = 0;
		map<E, AbstractKnot*>& getSonKnots() {
			return this->son_knots;
		}
		virtual ~AbstractKnot() {

		}
	};

	// Knot class for Trie knots, which do not have any value.
	class InnerKnot: public AbstractKnot {

	public:

		// Overrited abstract Class Method
		void print(int level) {
			string res;
			for (int i = 0; i < level; ++i) {
				res += ' ';
			}
			cout << res;
		}
		string toString(int level) {
			string res;
			for (int i = 0; i < level; ++i) {
				res += ' ';
			}
			return res;
		}

		InnerKnot() {

		}

		InnerKnot& operator =(AbstractKnot* knt) {
			this->getSonKnots() = knt->getSonKnots();
			return *this;
		}

		~InnerKnot() {

		}
	};
	// Knot class for Trie leafs, holding the value.
	class LeafKnot: public AbstractKnot {
	private:
		mapped_type valueLeaf;

	public:
		LeafKnot() {

		}

		LeafKnot(mapped_type word) :
				valueLeaf(word) {
		}
		void print(int level) {
			for (int i = 0; i < level; ++i) {
				cout << " ";
			}
			cout << " :" << valueLeaf << endl;
		}

		string toString(int level) {
			string res;
			for (int i = 0; i < level; ++i) {
				res += " ";
			}
			res += " :" + valueLeaf + "\n";
			return res;
		}
		mapped_type& getvalueLeaf() {
			return this->valueLeaf;
		}
		~LeafKnot() {

		}
	};

	class TrieIterator {
	private:
		stack<typename map<E, Trie<T, E>::AbstractKnot*>::iterator> stackOfCurrentLeaf;
		stack<typename map<E, Trie<T, E>::AbstractKnot*>::iterator> endOfSon;
		LeafKnot* current;
	public:
		typedef TrieIterator iterator;
		TrieIterator() :
				current(nullptr) {
		}

		TrieIterator(AbstractKnot* root) {
			// push root son Knots ontop of empty stack
			stackOfCurrentLeaf.push(root->getSonKnots().begin());
			endOfSon.push(root->getSonKnots().end());
			if (root->getSonKnots().find('\0') == root->getSonKnots().end()) {
				slideLeft();
			}
		}

		TrieIterator(const iterator& itr) :
				current(itr.current) {
			stackOfCurrentLeaf = itr.stackOfCurrentLeaf;
			endOfSon = itr.endOfSon;
		}

		TrieIterator(AbstractKnot* root, key_type& innerSeq) {
			stackOfCurrentLeaf.push(root->getSonKnots().begin());
			endOfSon.push(root->getSonKnots().end());
			for (unsigned int i = 0; i < innerSeq.length(); ++i) {

				if (stackOfCurrentLeaf.top()->second->getSonKnots().find(
						innerSeq[i])
						== stackOfCurrentLeaf.top()->second->getSonKnots().end()) {
					cout << "Die Sequenz konnte nicht gefunden werden." << endl;
					delete this;
				} else {
					stackOfCurrentLeaf.push(
							stackOfCurrentLeaf.top()->second->getSonKnots().find(
									innerSeq[i]));
					endOfSon.push(
							stackOfCurrentLeaf.top()->second->getSonKnots().end());
				}
			}
			current = nullptr;

		}

		string itToString() {
			stack<typename map<E, Trie<T, E>::AbstractKnot*>::iterator> tmpStack =
					stackOfCurrentLeaf;
			string res;
			list<string> resList;
			while (!tmpStack.empty()) {
				resList.push_back(tmpStack.top()->second->toString(tmpStack.size())+ tmpStack.top()->first + "\n");
				tmpStack.pop();
			}
			resList.reverse();

			for (string s : resList) {
				res += s;
			}
			res += current->toString(stackOfCurrentLeaf.size());

			return res;

		}
		stack<typename map<E, Trie<T, E>::AbstractKnot*>::iterator> getStackOfCurrentLeaf() {
			return this->stackOfCurrentLeaf;
		}
		iterator& operator =(const iterator& itr) {
			current = itr.current;
			return *this;
		}
		bool operator ==(const iterator& itr) {
			return current == itr.current;
		}
		bool operator !=(const iterator& itr) {
			return current != itr.current;
		}

		mapped_type& operator *() {
			return current->getvalueLeaf();
		}

		void popStacks() {
			stackOfCurrentLeaf.pop();
			endOfSon.pop();
		}
		void slideLeft() {
			// check if the next left element is a leaf.
			char leafToken = '\0';
			cout << "FIRST: " << (*stackOfCurrentLeaf.top()).first
					<< " SECOND: " << (*stackOfCurrentLeaf.top()).second
					<< endl;
			while (((*stackOfCurrentLeaf.top()).second->getSonKnots().find(
					leafToken)
					== (*stackOfCurrentLeaf.top()).second->getSonKnots().end())) {
				// push It of begin and end of the same map to the stacks.
				cout << "FIRST: "
						<< (*stackOfCurrentLeaf.top()).second->getSonKnots().begin()->first
						<< " SECOND: "
						<< (*stackOfCurrentLeaf.top()).second->getSonKnots().begin()->second
						<< endl;


				stackOfCurrentLeaf.push(
						(*stackOfCurrentLeaf.top()).second->getSonKnots().begin());

				endOfSon.push(
						(*stackOfCurrentLeaf.top()).second->getSonKnots().end());

			}

			current =
					(LeafKnot*) (*stackOfCurrentLeaf.top()).second->getSonKnots().find(
							'\0')->second;
			cout << "LEAF: " << current->getvalueLeaf() << endl;
		}

		//prefix increment
		iterator& operator ++() {
			//go up and right
			cout << "BEFORE ++ Top of the Stack:"
					<< stackOfCurrentLeaf.top()->second << endl;
			++(stackOfCurrentLeaf.top());

			//next(stackOfCurrentLeaf.top());
			if (stackOfCurrentLeaf.top()->first != '') {
				cout << "AFTER ++ Top of the Stack:"
						<< stackOfCurrentLeaf.top()->second << endl;

			} else {
				cout << "End erreicht!" << endl;
			}

			// pop until you find another sonKnot in your current top stack map.
			while (stackOfCurrentLeaf.top()->first == '' || stackOfCurrentLeaf.top() == endOfSon.top()) {
				cout <<"Pop Stacks!!" << endl;
				popStacks();
				++(stackOfCurrentLeaf.top());
			}

			// down to the next leaf
			slideLeft();

			return *this;
		}

		// postfix increment
		iterator operator ++(int) {
			iterator clone(*this);
			clone.operator ++();
			return clone;
		}
		~TrieIterator() {

		}

	};
	typedef TrieIterator iterator;

	// return true if root has no sons.
	bool empty() {
		return root.getSonKnots().empty();
	}

	//Inserts Element (\0param value) into the trie
	iterator insert(value_type value, AbstractKnot *current) {
		key_type key = value.first;
		key_type completeKey;

		// inserts the leaf after the key. checked.
		if (key.length() == 0) {
			current->getSonKnots().insert(
					make_pair(leafToken, new LeafKnot(value.second)));
			cout << "INSERT---------------" << value.second << endl;
			iterator it = iterator(&root);

			while (*it != value.second) {
				++it;

			}
			return it;

		} else if (current->getSonKnots().find(key[0])
				== current->getSonKnots().end()) {

			// inserts the key recurse and add the knot to the stack.
			auto currKnot = current->getSonKnots().insert(
					std::make_pair(key[0], (new InnerKnot()))).first->second;

			value.first = key.substr(1, key.length());
			insert(value, currKnot);
		} else {
			value.first = key.substr(1, key.length());
			insert(value, current->getSonKnots().find(key[0])->second);
		}

		return iterator();
	}

	// rekursiv mit substring überganbe erster char ist meiner ! usw
	// \0return true wenn letzter Knoten gelöscht werden kann.
	// \0return false wenn letzter Knoten nicht gelöscht werden kann.
	bool erase(const key_type& value) {
		key_type key = value;
		AbstractKnot* current;
		// build up the trackStack
		if (key.length() != 0) {

			if (trackStack.empty()) {
				trackStack.push(pair<AbstractKnot*, char>(&root, ' '));
			}
			// push next key Knot on top of the stack
			current = trackStack.top().first;
			trackStack.push(
					pair<AbstractKnot*, char>(
							current->getSonKnots().find(key[0])->second,
							key[0]));
			key = key.substr(1, key.length());
			erase(key);
		}

		// erase the leaf and the path of Inner Knots
		current = trackStack.top().first;
		char currentKeyPath = trackStack.top().second;
		if (current->getSonKnots().size() == 1) {
			delete current;
		} else if (current->getSonKnots().find(currentKeyPath)
				!= current->getSonKnots().end()) {
			delete current->getSonKnots().find(currentKeyPath)->second;
		} else {
			return false;
		}
		trackStack.pop();

		return true;
	}

	void clear() {
		iterator it(&root);
		delete it.getStackOfCurrentLeaf().top()->getSonKnots().begin();

		while (it.getStackOfCurrentLeaf().top()->getSonKnots.size() >= 1) {
			it.popStacks();
			delete it.getStackOfCurrentLeaf().top()->getSonKnots().begin();
		}
		if (root.getSonKnots().size() >= 1) {
			clear();
		}

	}

	iterator lower_bound(const key_type& testElement) {
		char bound = ' ';
		key_type lowerBound;
		// find multiplie chars in string
		for (int i = 0; i < testElement.length(); ++i) {
			if (testElement[i] == testElement[i + 1]) {
				bound = testElement[i];
			}
		}
		int j = 0;
		while (testElement[j] != testElement[j + 1]) {
			lowerBound += testElement[j];
			++j;
		}
		lowerBound += bound;
		cout << "LowerBound: " << lowerBound << endl;
		return iterator(&root, lowerBound);
	}
	iterator upper_bound(const key_type& testElement) {
		// first element >= testElement
		char bound = '\0';
		key_type upperBound;
		int count;

		// find multiplie chars in string
		for (int i = 0; i < testElement.length(); ++i) {
			if (testElement[i] == testElement[i + 1]) {
				bound = testElement[i];
			} else if (testElement[i] != bound && bound != '\0') {
				count = i;
			}

		}
		upperBound = testElement.substr(0, count);
		cout << "Upperbound: " << upperBound << endl;
		return iterator(&root, upperBound);	// first element > testElement
	}

	// return itr auf element falls dieses exsistiert.
	// return itr auf nullptr, wenn element nicht gefunden wurde.
	iterator find(const key_type& element) {

		InnerKnot* current = &root;
		cout << "Sucht nach dem Wort " << element << "..." << endl;
		for (unsigned int i = 0; i < element.length(); ++i) {

			if (current->getSonKnots().find(element[i])
					== current->getSonKnots().end()) {
				cout << "Das Wort konnte nicht gefunden werden." << endl;
				return iterator();
			} else {

				current =
						(InnerKnot*) current->getSonKnots().find(element[i])->second;
			}
		}
		iterator it = iterator(&root);
		while (it != current->getSonKnots().find(leafToken)->second) {
			++it;
		}
		return it;

	}

	// Gibt einen Iterator zurück, welcher auf das erste Wort im Baum zeigt.
	iterator begin() {
		return iterator(&root);
	}

	iterator end() {

		iterator it = iterator(&root);

	}


	// Change loop param to this.end() if done!!!
	string toString() {
		iterator it(&root);
		string result;
		for (int i = 0 ; i < 3 ; ++i) {
			result += it.itToString();
			++it;
		}
		return result;
	}
	InnerKnot& getRoot() {
		return this->root;
	}

	virtual ~Trie() {

	}
private:
	InnerKnot root;
	const char leafToken = '\0';
	stack<pair<AbstractKnot*, char>> trackStack;

};
#endif /* TRIE_H_ */
