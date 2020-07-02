#pragma once
#ifndef _LINEARLIST_H
#define _LINEARLIST_H

#include "Node.h"
#include <exception>
#include <iostream>
#include <initializer_list>
#include "Exception.h"

template <typename T>
class LList
{
private:
	Node<T>* m_Head;
	int count;
	void _PushBack(const T& newdata)
	{
		try {
			Node<T>* newNode = new Node<T>(newdata);
			if (!newNode) throw FailedApplyForSpace();
			newNode->next = nullptr;
			Node<T>* head = m_Head;
			if (!head)
			{
				m_Head = newNode;
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
		catch (std::exception & e)
		{
			std::cout << e.what() << '\n';
		}
	}

	void _BackInsert(const int& insertIndex, const T& newdata)
	{
		if (!m_Head && insertIndex != 0)
			return;
		if (insertIndex<0 || insertIndex>count)
			return;
		Node<T>* head = m_Head;
		int index = 1;
		while (index < insertIndex)
		{
			head = head->next;
			index++;
		}
		Node<T>* insertPostionNextNode = head->next;
		Node<T>* newNode = new Node<T>(newdata);
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
		Node<T>* head = m_Head;
		int index = 1;
		while (index < removeIndex - 1)
		{
			head = head->next;
			index++;
		}
		if (!head->next)
			return;
		Node<T>* preNode = head;
		Node<T>* removeNode = head->next;
		Node<T>* nextNode = removeNode->next;
		preNode->next = nextNode;
		delete removeNode;
		removeNode = nullptr;
		count--;
	}
	void _RemoveBaseOnData(const T& removedata)
	{
		Node<T>* head = m_Head;
		Node<T>* preNode = nullptr;
		while (head)
		{
			if (head->data == removedata)
			{
				Node<T>* nextNode = head->next;
				Node<T>* removeNode = head;
				preNode->next = nextNode;
				delete removeNode;
				count--;
				break;
			}
			preNode = head;
			head = head->next;
		}
		if (!head)
			std::cerr << "this data is not exist£¡" << '\n';
	}
public:
	LList() :m_Head(nullptr), count(0) {}
	LList(std::initializer_list<T> list)
	{
		if (!list.size()) return;
		m_Head = new Node<T>(*list.begin());
		Node<T>* head = m_Head;
		for (auto iter = list.begin() + 1; iter != list.end(); ++iter)
		{
			try {
				Node<T>* newNode = new Node<T>(*iter);
				if (!newNode) throw FailedApplyForSpace();
				head->next = newNode;
				head = newNode;
			}
			catch (std::exception & e)
			{
				std::cout << e.what() << '\n';
			}
		}
	}
	LList& PushBack(const T& newdata)
	{
		_PushBack(newdata);
		return *this;
	}

	LList& BackInsert(const int& insertIndex, const T& newdata)
	{
		_BackInsert(insertIndex, newdata);
		return *this;
	}

	LList& FrontInsert(const int& index, const T& newdata)
	{
		_FrontInsert(index, newdata);
		return *this;
	}

	LList& Remove(const int& removeIndex)
	{
		_Remove(removeIndex);
		return *this;
	}

	LList& RemoveBaseOnData(const T& removedata)
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

	friend std::ostream& operator <<(std::ostream& os,const LList* list)
	{
		return operator <<(os, *list);
	}

	friend std::ostream& operator <<(std::ostream& os, const LList& list)
	{
		if (!list.m_Head) return os;
		Node<T>* head = list.m_Head;
		while (head)
		{
			os << head->data << " ";
			head = head->next;
		}
		//os << std::endl;
		return os;
	}
	~LList()
	{
		Release();
	}

	void Release()
	{
		if (!this->m_Head) return;
		Node<T>* head = m_Head;
		while (head)
		{
			Node<T>* deleteNode = head;
			head = deleteNode->next;
			delete deleteNode;
			count--;
		}
		m_Head = nullptr;
	}

	T& operator [](int index)const
	{
		try {
			if (index <0 || index >count - 1 || !m_Head)
				throw new OutOfRange();
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
		Node<T>* head = m_Head;
		for (int i = 0; i < index; ++i)
		{
			head = head->next;
		}
		return head->data;
	}

	void ReverseList(int index)
	{
		try{
			if (index <0 || index >count - 1 || !m_Head)
				throw new OutOfRange();
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << '\n';
		}
		Node<T>* head = m_Head;
		Node<T>* nextNode = head->next;
		Node<T>* nextNextNode = nullptr;
		for (int i = 0; i < index; i++)
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
		this->m_Head->next = nextNode;
		this->m_Head = head;
	}

	void Reverse(int index)
	{
		try {
			if (index <0 || index >count - 1 || !m_Head)
				throw new OutOfRange();
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << '\n';
		}
		Node<T>* cur = m_Head->next;
		Node<T>* reversePartTail = m_Head;
		for (int i = 1; i < index; i++)
		{
			Node<T>* nextNode = cur->next;
			cur->next = m_Head;
			m_Head = cur;
			cur = nextNode;
		}
		reversePartTail->next = cur;
	}
};
template<typename T>
using List =LList<T>;
#endif