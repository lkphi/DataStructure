#pragma once
#ifndef _GRAPH_H
#define _GRAPH_H
#include "Queue.h"
#include "Heap.h"
#include "Set.h"
#define MaxValue 10000

using GraphIndex=int;
class EdgeNode {
public:
	GraphIndex v1, v2;//有向边v1，v2
	int weight;//权重
	explicit EdgeNode():v1(0), v2(0),weight(0) {}
	explicit EdgeNode(GraphIndex v1, GraphIndex v2) :v1(v1), v2(v2), weight(0) {}
	explicit EdgeNode(GraphIndex v1, GraphIndex v2, int weight) :v1(v1), v2(v2), weight(weight) {}
	bool operator <(const EdgeNode& edge2)const
	{
		if (weight < edge2.weight)
			return true;
		else return false;
	}
	bool operator <=(const EdgeNode& edge2)const
	{
		if (weight <= edge2.weight)
			return true;
		else return false;
	}
	bool operator >(const EdgeNode& edge2)const
	{
		if (weight > edge2.weight)
			return true;
		else return false;
	}
	bool operator >=(const EdgeNode& edge2)const
	{
		if (weight >= edge2.weight)
			return true;
		else return false;
	}
	friend std::ostream& operator <<(std::ostream& os, const EdgeNode& e)
	{
		os << e.v1 << "——" << e.v2 << " weight:" << e.weight;
		return os;
	}
};

template<typename T>
class MGraph
{
public:
	MGraph(int vertexCount, bool isDirected = false);
	bool Insert(const EdgeNode& edgeNode);
	bool DFS(GraphIndex start);
	bool BFS(GraphIndex start);
	bool CheckAllVisited();
	void RestVisited();
	void Dijkstra(GraphIndex start);
	void MinHeapDijkstra(GraphIndex start);
	void Floyd();
	int FindMinPoint2OtherPoint();
	bool Prim(int rootIndex);
	void Kruskal();//将森林合并成树
	void TopSort();//拓扑排序
	~MGraph();
	int** mGraphMatrix;//邻接矩阵
private:
	int mVertexCount;//顶点数
	int mEdgeCount;//边数
	//int** mGraphMatrix;//邻接矩阵
public:
	T* mDataArray;//存顶点数据
	bool mIsDirected;//判断是有向图还是无向图
	bool* mVisitedArray;
	int* mShortestPathLastIndex;
	int* mShortestDist;
	int** mShortestDistMatrix;
	int** mShortestPathLastIndexMatrix;
	int* mMSTParent;//minium spanning tree最小生成树
};

template<typename T>
inline MGraph<T>::MGraph(int vertexCount, bool isDirected)
{
	mGraphMatrix = new int*[vertexCount];
	if (!mGraphMatrix) throw;
	for (int i = 0; i < vertexCount; i++)
	{
		mGraphMatrix[i] = new int[vertexCount] {0};
		if (!mGraphMatrix[i]) throw;
	}
	//mDataArray = new int[vertexCount];
	//if (!mDataArray) throw;
	mVisitedArray = new bool[vertexCount];
	if (!mVisitedArray) throw;

	mVertexCount = vertexCount;
	mEdgeCount = 0;
	mIsDirected = isDirected;
}

template<typename T>
inline bool MGraph<T>::Insert(const EdgeNode& edgeNode)
{
	if (edgeNode.v1 < 0 || edgeNode.v1 >= mVertexCount || edgeNode.v2 < 0 || edgeNode.v2 >= mVertexCount)
	return false;
	mGraphMatrix[edgeNode.v1][edgeNode.v2] = edgeNode.weight;
	if(!mIsDirected)
		mGraphMatrix[edgeNode.v2][edgeNode.v1] = edgeNode.weight;
	mEdgeCount++;
	return true;
}

template<typename T>
inline bool MGraph<T>::DFS(GraphIndex start)//O(vertexCount^2)
{
	mVisitedArray[start] = true;
	if (CheckAllVisited())
	{
		RestVisited();
		return true;
	}
	for (int i = 0; i < mVertexCount; i++)
	{
		if (!mVisitedArray[i] && mGraphMatrix[start][i] != 0)
		if (DFS(i)) return true;
	}
	return false;
}

template<typename T>
inline bool MGraph<T>::BFS(GraphIndex start)//O(vertexCount^2)
{
	mVisitedArray[start] = true;
	queue<GraphIndex>* que = new queue<GraphIndex>();
	que->push(start);
	while (!que->isEmpty())
	{
		GraphIndex graphIndex = que->front();
		que->pop();
		if (CheckAllVisited())
		{
			RestVisited();
			return true;
		}
		for (int i = 0; i < mVertexCount; i++)
		{
			if (!mVisitedArray[i] && mGraphMatrix[start][i] != 0)
			{
				que->push(i);
				mVisitedArray[i] = true;
			}
		}
	}
	return false;
	delete que;
	que = nullptr;
}

