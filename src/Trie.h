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

		}
		mapped_type& getvalueLeaf() {
			return this->valueLeaf;
		}
		~LeafKnot() {

		}
	};

	class TrieIterator {
	private:
		LeafKnot* current = nullptr;
	public:
		typedef TrieIterator iterator;
		TrieIterator() {

		}

		TrieIterator(const iterator& itr) :
				current(itr.current) {
		}
		iterator& operator =(const iterator& itr) {
			current = itr.current;
			return *this;
		}
		bool operator ==(const iterator& itr) {
			return current == itr.current;
		}
		bool operator !=(const iterator& itr) {
			return !operator==(itr);
		}
		mapped_type& operator *() {
			return current->valueLeaf;
		}
		//prefix increment
		iterator& operator ++() {
			this->current = current->getSonKnots().begin();
			return this;
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

	bool empty() const {
		return root.son_knots.empty();
	}

	//Inserts Element (@param value) into the trie
	bool insert(value_type value, AbstractKnot *current) {
		key_type key = value.first;

		if (key.length() == 0) {
			current->getSonKnots().insert(make_pair(leafToken, new LeafKnot()));
			cout << value.second << endl;
			return true;
		} else if (current->getSonKnots().find(key[0])
				== current->getSonKnots().end()) {
			auto it = current->getSonKnots().insert(
					std::make_pair(key[0], (new InnerKnot())));
			value.first = key.substr(1, key.length());

			cout << key << endl;
			insert(value, it.first->second);
		} else {
			value.first = key.substr(1, key.length());
			insert(value, current->getSonKnots().find(key[0])->second);
		}

		return false;
	}
//	key_type key = value.first;
//			AbstractKnot *current = &root;
//			// Insert new knot for every character and jump to them.
//			for (unsigned int i = 0; i < key.length(); ++i) {
//
//				auto it = current->getSonKnots().insert(
//						std::make_pair(key[i], static_cast<AbstractKnot*>(new InnerKnot())));
//				cout << "FIRST: " << it.first->first << "SECOND: " << it.first->second << it.second<< endl;
//				cout << "KEY: " << current->getSonKnots().find(key[i])->second << endl;
//
//				current = current->getSonKnots().find(key[i])->second;
//			}
//			current->getSonKnots().insert(
//					make_pair(leafToken, new LeafKnot()));
//			cout << "END OF INSERT" << endl;
//			return iterator();

	// Erase the element at the given key
	// @return bool
	// rekursiv mit substring überganbe erster char ist meiner ! usw
	// @return true wenn letzter Knoten gelöscht werden kann.
	// @return false wenn letzter Knoten nicht gelöscht werden kann.
	void erase(const key_type& value) {
		key_type key = value;
		InnerKnot current = this->root;

		// Insert new knot for every character and jump to them.
		for (unsigned int i = 0; i < key.length(); ++i) {
			trieTrackStack.push(current);
			current = current.getSonKnots().find(key[i]).operator *().second;
		}
		trieTrackStack.push(
				current.getSonKnots().find(leafToken).operator *().second);

		while (!trieTrackStack.empty()) {

		}

	}
	void clear(); // erase all
	iterator lower_bound(const key_type& testElement); // first element >= testElement
	iterator upper_bound(const key_type& testElement); // first element > testElement
	iterator find(const key_type& testElement); // first element == testElement
	iterator begin(); // returns end() if not found
	iterator end();

	string toString() {
		return " ";
	}
	InnerKnot& getRoot() {
		return this->root;
	}

	virtual ~Trie() {

	}
private:
	InnerKnot root;
	const char leafToken = ' ';
	stack<AbstractKnot*> trieTrackStack;

};
#endif /* TRIE_H_ */
