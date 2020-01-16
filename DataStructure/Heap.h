#pragma once
#ifndef _HEAP_H
#define _HEAP_H
#include <ostream>
#include <string>

template<class T>
class Heap
{
public:
	Heap();
	Heap(int maxSize);
	Heap(T array[], int arrayLength);
	virtual bool BuildHeap() = 0;
	virtual bool Insert(T data) = 0;
	virtual T RemoveRoot() = 0;
	bool IsFull()const;
	bool IsEmpty()const;
	int Size()const;
	virtual ~Heap();
protected:
	T* mHeapTreeArray;
	int mSize;
	int mCapacity;
};

template<class T>
inline Heap<T>::Heap():mCapacity(10),mSize(0)
{
	mHeapTreeArray = new T[mCapacity];
	if (mHeapTreeArray == nullptr)
	{
		mCapacity = 0;
		throw;
	}
}

template<class T>
inline Heap<T>::Heap(int maxSize) :mSize(0), mCapacity(maxSize)
{
	mHeapTreeArray = new T[mCapacity];
	if (mHeapTreeArray == nullptr)
	{
		mCapacity = 0;
		throw;
	}
}

template<class T>
inline Heap<T>::Heap(T array[],int arrayLength):mCapacity(arrayLength * 2),mSize(arrayLength)
{
	mHeapTreeArray = new T[mCapacity];
	if (mHeapTreeArray == nullptr)
	{
		mCapacity = 0;
		throw;
	}
	for (int i = 0; i < arrayLength; i++)
	{
		mHeapTreeArray[i] = array[i];
	}
}

template<class T>
inline bool Heap<T>::IsFull()const
{
	return mSize == mCapacity;
}

template<class T>
inline bool Heap<T>::IsEmpty()const
{
	return mSize == 0;
}

template<class T>
inline int Heap<T>::Size() const
{
	return mSize;
}

template<class T>
inline Heap<T>::~Heap()
{
	delete[] mHeapTreeArray;
	mHeapTreeArray = nullptr;
	mSize = 0;
	mCapacity = 0;
}

template<class T>
class MaxHeap:public Heap<T>
{
public:
	MaxHeap() = default;//:Heap<T>() {};
	MaxHeap(int maxSize) :Heap<T>(maxSize) {};
	MaxHeap(T array[],int arrayLength) :Heap<T>(array, arrayLength) {};
	bool BuildHeap();
	bool Insert(T data);
	T RemoveRoot();
	~MaxHeap();
};

template<class T>
inline bool MaxHeap<T>::BuildHeap()//方法与删除节点类似
{
	if (this->IsEmpty()) return false;
	int child,parent;
	for (int i = this->mSize / 2; i > 0; i--)//先从最后一个有儿子的节点开始调整
	{
		T adjustElement = this->mHeapTreeArray[i - 1];
		for (parent = i; parent * 2 < this->mSize; parent = child)
		{
			child = parent * 2;
			if (child != this->mSize && this->mHeapTreeArray[child + 1 - 1] > this->mHeapTreeArray[child - 1])
				child++;
			if (adjustElement >= this->mHeapTreeArray[child - 1]) break;
			else
				this->mHeapTreeArray[parent - 1] = this->mHeapTreeArray[child - 1];
		}
		this->mHeapTreeArray[parent - 1] = adjustElement;
	}
	return true;
}

template<class T>
inline bool MaxHeap<T>::Insert(T data)//O(logN)
{
	if (this->IsFull()) return false;
	size_t i = ++this->mSize;
	for (; i > 1 && this->mHeapTreeArray[i / 2 - 1] < data; i /= 2)
	{
		this->mHeapTreeArray[i - 1] = this->mHeapTreeArray[i / 2 - 1];
	}
	this->mHeapTreeArray[i - 1] = data;
	return true;
}

template<class T>
inline T MaxHeap<T>::RemoveRoot()//RemoveMax
{
	if(this->IsEmpty())
		return T();
	int parent, child;
	T MaxItem = (this->mHeapTreeArray)[0];
	T lastItem = (this->mHeapTreeArray)[this->mSize - 1];
	this->mSize--;
	//从最大堆中最后一个元素从根节点开始向上与下层结点最大值进行比较
	(this->mHeapTreeArray)[0] = lastItem;//可去掉，帮助理解
	for (parent = 1; parent * 2 <= this->mSize; parent = child)//parent * 2 < = this->mSize用来判别是否有左儿子
	{
		child = parent * 2;
		if ((child != this->mSize) && ((this->mHeapTreeArray)[child - 1] < (this->mHeapTreeArray)[child + 1 - 1]))
			child++;//child指向左右儿子节点中较大的
		if (lastItem >= (this->mHeapTreeArray)[child - 1]) break;
		else
			(this->mHeapTreeArray)[parent - 1] = (this->mHeapTreeArray)[child - 1];
	}
	(this->mHeapTreeArray)[parent - 1] = lastItem;
	return MaxItem;
}

