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

class AbstractKnot;
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

// Abstrakte Knoten Klasse und deren Implementierungen
	class AbstractKnot {
	private:
		char value;
		AbstractKnot* parent;

	public:
		AbstractKnot() :
				parent(nullptr) {

		}

		AbstractKnot(char val, AbstractKnot father) :
				value(val), parent(father) {

		}

		bool operator==(const AbstractKnot &knot) {
			return this->value == knot.value;
		}
		bool operator!=(const AbstractKnot &knot) {
			return this->value != knot.value;
		}

		virtual bool operator=(const AbstractKnot &knot) {
			return this->value = knot.value;
		}
		virtual void setValue(char c) {
			this->value = c;
		}
		virtual char getValue() {
			return this->value;
		}
	};

	class InnerKnot: public AbstractKnot {
	private:
		list<AbstractKnot> son_knots;
	public:

		InnerKnot() :
				AbstractKnot() {

		}
		InnerKnot(char val, AbstractKnot father) :
				AbstractKnot(val, father) {
		}

		bool operator==(const InnerKnot &knot){
			return this->value == knot.value;
		}
		bool operator!=(const InnerKnot &knot) {
			return this->value != knot.value;
		}
		bool operator=(const InnerKnot &knot) {

		}



		void setSonKnot(AbstractKnot son) {
			son_knots.insert(son);
		}
		bool hasNextKnot(char cKnot) {
			for (AbstractKnot k : son_knots) {
				if (k.getValue() == cKnot)
					return true;
			}
			return false;
		}
		AbstractKnot nextKnot(char nKnot) {
			for (AbstractKnot k : son_knots) {
				if (k.getValue() == nKnot)
					return k;
			}
			return *this;
		}
		~InnerKnot();
	};

	class LeafKnot: public AbstractKnot {
	private:
		E translation;
	public:
		LeafKnot() {

		}

		LeafKnot(E word) : translation(word) {

		}

		virtual ~LeafKnot();
	};

	class TrieIterator {
	private:
		AbstractKnot* current;
	public:
		typedef TrieIterator iterator;
		TrieIterator();
		TrieIterator(AbstractKnot* root) :
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
	bool empty() const;

	//Inserts value Element into the trie
	iterator insert(const value_type& value) {
		string key = value.first;
		char knotValue;
		InnerKnot currentKnot;


		for (int i = 0; i <= key.length(); ++i) {
			knotValue = key[i];
			if (currentKnot.hasNextKnot(knotValue)) {
				currentKnot = currentKnot.nextKnot(knotValue);
				continue;
			} else {

				currentKnot.son_knots.insert(InnerKnot(knotValue));
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

	virtual ~Trie() {

	}

private:
	InnerKnot root;

};
#endif /* TRIE_H_ */