template<typename T>
inline bool MGraph<T>::CheckAllVisited()
{
	for (int i = 0; i < mVertexCount; i++)
	{
		if (!mVisitedArray[i])
			return false;
	}
	return true;
}

template<typename T>
inline void MGraph<T>::RestVisited()
{
	for (int i = 0; i < mVertexCount; i++)
		mVisitedArray[i] = false;
}

template<typename T>
inline void MGraph<T>::Dijkstra(GraphIndex start)//o(mVertexCount^2+mVertexCount^2),对于稠密图效果好
{
	#pragma region apply for memory
	if(!mShortestPathLastIndex)
		mShortestPathLastIndex = new int[mVertexCount];
	if (!mShortestPathLastIndex) throw;
	if(!mShortestDist)
		mShortestDist = new int[mVertexCount];
	if (!mShortestDist) throw;
	#pragma endregion
	int minWeight = MaxValue;
	int minWeightIndex = 0;
	for (int i = 0; i < mVertexCount; i++)
	{
		mShortestDist[i] = MaxValue;
		mShortestPathLastIndex[i] = -1;
		mVisitedArray[i] = false;
	}
	mShortestDist[start] = 0;
	for (int i = 0; i < mVertexCount; i++)
	{
		minWeight = MaxValue;
		for (int j = 0; j < mVertexCount; j++)
		{
			if (!mVisitedArray[j] && mShortestDist[j] < minWeight)
			{
				minWeight = mShortestDist[j];
				minWeightIndex = j;
			}
		}
		mVisitedArray[minWeightIndex] = true;
		for (int j = 0; j < mVertexCount; j++)
		{
			if (mGraphMatrix[minWeightIndex][j] != 0 && !mVisitedArray[j]
				&& mShortestDist[j] > mShortestDist[minWeightIndex] + mGraphMatrix[minWeightIndex][j])
			{
				mShortestDist[j] = mShortestDist[minWeightIndex] + mGraphMatrix[minWeightIndex][j];
				mShortestPathLastIndex[j] = minWeightIndex;
			}
		}
	}

}

template<typename T>
inline void MGraph<T>::MinHeapDijkstra(GraphIndex start)//T=O(|V|log|v|+|E|log|V|)=O(|E|log|V|),对于稀疏图效果好
{
	int minWeightIndex = 0;
	EdgeNode* array = new EdgeNode[mVertexCount];
	for (int i = 0; i < mVertexCount; i++)
	{
		mShortestDist[i] = MaxValue;
		mShortestPathLastIndex[i] = -1;
		mVisitedArray[i] = false;
		array[i].v1 = start;
		array[i].v2 = 0;
		array[i].weight = MaxValue;
	}
	mShortestDist[start] = 0;
	array[start].weight = MaxValue;
	MinHeap<EdgeNode>* minHeap = new MinHeap<EdgeNode>(array,mVertexCount);
	delete[] array;
	array = nullptr;
	if (!minHeap) return;
	for (int i = 0; i < mVertexCount; i++)
	{
		do {
			minWeightIndex = (minHeap->RemoveRoot()).v2;
		} while (mVisitedArray[minWeightIndex]);
		mVisitedArray[minWeightIndex] = true;
		for (int j = 0; j < mVertexCount; j++)
		{
			if (mGraphMatrix[minWeightIndex][j] != 0 && !mVisitedArray[j] &&
				mShortestDist[j] > mShortestDist[minWeightIndex] + mGraphMatrix[minWeightIndex][j])
			{
				mShortestDist[j] = mShortestDist[minWeightIndex] + mGraphMatrix[minWeightIndex][j];
				EdgeNode newEdge(start, j, mShortestDist[j]);
				minHeap->Insert(newEdge);
				mShortestPathLastIndex[j] = minWeightIndex;
			}
		}
	}
}

template<typename T>
inline void MGraph<T>::Floyd()//O(V^3)
{
	#pragma region apply for memeory
	if (!mShortestDistMatrix)
	{
		mShortestDistMatrix = new int* [mVertexCount];
		if (!mShortestDistMatrix) throw;
		for (int i = 0; i < mVertexCount; i++)
		{
			mShortestDistMatrix[i] = new int[mVertexCount] {0};
			if (!mShortestDistMatrix[i]) throw;
		}
	}
	if (!mShortestDistMatrix) throw;
	if (!mShortestPathLastIndexMatrix)
	{
		mShortestPathLastIndexMatrix = new int*[mVertexCount];
		for (int i = 0; i < mVertexCount; i++)
		{
			mShortestPathLastIndexMatrix[i] = new int[mVertexCount] {-1};
			if (!mShortestPathLastIndexMatrix[i]) throw;
		}
	}
	#pragma endregion

	for (int i = 0; i < mVertexCount; i++)
	{
		for (int j = 0; j < mVertexCount; j++)
		{
			mShortestDistMatrix[i][j] = mGraphMatrix[i][j] ?
				mGraphMatrix[i][j] : MaxValue;
		}
		mShortestDistMatrix[i][i] = 0;
	}
	for (int k = 0; k < mVertexCount; k++)
		for (int i = 0; i < mVertexCount; i++)
			for (int j = 0; j < mVertexCount; j++)
			{
				if (mShortestDistMatrix[i][k] + mShortestDistMatrix[k][j] < mShortestDistMatrix[i][j])
				{
					mShortestDistMatrix[i][j] = mShortestDistMatrix[i][k] + mShortestDistMatrix[k][j];
					mShortestPathLastIndexMatrix[i][j] = k;
					mShortestPathLastIndexMatrix[j][i] = k;
				}
			}
}

