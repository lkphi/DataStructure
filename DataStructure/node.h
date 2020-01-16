#pragma once
#ifndef _NODE_H
#define _NODE_H

template<class T>
class Node
{
public:
	Node() :next(nullptr) {}
	Node(T data) :data(data), next(nullptr) {};
	T data;//值
	Node* next;//指向下一个节点的指针
};
#endif // !_NODE_H