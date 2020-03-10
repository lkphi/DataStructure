#pragma once
#ifndef _TREE_H
#define _TREE_H
#include <ostream>
#include "Queue.h"
#include "Stack.h"

enum RBTreeColor
{
	black = 0,
	Red = 1,
};

template<typename T>
class BiNode {
public:
	BiNode* mLChild;
	BiNode* mRChild;
	BiNode* mParent;//为红黑树准备
	T data;
	BiNode() :mLChild(nullptr), mRChild(nullptr) {}
	BiNode(T data) :mLChild(nullptr), mRChild(nullptr), data(data) {}
	int nodeApperanceTimes = 0;//为非递归后序遍历所需的字段;
	int balanceFactor = 0;//平衡因子，左子树高度减去右子树高度
	RBTreeColor color;//为红黑树准备
};

template<typename T>
class BiTree
{
protected:
	BiNode<T>* mRoot;
	BiNode<T>* CreateBiTree(BiNode<T>* biTree);
	void PreOrderTraversal(BiNode<T>* biTree)const;
	void PostOrderTraversal(BiNode<T>* biTree)const;
	void InOrderTraversal(BiNode<T>* biTree)const;
	void PreOrderUsedByStack(BiNode<T>* biTree)const;
	void PostOrderUsedByStack(BiNode<T>* biTree)const;
	void InOrderUsedByStack(BiNode<T>* biTree)const;
	void LevelOrderTraversal(BiNode<T>* biTree)const;
	virtual void Release(BiNode<T>* biTree);
	bool IsEmpty(BiNode<T>* biTree)const;
	int LeafNodeCount(BiNode<T>* biTree)const;
	void PreOrderPrintLeaves(BiNode<T>* biTree)const;
	int PostOrderGetHeight(BiNode<T>* biTree)const;
	void PrintTree(BiNode<T>* biTree)const;
	int FindIndex(T* array, int arrayLen, T data);
public:
	BiTree() :mRoot(nullptr) {};
	void CreateBiTree();
	bool IsEmpty()const;
	void PreOrderTraversal()const;
	void PostOrderTraversal()const;
	void InOrderTraversal()const;
	void LevelOrderTraversal()const;
	void InOrderUsedByStack()const;
	void PreOrderUsedByStack()const;
	void PostOrderUsedByStack()const;
	int LeafNodeCount()const;
	void PreOrderPrintLeaves()const;
	int PostOrderGetHeight()const;
	void PrintTree()const;
	void GetPostOrderByPre_InOrderSeralize(T* preOrderArray, int preOrderArrayLen, T* InOrderArray, int InOrderArrayLen);
	virtual ~BiTree() { Release(mRoot); this->mRoot = nullptr;}
};

template<typename T>
inline BiNode<T>* BiTree<T>::CreateBiTree(BiNode<T>* biTree)
{
	T data;
	std::cin >> data;
	if (data == '#') biTree=nullptr;
	else {
		biTree = new BiNode<T>(data);
		biTree->mLChild = CreateBiTree(biTree->mLChild);
		biTree->mRChild = CreateBiTree(biTree->mRChild);
	}
	return biTree;
}

template<typename T>
inline void BiTree<T>::PreOrderTraversal(BiNode<T>* biTree)const
{
	if (biTree)
	{
		std::cout << biTree->data << " ";
		PreOrderTraversal(biTree->mLChild);
		PreOrderTraversal(biTree->mRChild);
	}
}

template<typename T>
inline void BiTree<T>::PostOrderTraversal(BiNode<T>* biTree)const
{
	if (biTree)
	{
		PostOrderTraversal(biTree->mLChild);
		PostOrderTraversal(biTree->mRChild);
		std::cout << biTree->data << " ";
	}
}

template<typename T>
inline void BiTree<T>::InOrderTraversal(BiNode<T>* biTree)const
{
	if (biTree)
	{
		InOrderTraversal(biTree->mLChild);
		std::cout << biTree->data << " ";
		InOrderTraversal(biTree->mRChild);
	}
	else return;
}

template<typename T>
inline void BiTree<T>::PreOrderUsedByStack(BiNode<T>* biTree) const
{
	if (!biTree) return;
	BiNode<T>* tempTree = biTree;
	BiNode<T>* topTree = nullptr;
	stack<BiNode<T>*> sTree;
	while (tempTree ||!sTree.IsEmpty())
	{
		while (tempTree)
		{
			std::cout << tempTree->data << " ";
			sTree.Push(tempTree);
			tempTree = tempTree->mLChild;
		}
		if (!sTree.IsEmpty())
		{
			topTree = sTree.Pop();
			tempTree = topTree->mRChild;
		}
	}
}