template<typename T>
inline int MGraph<T>::FindMinPoint2OtherPoint()
{
	Floyd();
	int* maxWeightArray = new int[mVertexCount] {0};
	if (!maxWeightArray)throw;
	for (int i = 0; i < mVertexCount; ++i)
		for (int j = 0; j < mVertexCount; ++j)
		{
			if (mShortestDistMatrix[i][j] && mShortestDistMatrix[i][j] > maxWeightArray[i])
			{
				maxWeightArray[i] = mShortestDistMatrix[i][j];
			}
		}
	int minWeight = MaxValue;
	int index = 0;
	for (int i = 0; i < mVertexCount; ++i)
	{
		if (maxWeightArray[i] == MaxValue)
		{
			return -1;
		}
		if (minWeight > maxWeightArray[i])
		{
			minWeight = maxWeightArray[i];
			index = i;
		}
		if (minWeight == maxWeightArray[i])
		{
			if (index > i)
				index = i;
		}
	}
	delete[] maxWeightArray;
	maxWeightArray = nullptr;
	return index;
}

template<typename T>
inline bool MGraph<T>::Prim(int rootIndex)//O(V^2) 适用于稠密图
{
	int* dist = new int[mVertexCount];//顶点i到生成树的距离,即顶点到生成树已收录的各顶点的最小距离
	if (!dist) throw;
	if(!mMSTParent)
		mMSTParent = new int[mVertexCount] {-1};//父节点的编号
	if (!mMSTParent) throw;
	for (int i = 0; i < mVertexCount; i++)
	{
		dist[i] = (mGraphMatrix[rootIndex][i] != 0 ?
			mGraphMatrix[rootIndex][i] : MaxValue);
	}
	dist[rootIndex] = 0;//根节点即最开始的点先收录进来
	mMSTParent[rootIndex] = -1;
	int minDist = MaxValue;
	int minDistIndex = 0;
	for (int i = 1; i < mVertexCount; i++)
	{
		minDist = MaxValue;
		for (int j = 0; j < mVertexCount; j++)
		{
			if (dist[j] != 0 && dist[j] < minDist)
			{
				minDist = dist[j];
				minDistIndex = j;
			}
		}
		if (minDist == MaxValue)
		{
			std::cout << "生成树不存在" << std::endl;
			delete[] dist;
			dist = nullptr;
			return false;
		}
		dist[minDistIndex] = 0;//表示已经被收录进树里
		for (int j = 0; j < mVertexCount; j++)
		{
			if (dist[j] != 0 && mGraphMatrix[minDistIndex][j] != 0 && dist[minDistIndex] + mGraphMatrix[minDistIndex][j] < dist[j])
			{
				dist[j] = mGraphMatrix[minDistIndex][j] + dist[minDistIndex];
				mMSTParent[j] = minDistIndex;
			}
		}
	}
	delete[] dist;
	dist = nullptr;
	return true;
}

template<typename T>
inline void MGraph<T>::Kruskal()//采用堆O(ElogE)
{
	int** graphMatrix = new int* [mVertexCount];
	if (!graphMatrix) throw;
	for (int i = 0; i < mVertexCount; i++)
	{
		graphMatrix[i] = new int[mVertexCount];
		if (!graphMatrix[i]) throw;
		for (int j = 0; j < mVertexCount; j++)
			graphMatrix[i][j] = mGraphMatrix[i][j];
	}	
	int minWeight = MaxValue;
	int minWeightFirstIndex, minWeightSecondIndex = 0;
	int* graphIndexArray = new int[mVertexCount];
	if (!graphIndexArray) throw;
	for (int i = 0; i < mVertexCount; ++i)
		graphIndexArray[i] = i;
	Set<int>* set = new Set<int>(graphIndexArray, mVertexCount);
	if (!set) throw;
	delete[] graphIndexArray;
	graphIndexArray = nullptr;
	queue<EdgeNode>* mstQueue = new queue<EdgeNode>();
	if (!mstQueue) throw;
	for (int i = 1; i < mVertexCount; ++i)
	{
		minWeight = MaxValue;
		for (int k = 0; k < mVertexCount; k++)
			for (int j = 0; j < mVertexCount; j++)
			{
				if (!graphMatrix[k][j]==0 && graphMatrix[k][j] < minWeight && !set->CheckConnection(k, j))
				{
					minWeight = graphMatrix[k][j];
					minWeightFirstIndex = k;
					minWeightSecondIndex = j;
				}
			}
		if (minWeight == MaxValue)
		{
			std::cout << "生成树不存在";
			while (!mstQueue->isEmpty())
				mstQueue->pop();
			break;
		}
		graphMatrix[minWeightFirstIndex][minWeightSecondIndex] = 0;
		mstQueue->push(EdgeNode(minWeightFirstIndex, minWeightSecondIndex, minWeight));
		set->Union(minWeightFirstIndex, minWeightSecondIndex);
	}
	std::cout << *mstQueue;
	delete set;
	set = nullptr;
	for (int i = 0; i < mVertexCount; ++i)
	{
		delete[] graphMatrix[i];
		graphMatrix[i] = nullptr;
	}
	delete[] graphMatrix;
	graphMatrix = nullptr;
	delete mstQueue;
	mstQueue = nullptr;
}

