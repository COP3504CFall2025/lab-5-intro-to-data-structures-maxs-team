#pragma once
#include <iostream>
#include "Node.hpp"
using namespace std;

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const;
	void PrintReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node<T>* getHead();
	const Node<T>* getHead() const;
	Node<T>* getTail();
	const Node<T>* getTail() const;

	// Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);

	// Removal
	bool RemoveHead();
	bool RemoveTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList() = default;
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
	unsigned int count = 0;

};

template<typename T>
[[nodiscard]] unsigned int LinkedList<T>::getCount() const {
	return count;
}

template<typename T>
Node<T>* LinkedList<T>::getHead() {
	return head;
}

template<typename T>
const Node<T>* LinkedList<T>::getHead() const {
	return head;
}

template<typename T>
Node<T>* LinkedList<T>::getTail() {
	return tail;
}

template<typename T>
const Node<T>* LinkedList<T>::getTail() const {
	return tail;
}

template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	if (head != nullptr) {
		head -> prev = new Node(data, nullptr, head);
		head = head -> prev;
	} else {
		head = new Node(data, nullptr, nullptr);
		tail = head;
	}
	count++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	if (tail != nullptr) {
		tail -> next = new Node(data, tail, nullptr);
		tail = tail -> next;
	} else {
		tail = new Node(data, nullptr, nullptr);
		head = tail;
	}
	count++;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
	if (head == nullptr)
		return false;
	if ((head -> next) != nullptr) {
		head = &(head -> next);
		delete head -> prev;
		head -> prev = nullptr;
	} else {
		delete head;
		head = nullptr;
	}
	count--;
	return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
	if (tail == nullptr)
		return false;
	if ((tail -> prev) != nullptr) {
		tail = &(tail -> prev);
		delete tail -> next;
		tail -> next = nullptr;
	} else {
		delete tail;
		tail = nullptr;
	}
	count--;
	return true;
}

template <typename T>
void LinkedList<T>::Clear() {
	if (head != nullptr) {
		Node<T>* curr = head;
		while (curr -> next != nullptr) {
			curr = (curr -> next);
			delete curr -> prev;
			curr -> prev = nullptr;
		}
		delete curr;
		curr = nullptr;
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
}

template <typename T>
void LinkedList<T>::printForward() const {
	Node<T>* curr = head;
	while (curr != nullptr) {
		std::cout << curr -> data << std::endl;
		curr = curr -> next;
	}
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
	Node<T>* curr = tail;
	while (curr != nullptr) {
		std::cout << curr -> data << std::endl;
		curr = curr -> prev;
	}
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
	if (this == &other)
		return *this;

	delete this -> head;
	delete this -> tail;

	this -> head = other.head;
	this -> tail = other.tail;
	this -> count = other.count;

	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;

	return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	if (this == &rhs)
		return *this;

	delete this -> head;
	delete this -> tail;

	this -> head = rhs.head;
	this -> tail = rhs.tail;
	this -> count = rhs.count;

	return *this;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) : head(list.head), tail(list.tail), count(list.count) {}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Clear();
}
