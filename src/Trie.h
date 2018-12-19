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
		LeafKnot* current = nullptr;
	public:
		typedef TrieIterator iterator;
		TrieIterator() {

		}

		TrieIterator(LeafKnot* start) :
				current(start) {

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
			this->current = (LeafKnot*) current->getSonKnots().begin()->second;
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

	bool empty() {
		return root.getSonKnots().empty();
	}

	//Inserts Element (@param value) into the trie
	iterator insert(value_type value, AbstractKnot *current) {
		key_type key = value.first;

		if (key.length() == 0) {
			current->getSonKnots().insert(make_pair(leafToken, new LeafKnot()));
			cout << value.second << endl;
			return iterator();
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

		return iterator();
	}

	void buildTrackStack(const key_type& value, AbstractKnot *current) {
		key_type key = value;
		trackStack.push(current);
		if (key.length() != 0) {
			buildTrackStack(key.substr(1, key.length()),
					current->getSonKnots().find(key[0])->second);
		}
	}
	// @return bool
	// rekursiv mit substring überganbe erster char ist meiner ! usw
	// @return true wenn letzter Knoten gelöscht werden kann.
	// @return false wenn letzter Knoten nicht gelöscht werden kann.
	bool erase(const key_type& value) {
		key_type key = value;

		if (trackStack.empty() && !erase(key)) {
			buildTrackStack(key, &root);
		}
		return true;
	}

	void clear(); // erase all
	iterator lower_bound(const key_type& testElement); // first element >= testElement
	iterator upper_bound(const key_type& testElement); // first element > testElement

	// return it auf first element == testElement
	// return it auf nullptr, wenn testElement nicht gefunden
	iterator find(const key_type& element) {
		AbstractKnot* current = root;

		for (unsigned int i = 0; i < element.length(); ++i) {
			if (current->getSonKnots().find(element[i])
					== current->getSonKnots().end()) {
				return iterator();
			} else {
				current = current->getSonKnots().find(element[i])->second;
			}
		}

		return iterator(current->getSonKnots().find(leafToken)->second);
	}

	// Gibt einen Iterator zurück, welcher auf das erste Wort im Baum zeigt.
	iterator begin() {
		AbstractKnot *current = &this->root;
		if (this->empty()) {
			return iterator();
		}
		while (current->getSonKnots().find(leafToken)
				== current->getSonKnots().end()) {
			current = current->getSonKnots().begin()->second;
		}
		return iterator(
				(LeafKnot*) current->getSonKnots().find(leafToken)->second);
	}

	iterator end() {
		iterator it = this->begin();
		while (it != nullptr) {
			++it;
		}
		return it;
	}

	string toString(InnerKnot current) {
		string result;
		//InnerKnot current = this->root;
		for (char c = 'a'; c <= 'z'; c++) {

			auto it = current.getSonKnots().find(c);

			if (it != current.getSonKnots().end()) {
				result += c;
				current = it->second;
				toString(current);
			}

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
	const char leafToken = ' ';
	stack<AbstractKnot*> trackStack;

};
#endif /* TRIE_H_ */
