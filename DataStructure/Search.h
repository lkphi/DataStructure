#pragma once
#ifndef _SEARCH_H
#define _SEARCH_H
#include "Tree.h"
#include <cmath>

template<typename type>
int BinarySearch(type* arrayAfterSort, unsigned int arrayLength,type searchData)
{
	if (arrayAfterSort == nullptr || arrayLength == 0)
		return -1;
	unsigned int left = 0;
	unsigned int right = arrayLength -1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;//(left + right) / 2;可能会发生溢出现象
		if (*(arrayAfterSort+mid) > searchData)
			right = mid - 1;
		else if (*(arrayAfterSort + mid) < searchData)
			left = mid + 1;
		else return mid;
	}
	return -1;
}

//时间复杂度：平均情况O(loglog(N))，最坏O(logN)
//对于数据量较大，关键字分布均匀的查找表情况好
template<typename type>
int InsertSearch(type* arrayAfterSort, unsigned int arrayLength, type searchData)
{
	if (arrayAfterSort == nullptr || arrayLength == 0)
		return -1;
	unsigned int left = 0;
	unsigned int right = arrayLength - 1;
	while (left <= right)
	{
		int mid = left + (right - left) * (searchData - arrayAfterSort[left])
			/ (arrayAfterSort[right] - arrayAfterSort[left]);//(left + right) / 2;可能会发生溢出现象
		if (*(arrayAfterSort + mid) > searchData)
			right = mid - 1;
		else if (*(arrayAfterSort + mid) < searchData)
			left = mid + 1;
		else return mid;
	}
	return -1;
}

template<typename T>
class BinSearchTree :public BiTree<T>
{
protected:
	BiNode<T>* Find(T data, BiNode<T>* bsTree);
	BiNode<T>* FindMin(BiNode<T>* bsTree);
	BiNode<T>* FindMax(BiNode<T>* bsTree);
	BiNode<T>* _Insert(T data, BiNode<T>* bsTree, bool& isInsertSucess);
	int GetLeftTreeLength(int treeArrayLength);
	void GetCompleteBinTree(T* sortArray, int left, int right, T* completeBinTreeArray, int root);
	virtual BiNode<T>* Remove(T data, BiNode<T>* bsTree);
	bool CheckSame(BiNode<T>* bsTree,T data);
	void ResetFlag(BiNode<T>* bsTree);
	virtual void Release(BiNode<T>* bsTree);
public:
	BinSearchTree() = default;
	bool BuildBSTTree(int nodeCount);
	BiNode<T>* Find(T data);
	BiNode<T>* FindMin();
	BiNode<T>* FindMax();
	virtual bool Insert(T data);
	virtual bool Remove(T data);
	void GetCompleteBinTree(T* sortArray, int arrayLength, T* completeBinTreeArray);
	bool JugeSame(int nodeCount);
	void ResetFlag();
	void Release();
	virtual ~BinSearchTree() { Release(); }
};

template<typename T>
inline BiNode<T>* BinSearchTree<T>::Find(T data, BiNode<T>* bsTree)
{
	#pragma region solution1
	//if (!bstTree) return nullptr;
	//if (data > bstTree->data)
	//	return Find(data, bstTree->mRChild);
	//else if (data < bstTree.data)
	//	return Find(data, bstTree->mLChild)
	//else return bstTree;
	#pragma endregion

	while (bsTree)
	{
		if (data > bsTree->data)
			bsTree = bsTree->mRChild;
		else if (data < bsTree->data)
			bsTree = bsTree->mLChild;
		else return bsTree;
	}
	return nullptr;
}

template<typename T>
inline BiNode<T>* BinSearchTree<T>::FindMin(BiNode<T>* bsTree)
{
	#pragma region solution1
	//if (!bsTree) return nullptr;
	//else if (!bsTree->mLChild)
	//	return bsTree;
	//else return FindMin(bsTree->mLChild);
	#pragma endregion
	if (bsTree)
	{
		while (bsTree->mLChild)
			bsTree = bsTree->mLChild;
		return bsTree;
	}
	else return nullptr;
}

template<typename T>
inline BiNode<T>* BinSearchTree<T>::FindMax(BiNode<T>* bsTree)
{
	if (bsTree)
	{
		while (bsTree->mRChild)
			bsTree = bsTree->mRChild;
		return bsTree;
	}
	else return nullptr;
}

