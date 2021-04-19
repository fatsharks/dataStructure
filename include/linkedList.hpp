#ifndef _FATSHARKS_LIST_H_
#define _FATSHARKS_LIST_H_

#include <iostream>
#include <global.hpp>

namespace myDataStructure
{
	// template<class T>;

	template<typename T> struct Node
	{
		T data;
		struct Node<T> *next;
	};

	template<typename T> class linkedList
	{
	private:
		Node<T> *head;
		int len_;

	public:
		linkedList();
		~linkedList();
		int getLenth() const;
		bool isEmpty();
		void createLinkedList(int _size);
		void printLinkedList();
		T getValue(int _index);
		Node<T> *findNode(T _data);
		void insertNode(Node<T> *_src, int _dst, int _size);
		void insertHead(Node<T> *_src, int _size);
		void insertEnd(Node<T> *_src, int _size);
		void deleteNode(Node<T> *_node);
		void deleteAll();
	};

	template<typename T> linkedList<T>::linkedList()
	{
		head = new Node<T>;
		head->data = 0;
		head->next = NULL;
	}

	template<typename T> linkedList<T>::~linkedList()
	{
		Node<T> *temp;
		while (head->next != NULL)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
		delete head;
	}

	template<typename T> inline int linkedList<T>::getLenth() const
	{
		return len_;
	}

	template<typename T> inline bool linkedList<T>::isEmpty()
	{
		if (head->next == NULL)
			return true;
		else
			return false;
	}

	template<typename T> T linkedList<T>::getValue(int _index)
	{
		int count = 0;
		Node<T> *temp = head;
		while (count < _index)
		{
			temp->next = temp;
		}
		return temp->data;
	}

	template<typename T> void linkedList<T>::printLinkedList()
	{
		int count = 0;
		while (head->next != NULL)
		{
			count++;
			std::cout << "node number: " << count << ", data： " << head->data << std::endl;
		}
	}

	template<typename T> void linkedList<T>::createLinkedList(int _size)
	{
		Node<T> *tempNode, *newNode;
		tempNode = head;
		if (_size < 0)
		{
			std::cout << "size of list error, put again please" << std::endl;
		}
		else
		{
			for (; len_ < _size; len_++)
			{
				std::cout << "No. " << len_++ << "please put the data: ";
				newNode = new Node<T>;
				std::cin >> newNode->data;
				std::cout << std::endl;
				newNode->next = NULL;
				tempNode->next = newNode;
				tempNode = newNode;
			}
		}
	}

	template<typename T> Node<T> *linkedList<T>::findNode(T _data)
	{
		Node<T> *p = head;
		if (p->next == NULL)
			std::cout << "list is empty!" << std::endl;
		else
		{
			while (p->next != NULL)
			{
				p = p->next;
				if (p->data == _data)
					return p;
			}
			return NULL;
		}
	}

	template<typename T> void linkedList<T>::insertNode(Node<T> *_src, int _dst, int _size)
	{
		Node<T> *pleft, *pnew, *pright;
		pleft = head;
		for (int i = 0; i < _dst; i++)
			pleft = pleft->next;
		pright = pleft->next;

		for (int i = 0; i < _size; i++)
		{
			if (_src->next == NULL)
			{
				return;
			}
			else
			{
				pnew = new Node<T>;
				pnew->data = _src->data;
				_src = _src->next;
				pleft->next = pnew;
				pleft = pnew;
				len_++;
			}
		}
		pleft->next = pright;
	}

	template<typename T> void linkedList<T>::insertHead(Node<T> *_src, int _size)
	{
		insertNode(_src, 0, _size);
	}

	template<typename T> void linkedList<T>::insertEnd(Node<T> *_src, int _size)
	{
		insertNode(_src, len_++, _size);
	}

	template<typename T> void linkedList<T>::deleteNode(Node<T> *_node)
	{
		Node<T> *pleft = head;
		while (pleft->next != NULL)
		{
			if (pleft->next = _node)
			{
				delete pleft->next;
				pleft->next = _node->next;
			}
		}
	}

	template<typename T> void linkedList<T>::deleteAll()
	{
		Node<T> *temp;
		while (head->next != NULL)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}
}

#endif