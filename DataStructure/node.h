#pragma once
#ifndef _NODE_H
#define _NODE_H

template<class T>
class Node
{
public:
	Node() :next(nullptr) {}
	Node(T data) :data(data), next(nullptr) {};
	T data;//ֵ
	Node* next;//ָ����һ���ڵ��ָ��
};
#endif // !_NODE_H