template<typename T>
inline BiNode<T>* BinSearchTree<T>::_Insert(T data, BiNode<T>* bsTree, bool& isInsertSucess)
{
	if (!bsTree)//若树为空
	{
		bsTree = new BiNode<T>(data);
		//bsTree->mLChild = bsTree->mRChild = nullptr;
		bsTree->nodeApperanceTimes = 0;
		isInsertSucess = true;
	}
	else
	{
		if (data < bsTree->data)
			bsTree->mLChild = _Insert(data, bsTree->mLChild, isInsertSucess);
		if (data > bsTree->data)
			bsTree->mRChild = _Insert(data, bsTree->mRChild, isInsertSucess);
	}
	//若data已存在,则什么也不做
	return bsTree;
}

template<typename T>
inline int BinSearchTree<T>::GetLeftTreeLength(int treeArrayLength)
{
	int treeHeight = (int)floor(log2(treeArrayLength + 1));
	int mayLastLevelCount = treeArrayLength + 1 - (int)pow(2, treeHeight);
	int maxLastLevelCount = (int)pow(2, treeHeight - 1);
	int rightChildLen = mayLastLevelCount < maxLastLevelCount ? mayLastLevelCount : maxLastLevelCount;
	return (int)pow(2, treeHeight - 1) - 1 + rightChildLen;
}

template<typename T>
inline void BinSearchTree<T>::GetCompleteBinTree(T* sortArray, int left, int right, T* completeBinTreeArray, int rootIndex)
{
	int count = right - left + 1;
	if (!count) return;
	int leftTreeLen = GetLeftTreeLength(count);//计算count个结点的树的左子树的结点个数
	completeBinTreeArray[rootIndex] = sortArray[left + leftTreeLen];
	int leftTreeIndex = (rootIndex << 1) + 1;//rootIndex * 2 + 1;
	int rightTreeIndex = leftTreeIndex + 1;
	GetCompleteBinTree(sortArray, left, left + leftTreeLen - 1, completeBinTreeArray, leftTreeIndex);
	GetCompleteBinTree(sortArray, left + leftTreeLen + 1, right, completeBinTreeArray, rightTreeIndex);
}

template<typename T>
inline BiNode<T>* BinSearchTree<T>::Remove(T data, BiNode<T>* bsTree)
{
	if (!bsTree) return nullptr;
	else if (data < bsTree->data)
		bsTree->mLChild = Remove(data, bsTree->mLChild);
	else if (data > bsTree->data)
		bsTree->mRChild = Remove(data, bsTree->mRChild);
	else {//在data == bsTree->data，即找到data的条件下
		if (bsTree->mLChild && bsTree->mRChild)//被删除的节点有两个子结点
		{
			BiNode<T>* minChild=FindMin(bsTree->mRChild);
			//在右子树中找到最小的元素填充删除结点
			bsTree->data = minChild->data;
			bsTree->mRChild = Remove(bsTree->data, bsTree->mRChild);//在右子树中删除最小的元素
		}
		else//被删除的结点有一个或无子结点
		{
			BiNode<T>* minChild = bsTree;
			if (!bsTree->mLChild)//有右孩子或无子结点
				bsTree = bsTree->mRChild;
			else if (!bsTree->mRChild)//有左孩子或无子结点
				bsTree = bsTree->mLChild;
			delete minChild;
		}
	}
	return bsTree;
}

template<typename T>
inline bool BinSearchTree<T>::CheckSame(BiNode<T>* bsTree, T data)
{
	if (!bsTree) return false;
	if (bsTree->nodeApperanceTimes)
	{
		if (data < bsTree->data) return CheckSame(bsTree->mLChild, data);
		else if (data > bsTree->data) return CheckSame(bsTree->mRChild, data);
		else return false;
	}
	else
	{
		if (data == bsTree->data)
		{
			bsTree->nodeApperanceTimes = 1;
			return true;
		}
		else return false;
	}
}

template<typename T>
inline void BinSearchTree<T>::ResetFlag(BiNode<T>* bsTree)
{
	if (bsTree->mLChild) ResetFlag(bsTree->mLChild);
	if (bsTree->mRChild) ResetFlag(bsTree->mRChild);
	if (bsTree) bsTree->nodeApperanceTimes = 0;
}

template<typename T>
inline void BinSearchTree<T>::Release(BiNode<T>* bsTree)
{
	if (bsTree->mLChild) Release(bsTree->mLChild);
	if (bsTree->mRChild) Release(bsTree->mRChild);
	if (bsTree)
	{
		delete bsTree;
		bsTree = nullptr;
	}
}

