#pragma once
#ifndef _LINEARLIST_H
#define _LINEARLIST_H
#include <exception>
#include <iostream>

template <typename T>
class listNode
{
private:
	listNode* next;
	T data;
	int count;
	void _PushBack(const T& newdata)
	{
		listNode* newNode = new listNode();
		newNode->data = newdata;
		newNode->next = nullptr;
		listNode* head = next;
		if (head == nullptr)
		{
			next = newNode;
			count++;
			return;
		}
		while (head->next != nullptr)
		{
			head = head->next;
		}
		head->next = newNode;
		count++;
	}

	void _BackInsert(const int& insertIndex, const T& newdata)
	{
		if (next == nullptr && insertIndex != 0)
			return;
		if (insertIndex<0 || insertIndex>count)
			return;
		listNode* head = next;
		int index = 1;
		while (index < insertIndex)
		{
			head = head->next;
			index++;
		}
		listNode* insertPostionNextNode = head->next;
		listNode* newNode = new listNode();
		newNode->data = newdata;
		newNode->next = insertPostionNextNode;
		head->next = newNode;
		count++;
	}
	void _FrontInsert(const int& index, const T& newdata)
	{
		_BackInsert(index - 1, newdata);
	}
	void _Remove(const int& removeIndex)
	{
		if (removeIndex<1 || removeIndex>count)
			return;
		listNode* head = next;
		int index = 1;
		while (index < removeIndex - 1)
		{
			head = head->next;
			index++;
		}
		if (head->next == nullptr)
			return;
		listNode* preNode = head;
		listNode* removeNode = head->next;
		listNode* nextNode = removeNode->next;
		preNode->next = nextNode;
		delete removeNode;
		removeNode = nullptr;
		count--;
	}
	void _RemoveBaseOnData(const T& removedata)
	{
		listNode* head = next;
		listNode* preNode = nullptr;
		while (head != nullptr)
		{
			if (head->data == removedata)
			{
				listNode* nextNode = head->next;
				listNode* removeNode = head;
				preNode->next = nextNode;
				delete removeNode;
				count--;
				break;
			}
			preNode = head;
			head = head->next;
		}
		if (head == nullptr)
			throw;
	}
public:
	listNode() :next(nullptr), count(0) {}
	listNode& PushBack(const T& newdata)
	{
		_PushBack(newdata);
		return *this;
	}

	listNode& BackInsert(const int& insertIndex, const T& newdata)
	{
		_BackInsert(insertIndex, newdata);
		return *this;
	}

	listNode& FrontInsert(const int& index, const T& newdata)
	{
		_FrontInsert(index, newdata);
		return *this;
	}

	listNode& Remove(const int& removeIndex)
	{
		_Remove(removeIndex);
		return *this;
	}

	listNode& RemoveBaseOnData(const T& removedata)
	{
		_RemoveBaseOnData(removedata);
		return *this;
	}

	int Length()const
	{
		return count;
	}

	void PrintList()const
	{
		operator <<(std::cout, *this);
	}

	friend std::ostream& operator <<(std::ostream& os,const listNode<T>* list)
	{
		return operator <<(os, *list);
	}

	friend std::ostream& operator <<(std::ostream& os, const listNode<T>& list)
	{
		if (!list.next) return os;
		listNode* head = list.next;
		while (head != nullptr)
		{
			os << head->data << " ";
			head = head->next;
		}
		os << std::endl;
		return os;
	}
	~listNode()
	{
	}

	void Release()
	{
		if (next == nullptr) return;
		listNode* head = next;
		while (head != nullptr)
		{
			listNode* deleteNode = head;
			head = deleteNode->next;
			delete deleteNode;
			count--;
		}
		next = nullptr;
	}

	T& operator [](int index)const
	{
		if (index <0 || index >count - 1 || next == nullptr)
			throw;
		listNode* head = next;
		for (size_t i = 0; i < index; ++i)
		{
			head = head->next;
		}
		return head->data;
	}

	void ReverseList(int index)
	{
		if (index <0 || index >count - 1 || next == nullptr)
			throw;
		listNode<T>* head = next;
		listNode<T>* nextNode = head->next;
		listNode<T>* nextNextNode = nullptr;
		for (size_t i = 0; i < index; i++)
		{
			if (nextNode)
				nextNextNode = nextNode->next;
			else nextNextNode = nullptr;
			nextNode->next = head;
			head = nextNode;
			nextNode = nextNextNode;
			if (nextNextNode)
				nextNextNode = nextNextNode->next;
			else nextNextNode = nullptr;
		}
		this->next->next = nextNode;
		this->next = head;
	}
};
template<typename T>
using List =listNode<T>;
#endif