template<typename T>
inline void MGraph<T>::TopSort()//O(|V|^2)
{
	if (!mIsDirected)
	{
		std::cout << "无向图不能拓扑排序" << std::endl;
		return;
	}
	int* indegree = new int[mVertexCount](0);//每个顶点的入度
	if (!indegree) throw;
	queue<int>* vertexQueue = new queue<int>();
	if (!vertexQueue) throw;
	queue<int>* sortQueue = new queue<int>();
	if (!sortQueue) throw;
	for (int i = 0; i < mVertexCount; ++i)
	{
		for (int j = 0; j < mVertexCount; ++j)
		{
			if (mGraphMatrix[i][j] != 0)
				++indegree[j];
		}
	}
	//int popVertexCount = 0;
	for (int i = 0; i < mVertexCount; ++i)
	{
		if (!indegree[i])
			vertexQueue->push(i);
	}
	while (!vertexQueue->isEmpty())
	{
		int popVertex = vertexQueue->front();
		vertexQueue->pop();
		sortQueue->push(popVertex);
		//popVertexCount++;
		for (int j = 0; j < mVertexCount; j++)
		{
			if (mGraphMatrix[popVertex][j] != 0)
			{
				if (--indegree[j])
					vertexQueue->push(j);
			}

		}
	}
		//if (popVertexCount != mVertexCount)
	if (sortQueue->size() != mVertexCount)
		std::cout << "图中有回路" << std::endl;
	else std::cout << sortQueue;
	delete[] indegree;
	delete[] vertexQueue;
	delete[] sortQueue;
	indegree = vertexQueue = sortQueue = nullptr;
}

template<typename T>
inline MGraph<T>::~MGraph()
{
	if (!mGraphMatrix)
	{
		for (int i = 0; i < mVertexCount; ++i)
		{
			if (!mGraphMatrix[i])
			{
				delete[] mGraphMatrix[i];
				mGraphMatrix[i] = nullptr;
			}
		}
		delete[] mGraphMatrix;
		mGraphMatrix = nullptr;
	}
	if (!mDataArray) {
		delete[] mDataArray;
		mDataArray = nullptr;
	}
	if (!mVisitedArray) {
		delete[] mVisitedArray;
		mVisitedArray = nullptr;
	}
	if (!mShortestDist) {
		delete[] mShortestDist;
		mShortestDist = nullptr;
	}
	if (!mShortestPathLastIndex) {
		delete[] mShortestPathLastIndex;
		mShortestPathLastIndex = nullptr;
	}
	mVertexCount = mEdgeCount = 0;
	mIsDirected = false;
	if (!mShortestDistMatrix)
	{
		for (int i = 0; i < mVertexCount; i++)
		{
			if (!mShortestDistMatrix[i])
			{
				delete[] mShortestDistMatrix[i];
				mShortestDistMatrix[i] = nullptr;
			}
		}
		delete[] mShortestDistMatrix;
		mShortestDistMatrix = nullptr;
	}
	if (!mShortestPathLastIndexMatrix)
	{
		for (int i = 0; i < mVertexCount; i++)
		{
			if (!mShortestPathLastIndexMatrix[i])
			{
				delete[] mShortestPathLastIndexMatrix[i];
				mShortestPathLastIndexMatrix[i] = nullptr;
			}
		}
		delete[] mShortestPathLastIndexMatrix;
		mShortestPathLastIndexMatrix = nullptr;
	}
	if (!mMSTParent)
	{
		delete[] mMSTParent;
		mMSTParent = nullptr;
	}
}

template<typename T>
class AdjVNode {
public:
	GraphIndex mAdjv;//邻接点下标
	T mWeight;//权重
	bool mIsVisited;
	AdjVNode* next;
	AdjVNode() :mWeight(0), mIsVisited(false), next(nullptr) {}
	AdjVNode(GraphIndex adjv, T weight) :mAdjv(adjv), mWeight(weight), mIsVisited(false), next(nullptr) {}
};

