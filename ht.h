#ifndef HT_H
#define HT_H
#include "queue.h"
#include <string>
#include <sstream>

#include <iostream>

using std::string;
using std::stringstream;
using std::endl;

using std::cout;

unsigned hashCode(const std::string& s, int size) {
	unsigned index = 0;
	for(unsigned int i = 0; i < s.length(); i++)
		index = index * 31 + s.at(i);
	index %= size;

	return index;
}

template<typename ItemType>
class ht {
private:
	struct bucket {
		ItemType* item;
		bucket* next;

		bucket(ItemType item) {
			this->item = new ItemType(item);
			next = NULL;
		}
		bucket() {
			item = new ItemType();
			next = NULL;
		}
		~bucket() {
			delete item;
		}
	};
	int size;
	bucket* buckets; // the array of buckets
	int capacity;
	queue<bucket*> q;
public:
	ht() {
		size = 0;
		buckets = NULL;
		capacity = 4;
	}
	~ht() {
		delete[] buckets;
	}
	void resize() {
		int ncap = capacity;
		if(size == capacity) // grow
			ncap = (capacity * 2) + 1;
		else if(size < capacity / 2) // shrink
			ncap = (capacity - 1) / 2;
		else // return
			return;

		bucket* temp = buckets;
		buckets = new bucket[ncap];
		for(int i = 0; i < capacity; i++) {
			bucket* btemp = temp + i;
			ItemType* itemp = btemp->item;
			buckets[hashCode(*itemp, ncap)].item = itemp;
			while(btemp->next != NULL) {
				itemp = btemp->item;
				buckets[hashCode(*itemp, ncap)].item = itemp;
				btemp = btemp->next;
			}
			delete[] temp;
		}
		capacity = ncap;
	}
	void add(const ItemType& item) {
		if(find(item))
			return;
		if(buckets == NULL)
			buckets = new bucket[size+1];
		else
			resize();
		buckets[hashCode(item, size)] = bucket(item);

		size++;
	}
	void remove(const ItemType& item) {
		if(find(item))
			return;

		size--;
	}
	bool find(const ItemType& item) const {
		unsigned hash = hashCode(item, size);
		for(bucket* temp = buckets + hash; temp != NULL; temp = temp->next) {
			if(*temp->item == item)
				return true;
		}
		return false;
	}
	string print() const {
		if(size == 0)
			return ItemType();
		stringstream s;

		int count = 0;
		for(int i = 0; i < capacity; i++) {
			s << "hash " << i << ": ";
			bucket* tbucket = buckets + i;
			while(tbucket != NULL) {
				if(count == 8) {
					s << endl << "hash " << i << ": ";
					count = 0;
				}
				s << tbucket->item << " ";
				tbucket = tbucket->next;
				count++;
			}
		}
/*
		while(!q.empty()) {
			Node* n = q.pop();
			if(n == sentinal && !q.empty()) {
				q.push(sentinal);
				s << endl << "hash " << hash << ": ";
				hash++;
				count = 0;
			}
			if(count == 8 && n != sentinal) {
				s << endl << "hash " << hash - 1 << ": ";
				count = 0;
			}
			if(n != sentinal) {
				s << n->item << "(" << height(n) << ") "; 
				count++;
			}
			if(n->left != NULL)
				q.push(n->left);
			if(n->right != NULL)
				q.push(n->right);
		}
		s << endl;
*/

		return s.str();
	}
};
#endif
