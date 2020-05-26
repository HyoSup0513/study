#include "dlist.hpp"
#include <iostream>
using namespace std;

dlist::node* dlist::at(int n) const {
	if (n >= size())
		return nullptr;
	else if (n < 0)
		return head();
	else {
		node* current = head();

		for (int i = 0; i < n; i++) {
			current = current->next;
		}
	}

};

void dlist::insert(node* previous, int value)
{
	if (previous == nullptr && _head == nullptr && _tail == nullptr) {

		node* newNode = new node;
		newNode->value = value;

		_head = newNode;
		_tail = _head;
		_head->prev = nullptr;
		_head->next = nullptr;

	}
	else if (_head == _tail && size() == 1) {
		node* newNode = new node;
		newNode->value = value;
		_head->next = newNode;
		_tail = newNode;
		_tail->next = nullptr;
		_tail->prev = _head;
	}
	else if (previous != _head && previous != _tail && size() == 2) {
		node* newNode = new node;
		newNode->value = value;
		_tail->next = newNode;
		_tail = newNode;
		_tail->next = nullptr;
	}
	else if (previous == _tail && previous != _head) {
		push_back(value);
	}

	else {
		node* newNode = new node;
		newNode->value = value;
		node* storenode = new node;

		storenode = previous->next;
		previous->next = newNode;
		storenode->prev = previous->next;
		newNode->next = storenode;
		newNode->prev = previous;
	}
}

// Delete the given node. Should do nothing if which == nullptr.
// Must run in O(1) time.
void dlist::remove(node* which) {
	node* temp = which;
	if (which == nullptr) {
		return;
	}

	else if (which != nullptr) {

		if (which == _head) {
			node* newNode = new node;
			newNode->value = which->value;
			_head = which->next;
			_head->prev = nullptr;
		}

		else {
			which = which->next;
		}
	}
}

void dlist::push_back(int value) {

	if (_head == nullptr || _tail == nullptr) {
		node* newNode = new node;
		newNode->value = value;

		_head = newNode;
		_tail = _head;
		_head->prev = nullptr;
		_head->next = nullptr;
		_head = _tail;
	}
	else {
		node* newNode = new node;
		node* storeNode = new node;
		newNode->value = value;

		storeNode = _tail;
		_tail = newNode;
		_tail->prev = storeNode;
		_tail->next = nullptr;
		if (storeNode != nullptr)
			storeNode->next = _tail;
	}
}

void dlist::push_front(int value) {

	if (_head == nullptr || _tail == nullptr) {
		node* newNode = new node;
		newNode->value = value;

		_head = newNode;
		_tail = _head;
		_head->prev = nullptr;
		_head->next = nullptr;
	}

	else {
		node* newNode = new node;
		node* storeNode = new node;
		newNode->value = value;

		storeNode = _head;
		_head = newNode;
		_head->next = storeNode;
		_head->prev = nullptr;
		if (storeNode != nullptr)
			storeNode->prev = _head;
	}
}

void dlist::pop_front() {

	if (_head == nullptr || _tail == nullptr) {
		return;
	}
	else if (size() == 1) {
		_head = nullptr;
		_tail = nullptr;
	}
	else {
		node* newNode = new node;
		newNode = _head->next->next;

		_head = _head->next;
		_head->prev = nullptr;

	}

}

void dlist::pop_back() {

	if (_head == nullptr || _tail == nullptr) {
		return;
	}
	else if (size() == 1) {
		_head = nullptr;
		_tail = nullptr;
	}
	else {

		_tail = _tail->prev;
		_tail->next = nullptr;

	}
}

int dlist::size() const {
	int listsize = 0;

	node* current = head();
	if (current != nullptr) {

		while (current != nullptr) {
			listsize++;
			current = current->next;
		}
	}
	return listsize;
}

bool dlist::empty() const{
	return head() == tail();
}