template<typename T>
class TGraph 
{
public:
	T* mDataArray;//存顶点数据
	TGraph(int vertexCount, bool isDirected = false);
	bool Insert(const EdgeNode& edgeNode);
	bool DFS(GraphIndex start);
	bool BFS(GraphIndex start);
	bool CheckAllVisited();
	void RestVisited();
	void Dijkstra(GraphIndex start);
	void MinHeapDijkstra(GraphIndex start);
	//void Floyd();
	bool Prim(int rootIndex);
	void Kruskal();//将森林合并成树
	void TopSort();//拓扑排序
	~TGraph();
private:
	int mVertexCount;//顶点数
	int mEdgeCount;//边数
public:
	AdjVNode<int>* mGraphTable;//邻接表
	bool mIsDirected;//判断是有向图还是无向图
	int* mShortestPathLastIndex;
	int* mShortestDist;
	int* mMSTParent;//minium spanning tree最小生成树
};

template<typename T>
inline TGraph<T>::TGraph(int vertexCount, bool isDirected)
{
	mGraphTable = new AdjVNode<int>[vertexCount];
	if (!mGraphTable) throw;
	mVertexCount = vertexCount;
	mEdgeCount = 0;
	mIsDirected = isDirected;
}

template<typename T>
inline bool TGraph<T>::Insert(const EdgeNode& edgeNode)
{
	if (edgeNode.v1 < 0 || edgeNode.v1 >= mVertexCount || edgeNode.v2 < 0 || edgeNode.v2 >= mVertexCount)
	return false;
	AdjVNode<int>* newNode = new AdjVNode<int>(edgeNode.v2, edgeNode.weight);
	if (!newNode) return false;
	newNode->next = mGraphTable[edgeNode.v1].next;
	mGraphTable[edgeNode.v1].next = newNode;
	if (!mIsDirected)
	{
		AdjVNode<int>* newNode = new AdjVNode<int>(edgeNode.v1, edgeNode.weight);
		if (!newNode) return false;
		newNode->next = mGraphTable[edgeNode.v2].next;
		mGraphTable[edgeNode.v2].next = newNode;
	}
	mEdgeCount++;
	return true;
}

//深度优先搜索（depth first search）
template<typename T>
inline bool TGraph<T>::DFS(GraphIndex start)//O(vertexCount+EdgeCount)
{
	mGraphTable[start].mIsVisited = true;
	AdjVNode<int>* head = mGraphTable[start].next;
	while (head)
	{
		if (CheckAllVisited())
		{
			RestVisited();
			return true;
		}
		if (!mGraphTable[head->mAdjv].mIsVisited)
			if (DFS(head->mAdjv)) return true;
		head = head->next;
	}
}

//广度优先遍历（Breadth First Search）
template<typename T>
inline bool TGraph<T>::BFS(GraphIndex start)//O(vertexCount+EdgeCount)
{
	queue<GraphIndex>* que = new queue<GraphIndex>();
	que->push(start);
	mGraphTable[start].mIsVisited = true;
	while (!que->isEmpty())
	{
		GraphIndex graphIndex = que->front();
		que->pop();
		AdjVNode<int>* head = mGraphTable[graphIndex].next;
		while (head)
		{
			if (CheckAllVisited())
			{
				RestVisited();
				return true;
			}
			if (!mGraphTable[head->mAdjv].mIsVisited)
			{
				mGraphTable[head->mAdjv].mIsVisited = true;
				que->push(head->mAdjv);
			}
			head = head->next;
		}
	}
	return false;
	delete que;
	que = nullptr;
}

template<typename T>
inline bool TGraph<T>::CheckAllVisited()
{
	for (int index = 0; index < mVertexCount; index++)
	{
		if (!mGraphTable[index].mIsVisited)
			return false;
	}
	return true;
}

template<typename T>
inline void TGraph<T>::RestVisited()
{
	for (int i = 0; i < mVertexCount; i++)
		mGraphTable[i].mIsVisited = false;
}

