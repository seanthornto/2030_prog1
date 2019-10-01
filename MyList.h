#include <vector> 
#include<string>
#include <iostream>
using namespace std;
#ifndef MYLIST_H
#define MYLIST_H


template <class dtype>
struct Node {
	dtype data;
	Node<dtype>* next;
	Node<dtype>* prev;

	Node<dtype>()
	{
		next = nullptr;
		prev = nullptr;
	}

	bool operator==(const Node<dtype> &rhs)
	{
		return next == rhs.next;
	}
};

template <class dtype>
struct Mark {
	Node<dtype>* point;
	int index;
	Mark()
	{
		point = nullptr;
		index = -1;
	}
	Mark<dtype>(Node<dtype>* pnt, int ind)
	{
		point = pnt;
		index = ind;
	}
};

template <class dtype>
class MyList {
	Node<dtype> *head;
	Node<dtype> *tail;
	Mark<dtype> cursor;
	int size;
public:
	MyList()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
		cursor.index = -1;
	}

	~MyList()
	{
		while (!isEmpty())
		{
			deleteNode(head);
		}
	};

	//bool isEmpty();
	//int getSize();
	//bool moveCursorRight(int n);
	//bool moveCursorLeft(int n);
	//bool moveCursorTo(int index);
	//bool moveCursorTo(Node<dtype>* node);
	//bool moveCursorTo(Mark<dtype> mark);
	//Node<dtype>* pushNode(dtype val);
	//Node<dtype>* appendNode(dtype val);
	//void deleteNode(Node<dtype>* del);
	//Node<dtype>* getNode(int index);
	//int getIndex(Node<dtype>* node);
	//Node<dtype>* insertBefore(Node<dtype>* nextNode, dtype data);
	//Node<dtype>* insertAfter(Node<dtype>* prevNode, dtype data);
	//Node<dtype>* insertNode(int index, dtype data);
	//Mark<dtype> getCursor();
	//Node<dtype>* getHead();
	//Node<dtype>* getTail();
	//void addList(MyList<dtype> listA);
	//void print();

	bool isEmpty()
	{
		return size == 0;
	}

	int getSize()
	{
		return size;
	}

	bool moveCursorRight(int n)
	{
		
		for (int i = 0; i < n; i++) {
			if (cursor.point == tail) return false;
			cursor.point = cursor.point->next;
			cursor.index++;
		}
		return true;
	}

	bool moveCursorLeft(int n)
	{
		for (int i = 0; i < n; i++) {
			if (cursor.point == head) return false;
			cursor.point = cursor.point->prev;
			cursor.index--;
		}
		return true;
	}

	bool moveCursorTo(int index)
	{
		if (index < cursor.index)
		{
			return moveCursorLeft(cursor.index - index);
		}
		else if (index > cursor.index)
		{	
			return moveCursorRight(index - cursor.index);
		}
		return true;
	}

	void print()
	{
		moveCursorTo(head);
		for (int i = 0; i < size; i++)
		{
			cout << cursor.point->data << " ";
			moveCursorRight(1);
		}
	}

	void resetCursor()
	{
		moveCursorTo(head);
	}

	bool moveCursorTo(Node<dtype>* node)
	{
		if (node == nullptr) return false;
		int index = getIndex(node);
		cursor.point = node;
		cursor.index = index;
		return true;
	}

	bool moveCursorTo(Mark<dtype> mark)
	{
		if (mark.point == nullptr) return false;
		cursor = mark;
		return true;
	}

	Node<dtype>* pushNode(dtype val)
	{
		Node<dtype> *newNode = new Node<dtype>; //Create the node
		newNode->data = val;					//Initialize its value
		newNode->next = head;					//Set the node's next pointer to the head pointer
		newNode->prev = nullptr;				//Set the node's prev pointer to null

		if (!isEmpty())
		{
			head->prev = newNode;				//Set the second node's prev to the new node
			head = newNode;						//Set the head to point to the new node
		}
		else
		{
			head = newNode;						//Set the head and tail to point to the new node
			tail = newNode;
			cursor.point = newNode;
		}

		size++;
		cursor.index++;
		return newNode;
	}

	Node<dtype>* appendNode(dtype val)
	{
		Node<dtype> *newNode = new Node<dtype>; //Create the node
		newNode->data = val;					//Initialize its value
		newNode->next = nullptr;				//Set the node's next pointer to null
		newNode->prev = tail;					//Set the node's prev pointer to the tail pointer

		if (!isEmpty())
		{
			tail->next = newNode;				//Set second to last node's next to the new node
			tail = newNode;						//Set the tail to point to the new node
		}
		else
		{
			head = newNode;						//Set  the head and tail to point ot the new node
			tail = newNode;
		}

		size++;
		return newNode;
	}

	void deleteNode(Node<dtype>* del)
	{

		if (isEmpty() || del == nullptr) return;					     //Do nothing if the list is empty or the argument doesnt point to anything

		if (getIndex(del) < cursor.index) cursor.index--;				 //If the node being deleted is below the cursor in index, decrement cursor's index
		else if (del == cursor.point) cursor.point = cursor.point->next; //If the node the cursor is pointing to is being deleted, move the cursor right

		if (del == head)							//If the head is being deleted
		{
			if (size == 1)							//If it is the only node
			{
				head = nullptr;						//Set head and tail to null
				tail = nullptr;
			}
			else
			{
				head = head->next;					//Otherwise set the head to the next node
				head->prev = nullptr;

			}

		}
		else if (del == tail)
		{
			tail = tail->prev;
			tail->next = nullptr;

		}
		else
		{
			del->next->prev = del->prev;
			del->prev->next = del->next;
		}

		size--;
		delete(del);

	}

	Node<dtype>* getNode(int index)
	{
		if (isEmpty()) return nullptr;

		Node<dtype>* temp;
		if (index < size / 2)
		{
			temp = head;
			for (int i = 0; i < index; i++)
			{
				temp = temp->next;
			}
		}
		else
		{
			temp = tail;
			for (int i = size - 1; i > index; i--)
			{
				temp = temp->prev;
			}
		}

		return temp;
	}

	int getIndex(Node<dtype>* node)
	{

		Node<dtype>* temp = head;
		int index = 0;
		while (temp != node)
		{
			temp = temp->next;
			index++;
		}
		return index;
	}

	Node<dtype>* insertAfter(Node<dtype>* prevNode, dtype data)
	{
		if (getIndex(prevNode) < cursor.index) cursor.index++;
		if (prevNode == tail)
		{
			return appendNode(data);
		}
		Node<dtype> *newNode = new Node<dtype>;
		newNode->data = data;
		newNode->next = prevNode->next;
		newNode->prev = prevNode;

		prevNode->next = newNode;
		newNode->next->prev = newNode;

		size++;
		return newNode;
	}

	Node<dtype>* insertBefore(Node<dtype>* nextNode, dtype data)
	{
		if (getIndex(nextNode) <= cursor.index) cursor.index++;
		if (nextNode == head)
		{
			return pushNode(data);
		}
		Node<dtype> *newNode = new Node<dtype>;
		newNode->data = data;
		newNode->prev = nextNode->prev;
		newNode->next = nextNode;

		nextNode->prev = newNode;
		newNode->prev->next = newNode;

		size++;
		return newNode;
	}

	Node<dtype>* insertNode(int index, dtype data)
	{
		if (index == 0)
			return pushNode(data);
		else if (size > 1)
			return insertAfter(getNode(index - 1), data);
		else
			return appendNode(data);
	}


	Mark<dtype> getCursor()
	{
		return cursor;
	}

	Node<dtype>* getHead()
	{
		return head;
	}

	Node<dtype>* getTail()
	{
		return tail;
	}

	void addList(MyList<dtype> *list)
	{
		if (list->head != nullptr) {
			if (isEmpty()) {
				head = list->head;
				tail = list->tail;
			}
			else {
				tail->next = list->head;
				tail = list->tail;
			}
		}
		size += list->size;

	}

};


#endif