template<class T>
inline MaxHeap<T>::~MaxHeap()
{
	delete[] this->mHeapTreeArray;
	this->mHeapTreeArray = nullptr;
	this->mSize = 0;
}

template<class T>
class MinHeap :public Heap<T>
{
public:
	MinHeap() = default;//:Heap<T>() {}
	MinHeap(int maxSize) :Heap<T>(maxSize) {}
	MinHeap(T array[], int arrayLength) :Heap<T>(array, arrayLength) {}
	bool BuildHeap();
	bool Insert(T data);
	T RemoveRoot();
	~MinHeap() = default;
	friend std::ostream& operator<<(std::ostream& os, MinHeap<T>& minHeap);
};

template<class T>
inline bool MinHeap<T>::BuildHeap()//方法与删除节点类似
{
	if (this->IsEmpty()) return false;
	int child, parent;
	for (int i = this->mSize / 2; i > 0; i--)//先从最后一个有儿子的节点开始调整
	{
		T adjustElement = this->mHeapTreeArray[i - 1];
		for (parent = i; parent * 2 < this->mSize; parent = child)
		{
			child = parent * 2;
			if (child != this->mSize && this->mHeapTreeArray[child + 1 - 1] < this->mHeapTreeArray[child - 1])
				child++;
			if (adjustElement <= this->mHeapTreeArray[child - 1]) break;
			else
				this->mHeapTreeArray[parent - 1] = this->mHeapTreeArray[child - 1];
		}
		this->mHeapTreeArray[parent - 1] = adjustElement;
	}
	return true;
}

template<class T>
inline bool MinHeap<T>::Insert(T data)//O(logN)
{
	if (this->IsFull()) return false;
	size_t i = this->mSize++;
	for (; i > 1 && this->mHeapTreeArray[i / 2 - 1] > data; i /= 2)
	{
		this->mHeapTreeArray[i - 1] = this->mHeapTreeArray[i / 2 - 1];
	}
	this->mHeapTreeArray[i - 1] = data;
	return true;
}

template<class T>
inline T MinHeap<T>::RemoveRoot()//RemoveMin
{
	if (this->IsEmpty())
		return T();
	int parent, child;
	T MinItem = (this->mHeapTreeArray)[0];
	T lastItem = (this->mHeapTreeArray)[this->mSize - 1];
	this->mSize--;
	//从最小堆中最后一个元素从根节点开始向上与下层结点最小值进行比较
	(this->mHeapTreeArray)[0] = lastItem;//可去掉，帮助理解
	for (parent = 1; parent * 2 <= this->mSize; parent = child)
	{
		child = parent * 2;
		if ((child != this->mSize) && ((this->mHeapTreeArray)[child - 1] > (this->mHeapTreeArray)[child + 1 - 1]))
			child++;
		if (lastItem <= (this->mHeapTreeArray)[child - 1]) break;
		else
			(this->mHeapTreeArray)[parent - 1] = (this->mHeapTreeArray)[child - 1];
	}
	(this->mHeapTreeArray)[parent - 1] = lastItem;
	return MinItem;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, MinHeap<T>& minHeap)
{
	if (minHeap.IsEmpty()) return os;
	for (int i = 0; i < minHeap.mSize; i++)
	{
		os << minHeap.mHeapTreeArray[i]<< " ";
	}
	os << std::endl;
}

#pragma region Huffman Tree
template<typename T = int>
class HuffmanTreeNode {
public:
	T mWeight;
	HuffmanTreeNode* mLeft,*mRight;
	HuffmanTreeNode() :mLeft(nullptr), mRight(nullptr) {}
	HuffmanTreeNode(T weight) :mWeight(weight), mLeft(nullptr), mRight(nullptr) {}
};

template<typename T>
class MinHeap<HuffmanTreeNode<T>*>:public Heap< HuffmanTreeNode<T>*>
{
public:
	MinHeap();
	MinHeap(int maxSize);
	MinHeap(T array[], int arrayLength);
	bool BuildHeap();
	bool Insert(HuffmanTreeNode<T>* data);
	HuffmanTreeNode<T>* RemoveRoot();
	~MinHeap();
	template<typename U>
	friend std::ostream& operator<<(std::ostream& os, MinHeap<HuffmanTreeNode<U>*>& minHeap);
};