template<typename T>
inline void TGraph<T>::Dijkstra(GraphIndex start)//o(mVertexCount^2+edgeCount),对于稠密图效果好
{
	#pragma region apply for memory
	if (!mShortestPathLastIndex)
		mShortestPathLastIndex = new int[mVertexCount];
	if (!mShortestPathLastIndex) throw;
	if (!mShortestDist)
		mShortestDist = new int[mVertexCount];
	if (!mShortestDist) throw;
	for (int i = 0; i < mVertexCount; i++)
	{
		mShortestDist[i] = MaxValue;
		mShortestPathLastIndex[i] = -1;
		mGraphTable[i].mIsVisited = false;
	}
	#pragma endregion
	int minWeight = MaxValue;
	int minWeightIndex = 0;
	mShortestDist[start] = 0;
	for (int i = 0; i < mVertexCount; i++)
	{
		minWeight = MaxValue;
		for (int j = 0; j < mVertexCount; j++)
		{
			if (!mGraphTable[j].mIsVisited && mShortestDist[j] < minWeight)
			{
				minWeight = mShortestDist[j];
				minWeightIndex = j;
			}
		}
		mGraphTable[minWeightIndex].mIsVisited = true;
		AdjVNode<int>* head = mGraphTable[minWeightIndex].next;
		while (head)
		{
			int index = head->mAdjv;
			if (!mGraphTable[index].mIsVisited &&
				mShortestDist[index] > mShortestDist[minWeightIndex] + head->mWeight)
			{
				mShortestDist[index] = mShortestDist[minWeightIndex] + head->mWeight;
				mShortestPathLastIndex[index] = minWeightIndex;
			}
			head = head->next;
		}
	}
}

template<typename T>
inline void TGraph<T>::MinHeapDijkstra(GraphIndex start)//T = O(| V | log | v | +| E | log | V | ) = O(| E | log | V | ), 对于稀疏图效果好
{
	int minWeightIndex = 0;
	EdgeNode* array = new EdgeNode[mVertexCount];
	for (int i = 0; i < mVertexCount; i++)
	{
		mShortestDist[i] = MaxValue;
		mShortestPathLastIndex[i] = -1;
		mGraphTable[i].mIsVisited = false;
		array[i].v1 = start;
		array[i].v2 = i;
		array[i].weight = MaxValue;
	}
	mShortestDist[start] = 0;
	array[start].weight = 0;
	MinHeap<EdgeNode>* minHeap = new MinHeap<EdgeNode>(array, mVertexCount);
	minHeap->BuildHeap();
	delete[] array;
	array = nullptr;
	if (!minHeap) throw;
	for (int i = 0; i < mVertexCount; i++)
	{
		do {
			minWeightIndex = (minHeap->RemoveRoot()).v2;
		} while (mGraphTable[minWeightIndex].mIsVisited);
		mGraphTable[minWeightIndex].mIsVisited = true;
		AdjVNode<int>* head = mGraphTable[minWeightIndex].next;
		while(head)
		{
			if (!mGraphTable[head->mAdjv].mIsVisited && mShortestDist[head->mAdjv] > mShortestDist[minWeightIndex] + head->mWeight)
			{
				mShortestDist[head->mAdjv] = mShortestDist[minWeightIndex] + head->mWeight;
				EdgeNode newEdge(start, head->mAdjv, mShortestDist[head->mAdjv]);
				minHeap->Insert(newEdge);
				mShortestPathLastIndex[head->mAdjv] = minWeightIndex;
			}
			head = head->next;
		}
	}
}

template<typename T>
inline bool TGraph<T>::Prim(int rootIndex)
{
	int* dist = new int[mVertexCount];//顶点i到生成树的距离,即顶点到生成树已收录的各顶点的最小距离
	if (!dist) throw;
	for (int i = 0; i < mVertexCount; ++i)
		dist[i] = MaxValue;
	if (!mMSTParent)
		mMSTParent = new int[mVertexCount] {-1};//父节点的编号
	if (!mMSTParent)
	{
		delete[] dist;
		dist = nullptr;
		throw;
	}
	AdjVNode<int>* head = mGraphTable[rootIndex].next;
	while(head)
	{
		dist[head->mAdjv] = head->mWeight;
		head = head->next;
	}
	dist[rootIndex] = 0;//根节点即最开始的点先收录进来
	mMSTParent[rootIndex] = -1;
	int minDist = MaxValue;
	int minDistIndex = 0;
	for (int i = 1; i < mVertexCount; i++)
	{
		minDist = MaxValue;
		for (int j = 0; j < mVertexCount; j++)
		{
			if (dist[j] != 0 && dist[j] < minDist)
			{
				minDist = dist[j];
				minDistIndex = j;
			}
		}
		if (minDist == MaxValue)
		{
			std::cout << "生成树不存在" << std::endl;
			delete[] dist;
			dist = nullptr;
			return false;
		}
		dist[minDistIndex] = 0;//表示已经被收录进树里
		head = mGraphTable[minDistIndex].next;
		while(head)
		{
			if (dist[head->mAdjv] != 0 && head->mWeight + dist[minDistIndex] < dist[head->mAdjv])
			{
				dist[head->mAdjv] = head->mWeight + dist[minDistIndex];
				mMSTParent[head->mAdjv] = minDistIndex;
			}
			head = head->next;
		}
	}
	delete[] dist;
	dist = nullptr;
	return true;
}

