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
				cout << "-";
			}
			cout << valueLeaf << endl;
		}
		mapped_type& getvalueLeaf() {
			return this->valueLeaf;
		}
		~LeafKnot() {

		}
	};

	class TrieIterator {
	private:
		stack<AbstractKnot*> stackOfCurrentLeaf;
		LeafKnot* current;
	public:
		typedef TrieIterator iterator;
		TrieIterator() :
				current(nullptr) {

		}

		TrieIterator(LeafKnot* start, stack<AbstractKnot*> startLeaf) :
				current(start), stackOfCurrentLeaf(startLeaf) {

		}
		TrieIterator(const iterator& itr) :
				current(itr.current) {
		}
		void print() {
			current->print(stackOfCurrentLeaf.size());
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
			return *current->getvalueLeaf();
		}
		//prefix increment
		iterator& operator ++() {
			AbstractKnot* tmpLast;
			stack<AbstractKnot*> tmpLeafStack = stackOfCurrentLeaf
			while (turh) {
				if (tmpLeafStack.top()->getSonKnots().size() > 1) {
					// if there are more sons under this knot.

				} else {
					// there is only a leaf under the top knot.

					tmpLeafStack.pop();
				}
			}

			return *this;
		}

		// postfix increment
		iterator operator ++(int) {
			iterator clone(*this);
			operator ++();
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

	//Inserts Element (@param value) into the trie
	iterator insert(value_type value, AbstractKnot *current) {
		key_type key = value.first;
		// inserts the leaf after the key.
		if (key.length() == 0) {
			current->getSonKnots().insert(
					make_pair(leafToken, new LeafKnot(value.second)));
			cout << "Inserted the word: " << value.second << endl;
			return iterator(find(value.first));

		} else if (current->getSonKnots().find(key[0])
				== current->getSonKnots().end()) {

			// inserts the key recurse and add the knot to the stack.
			auto it = current->getSonKnots().insert(
					std::make_pair(key[0], (new InnerKnot())));

			cout << "Inserted :" << current->getSonKnots().find(key[0])->first
					<< endl;
			value.first = key.substr(1, key.length());
			insert(value, it.first->second);
		} else {
			value.first = key.substr(1, key.length());
			insert(value, current->getSonKnots().find(key[0])->second);
		}

		return iterator();
	}

	// rekursiv mit substring überganbe erster char ist meiner ! usw
	// @return true wenn letzter Knoten gelöscht werden kann.
	// @return false wenn letzter Knoten nicht gelöscht werden kann.
	bool erase(const key_type& value) {
		key_type key = value;
		AbstractKnot* current;
		// build up the trackStack
		if (key.length() != 0) {

			if (trackStack.empty()) {
				trackStack.push(pair<AbstractKnot*, char>(&root, ' '));
			}
			// push next key Knot ontop of the stack
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
		} else {
			delete current->getSonKnots().find(currentKeyPath)->second;
		}
		trackStack.pop();

		return true;
	}

	void clear() {
		// erase all
	}
	iterator lower_bound(const key_type& testElement); // first element >= testElement
	iterator upper_bound(const key_type& testElement); // first element > testElement

	// return itr auf element falls dieses exsistiert.
	// return itr auf nullptr, wenn element nicht gefunden wurde.
	iterator find(const key_type& element) {
		AbstractKnot* current = &root;
		stack<AbstractKnot*> stackOfLeafToFind;
		for (unsigned int i = 0; i < element.length(); ++i) {
			if (current->getSonKnots().find(element[i])
					== current->getSonKnots().end()) {
				return iterator();
			} else {
				stackOfLeafToFind.push(current);
				current = current->getSonKnots().find(element[i])->second;
			}
		}

		return iterator(
				(LeafKnot*) current->getSonKnots().find(leafToken)->second,
				stackOfLeafToFind);
	}

	// Gibt einen Iterator zurück, welcher auf das erste Wort im Baum zeigt.
	iterator begin() {
		stack<AbstractKnot*> stackOfFirstLeaf;
		AbstractKnot *current = &this->root;
		if (empty()) {
			return iterator();
		}
		while (current->getSonKnots().find(leafToken)
				== current->getSonKnots().end()) {
			stackOfFirstLeaf.push(current);
			current = current->getSonKnots().begin()->second;
		}

		return iterator(
				(LeafKnot*) current->getSonKnots().find(leafToken)->second,
				stackOfFirstLeaf);
	}

	iterator end() {
		stack<AbstractKnot*> stackOfLastLeaf;
		AbstractKnot *current = &root;
		if (this->empty()) {
			return iterator();
		}
		while (current->getSonKnots().find(leafToken)
				== current->getSonKnots().end()) {
			stackOfLastLeaf.push(current);
			current = current->getSonKnots().rbegin()->second;
		}
		return iterator(
				(LeafKnot*) current->getSonKnots().find(leafToken)->second,
				stackOfLastLeaf);
	}

	string toString() {
		cout << "fuck this shit" << endl;
		string result = "";

		iterator it = begin();
		//InnerKnot current = this->root;

		do {
			it.print();
		} while (it != end());

		return result;

	}
	InnerKnot& getRoot() {
		return this->root;
	}

	virtual ~Trie() {

	}
private:
	InnerKnot root;
	const char leafToken = ' ';
	stack<pair<AbstractKnot*, char>> trackStack;

};
#endif /* TRIE_H_ */
