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
#include <ctype.h>

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

	public:

		virtual void print(int level) = 0;
		virtual string toString(int level) = 0;

		virtual ~AbstractKnot() {

		}
	};






	// Knot class for Trie knots, which do not have any value.
	class InnerKnot: public AbstractKnot {
	private:
			map<E, AbstractKnot*> son_knots;
	public:

		// Overrited abstract Class Method
		void print(int level) {
			for (auto elem : son_knots) {
				string res;
				for (int i = 0; i < level; ++i) {
								res += ' ';
				}
				res += elem.first;
				cout << res << endl;
				elem.second->print(level + 1);
			}

		}
		map<E, AbstractKnot*>& getSonKnots() {
					return this->son_knots;
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

		InnerKnot& operator =(InnerKnot* knt) {
			this->getSonKnots() = knt->getSonKnots();
			return *this;
		}
		//Inserts Element (\0param value) into the trie
		void insert(key_type key, const mapped_type& value) {
			InnerKnot* current = this;
			// inserts the leaf after the key. checked.
			if (key.length() == 0) {
				current->getSonKnots().insert(
						make_pair(leafToken, new LeafKnot(value)));

				//cout << "Inserted Word: " << endl << it.itToString() << endl;
				cout << "Inserted Word: " << endl << value << endl;


			} else if (current->getSonKnots().find(key[0])
					== current->getSonKnots().end()) {

				// inserts the key recurse and add the knot to the stack.
				InnerKnot* tmp = new InnerKnot();
				current->getSonKnots()[key[0]] = tmp;

				key = key.substr(1, key.length());
				tmp->insert(key, value);
			} else {
				key = key.substr(1, key.length());
				static_cast<InnerKnot*>(current->getSonKnots().find(key[0])->second)->insert(key, value);
			}


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
		const char leafToken = '\0';
	public:
		typedef TrieIterator iterator;
		TrieIterator() :
				current(nullptr) {
		}
		LeafKnot* getCurrent() {
			return current;
		}

		TrieIterator(InnerKnot* root) {
			// push root son Knots ontop of empty stack
			stackOfCurrentLeaf.push(root->getSonKnots().begin());
			endOfSon.push(root->getSonKnots().end());
			if (root->getSonKnots().find(leafToken) == root->getSonKnots().end()) {
				slideLeft();
			}
		}

		TrieIterator(const iterator& itr) :
				current(itr.current) {
			stackOfCurrentLeaf = itr.stackOfCurrentLeaf;
			endOfSon = itr.endOfSon;
		}

		string itToString() {
			stack<typename map<E, Trie<T, E>::AbstractKnot*>::iterator> tmpStack =
					stackOfCurrentLeaf;
			string res;
			list<string> resList;
			while (!tmpStack.empty()) {
				resList.push_back(
						tmpStack.top()->second->toString(tmpStack.size())
								+ tmpStack.top()->first + "\n");
				tmpStack.pop();
			}
			resList.reverse();

			for (string s : resList) {
				res += s;
			}
			res += current->toString(stackOfCurrentLeaf.size());

			return res;

		}
		stack<typename map<E, Trie<T, E>::AbstractKnot*>::iterator>& getStackOfCurrentLeaf() {
			return this->stackOfCurrentLeaf;
		}
		iterator& operator =(const iterator& itr) {
			current = itr.current;
			return *this;
		}
		bool operator ==(const iterator& itr) {
			return current == itr.current
					&& stackOfCurrentLeaf == itr.stackOfCurrentLeaf;
		}
		bool operator !=(const iterator& itr) {
			return current != itr.current
					&& stackOfCurrentLeaf != itr.stackOfCurrentLeaf;
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
			if (!stackOfCurrentLeaf.empty()) {
				while ((static_cast<InnerKnot*>((*stackOfCurrentLeaf.top()).second)->getSonKnots().find(
						leafToken)
						== static_cast<InnerKnot*>((*stackOfCurrentLeaf.top()).second)->getSonKnots().end())) {
					// push It of begin and end of the same map to the stacks.

					stackOfCurrentLeaf.push(
							static_cast<InnerKnot*>((*stackOfCurrentLeaf.top()).second)->getSonKnots().begin());

					endOfSon.push(
							static_cast<InnerKnot*>((*stackOfCurrentLeaf.top()).second)->getSonKnots().end());
				}

				current =
						(LeafKnot*) static_cast<InnerKnot*>((*stackOfCurrentLeaf.top()).second)->getSonKnots().find(
								leafToken)->second;
			}
		}

		//prefix increment
		iterator& operator ++() {

			++(stackOfCurrentLeaf.top());
			// pop until you find another sonKnot in your current top stack map.
			//stackOfCurrentLeaf.top()->first == ''
			while ( stackOfCurrentLeaf.top()->first < 3 && stackOfCurrentLeaf.top()->first != leafToken) {
//			while (stackOfCurrentLeaf.top() == endOfSon.top()) {
				popStacks();
				if (stackOfCurrentLeaf.empty()) {
					current = nullptr;
					return *this;
				}
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
	iterator insert(value_type value) {
		key_type key = value.first;
		root.insert(key, value.second);
		 return iterator();


	}


	// rekursiv mit substring überganbe erster char ist meiner ! usw
	// return true wenn letzter Knoten gelöscht werden kann.
	// return false wenn letzter Knoten nicht gelöscht werden kann.
	bool erase(const key_type& value) {
		key_type key = value;
		reverse(key.begin(), key.end());
		iterator itToErase = find(value);

		if(itToErase == iterator(&root)){
			return false;
		}

		// if value could not be found.

		// in case of multiple SonKnots and another leaf on the path.
		bool hasAnotherLeaf = false;
		char lastFullDeleted = '\0';

		// erase the leaf and the path of Inner Knots
		delete itToErase.getCurrent();
		while (key.length() != 0 && !hasAnotherLeaf) {

			if (static_cast<InnerKnot*>(itToErase.getStackOfCurrentLeaf().top()->second)->getSonKnots().size()
					<= 1) {
				delete itToErase.getStackOfCurrentLeaf().top()->second;
				lastFullDeleted = key[0];
			} else {
				static_cast<InnerKnot*>(itToErase.getStackOfCurrentLeaf().top()->second)->getSonKnots().erase(
						key[0]);

				// if the last knot was completley erased.
				if (lastFullDeleted != '\0') {
					static_cast<InnerKnot*>(itToErase.getStackOfCurrentLeaf().top()->second)->getSonKnots().erase(
							lastFullDeleted);
					lastFullDeleted = '\0';
					hasAnotherLeaf = true;
				}

			}
			itToErase.getStackOfCurrentLeaf().pop();
			key = key.substr(1, key.length());

		}

		return true;
	}

	// overloaded version for it at element.

	void clear() {

	}

	// return itr auf element falls dieses exsistiert.
	// return itr auf nullptr, wenn element nicht gefunden wurde.
	// return itr auf begin ... damn...
	iterator find(const key_type& element) {
		InnerKnot* current = &root;



		for (unsigned int i = 0; i < element.length(); ++i) {

			if (current->getSonKnots().find(element[i])
					== current->getSonKnots().end()) {
				return iterator(&root);
			} else {
				current =
						(InnerKnot*) current->getSonKnots().find(element[i])->second;
			}
		}
		iterator it = iterator(&root);
		while ( static_cast<InnerKnot*>( it.getStackOfCurrentLeaf().top()->second)->getSonKnots().find(
				leafToken)->second
				!= current->getSonKnots().find(leafToken)->second) {
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
		while (!it.getStackOfCurrentLeaf().empty()) {
			++it;

		}
		return it;
	}

	// Change loop param to this.end() if done!!!
	string toString() {
		iterator it(&root);
		string result;
		while (it != end()) {
			result += it.itToString();
			++it;
		}
		result += "\n|   | \n"
				"|   | \n"
				"|___| \n";
		return result;
	}
	InnerKnot& getRoot() {
		return this->root;
	}

	void print() {
		root.print(0);
	}
	virtual ~Trie() {

	}
private:
	InnerKnot root;
	const static char leafToken = '\0';

};
template <class T, class E>
const char Trie<T,E>::leafToken;
#endif /* TRIE_H_ */
