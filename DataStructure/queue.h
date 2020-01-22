#pragma once
#ifndef _QUEUE_H
#define _QUEUE_H
#include "QueueService.h"
#include <iostream>

template<class T>
class LoopQueue:public virtual QueueService<T> {
private:
	int mFront;//队首指针
	int mRear;//队尾指针
	T* mQueueArray;//队列底层数组
	int mCapacity;//队列容量
public:
	LoopQueue() :mCapacity(10), mFront(0), mRear(0) { mQueueArray = new T[mCapacity]; }
	LoopQueue(int capacity) :mCapacity(capacity), mFront(0), mRear(0) { mQueueArray = new T[capacity]; }
	~LoopQueue();
	bool isEmpty()const override;
	bool isFull()const;
	int size()const override;
	bool push(T data) override;
	bool pop() override;
	T front()const override;//队首指向的元素
	void print()override;
	template<class U>
	friend std::ostream& operator<<(std::ostream& os, const LoopQueue<U>& queue);
};

template<class T>
inline LoopQueue<T>::~LoopQueue()
{
	delete[] mQueueArray;
}

template<class T>
inline bool LoopQueue<T>::isEmpty()const
{
	return mFront==mRear;
}

template<class T>
inline bool LoopQueue<T>::isFull() const
{
	return (mRear + 1) % mCapacity == mFront;
}

template<class T>
inline int LoopQueue<T>::size() const
{
	return (mRear - mFront + mCapacity) % mCapacity;
}

template<class T>
inline bool LoopQueue<T>::push(T data)
{
	if(isFull())
		return false;
	mQueueArray[mRear++] = data;
	mRear %= mCapacity;
	return true;
}

template<class T>
inline bool LoopQueue<T>::pop()
{
	if(isEmpty())
		return false;
	mFront++;
	mFront %= mCapacity;
	return true;
}

template<class T>
inline T LoopQueue<T>::front()const
{
	if (isEmpty())
		throw ;
	return mQueueArray[mFront];
}

template<class T>
inline void LoopQueue<T>::print()
{
	operator<<(std::cout, *this);
}

template<class U>
inline std::ostream& operator<<(std::ostream& os,const LoopQueue<U>& queue)
{
	if (queue.isEmpty())	return os;
	for (int i = queue.mFront; i <= queue.mRear; i++)
		os << queue.mQueueArray[i] << " ";
	os << std::endl;
	return os;
}


template<class T>
using qNode=Node<T>;

template<class T>
class queue : public virtual QueueService<T> {
protected:
	qNode<T>* mHead;
	qNode<T>* mTail;
	int mCount;
public:
	queue() :mHead(nullptr), mTail(nullptr), mCount(0) {}
	~queue();
	bool isEmpty()const override;
	int size()const override;
	bool push(T data) override;
	bool pop() override;
	T front()const override;//队首指向的元素
	void print();
	template<class U>
	friend std::ostream& operator<<(std::ostream& os, const queue<U>& queue);
	//todo：要针对T为指针时的浅拷贝问题，和==,拷贝构造函数的问题
};

template<class T>
inline queue<T>::~queue()
{
	if (isEmpty()) return;
	while (mHead != nullptr)
	{
		qNode<T>* deleteNode = mHead;
		mHead = deleteNode->next;
		delete deleteNode;
		mCount--;
	}
	mHead = mTail = nullptr;
}

template<class T>
inline bool queue<T>::isEmpty() const
{
	return mHead==nullptr;
}

template<class T>
inline int queue<T>::size() const
{
	return mCount;
}

template<class T>
inline bool queue<T>::push(T data)
{
	if (mHead == nullptr)
	{
		mTail=mHead = new qNode<T>(data);
		if (mHead == nullptr) return false;
		mCount++;
	}
	else
	{
		qNode<T>* newNode = new qNode<T>(data);
		if (newNode == nullptr) return false;
		mTail->next = newNode;
		mTail = newNode;
		mCount++;
	}
	return true;
}

