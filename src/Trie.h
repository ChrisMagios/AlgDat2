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
			if (root->getSonKnots().find('@') == root->getSonKnots().end()) {
				slideLeft();
			}
			// set to first leaf
			current =
					(LeafKnot*) (*stackOfCurrentLeaf.top()).second->getSonKnots().find(
							'@')->second;
			cout << "ITERATOR FINISHED AT: " << stackOfCurrentLeaf.top()->first
					<< " : " << current->getvalueLeaf() << endl;

		}

		TrieIterator(const iterator& itr) :
				current(itr.current) {
		}

		void print() {
			current->print(stackOfCurrentLeaf.size());
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
		void slideLeft() {
			// check if the next left element is a leaf.
			char leafToken = '@';

			while (((*stackOfCurrentLeaf.top()).second->getSonKnots().find(
					leafToken)
					== (*stackOfCurrentLeaf.top()).second->getSonKnots().end())) {
				// push It of begin and end of the same map to the stacks.
				stackOfCurrentLeaf.push(
						(*stackOfCurrentLeaf.top()).second->getSonKnots().begin());

				endOfSon.push(
						(*stackOfCurrentLeaf.top()).second->getSonKnots().end());

			}

			//push left element and end of map ontop of the stacks.

		}

		//prefix increment
		iterator& operator ++() {
			//go up and right
			cout << "BEFORE ++TOP:" << stackOfCurrentLeaf.top()->second << endl;
			++(stackOfCurrentLeaf.top());
			cout << "AFTER ++TOP:" << stackOfCurrentLeaf.top()->second << endl;
			cout << "END OF SONS TOP:" << endOfSon.top()->second << endl;
			// pop until you find another sonKnot in your current top stack map.
			while (stackOfCurrentLeaf.top() == endOfSon.top()) {
				stackOfCurrentLeaf.pop();
				endOfSon.pop();
				++(stackOfCurrentLeaf.top());
			}

			// down to the next leaf
			slideLeft();
			current =
					(LeafKnot*) (*stackOfCurrentLeaf.top()).second->getSonKnots().find(
							'@')->second;

			// Outputs
			cout << "Top of the Stacks after ++:  "
					<< (*stackOfCurrentLeaf.top()).second << " , "
					<< (*endOfSon.top()).second << endl;
			cout << "Size OF STACKS: " << stackOfCurrentLeaf.size() << " END: "
					<< endOfSon.size() << endl;
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
		key_type completeKey;

		// inserts the leaf after the key.
		if (key.length() == 0) {
			current->getSonKnots().insert(
					make_pair(leafToken, new LeafKnot(value.second)));
			iterator it =  iterator(&root);

			cout << "iterator in insert: " << *it << endl;
			cout << "value in insert: " << value.second << endl;
			while (*it != value.second) {
				++it;
				cout << "++" << endl;
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
	iterator lower_bound(const key_type& testElement) {
		// first element >= testElement
	}
	iterator upper_bound(const key_type& testElement); // first element > testElement

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

	string toString() {
//		string result = "";
//		iterator it = begin();
//		//stack<InnerKnot*> stack = it.getStackOfCurrentLeaf();
//		auto tmpStack = it.getStackOfCurrentLeaf();
//
//		while (it != end()) {
//			//cout << stack.top()->getSonKnots().begin()->first << endl;
//			++it;
//			cout << "hi";
//		}

		//InnerKnot current = this->root;
		//InnerKnot currentX = it.getCurrent()->root;
		//cout << current.getSonKnots().find('d')->first << endl;
		//cout << current.getSonKnots().begin()->first << endl;
		//it.getStackOfCurrentLeaf().pop();
		//cout << "TEST: " << it.getStackOfCurrentLeaf().top()->getSonKnots().begin()->first << endl;

//		do {
//			//sollten wir mal im print nach schauen... wegen extra Loop

//			if (stack.top()->getSonKnots().size() >= 1) {
//				tmpStack = stack;
//				cout << stack.top()->getSonKnots().size() << "@"
//						<< " current Knot: ";
//				for (auto itt = stack.top()->getSonKnots().begin();
//						itt != stack.top()->getSonKnots().end(); itt++) {
//					cout << itt->first << " ";
//				}
//				cout << endl;
//			}
//
//			//hab hier ne 2 rein weil iwas sonst ned stimmt :*
//			for (int i = 0; i <= stack.size(); i++) {
//				cout << "-";
//			}
//			cout << stack.top()->getSonKnots().begin()->first << endl;
//			stack.pop();
//			if (stack.empty()) {
//				cout << "Next Leaf---" << endl;
//				++it;
//				stack = it.getStackOfCurrentLeaf();
//			}
//		} while (it != end());

		//do {
		//	it.print();
		//	++i;
		//	cout << i << endl;
		//} while (i <= 5 && it != end());
//		return result;
	}
	InnerKnot& getRoot() {
		return this->root;
	}

	virtual ~Trie() {

	}
private:
	InnerKnot root;
	const char leafToken = '@';
	stack<pair<AbstractKnot*, char>> trackStack;

};
#endif /* TRIE_H_ */