template<typename T>
inline void BiTree<T>::PostOrderUsedByStack(BiNode<T>* biTree) const
{
#pragma region  first solution (add node apperance times variables)
	//if (!biTree) return;
	//BiNode<T>* tempTree = biTree;
	//BiNode<T>* topTree = nullptr;
	//stack<BiNode<T>*> sTree;
	//while (tempTree || !sTree.IsEmpty())
	//{
	//	while (tempTree)
	//	{
	//		tempTree->nodeApperanceTimes = 1;
	//		sTree.Push(tempTree);
	//		tempTree = tempTree->mLChild;
	//	}
	//	if (!sTree.IsEmpty())
	//	{
	//		topTree = sTree.Pop();
	//		if (topTree->nodeApperanceTimes == 1)
	//		{
	//			topTree->nodeApperanceTimes++;
	//			sTree.Push(topTree);
	//			tempTree = topTree->mRChild;
	//		}
	//		else if (topTree->nodeApperanceTimes == 2)
	//		{
	//			std::cout << topTree->data << " ";
	//			topTree->nodeApperanceTimes = 0;
	//			tempTree = nullptr;
	//		}
	//	}
	//}
#pragma endregion
	if (!biTree) return;
	stack<BiNode<T>*> sTree;
	stack<BiNode<T>*> sPrintTree;
	BiNode<T>* tempTree = nullptr;;
	sTree.Push(biTree);
	while(!sTree.IsEmpty())
	{
		tempTree = sTree.Pop();
		sPrintTree.Push(tempTree);
		if (tempTree->mLChild) sTree.Push(tempTree->mLChild);
		if (tempTree->mRChild) sTree.Push(tempTree->mRChild);
	}
	while (!sPrintTree.IsEmpty())
	{
		tempTree = sPrintTree.Pop();
		std::cout << tempTree->data << " ";
	}
#pragma region  second solution
#pragma endregion
}

template<typename T>
inline void BiTree<T>::InOrderUsedByStack(BiNode<T>* biTree) const
{
	if (!biTree) return;
	BiNode<T>* tempTree = biTree;
	BiNode<T>* topTree = nullptr;
	stack<BiNode<T>*> sTree;
	while (tempTree || !sTree.IsEmpty())
	{
		while (tempTree)
		{
			sTree.Push(tempTree);
			tempTree = tempTree->mLChild;
		}
		if (!sTree.IsEmpty())
		{
			topTree = sTree.Pop();
			std::cout << topTree->data << " ";
			tempTree = topTree->mRChild;
		}
	}
}

template<typename T>
inline void BiTree<T>::LevelOrderTraversal(BiNode<T>* biTree) const
{
	if (biTree == nullptr) return;
	queue<BiNode<T>*> qTree;
	qTree.push(biTree);
	while (!qTree.isEmpty())
	{
		BiNode<T>* frontTree = qTree.front();
		std::cout << frontTree->data << " ";
		if (frontTree->mLChild) qTree.push(frontTree->mLChild);
		if (frontTree->mRChild) qTree.push(frontTree->mRChild);
		qTree.pop();
	}
}

template<typename T>
inline void BiTree<T>::Release(BiNode<T>* biTree)
{
	if (biTree)
	{
		Release(biTree->mLChild);
		Release(biTree->mRChild);
		delete biTree;
		biTree = nullptr;
	}
}

template<typename T>
inline bool BiTree<T>::IsEmpty(BiNode<T>* biTree)const
{
	return biTree == nullptr;
}

template<typename T>
inline int BiTree<T>::LeafNodeCount(BiNode<T>* biTree)const
{
	if (biTree)
	{
		if (!biTree->mLChild && !biTree->mRChild)
			return 1;
		return LeafNodeCount(biTree->mLChild) + LeafNodeCount(biTree->mRChild);
	}
	else return 0;
}

template<typename T>
inline void BiTree<T>::PreOrderPrintLeaves(BiNode<T>* biTree) const
{
	if (biTree)
	{
		if (!biTree->mLChild && !biTree->mRChild)
			std::cout << biTree->data << " ";
		else
		{
			PreOrderPrintLeaves(biTree->mLChild);
			PreOrderPrintLeaves(biTree->mRChild);
		}
	}
	else return;
}

template<typename T>
inline int BiTree<T>::PostOrderGetHeight(BiNode<T>* biTree) const
{
	int maxHeight, lHeight, rHeight;
	if (biTree)
	{
		lHeight = PostOrderGetHeight(biTree->mLChild);
		rHeight = PostOrderGetHeight(biTree->mRChild);
		maxHeight = (lHeight > rHeight) ? lHeight : rHeight;
		return maxHeight + 1;
	}
	else return 0;
}

