#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
	// Behaviors
	void printForward() const {
		Node* curr = head;
		while (curr != nullptr) {
			std::cout << curr->data << std::endl;
			Node* next = curr->next;
			curr = next;
		}
	}
	void printReverse() const {
		Node* curr = tail;
		while (curr != nullptr) {
			std::cout << curr->data << std::endl;
			Node* prev = curr->prev;
			curr = prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node* curr = new Node{data, nullptr, head};
		if (head == nullptr) {
			tail = curr;
		} else {
			head->prev = curr;
		}
		head = curr;
		count++;
	}
	void addTail(const T& data) {
		Node* curr = new Node{data, tail, nullptr};
		if (tail == nullptr) {
			head = curr;
		} else {
			tail->next = curr;
		}
		tail = curr;
		count++;
	}

	// Removal
	bool removeHead() {
		if (head == nullptr) {
			return false;
		} else {
			Node* next = head->next;
			delete head;
			head = next;
			if (head) {
				head->prev = nullptr;
			} else {
				tail = nullptr;
			}
			count--;
			return true;
		}
	}
	bool removeTail() {
		if (tail == nullptr) {
			return false;
		} else {
			Node* prev = tail->prev;
			delete tail;
			tail = prev;
			if (tail) {
				tail->next = nullptr;
			} else {
				head = nullptr;
			}
			count--;
			return true;
		}
	}

	void Clear() {
		Node* curr = head;
		while (curr != nullptr) {
			Node* next = curr->next;
			delete curr;
			curr = next;
		}
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept { 
		if (this == &other) {
			return *this;
		}
		Clear();
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		Clear();
		Node* curr = rhs.head;
		while (curr != nullptr) {
			addTail(curr->data);
			curr = curr->next;
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0) {
		Node* curr = list.head;
		while (curr != nullptr) {
			addTail(curr->data);
			curr = curr->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		Node* curr = head;
		while (curr != nullptr) {
			Node* next = curr->next;
			delete curr;
			curr = next;
		}
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


