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

class RootKnot;
class AbstractKnot;
class TrieIterator;
using namespace std;
template<class T, class E = char>
class Trie {

	typedef basic_string<E> key_type; // string=basic_string<char>
	typedef pair<const string, T> value_type;
	typedef T mapped_type;

	// „...“ im folgenden typedef: keine C/C++ Ellipse, sondern von Ihnen
	// - am besten als innere Klasse - zu entwickeln…
	typedef TrieIterator iterator;
private:
	RootKnot root;

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
		AbstractKnot() {
			value = " ";
			parent = nullptr;
		}

		AbstractKnot(char val, AbstractKnot father): value(val), parent(&father){

		}

		virtual char getValue() {
			return this->value;
		}

	};

	class InnerKnot: public AbstractKnot {
	private:
		list<AbstractKnot> son_knots;
	public:

		InnerKnot(): AbstractKnot() {

		}
		InnerKnot(char val, AbstractKnot father) : AbstractKnot(val, father) {

		}

		void setSonKnot(AbstractKnot son) {
			son_knots.insert(son);
		}

		virtual ~InnerKnot();
	};

	class LeafKnot: public AbstractKnot {
	public:
		LeafKnot() {

		}

		virtual ~LeafKnot();
	};


	class TrieIterator {

	};

	bool empty() const;
	iterator insert(const value_type& value);
	void erase(const key_type& value);
	void clear(); // erase all
	iterator lower_bound(const key_type& testElement); // first element >= testElement
	iterator upper_bound(const key_type& testElement); // first element > testElement
	iterator find(const key_type& testElement); // first element == testElement
	iterator begin(); // returns end() if not found
	iterator end();

	virtual ~Trie() {

	}
};
#endif /* TRIE_H_ */
