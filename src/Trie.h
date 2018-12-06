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
#include <list>

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
		root = InnerKnot();
	}

	class InnerKnot {
	private:
		char value;
		InnerKnot* parent;
		list<InnerKnot> son_knots;
	public:

		InnerKnot() :
				parent(nullptr) {

		}
		InnerKnot(char val, InnerKnot father) :
				value(val), parent(father) {
		}

		bool operator==(const InnerKnot &knot) {
			return this->value == knot.value;
		}
		bool operator!=(const InnerKnot &knot) {
			return this->value != knot.value;
		}
		virtual void setValue(char c) {
			this->value = c;
		}
		virtual char getValue() {
			return this->value;
		}

		void setSonKnot(InnerKnot son) {
			son_knots.insert(son);
		}

		list<InnerKnot> getSonKnot() {
			return this->son_knots;
		}
		bool hasNextKnot(char cKnot) {
			for (InnerKnot k : son_knots) {
				if (k.getValue() == cKnot)
					return true;
			}
			return false;
		}
		InnerKnot nextKnot(char nKnot) {
			for (InnerKnot k : son_knots) {
				if (k.getValue() == nKnot)
					return k;
			}
			return *this;
		}

		~InnerKnot();
	};

	class LeafKnot: public InnerKnot {
	private:
		E translation;
	public:
		LeafKnot() {

		}

		LeafKnot(E word, InnerKnot father) :
				translation(word), InnerKnot::parent(father) {
		}

		virtual ~LeafKnot();
	};

	class TrieIterator {
	private:
		InnerKnot* current;
	public:
		typedef TrieIterator iterator;
		TrieIterator();
		TrieIterator(InnerKnot* root) :
				current(root) {
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
		T& operator *() {
			return current->value();
		}
		iterator& operator ++(); // prefix
		iterator operator ++(int) // postfix
				{
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

	//Inserts value Element into the trie
	iterator insert(const value_type& value) {
		string key = value.first;
		char knotValue;
		InnerKnot currentKnot = root;

		for (int i = 0; i <= key.length(); ++i) {
			knotValue = key[i];
			if (currentKnot.hasNextKnot(knotValue)) {
				currentKnot = currentKnot.nextKnot(knotValue);
			} else {

				currentKnot.setSonKnot(InnerKnot(knotValue, currentKnot));
				currentKnot = currentKnot.nextKnot(knotValue);

			}
		}
		return TrieIterator(this->root);
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

};
#endif /* TRIE_H_ */