template<typename T>
inline void BiTree<T>::PrintTree(BiNode<T>* biTree) const
{
	if (biTree == nullptr) return;
	queue<BiNode<T>*> qTree;
	queue<std::string> qEveryLevelTree;
	qTree.push(biTree);
	qTree.push(0);
	while (!qTree.isEmpty())
	{
		BiNode<T>* frontTree = qTree.front();
		qTree.pop();
		if (frontTree)
		{
			std::cout << frontTree->data << " ";
			if (frontTree->mLChild)
			{
				qTree.push(frontTree->mLChild);
				qEveryLevelTree.push("/");
			}
			if (frontTree->mRChild)
			{
				qTree.push(frontTree->mRChild);
				qEveryLevelTree.push("\\");
			}
		}
		else if(!qTree.isEmpty())
		{
			std::cout << std::endl;
			while (!qEveryLevelTree.isEmpty()) {
				std::cout << qEveryLevelTree.front() << " ";
					qEveryLevelTree.pop();
			}
			qTree.push(0);
			std::cout << std::endl;
		}

	}
}

template<typename T>
inline void BiTree<T>::CreateBiTree()
{
	std::cout << "please in put tree data." << std::endl;
	std::cout << "use '#' represent null node." << std::endl;
	std::cout << "use preOrder input." << std::endl;
	mRoot = CreateBiTree(mRoot);
}

template<typename T>
inline bool BiTree<T>::IsEmpty() const
{
	return mRoot==nullptr;
}

template<typename T>
inline void BiTree<T>::PreOrderTraversal()const
{
	std::cout << "前序遍历结果：";
	PreOrderTraversal(mRoot);
	std::cout<<std::endl;
}

template<typename T>
inline void BiTree<T>::PostOrderTraversal() const
{
	std::cout << "后序遍历结果：";
	PostOrderTraversal(mRoot);
	std::cout << std::endl;
}

template<typename T>
inline void BiTree<T>::InOrderTraversal() const
{
	std::cout << "中序遍历结果：";
	InOrderTraversal(mRoot);
	std::cout << std::endl;
}

template<typename T>
inline void BiTree<T>::LevelOrderTraversal() const
{
	std::cout << "层序遍历结果：";
	LevelOrderTraversal(mRoot);
	std::cout << std::endl;
}

template<typename T>
inline void BiTree<T>::InOrderUsedByStack() const
{
	std::cout << "非递归方式中序遍历结果：";
	InOrderUsedByStack(mRoot);
	std::cout << std::endl;
}

template<typename T>
inline void BiTree<T>::PreOrderUsedByStack() const
{
	std::cout << "非递归方式前序遍历结果：";
	PreOrderUsedByStack(mRoot);
	std::cout << std::endl;
}

template<typename T>
inline void BiTree<T>::PostOrderUsedByStack() const
{
	std::cout << "非递归方式后序遍历结果：";
	PostOrderUsedByStack(mRoot);
	std::cout << std::endl;
}

template<typename T>
inline int BiTree<T>::LeafNodeCount() const
{
	return LeafNodeCount(mRoot);
}

template<typename T>
inline void BiTree<T>::PreOrderPrintLeaves() const
{
	std::cout << "the leaf node of tree is: ";
	PreOrderPrintLeaves(mRoot);
	std::cout<< std::endl;
}

template<typename T>
inline int BiTree<T>::PostOrderGetHeight() const
{
	return PostOrderGetHeight(mRoot);
}

template<typename T>
inline void BiTree<T>::PrintTree() const
{
	PrintTree(mRoot);
	std::cout << std::endl;
}

template<typename T>
inline void BiTree<T>::GetPostOrderByPre_InOrderSeralize(T* preOrderArray, int preOrderArrayLen, T* InOrderArray, int InOrderArrayLen)
{
	if (!preOrderArray || !InOrderArray || preOrderArrayLen <= 0 || InOrderArrayLen <= 0 || preOrderArrayLen != InOrderArrayLen)
		return;
	int index = FindIndex(InOrderArray, InOrderArrayLen, *preOrderArray);
	if (index == -1)return;
	GetPostOrderByPre_InOrderSeralize(preOrderArray + 1, index, InOrderArray, index );
	GetPostOrderByPre_InOrderSeralize(preOrderArray + index + 1, preOrderArrayLen - index - 1, InOrderArray + index + 1, InOrderArrayLen - index - 1);
	std::cout << *preOrderArray << " ";
}

template<typename T>
inline int BiTree<T>::FindIndex(T* array, int arrayLen,T data)
{
	for (int i = 0; i < arrayLen; i++)
	{
		if (*(array + i) == data)
			return i;
	}
	return -1;
}

#define Null -1
template<typename T>
class BinTreeNode {
public:
	int mLChild;
	int mRChild;
	T data;
	BinTreeNode() :mLChild(Null), mRChild(Null) {}
	BinTreeNode(T data) :mLChild(Null), mRChild(Null), data(data) {}
};

