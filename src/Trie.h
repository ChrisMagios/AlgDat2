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
class InnerKnot;
class TrieIterator;
using namespace std;
template<class T, class E = char>
class Trie {

	typedef basic_string<E> key_type; // string=basic_string<char>
	typedef pair<const string, T> value_type;
	typedef T mapped_type;

public:

	Trie() {
	}

	// AbstractKnot class for easier inheritance
	class AbstractKnot {
		virtual void print(int level) = 0;
	};

	// Knot class for Trie knots, which do not have any value.
	class InnerKnot: public AbstractKnot {
	private:
		map<E, AbstractKnot*> son_knots;
	public:

		// Overrited abstract Class Method
		void print(int level) {

		}

		InnerKnot() {

		}

		map<E, AbstractKnot*>& getSonKnots() {
			return this->son_knots;
		}
		AbstractKnot& nextKnot(char nKnot) {
			return *(this->son_knots.find(nKnot));
		}

		~InnerKnot() {

		}
	};
	// Knot class for Trie leafs, holding the value.
	class LeafKnot: public AbstractKnot {
	private:
		mapped_type valueLeaf;
		AbstractKnot *nextLeaf = nullptr;
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
		virtual ~LeafKnot();
	};

	class TrieIterator {
	private:
		LeafKnot* current = nullptr;
	public:
		typedef TrieIterator iterator;
		TrieIterator() {

		}
		TrieIterator(LeafKnot start) :
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
			return *current->valueLeaf;
		}
		//prefix increment
		iterator& operator ++() {
			this->current = current->nextLeaf;
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

	//Inserts Element @param value, into the trie
	iterator insert(value_type& value) {
		key_type key = value.first;
		InnerKnot current = root;

		// Insert new knot for every character and jump to them.
		for (unsigned int i = 0; i <= key.length(); ++i) {
			current.getSonKnots().insert(
					pair<E, AbstractKnot*>(key[i], InnerKnot()));
			current = current.getSonKnots().at(key[i]);
		}

		//Insert our beautiful happy little leaf
		current.getSonKnots().insert(leafToken, LeafKnot(value.second));

		return iterator(current.getSonKnots().at(leafToken));
	}

	void erase(const key_type& value);
	void clear(); // erase all
	iterator lower_bound(const key_type& testElement); // first element >= testElement
	iterator upper_bound(const key_type& testElement); // first element > testElement
	iterator find(const key_type& testElement); // first element == testElement
	iterator begin(); // returns end() if not found
	iterator end();

	string toString() {
		return "Dummy Dummy toStringTrie";
	}

	virtual ~Trie() {

	}
private:
	InnerKnot root;
	char leafToken = ' ';
	stack<AbstractKnot*> trieTrackStack;

};
#endif /* TRIE_H_ */