template<typename T>
inline bool BinSearchTree<T>::BuildBSTTree(int nodeCount)
{
	T data;
	for (int i = 0; i < nodeCount; i++)
	{
		std::cin >> data;
		if (!Insert(data))
		{
			std::cout << "bulid binary search tree failed!" << std::endl;
			return false;
		}
	}
	return true;
}

template<typename T>
inline BiNode<T>* BinSearchTree<T>::Find(T data)
{
	return Find(data, this->mRoot);
}

template<typename T>
inline BiNode<T>* BinSearchTree<T>::FindMin()
{
	return FindMin(this->mRoot);
}

template<typename T>
inline BiNode<T>* BinSearchTree<T>::FindMax()
{
	return FindMax(this->mRoot);
}

template<typename T>
inline bool BinSearchTree<T>::Insert(T data)
{
	bool isInsertSucess = false;
	this->mRoot = _Insert(data, this->mRoot, isInsertSucess);
	return isInsertSucess ? true : false;
}

template<typename T>
inline bool BinSearchTree<T>::Remove(T data)
{
	if (Remove(data, this->mRoot)) return true;
	else return false;
}

template<typename T>
inline void BinSearchTree<T>::GetCompleteBinTree(T* sortArray, int arrayLength, T* completeBinTreeArray)
{
	if (!sortArray || arrayLength < 0)
		return;
	if(!completeBinTreeArray)
		completeBinTreeArray = new T[arrayLength];
	if (!completeBinTreeArray) throw;
	GetCompleteBinTree(sortArray, 0, arrayLength - 1, completeBinTreeArray, 0);
}

template<typename T>
inline bool BinSearchTree<T>::JugeSame(int nodeCount)
{
	T data;
	ResetFlag();
	std::cout << "please input tree data(use levelOrder):\n";
	for (int i = 0; i < nodeCount; i++)
	{
		std::cin >> data;
		//if (data != this->mRoot->data) return false;
		//else this->mRoot->nodeApperanceTimes = 1;
		if (!CheckSame(this->mRoot,data)) return false;
		
	}
	return true;
}

template<typename T>
inline void BinSearchTree<T>::ResetFlag()
{
	ResetFlag(this->mRoot);
}

template<typename T>
inline void BinSearchTree<T>::Release()
{
	Release(this->mRoot);
	this->mRoot = nullptr;
}

template <typename T>
class BalanceBinTree : public BinSearchTree<T>
{
private:
	BiNode<T>* _Insert(T data, BiNode<T>* bsTree, bool& isHeightChanged, bool& isInsertSucess);
	BiNode<T>* LeftBalance(BiNode<T>* troubleNode);
	BiNode<T>* RightBalance(BiNode<T>* troubleNode);
	BiNode<T>* LLRotate(BiNode<T>* troubleNode);
	BiNode<T>* LRRotate(BiNode<T>* troubleNode);
	BiNode<T>* RRRotate(BiNode<T>* troubleNode);
	BiNode<T>* RLRotate(BiNode<T>* troubleNode);
public:
#define LeftHigher 1
#define	EqualHigh 0
#define	RightHigher -1
	bool Insert(T data);
	~BalanceBinTree() = default;
};

template<typename T>
inline BiNode<T>* BalanceBinTree<T>::_Insert(T data, BiNode<T>* bsTree, bool& isHeightChanged, bool& isInsertSucess)
{
	if (!bsTree)//若树为空
	{
		bsTree = new BiNode<T>(data);
		//bsTree->mLChild = bsTree->mRChild = nullptr;
		//bsTree->nodeApperanceTimes = 0;
		bsTree->balanceFactor = EqualHigh;
		isHeightChanged = true;
		isInsertSucess = true;
	}
	else {
		if (data < bsTree->data)
		{
			bsTree->mLChild = _Insert(data, bsTree->mLChild, isHeightChanged, isInsertSucess);
			if (isHeightChanged)
			{
				switch (bsTree->balanceFactor)
				{
					case LeftHigher: 
						isHeightChanged = false;
						return LeftBalance(bsTree);
					case EqualHigh:
						bsTree->balanceFactor = LeftHigher; 
						isHeightChanged = true; break;
					case RightHigher:
						bsTree->balanceFactor = EqualHigh; 
						isHeightChanged = false; break;
				}
			}
		}
		else if (data > bsTree->data) {
			bsTree->mRChild = _Insert(data, bsTree->mRChild, isHeightChanged, isInsertSucess);
			if (isHeightChanged)
			{
				switch (bsTree->balanceFactor)
				{
					case LeftHigher:
						bsTree->balanceFactor = EqualHigh; 
						isHeightChanged = false; break;
					case EqualHigh:
						bsTree->balanceFactor = RightHigher; 
						isHeightChanged = true;  break;
					case RightHigher:
						isHeightChanged = false;
						return RightBalance(bsTree);
				}
			}
		}
	}
	return bsTree;
}

