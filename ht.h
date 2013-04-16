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
	List<ItemType>* table;
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

		List<ItemType>* temp = table;
		table = new List<ItemType>[ncap];
		for(int i = 0; i < capacity; i++) {
			ItemType item = temp[i].pop();
			List<ItemType>* list = new List<ItemType>(item);
			while(temp[i].getSize() > 0)
				list->push(temp[i].pop());
			table[hashCode(item, ncap)] = *list;
		}
		delete[] temp;
		capacity = ncap;
	}
	void add(const ItemType& item) {
		if(find(item))
			return;
		else if(table == NULL) {
			capacity++;
			table = new List<ItemType>[capacity];
		}
		else 
			resize();

		List<ItemType>* temp = table + hashCode(item, capacity);
		if(temp == NULL)
			temp = new List<ItemType>[capacity];
		temp->push(item);

		size++;
		cout << "capacity: " << capacity << " size: " << size << endl;
	}
	void remove(const ItemType& item) {
		if(!find(item))
			return;
		List<ItemType>* temp = table + hashCode(item, capacity);
		temp->remove(item);
		size--;
		resize();
	}
	bool find(const ItemType& item) const {
		if(size == 0)
			return false;
		unsigned hash = hashCode(item, capacity);
		cout << "hash: " << hash << endl;
		List<ItemType>* temp = table + hash;
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
			s << "hash " << i << ": " << table[i].print() << endl;
		}

		return s.str();
	}
};
#endif
