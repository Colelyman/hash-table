#ifndef HT_H
#define HT_H
#include "list.h"
#include <string>
#include <sstream>

#include <iostream>

using std::string;
using std::stringstream;
using std::endl;

using std::cout;

unsigned hashCode(const std::string& s, int capacity) {
	unsigned index = 0;
	for(unsigned int i = 0; i < s.length(); i++)
		index = index * 31 + s.at(i);
	index %= capacity;

	return index;
}
unsigned hashCode(const int& s, int capacity) {
	unsigned index = 0;
	index = index * 31 + s;
	index %= capacity;

	return index;
}

template<typename ItemType>
class ht {
private:
	int size;
	int capacity;
	List<ItemType>** table;
public:
	ht() {
		size = 0;
		table = NULL;
		capacity = 0;
	}
	~ht() {
		// deallocate using remove function
	}
	void resize() {
		int ncap;
		if(size == capacity) // grow
			ncap = (capacity * 2) + 1;
		else if(size < capacity / 2) // shrink
			ncap = (capacity - 1) / 2;
		else // return
			return;

		List<ItemType>** old = table;
		table = new List<ItemType>*[ncap]();
		for(int i = 0; i < capacity; i++) {
			if(old[i] == NULL)
				continue;
			cout << "i: " << i << endl;
			ItemType item = old[i]->pop();
			while(old[i]->empty()) {
				item = old[i]->pop();
				unsigned hash = hashCode(item, ncap);
				if(table[hash] == NULL)
					table[hash] = new List<ItemType>(item);
				else
					table[hash]->push(item);
			}
		}
		for(int i = 0; i < capacity; i++) {
			if(old[i] != NULL)
				delete old[i];
		}
		delete[] old;
		capacity = ncap;
	}
	void add(const ItemType& item) {
		if(find(item))
			return;
		else if(table == NULL) {
			capacity++;
			table = new List<ItemType>*[capacity]();
		}
		else 
			resize();
		unsigned hash = hashCode(item, capacity);

		List<ItemType>* temp = table[hash];
		if(temp == NULL) {
			cout << "temp == NULL" << endl;
			temp = new List<ItemType>;
		}
		temp->push(item);
		table[hash] = temp;

		size++;
		cout << "capacity: " << capacity << " size: " << size << endl;
	}
	void remove(const ItemType& item) {
		if(!find(item))
			return;
		List<ItemType>* temp = table[hashCode(item, capacity)];
		temp->remove(item);
		size--;
		resize();
	}
	bool find(const ItemType& item) const {
		if(size == 0)
			return false;
		unsigned hash = hashCode(item, capacity);
		cout << "hash: " << hash << endl;
		List<ItemType>* temp = table[hashCode(item, capacity)];
		if(temp->find(item))
			return true;
		else
			return false;
	}
	string print() const {
		if(size == 0)
			return ItemType();
		stringstream s;

		for(int i = 0; i < capacity; i++) {
			s << "hash " << i << ": ";
			if(table[i] != NULL)
				s << table[i]->print();
			s << endl;
		}

		return s.str();
	}
};
#endif
