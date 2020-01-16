#pragma once
#ifndef _STACK_H
#define _STACK_H
#include <exception>
#include "node.h"

template<class T>
using stackNode=Node<T>;
//template<class T>
//class stackNode
//{
//public:
//	stackNode() :next(nullptr) {}
//	stackNode(T data) :data(data),next(nullptr) {};
//	T data;//值
//	stackNode* next;//指向下一个节点的指针
//};
template<typename T>
class stack
{
private:
	unsigned int mStackLength;
	stackNode<T>* mTopNode;
	stackNode<T>* mBaseNode;
public :
	stack();
	int Size()const;
	T Pop();
	bool IsEmpty()const;
	void Push(T data);
	T Top()const;
	void Clear();
	void PrintStack();
	template<class U>
	friend std::ostream& operator<<(std::ostream& os, const stack<U>& cStack);
	~stack();
};

template<typename T>
inline stack<T>::stack()
{
	mStackLength = 0;
	mTopNode = nullptr;
	mBaseNode = nullptr;
}

template<typename T>
inline int stack<T>::Size()const
{
	return mStackLength;
}

template<typename T>
inline T stack<T>::Pop()
{
	if (IsEmpty()) return T();
	T popData = mTopNode->data;
	stackNode<T>* popNode = mTopNode;
	mTopNode = mTopNode->next;
	delete popNode;
	popNode = nullptr;
	mStackLength--;
	return popData;
#pragma region top in LinearList tail
	//if (this->IsEmpty())
	//	return T();
	//stackNode<T>* popNode = mTopNode;
	//stackNode<T>* curNode = mBaseNode;
	//T popData = popNode->data;
	//while (curNode->next!= mTopNode)
	//{
	//	curNode = curNode->next;
	//}
	//mTopNode = curNode;
	//mTopNode->next = nullptr;
	//delete popNode;
	//mStackLength--;
	//return popData;
#pragma endregion
}

template<typename T>
inline bool stack<T>::IsEmpty()const
{
	if (mStackLength)
		return false;
	return true;
}

template<typename T>
inline void stack<T>::Push(T data)
{
	stackNode<T>* newStackNode = new stackNode<T>(data);
	newStackNode->next = mTopNode;
	mTopNode = newStackNode;
	mStackLength++;

#pragma region top in LinearList tail
	//if (mTopNode == nullptr)
	//{
	//	mBaseNode=mTopNode = new stackNode<T>(data);
	//	mStackLength++;
	//	return;
	//}
	//stackNode<T>* newStackNode = new stackNode<T>(data);
	//mTopNode->next = newStackNode;
	//mTopNode = newStackNode;
	//mStackLength++;
#pragma endregion
}

template<typename T>
inline T stack<T>::Top()const
{
	if (this->IsEmpty())
		return T();
	return mTopNode->data;
}

template<typename T>
inline void stack<T>::Clear()
{
	stackNode<T>* curNode = mTopNode;
	while (curNode != nullptr)
	{
		stackNode<T>* removeNode = curNode;
		curNode = curNode->next;
		delete removeNode;
		mStackLength--;
	}
	mBaseNode = mTopNode = nullptr;
#pragma region top in LinearList tail
	//stackNode<T>* curNode = mBaseNode;
	//while (curNode != nullptr)
	//{
	//	stackNode<T>* removeNode = curNode;
	//	curNode = curNode->next;
	//	delete removeNode;
	//	mStackLength--;
	//}
	//mBaseNode = mTopNode = nullptr;
#pragma endregion
}

template<typename T>
inline void stack<T>::PrintStack()
{
	operator<<(std::cout, *this);
}

template<class U>
inline std::ostream& operator<<(std::ostream& os, const stack<U>& cStack)
{
	if (cStack.mTopNode == nullptr)
		return os;
	stackNode<U>* curNode = cStack.mTopNode;
	while (curNode != nullptr)
	{
		os << curNode->data << " ";
		curNode = curNode->next;
	}
	os << std::endl;
#pragma region top in LinearList tail
	//if (cStack.mBaseNode == nullptr)
	//	return;
	//stackNode<U>* curNode = cStack.mBaseNode;
	//while (curNode != nullptr)
	//{
	//	os << curNode->data << " ";
	//	curNode = curNode->next;
	//}
	//os << std::endl;
#pragma endregion
	return os;
}

template<typename T>
inline stack<T>::~stack()
{
	Clear();
}


template<typename T>
class Stack
{
private:
	T* mStackArray;
	int mTop;
	int mCapacity;
public:
	Stack();
	int Size()const;

	T Pop();
	bool IsEmpty()const;
	void Push(T data);
	T Top()const;
	void Clear();
	void PrintStack();
	template<class U>
	friend std::ostream& operator<<(std::ostream& os, const Stack<U>& cStack);
	void Expand();
};
///
///
///
class outOfRange :public std::exception
{
public:
	const char* what()const 
	throw()
	{
		return "Error! Out Of Range.\n";
	}
};
class badSize :public std::exception
{
public:
	const char* what()const
	throw()
	{
		return "Error! Bad Size.\n";
	}
};
class FailedApplyForSpace :public std::exception
{
public:
	const char* what()const
	throw()
	{
		return "Error! Apply For Space Failed.\n";
	}
};

template<typename T>
inline Stack<T>::Stack()
{
	mStackArray = new T[10];
	if (!mStackArray) throw FailedApplyForSpace();
	mTop = -1;
	mCapacity = 10;
}

template<typename T>
inline int Stack<T>::Size()const
{
	return mTop+1;
}

template<typename T>
inline T Stack<T>::Pop()
{
	if (mTop == -1) throw outOfRange();
	return mStackArray[mTop--];
}

template<typename T>
inline bool Stack<T>::IsEmpty()const
{
	return mTop == -1;
}

template<typename T>
inline void Stack<T>::Push(T data)
{
	if (mTop == mCapacity-1)
		Expand();
	mStackArray[++mTop] = data;
}

template<typename T>
inline T Stack<T>::Top()const
{
	if (mTop == -1) throw outOfRange();
	return mStackArray[mTop];
}

template<typename T>
inline void Stack<T>::Clear()
{
	delete[] mStackArray;
	mStackArray = nullptr;
}

template<typename T>
inline void Stack<T>::PrintStack()
{
	operator<<(std::cout, *this);
}

template<class U>
inline std::ostream& operator<<(std::ostream& os, const Stack<U>& cStack)
{
	if (cStack.mTop == -1)return os;
	for (int i = 0; i < cStack.mTop; ++i)
		os << cStack.mStackArray[i] << " ";
	os << std::endl;
	return os;
}
template<typename T>
inline void Stack<T>::Expand()
{
	T* newStackArray = new T[mCapacity*2];
	if (newStackArray == nullptr)
		throw FailedApplyForSpace();
	for (int i = 0; i < mCapacity; i++)
		newStackArray[i] = mStackArray[i];
	mCapacity *= 2;
	delete[] mStackArray;
	mStackArray = newStackArray;
}
#endif
