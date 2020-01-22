#pragma once
#ifndef _NODE_H
#define _NODE_H

template<class T>
class Node
{
public:
	Node() :next(nullptr) {}
	explicit Node(const T& data) :data(data), next(nullptr) {};
	T data;//ֵ
	Node<T>* next;//ָ����һ���ڵ��ָ��
	~Node()
	{
		if (!next)
		{
			delete next;
			next = nullptr;
		}
	}
};
#endif // !_NODE_H