template<typename T>
inline void TGraph<T>::Kruskal()
{
	EdgeNode* array = new EdgeNode[mEdgeCount];
	if (!array) throw;
	for (int i = 0, j = 0; i < mVertexCount; ++i)
	{
		AdjVNode<int>* head = mGraphTable[i].next;
		while (head)
		{
			if (head->mAdjv > i)
				array[j++] = EdgeNode(i, head->mAdjv, head->mWeight);
			head = head->next;
		}
	}
	MinHeap<EdgeNode>* minHeap = new MinHeap<EdgeNode>(array, mEdgeCount);
	minHeap->BuildHeap();
	delete[] array;
	array = nullptr;
	if (!minHeap) throw;
	queue<EdgeNode>* mstQueue = new queue<EdgeNode>();
	if (!mstQueue) throw;
	int* setArray = new int[mVertexCount];
	for (int i = 0; i < mVertexCount; ++i)
		setArray[i] = i;
	Set<int>* set = new Set<int>(setArray,mVertexCount);
	delete[] setArray;
	setArray = nullptr;
	if (!set) throw;
	for (int i = 0; i < mEdgeCount; ++i)
	{
		EdgeNode minEdge = minHeap->RemoveRoot();
		if (!set->CheckConnection(minEdge.v1, minEdge.v2))
		{
			mstQueue->push(minEdge);
			set->Union(minEdge.v1, minEdge.v2);
		}
	}
	if (mstQueue->size() == mVertexCount - 1)
		std::cout << *mstQueue;
	else {
		std::cout << "生成树不存在" << std::endl;
		while (!mstQueue->isEmpty())
			mstQueue->pop();
	}
	delete minHeap;
	minHeap = nullptr;
	delete mstQueue;
	mstQueue = nullptr;
	delete set;
	set = nullptr;
}

template<typename T>
inline void TGraph<T>::TopSort()//邻接表O(| V | +| E | )
{
	if (!mIsDirected)
	{
		std::cout << "无向图不能拓扑排序" << std::endl;
		return;
	}
	int* indegree = new int[mVertexCount];//每个顶点的入度
	if (!indegree) throw;
	for (int i = 0; i < mVertexCount; ++i)
		indegree[i] = 0;
	queue<int>* vertexQueue = new queue<int>();
	if (!vertexQueue) throw;
	queue<int>* sortQueue = new queue<int>();
	if (!sortQueue) throw;
	for (int i = 0; i < mVertexCount; ++i)
	{
		AdjVNode<int>* head = mGraphTable[i].next;
		while (head)
		{
			++indegree[head->mAdjv];
			head = head->next;
		}
	}
	//int popVertexCount = 0;
	for (int i = 0; i < mVertexCount; ++i)
	{
		if (!indegree[i])
			vertexQueue->push(i);
	}
	while (!vertexQueue->isEmpty())
	{
		int popVertex = vertexQueue->front();
		vertexQueue->pop();
		sortQueue->push(popVertex);
		//popVertexCount++;
		AdjVNode<int>* head = mGraphTable[popVertex].next;
		while (head)
		{
			if((--indegree[head->mAdjv]==0))
				vertexQueue->push(head->mAdjv);
			head = head->next;
		}
	}
	//if (popVertexCount != mVertexCount)
	if (sortQueue->size() != mVertexCount)
		std::cout << "图中有回路" << std::endl;
	else std::cout << *sortQueue;
	delete[] indegree;
	delete vertexQueue;
	delete sortQueue;
	indegree = nullptr;
	vertexQueue = nullptr;
	sortQueue = nullptr;
}

template<typename T>
inline TGraph<T>::~TGraph()
{
	if (mGraphTable)
	{
		for (int i = 0; i < mVertexCount; i++)
		{
			AdjVNode<int>* head = mGraphTable[i].next;
			while (head)
			{
				AdjVNode<int>* deleteNode = head;
				head = head->next;
				delete deleteNode;
				deleteNode = nullptr;
			}
		}
		delete[] mGraphTable;
		mGraphTable = nullptr;
	}
	//if (!mDataArray)
	//{
	//	delete[] mDataArray;
	//	mDataArray = nullptr;
	//}
	if (!mShortestDist) {
		delete[] mShortestDist;
		mShortestDist = nullptr;
	}
	if (!mShortestPathLastIndex) {
		delete[] mShortestPathLastIndex;
		mShortestPathLastIndex = nullptr;
	}
	mVertexCount = mEdgeCount = 0;
	mIsDirected = false;
}

class AOE//Activity On Edge,一般用于安排项目的工序
{
public:
	int earliestTime;//最早完成时间
	int latestTime;//最晚完成时间
	AOE() = default;
	AOE(int earliestTime, int latestTime) :earliestTime(earliestTime), latestTime(latestTime) {}
};

class RoadEdgeNode
{
public:
	int v1Index;
	int v2Index;
	int length;
	int cost;
	RoadEdgeNode() = default;
	RoadEdgeNode(int v1Index, int v2Index, int length, int cost):
		v1Index(v1Index), v2Index(v2Index), length(length), cost(cost) {}
};