template<typename T>
class BinTreeArray
{
private:
	int mRoot;
	int mTreeNodeCount;
	BinTreeNode<T>* mBinTree;
	bool Isomorphic(BinTreeArray& tree1, int tree1Root, BinTreeArray& tree2, int tree2Root);
public:
	BinTreeArray() :mRoot(-1), mTreeNodeCount(0), mBinTree(nullptr) {};
	BinTreeArray(int treeNodeCount):mRoot(-1), mTreeNodeCount(treeNodeCount)
	{
		mBinTree = new BinTreeNode<T>[mTreeNodeCount];
		if (!mBinTree) throw;
	}
	void BuildTree();
	bool Isomorphic(BinTreeArray& tree1);
	~BinTreeArray();
	
};

template<typename T>
inline void BinTreeArray<T>::BuildTree()
{
	int treeNodeCount = 0;
	std::cin >> treeNodeCount;
	bool* check = new bool[treeNodeCount];
	mTreeNodeCount = treeNodeCount;
	mBinTree = new BinTreeNode<T>[mTreeNodeCount];
	if (!check) return;
	if (treeNodeCount)
	{
		for (int i = 0; i < treeNodeCount; i++) check[i] = false;
		char lChildIndex, rChildIndex;
		T data;
		for (int i = 0; i < treeNodeCount; i++)
		{
			
			std::cin >> data >> lChildIndex >> rChildIndex;
			(mBinTree + i)->data = data;
			if (lChildIndex != '#')
			{
				(mBinTree + i)->mLChild = lChildIndex - '0';
				check[(mBinTree + i)->mLChild] = true;
			}
			else (mBinTree + i)->mLChild = Null;
			if (rChildIndex != '#')
			{
				(mBinTree + i)->mRChild = rChildIndex - '0';
				check[(mBinTree + i)->mRChild] = true;
			}
			else (mBinTree + i)->mRChild = Null;
		}
		int index = 0;
		for (index = 0; index < treeNodeCount; index++)
			if (!check[index]) break;
		if (index < treeNodeCount) mRoot = index;
		else throw;
	}
	delete[] check;
	check = nullptr;
}

template<typename T>
inline bool BinTreeArray<T>::Isomorphic(BinTreeArray& tree1)
{
	return Isomorphic(*this, this->mRoot, tree1, tree1.mRoot);
}

template<typename T>
inline BinTreeArray<T>::~BinTreeArray()
{
	if (mBinTree)
	{
		delete[] mBinTree;
		mBinTree = nullptr;
		mRoot = -1;
		this->mTreeNodeCount = 0;
	}
}

template<typename T>
inline bool BinTreeArray<T>::Isomorphic(BinTreeArray<T>& tree1, int tree1Root, BinTreeArray<T>& tree2, int tree2Root)
{
	if (tree1Root == Null && tree2Root == Null)//both empty
		return true;
	if ((tree1Root != Null && tree2Root == Null) || (tree1Root == Null && tree2Root != Null))//one of them is empty
		return false;
	if ((tree1.mBinTree + tree1Root)->data != (tree2.mBinTree + tree2Root)->data)
		return false;
	if (((tree1.mBinTree + tree1Root)->mLChild == Null) && ((tree2.mBinTree + tree2Root)->mLChild == Null))//如果左边都为空，只需判断右边是否同构
		return Isomorphic(tree1, (tree1.mBinTree + tree1Root)->mRChild, tree2, (tree2.mBinTree + tree2Root)->mRChild);
	if (((tree1.mBinTree + tree1Root)->mLChild != Null) && ((tree2.mBinTree + tree2Root)->mLChild != Null)
		&& ((tree1.mBinTree + (tree1.mBinTree + tree1Root)->mLChild))->data == ((tree2.mBinTree + (tree2.mBinTree + tree2Root)->mLChild)->data))//如果左子树都不空且值相同，则判断右子树是否同构
		return Isomorphic(tree1, (tree1.mBinTree + tree1Root)->mLChild, tree2, (tree2.mBinTree + tree2Root)->mLChild) &&
		Isomorphic(tree1, (tree1.mBinTree + tree1Root)->mRChild, tree2, (tree2.mBinTree + tree2Root)->mRChild);
	else//如果左子树一空一不空，则判断1的右子树和2的左子树是否同构，如果左右子树根结点不同，则判断是否互相同构
		return Isomorphic(tree1, (tree1.mBinTree + tree1Root)->mLChild, tree2, (tree2.mBinTree + tree2Root)->mRChild) &&
		Isomorphic(tree1, (tree1.mBinTree + tree1Root)->mRChild, tree2, (tree2.mBinTree + tree2Root)->mLChild);
}

#pragma endregion
#endif // !_TREE_H