template<class T>
inline bool queue<T>::pop()
{
	if (isEmpty()) return false;
	qNode<T>* frontNode = mHead;
	mHead = frontNode->next;
	delete frontNode;
	mCount--;
	return true;
}

template<class T>
inline T queue<T>::front()const
{
	if (isEmpty()) throw;
	return mHead->data;
}

template<class T>
inline void queue<T>::print()
{
	operator<<(std::cout, *this);
}

template<class U>
inline std::ostream& operator<<(std::ostream& os, const queue<U>& queue)
{
	if (queue.isEmpty()) return os;
	qNode<U>* cur = queue.mHead;
	while (cur != nullptr)
	{
		os << cur->data << " ";
		cur = cur->next;
	}
	os << std::endl;
	return os;
}

template<class T>
class deque :public queue<T>
{
private:
	qNode<T>* qNodeForIndex(int index)const;
public:
	deque() = default;
	bool front_append(T data);
	bool back_append(T data);
	bool front_remove();
	bool back_remove();
	T& operator [](int index)const;
	template<typename U>
	friend std::ostream& operator<<(std::ostream& os, const deque<U>& deque);
};

template<class T>
inline qNode<T>* deque<T>::qNodeForIndex(int index) const
{
	//if (this->isEmpty() || index<0 || index>this->mCount - 1)
	if (queue<T>::isEmpty() || index<0 || index>queue<T>::mCount - 1)
		throw;
	qNode<T>* cur = queue<T>::mHead;//qNode<T>* cur = this->mHead;
	for (int i = 0; i < index; i++)
		cur = cur->next;
	return cur;
}

template<class T>
inline bool deque<T>::front_append(T data)
{
	if (queue<T>::mHead == nullptr)//this->mHead == nullptr
	{
		//this->mTail = this->mHead = new qNode<T>(data);
		if (queue<T>::mHead == nullptr) return false;
		//this->mTail = this->mHead = new qNode<T>(data);
		queue<T>::mTail = queue<T>::mHead = new qNode<T>(data);
		//if (this->mHead == nullptr) return false;
		if (queue<T>::mHead == nullptr) return false;
		queue<T>::mCount++;//this->mCount++;
	}
	else {
		qNode<T>* newNode = new qNode<T>(data);
		if (newNode == nullptr) return false;
		newNode->next = queue<T>::mHead;//newNode->next = this->mHead;
		queue<T>::mHead = newNode;//this->mHead=newNode;
		queue<T>::mCount++;//this->mCount++;
	}
	return true;
}

template<class T>
inline bool deque<T>::back_append(T data)
{
	return queue<T>::push(data);
}

template<class T>
inline bool deque<T>::front_remove()
{
	return queue<T>::pop();
}

template<class T>
inline bool deque<T>::back_remove()
{
	if (queue<T>::isEmpty()) return false;//if (this->isEmpty()) return false;
	qNode<T>* removeNode = queue<T>::mTail;//qNode<T>* removeNode =this->mTail;
	qNode<T>* preNode = qNodeForIndex(queue<T>::mCount - 2);
	queue<T>::mTail = preNode;//this->mTail = preNode;
	preNode->next = nullptr;
	delete removeNode;
	return true;
}

template<class T>
inline T& deque<T>::operator[](int index)const
{
	return qNodeForIndex(index)->data;
}

template<class U>
std::ostream& operator<<(std::ostream& os, const deque<U>& deque)
{
	return operator<<(os, (const queue<U>&)deque);//必须强制转换为父类对象，不转换会导致一直递归,死循环。
	
	//os << (const queue<U>&)deque;
	//return os;

	//if (deque.isEmpty()) return os;
	//qNode<U>* cur = deque.mHead;
	//while (cur != nullptr)
	//{
	//	os << cur->data << " ";
	//	cur = cur->next;
	//}
	//os << std::endl;
	//return os;
}
#endif // _QUEUE_H