template<typename T>
inline BiNode<T>* BalanceBinTree<T>::LeftBalance(BiNode<T>* findNode)
{
	switch (findNode->mLChild->balanceFactor)
	{
		case LeftHigher:
			findNode->balanceFactor = findNode->mLChild->balanceFactor = EqualHigh;
			return LLRotate(findNode);
		case RightHigher:
			switch (findNode->mLChild->mRChild->balanceFactor)
			{
				case LeftHigher:
					findNode->balanceFactor = RightHigher;
					findNode->mLChild->balanceFactor = EqualHigh;
					break;
				case EqualHigh:
					findNode->balanceFactor = findNode->mLChild->balanceFactor = EqualHigh;
					break;
				case RightHigher:
					findNode->balanceFactor = EqualHigh;
					findNode->mLChild->balanceFactor = LeftHigher;
					break;
			}	
			findNode->mLChild->mRChild->balanceFactor = EqualHigh;
			return LRRotate(findNode);
		default:return findNode;
	}
}

template<typename T>
inline BiNode<T>* BalanceBinTree<T>::RightBalance(BiNode<T>* findNode)
{
	switch (findNode->mRChild->balanceFactor)
	{
		case LeftHigher:
			switch (findNode->mRChild->mLChild->balanceFactor)
			{
				case LeftHigher:
					findNode->balanceFactor = EqualHigh;
					findNode->mRChild->balanceFactor = RightHigher;
					break;
				case EqualHigh:
					findNode->balanceFactor = findNode->mRChild->balanceFactor = EqualHigh;
					break;
				case RightHigher:
					findNode->balanceFactor = LeftHigher;
					findNode->mRChild->balanceFactor = EqualHigh;
					break;
			}
			findNode->mRChild->mLChild->balanceFactor = EqualHigh;
			return RLRotate(findNode);
		case RightHigher:
			findNode->balanceFactor = findNode->mRChild->balanceFactor = EqualHigh;
			return RRRotate(findNode);
		default:return findNode;
	}
}

template<typename T>
inline BiNode<T>* BalanceBinTree<T>::LLRotate(BiNode<T>* findNode)
{
	BiNode<T>* newRoot = findNode->mLChild;
	findNode->mLChild = newRoot->mRChild;
	newRoot->mRChild = findNode;
	return newRoot;
}

template<typename T>
inline BiNode<T>* BalanceBinTree<T>::LRRotate(BiNode<T>* findNode)
{
	//BiNode<T>* newRoot = findNode->mLChild->mRChild;
	//findNode->mLChild->mRChild = newRoot->mLChild;
	//newRoot->mLChild = findNode->mLChild;
	//findNode->mLChild = newRoot->mRChild;
	//newRoot->mRChild = findNode;
	BiNode<T>* newRoot = RRRotate(findNode->mLChild);
	findNode = LLRotate(findNode);
	return newRoot;
}

template<typename T>
inline BiNode<T>* BalanceBinTree<T>::RRRotate(BiNode<T>* findNode)
{
	BiNode<T>* newRoot = findNode->mRChild;
	findNode->mRChild = newRoot->mLChild;
	newRoot->mLChild = findNode;
	return newRoot;
}

template<typename T>
inline BiNode<T>* BalanceBinTree<T>::RLRotate(BiNode<T>* findNode)
{
	//BiNode<T>* newRoot = findNode->mRChild->mLChild;
	//findNode->mRChild->mLChild = newRoot->mRChild;
	//newRoot->mRChild = findNode->mRChild;
	//findNode->mRChild = newRoot->mLChild;
	//newRoot->mLChild = findNode;
	BiNode<T>* newRoot = LLRotate(findNode->mRChild);
	findNode = RRRotate(findNode);
	return newRoot;
}

template<typename T>
inline bool BalanceBinTree<T>::Insert(T data)
{
	bool isInsertSucess = false;
	bool isHeightChaged = false;
	this->mRoot = _Insert(data, this->mRoot, isHeightChaged, isInsertSucess);
	return isInsertSucess ? true : false;
}

#endif // _SEARCH_H