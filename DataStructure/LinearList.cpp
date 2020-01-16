#include "LinearList.h"
#include <exception>
#include <iostream>

template<typename T>
sNode<T>* sNode<T>::push_back(T newdata)
{
	sNode* newNode = new sNode();
	newNode->data = newdata;
	newNode->next = nullptr;
	sNode* head = next;
	while (head != nullptr)
	{
		head = head->next;
	}
	head->next = newNode;
	this.count++;
	return newNode;
}

template<typename T>
void sNode<T>::back_insert(T newdata,int insertIndex)
{
	if (next == nullptr && insertIndex != 0)
		return;
	if (insertIndex<0 || insertIndex>count)
		return;
	sNode* head = next;
	int index = 0;
	while (index<= insertIndex)
	{
		head = head->next;
		index++;
	}
	sNode* insertPostionNextNode = head->next;
	sNode* newNode = new sNode();
	newNode->data = newdata;
	newNode->next = insertPostionNextNode;
	head->next = newNode;
	count--;
}

template<typename T>
void sNode<T>::front_insert(T newdata, int index)
{
	back_insert(newdata, index - 1);
}

template<typename T>
void sNode<T>::remove(int removeIndex)
{
	if (removeIndex<1 || removeIndex>count)
		return;
	sNode* head = next;
	int index = 0;
	while (index <= removeIndex)
	{
		head = head->next;
	}
	sNode* nextNode = head->next;
	delete head;
	head->next = nextNode;
	count--;
}

template<typename T>
void sNode<T>::Remove(T removedata)
{
	sNode* head = next;
	while (head != nullptr)
	{
		head = head->next;
		if (head->data == removedata)
		{
			sNode* nextNode = head->next;
			delete head;
			head->next = nextNode;
			count--;
			break;
		}
	}
	if (head == nullptr)
		throw;
}

template<typename T>
void sNode<T>::length()
{
	return count;
}

template<typename T>
void sNode<T>::printList()
{
	sNode* head = next;
	while (head != nullptr)
	{
		std::cout << head->data << std::endl;
		head = head->next;
	}
}

template<typename T>
sNode<T>::~sNode()
{
	sNode* head = next;
	while (head != nullptr)
	{
		sNode* nextDeleteNode = head->next;
		delete head;
		head = nextDeleteNode;
	}
	count = 0;
}