template<typename T>
inline MinHeap<HuffmanTreeNode<T>*>::MinHeap()//:this->mCapacity(10)
{
	this->mCapacity = 10;
	MinHeap(this->mCapacity);
}

template<typename T>
inline MinHeap<HuffmanTreeNode<T>*>::MinHeap(int maxSize)// :this->mCapacity(maxSize)
{
	this->mCapacity = maxSize;
	this->mHeapTreeArray = new HuffmanTreeNode<T> * [this->mCapacity];
	if (!this->mHeapTreeArray)
	{
		this->mCapacity = 0;
		throw;
	}
	//for (int i = 0; i < mCapacity; i++)
	//{
	//	HuffmanTreeNode<T>* huffmanTreeNode = new HuffmanTreeNode<T>();
	//	this->mHeapTreeArray[i] = huffmanTreeNode;
	//}
}

template<typename T>
inline MinHeap<HuffmanTreeNode<T>*>::MinHeap(T array[], int arrayLength)//:this->mCapacity(arrayLength*2),this->mSize(arrayLength)
{
	this->mCapacity = arrayLength * 2;
	this->mSize = arrayLength;
	MinHeap(this->mCapacity);
	for (int i = 0; i < arrayLength; i++)
	{
		HuffmanTreeNode<T>* huffmanTreeNode = new HuffmanTreeNode<T>(array[i]);
		this->mHeapTreeArray[i] = huffmanTreeNode;
	}
}

template<class T>
inline bool MinHeap<HuffmanTreeNode<T>*>::BuildHeap()//方法与删除节点类似
{
	if (this->IsEmpty()) return false;
	int child, parent;
	for (int i = this->mSize / 2; i > 0; i--)//先从最后一个有儿子的节点开始调整
	{
		HuffmanTreeNode<T>* adjustElement = this->mHeapTreeArray[i - 1];
		for (parent = i; parent * 2 < this->mSize; parent = child)
		{
			child = parent * 2;
			if (child != this->mSize && (this->mHeapTreeArray)[child + 1 - 1]->mWeight < (this->mHeapTreeArray)[child - 1]->mWeight)
				child++;
			if (adjustElement->mWeight <= (this->mHeapTreeArray)[child - 1]->mWeight) break;
			else
				(this->mHeapTreeArray)[parent - 1] = (this->mHeapTreeArray)[child - 1];
		}
		(this->mHeapTreeArray)[parent - 1] = adjustElement;
	}
	return true;
}

template<class T>
inline bool MinHeap<HuffmanTreeNode<T>*>::Insert(HuffmanTreeNode<T>* data)//O(logN)
{
	if (this->IsFull()) return false;
	size_t i = ++this->mSize;
	for (; i > 1 && (this->mHeapTreeArray)[i / 2 - 1]->mWeight > data->mWeight; i /= 2)
	{
		(this->mHeapTreeArray)[i - 1] = (this->mHeapTreeArray)[i / 2 - 1];
	}
	(this->mHeapTreeArray)[i - 1] = data;
	
	return true;
}

template<class T>
inline HuffmanTreeNode<T>* MinHeap<HuffmanTreeNode<T>*>::RemoveRoot()//RemoveMin
{
	if (this->IsEmpty())
		return nullptr;
	int parent, child;
	HuffmanTreeNode<T>* MinItem = (this->mHeapTreeArray)[0];
	HuffmanTreeNode<T>* lastItem = this->mHeapTreeArray[this->mSize - 1];
	this->mSize--;
	//从最小堆中最后一个元素从根节点开始向上与下层结点最小值进行比较
	this->mHeapTreeArray[0] = lastItem;//可去掉，帮助理解
	for (parent = 1; parent * 2 <= this->mSize; parent = child)
	{
		child = parent * 2;
		if ((child != this->mSize) && (this->mHeapTreeArray[child - 1]->mWeight > this->mHeapTreeArray[child + 1 - 1]->mWeight))
			child++;
		if (lastItem->mWeight <= this->mHeapTreeArray[child - 1]->mWeight) break;
		else
			this->mHeapTreeArray[parent - 1] = this->mHeapTreeArray[child - 1];
	}
	this->mHeapTreeArray[parent - 1] = lastItem;
	return MinItem;
}