class TPNode {
public:
	int mAdjv;//邻接点下标
	int mLength;
	int mCost;
	bool mIsVisited;
	TPNode* next;
	TPNode() :mLength(0), mCost(0), mIsVisited(false), next(nullptr) {}
	TPNode(int adjv, int length,int cost) :mAdjv(adjv), mLength(length),mCost(cost), mIsVisited(false), next(nullptr) {}
};

struct TPFactor
{
	int length;
	int cost;
};
class TravelPlanGraphic
{
	TPNode* mGraphicTable;
	int mVertexCount;
	int mEdgeCount;
public:
	TravelPlanGraphic(int vertexCount);
	bool Insert(const RoadEdgeNode& roadEdgeNode);
	void Dijkstra(int start, int end);
	~TravelPlanGraphic();
};

inline TravelPlanGraphic::TravelPlanGraphic(int vertexCount)
{
	mGraphicTable = new TPNode[vertexCount];
	if (!mGraphicTable) throw;
	mVertexCount = vertexCount;
	mEdgeCount = 0;
}

bool TravelPlanGraphic::Insert(const RoadEdgeNode& roadEdgeNode)
{
	if (roadEdgeNode.v1Index < 0 || roadEdgeNode.v1Index >= mVertexCount || roadEdgeNode.v2Index < 0 || roadEdgeNode.v2Index >= mVertexCount)
		return false;
	TPNode* newNode = new TPNode(roadEdgeNode.v2Index, roadEdgeNode.length,roadEdgeNode.cost);
	if (!newNode) return false;
	newNode->next = mGraphicTable[roadEdgeNode.v1Index].next;
	mGraphicTable[roadEdgeNode.v1Index].next = newNode;
	mEdgeCount++;
	return true;
}

inline void TravelPlanGraphic::Dijkstra(int start, int end)
{
#pragma region apply for memory
	int* shortestPathLastIndex = new int[mVertexCount];
	if (!shortestPathLastIndex) throw;
	TPFactor* shortestDist = new TPFactor[mVertexCount];
	if (!shortestDist) throw;
	for (int i = 0; i < mVertexCount; i++)
	{
		shortestDist[i].length = MaxValue;
		shortestDist[i].cost= MaxValue;
		shortestPathLastIndex[i] = -1;
		mGraphicTable[i].mIsVisited = false;
	}
#pragma endregion
	TPFactor minWeight;
	int minWeightIndex = 0;
	shortestDist[start].length = 0;
	shortestDist[start].cost= 0;
	for (int i = 0; i < mVertexCount; i++)
	{
		minWeight.length = MaxValue;
		minWeight.cost = MaxValue;
		for (int j = 0; j < mVertexCount; j++)
		{
			if ((!mGraphicTable[j].mIsVisited && shortestDist[j].length < minWeight.length)
				|| (!mGraphicTable[j].mIsVisited && (shortestDist[j].length == minWeight.length)
					&& shortestDist[j].cost < minWeight.cost))
			{
				minWeight = shortestDist[j];
				minWeightIndex = j;
			}
		}
		mGraphicTable[minWeightIndex].mIsVisited = true;
		TPNode* head = mGraphicTable[minWeightIndex].next;
		while (head)
		{
			int index = head->mAdjv;
			if (!mGraphicTable[index].mIsVisited &&
				shortestDist[index].length > shortestDist[minWeightIndex].length+ head->mLength)
			{
				shortestDist[index].length = shortestDist[minWeightIndex].length + head->mLength;
				shortestDist[index].cost = shortestDist[minWeightIndex].cost + head->mCost;
				shortestPathLastIndex[index] = minWeightIndex;
			}
			else if (!mGraphicTable[index].mIsVisited &&
				(shortestDist[index].length == shortestDist[minWeightIndex].length + head->mLength) &&
				shortestDist[index].cost > shortestDist[minWeightIndex].cost + head->mCost)
			{
				shortestDist[index].cost= shortestDist[minWeightIndex].cost+ head->mCost;
				shortestPathLastIndex[index] = minWeightIndex;
			}
			head = head->next;
		}
	}
	std::cout << shortestDist[end].length << " " << shortestDist[end].cost << std::endl;
	delete[] shortestPathLastIndex;
	shortestPathLastIndex = nullptr;
	delete[] shortestDist;
	shortestDist = nullptr;
}

inline TravelPlanGraphic::~TravelPlanGraphic()
{
	if (mGraphicTable)
	{
		for (int i = 0; i < mVertexCount; i++)
		{
			TPNode* head = mGraphicTable[i].next;
			while (head)
			{
				TPNode* deleteNode = head;
				head = head->next;
				delete deleteNode;
				deleteNode = nullptr;
			}
		}
		delete[] mGraphicTable;
		mGraphicTable = nullptr;
	}
	mVertexCount = 0;
	mEdgeCount = 0;
}
#endif // !_GRAPH_H
