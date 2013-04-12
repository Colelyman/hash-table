#ifndef HT_H
#define HT_H
#include <string>
#include <sstream>

#include <iostream>

using std::string;
using std::stringstream;
using std::endl;

using std::cout;

template<typename ItemType>
class ht {
private:
	struct bucket {
		ItemType item;
		bucket* next;

		bucket(ItemType item) {
			this->item = item;
			next = NULL;
		}
	};
	int size;
	bucket* buckets; // the array of buckets
	int capacity;
public:
	ht() {
		size = 0;
		buckets = new bucket[4];
		capacity = 4;
	}
	void add(const ItemType& item) {
		if(find(item))
			return;


		size++;
	}
	void remove(const ItemType& item) {

		size--;
	}
	bool find(const ItemType& item) {

		return false;
	}
	string print() {
		if(size == 0)
			return ItemType();
		stringstream s;

		int hash = 0;
		int count = 0;
		s << "hash " << level << ": ";
		hash++;
		while(!q.empty()) {
			Node* n = q.pop();
			if(n == sentinal && !q.empty()) {
				q.push(sentinal);
				s << endl << "hash " << level << ": ";
				hash++;
				count = 0;
			}
			if(count == 8 && n != sentinal) {
				s << endl << "hash " << level - 1 << ": ";
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


		return s.str();
	}
};
#endif