template<typename T>
inline MinHeap<HuffmanTreeNode<T>*>::~MinHeap()
{
	if (this->mHeapTreeArray)
	{
		for (int i = 0; i < this->mSize; i++)
		{
			delete this->mHeapTreeArray[i];
			this->mHeapTreeArray[i] = nullptr;
		}
		delete[] this->mHeapTreeArray;
		this->mHeapTreeArray = nullptr;
		this->mSize = 0;
	}
}

template<typename U>
inline std::ostream& operator<<(std::ostream& os, MinHeap<HuffmanTreeNode<U>*>& minHeap)
{
	if (minHeap.IsEmpty()) return os;
	for (int i = 0; i < minHeap.mSize; i++)
	{
		os << minHeap.mHeapTreeArray[i]->mWeight << " ";
	}
	os << std::endl;
	return os;
}

template<typename T = int>
class HuffmanTree
{
private:
	HuffmanTreeNode<T>* mRoot;
	void PreOrderTraversal(HuffmanTreeNode<T>* huffmanTreeNode)const;
	void HuffmanCoded(HuffmanTreeNode<T>* huffmanTreeNode, std::string s);
	int WPL(HuffmanTreeNode<T>* huffmanTreeNode, int depth);//带权路径长度
public:
	HuffmanTree(MinHeap<HuffmanTreeNode<T>*>& minHeap);
	void PreOrderTraversal()const;
	void HuffmanCoded();//哈夫曼编码不唯一
	int GetBestCodeLen();//最有编码长度
};

template<typename T>
inline void HuffmanTree<T>::PreOrderTraversal(HuffmanTreeNode<T>* huffmanTreeNode) const
{
	if (huffmanTreeNode)
	{
		std::cout << huffmanTreeNode->mWeight << " ";
		PreOrderTraversal(huffmanTreeNode->mLeft);
		PreOrderTraversal(huffmanTreeNode->mRight);
	}
}

template<typename T>
inline void HuffmanTree<T>::HuffmanCoded(HuffmanTreeNode<T>* huffmanTreeNode, std::string s)
{
	if (huffmanTreeNode)
	{
		if (!huffmanTreeNode->mLeft && !huffmanTreeNode->mRight)
			std::cout << huffmanTreeNode->mWeight << " huffman code is " << s << std::endl;
		else{
			HuffmanCoded(huffmanTreeNode->mLeft, s + "0");
			HuffmanCoded(huffmanTreeNode->mRight, s + "1");
		}
	}
}

template<typename T>
inline int HuffmanTree<T>::WPL(HuffmanTreeNode<T>* huffmanTreeNode, int depth)
{
	if (huffmanTreeNode)
	{
		if (!huffmanTreeNode->mLeft && !huffmanTreeNode->mRight)
			return depth * huffmanTreeNode->mWeight;
		else return HuffmanCoded(huffmanTreeNode->mLeft, depth + 1) +
			HuffmanCoded(huffmanTreeNode->mRight, depth + 1);
	}
}

template<typename T>
inline HuffmanTree<T>::HuffmanTree(MinHeap<HuffmanTreeNode<T>*>& minHeap)//O(NlogN)
{
	minHeap.BuildHeap();
	int count = minHeap.Size();
	for (int i = 0; i < count -1; i++)
	{
		HuffmanTreeNode<T>* huffmanNode = new HuffmanTreeNode<T>();
		huffmanNode->mLeft = minHeap.RemoveRoot();
		huffmanNode->mRight = minHeap.RemoveRoot();
		huffmanNode->mWeight = huffmanNode->mLeft->mWeight + huffmanNode->mRight->mWeight;
		//std::cout <<i<<"---"<< minHeap.Size() << std::endl;
		minHeap.Insert(huffmanNode);
		//std::cout << i << "---" << minHeap.Size() << std::endl;
	}
	//std::cout << minHeap.Size() << std::endl;
	mRoot = minHeap.RemoveRoot();
	//std::cout << minHeap.Size()<<std::endl;
}
template<typename T>
inline void HuffmanTree<T>::PreOrderTraversal()const
{
	PreOrderTraversal(mRoot);
	std::cout << std::endl;
}
template<typename T>
inline void HuffmanTree<T>::HuffmanCoded()
{
	HuffmanCoded(mRoot, "");
}
template<typename T>
inline int HuffmanTree<T>::GetBestCodeLen()
{
	return WPL(mRoot, 0);
}
#endif // !_HEAP_H


