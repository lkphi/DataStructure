// DataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "LinearList.h"
#include "stack.h"
#include "queue.h"
#include <string>
#include "Search.h"
#include "tree.h"
#include "sort.h"
#include "HashTable.h"
#include "Heap.h"
#include "Set.h"
#include <iomanip>
#include "Graph.h"
#include "kmp.h"
#include "Polygon.h"

void printArray(int a[], unsigned int length);
void printArray(char a[], unsigned int length);

#pragma region save 007 function
float Distance(float p1x, float p1y, float p2x, float p2y)
{
	return sqrt((p1x - p2x) *(p1x - p2x)+ (p1y - p2y) * (p1y - p2y));
}
struct CPoint
{
	float x, y;
};
const int maxNodeCount = 150;
CPoint cNodeArray[maxNodeCount];
bool isVisitdArray[maxNodeCount];
int crocodileCount, maxJumpDistance;
queue<int>* cqueue = new queue<int>();
bool CanJump(CPoint point,CPoint nextPoint)
{
	float dis = Distance(nextPoint.x, nextPoint.y, point.x, point.y);
	if (dis <= maxJumpDistance) return true;
	else return false;
}
bool IsSafe(CPoint point)
{
	float max = abs(point.x) > abs(point.y) ? abs(point.x) : abs(point.y);
	if (max + maxJumpDistance >= 50)
		return true;
	else return false;
}

bool DFS(int index)
{
	if (IsSafe(cNodeArray[index])) return true;
	for (int i = 0; i < crocodileCount; i++)
	{
		if (!isVisitdArray[i] && CanJump(cNodeArray[i], cNodeArray[index]))
		{
			isVisitdArray[i] = true;
			if (DFS(i)) return true;
			//isVisitdArray[i] = false;
		}
	}
	return false;
}

bool BFS()
{
	while (!cqueue->isEmpty())
	{
		int index=cqueue->front();
		cqueue->pop();
		if (IsSafe(cNodeArray[index])) return true;
		for (int i = 0; i < crocodileCount; i++)
		{
			if (!isVisitdArray[i] && CanJump(cNodeArray[i], cNodeArray[index]))
			{
				isVisitdArray[i] = true;
				cqueue->push(i);
			}
		}
	}
	return false;
}
//distance[w]表示为起点s到w的最短距离
//path[w]表示为起点s到w的路上经过的某个顶点
int distance[maxNodeCount];
int path[maxNodeCount];
int lastLeavelIndex = 0;
bool ShorterPath()
{
	while (!cqueue->isEmpty())
	{
		int index = cqueue->front();
		cqueue->pop();
		if (IsSafe(cNodeArray[index]))
		{
			lastLeavelIndex = index;
			return true;
		}
		for (int i = 0; i < crocodileCount; i++)
		{
			if (distance[i]==-1 && CanJump(cNodeArray[i], cNodeArray[index]))
			{
				distance[i] = distance[index] + 1;
				path[i] = index;
				cqueue->push(i);
			}
		}
	}
	return false;
}
#pragma endregion

#pragma region six degrees of separation function
int nodeCount, edgeCount;
int AdjMatrix[maxNodeCount][maxNodeCount];
int SDS_BFS(int index)
{
	isVisitdArray[index] = true;
	queue<int>* squeue = new queue<int>();
	squeue->push(index);
	int count = 1, level = 0;//level为层数
	int last = index, tail = 0;
	while (!squeue->isEmpty())
	{
		int popIndex=squeue->front();
		squeue->pop();
		for (int i = 0; i < nodeCount; i++)
		{
			if (!isVisitdArray[i] && AdjMatrix[popIndex][i] == 1)
			{
				isVisitdArray[i] = true;
				squeue->push(i);
				count++;
				tail = i;
			}//tail为每次访问下一层的最后元素
		}
		if (popIndex == last) {
			level++;
			last = tail;
		}
		if (level == 6) break;
	}
	delete squeue;
	squeue = nullptr;
	return count;
}
#pragma endregion

int main()
{
	#pragma region test Linear List
		//List<int>* node = new List<int>();
		//(node->PushBack(2)).PushBack(34);
		//(*node).PushBack(54).PushBack(44).PushBack(32);
		//std::cout << node;
		//(*node).BackInsert(3,89).BackInsert(3,23);
		//(*node).FrontInsert(2,76);
		//node->PrintList();
		//(node->FrontInsert(-1, 89)).FrontInsert(2,55);
		//std::cout << node;
		//node->FrontInsert(0, 89);
		//std::cout << node;
		//node->FrontInsert(node->Length() + 1, 89);
		//std::cout << node;
		//std::cout << (*node)[4] << std::endl;
		//node->ReverseList(0);
		//std::cout << node;
		//node->ReverseList(1);
		//std::cout << node;
		//node->ReverseList(2);
		//std::cout << node;
		//node->ReverseList(node->Length() - 1);
		//node->RemoveBaseOnData(44);
		//std::cout << node;
		//std::cout << node->Length() << std::endl;
		//node->Release();
		//std::cout << node->Length() << std::endl;
		//std::cout << node;
	#pragma endregion

	#pragma region test polygon
	//float coef[] = { 2.0f,4.5f,8.0f,2.3f };
	//int exp[] = {2,5,3,1};
	//float coef1[] = { 3.0f,6.7f,1.3f,4.5f,0.5 };
	//int exp1[] = { 7,3,5,6,11 };
	//float coef2[] = { 1.2f,8.3f,4.56f,7.8f };
	//int exp2[] = { 3,9,1,0 };
	//Polygon<float>* p = new Polygon<float>(coef, 4, exp, 4);
	//Polygon<float>* p1 = new Polygon<float>(coef1, 5, exp1, 5);
	//Polygon<float>* p2 = new Polygon<float>(coef2, 4, exp2, 4);
	//Polygon<float> p3 = (*p) * (*p2);
	//std::cout << "*p:  " << *p << std::endl;
	//std::cout << "-(*p):  " << -(*p) << std::endl;
	//std::cout << "(*p)(3):  " << (*p)(3) << std::endl;
	//std::cout << "*p1:  " << *p1 << std::endl;
	//std::cout << "-(*p1):  " << -(*p1) << std::endl;
	//std::cout << "(*p1)(3):  " << (*p1)(3) << std::endl;
	//std::cout << "(*p2):  " << (*p2) << std::endl;
	//std::cout << "*p + *p1:  " << *p + *p1 << std::endl;
	//std::cout << "*p - *p1:  " << *p - *p1 << std::endl;
	//std::cout << "*p + *p1 +*p2:  " << *p + *p1 + *p2 << std::endl;
	//std::cout << "*p - *p1 - *p2:  " << *p - *p1 - *p2 << std::endl;
	//std::cout << "p3: " << p3 << std::endl;
	//p3 *= (*p);
	//std::cout << "p3: " << p3 << std::endl;
	//(*p2) += (*p1);
	//std::cout << "(*p2):  " << *p2 << std::endl;
	//(*p2) -= (*p);
	//std::cout << "(*p2):  " << *p2 << std::endl;
	//(*p2) = (*p1);
	//std::cout << "(*p2):  " << *p2 << std::endl;
	//(*p) = (*p2) = (*p1);
	//std::cout << "(*p2):  " << *p2 << std::endl;
	//std::cout << "(*p):  " << *p << std::endl;
	//float coef4[] = { 2.0f,3.4f,5.3f,-2.0f,5.6f};
	//int exp4[] = { 2,5,3,2,6 };
	//Polygon<float>* p4 = new Polygon<float>(coef4, 5, exp4, 5);
	//std::cout << *p4 << std::endl;
	//delete p4;
	//delete p2;
	//delete p1;
	//delete p;
	//p4 = nullptr;
	//p2 = nullptr;
	//p1 = nullptr;
	//p = nullptr;
	#pragma endregion

	#pragma region test stack
	//stack<int>* int_stack = new stack<int>();
	//std::cout << int_stack->IsEmpty() << std::endl;
	//std::cout << int_stack->Size() << std::endl;

	//int_stack->Push(2);
	//std::cout << int_stack->IsEmpty() << std::endl;
	//std::cout << int_stack->Size() << std::endl;

	//int_stack->Push(342);
	//int_stack->Push(56);
	//int_stack->Push(87);
	//int_stack->Push(324);
	//int_stack->PrintStack();
	//std::cout << int_stack->Top() << std::endl;
	//std::cout << int_stack->Size() << std::endl;
	//std::cout << int_stack->Pop() << std::endl;
	//int_stack->PrintStack();
	//int_stack->Clear();
	//std::cout << int_stack->IsEmpty() << std::endl;
	//std::cout << int_stack->Size() << std::endl;
	#pragma endregion

	#pragma region test Stack
	//Stack<int>* int_Stack = new Stack<int>();
	//std::cout << "stack is emty?  :" << int_Stack->IsEmpty() << std::endl;
	//std::cout << "the sizez of stack is " << int_Stack->Size() << std::endl;

	//int_Stack->Push(2);
	//std::cout << "stack is emty?  :" << int_Stack->IsEmpty() << std::endl;
	//std::cout << "the size of stack is " << int_Stack->Size() << std::endl;

	//int_Stack->Push(342);
	//int_Stack->Push(56);
	//int_Stack->Push(87);
	//int_Stack->Push(12);
	//int_Stack->Push(24);
	//int_Stack->Push(34);
	//int_Stack->Push(67);
	//int_Stack->Push(89);

	//int_Stack->Push(7);
	//int_Stack->Push(65);
	//std::cout << "the size of stack is " << int_Stack->Size() << std::endl;
	//int_Stack->Push(54);
	//int_Stack->Push(21);
	//int_Stack->PrintStack();
	//std::cout <<"the top element of satck is "<< int_Stack->Top() << std::endl;
	//std::cout << "the size of stack is " << int_Stack->Size() << std::endl;
	//std::cout <<"the pop element of satck is "<< int_Stack->Pop() << std::endl;
	//int_Stack->PrintStack();
	//int_Stack->Clear();
	//std::cout << "stack is emty?  :" << int_Stack->IsEmpty() << std::endl;
	//std::cout << "the size of stack is " << int_Stack->Size() << std::endl;
	#pragma endregion

	#pragma region test LoopQueue
	//LoopQueue<std::string> queue(6);
	//queue.push("one");
	//queue.push("two");
	//queue.push("three");
	//queue.push("four");
	//queue.push("five");
	//queue.print();
	//std::cout << queue;
	//std::cout << "队列长度:" << queue.size() << std::endl;
	//std::cout << queue.front() << std::endl;
	//queue.pop();
	//std::cout << "队列长度:" << queue.size() << std::endl;
	//std::cout << queue.isFull() << std::endl;
	//while (!queue.isEmpty()) {
	//	queue.pop();
	//}
	//std::cout << queue.isEmpty() << std::endl;
	#pragma endregion

	#pragma region test Queue
	//queue<std::string> queues;
	//queues.push("one");
	//queues.push("two");
	//queues.push("three");
	//queues.push("four");
	//queues.push("five");
	//queues.print();
	//std::cout << queues;
	//std::cout << "队列长度:" << queues.size() << std::endl;
	//std::cout << queues.front() << std::endl;
	//queues.pop();
	//std::cout << "队列长度:" << queues.size() << std::endl;
	//queues.print();
	//std::cout << queues.isEmpty() << std::endl;
	#pragma endregion

	#pragma region test Dequue
	//deque<std::string> deque;
	//deque.push("one");
	//deque.push("two");
	//deque.push("three");
	//deque.push("four");
	//deque.push("five");
	//deque.print();
	//std::cout << deque;
	//std::cout << "队列长度:" << deque.size() << std::endl;
	//std::cout << deque.front() << std::endl;
	//deque.pop();
	//std::cout << "队列长度:" << deque.size() << std::endl;
	//deque.print();
	//deque.back_append("six");
	//deque.print();
	//std::cout << deque;
	//deque.front_append("zero");
	//deque.print();

	//deque.front_remove();
	//deque.print();
	//deque.back_remove();
	//deque.print();

	//std::cout << deque[2] << std::endl;
	//std::cout << deque.isEmpty() << std::endl;
	#pragma endregion

	#pragma region test BinarySearch
	//int a[6] = { 12,23,34,56,78,90 };
	//std::cout << BinarySearch(a, 6, 23) << std::endl;
	//std::cout << BinarySearch(a, 6, 12) << std::endl;
	//std::cout << BinarySearch(a, 6, 34) << std::endl;
	//std::cout << BinarySearch(a, 6, 56) << std::endl;
	//std::cout << BinarySearch(a, 6, 78) << std::endl;
	//std::cout << BinarySearch(a, 6, 90) << std::endl;
	//std::cout << BinarySearch(a, 6, 77) << std::endl;
	//std::cout << BinarySearch(a, 6, 1000) << std::endl;
	//int b[5] = { 12,23,34,56,78 };
	//std::cout << BinarySearch(b, 5, 23) << std::endl;
	//std::cout << BinarySearch(b, 5, 12) << std::endl;
	//std::cout << BinarySearch(b, 5, 34) << std::endl;
	//std::cout << BinarySearch(b, 5, 56) << std::endl;
	//std::cout << BinarySearch(b, 5, 78) << std::endl;
	//std::cout << BinarySearch(b, 5, 563) << std::endl;
	//std::cout << BinarySearch(b, 5, 782) << std::endl;
	//int c[7] = { 1,4,7,10,13,16,19 };
	//std::cout << BinarySearch(c, 7, 10) << std::endl;
	#pragma endregion

	#pragma region test binarytree
	//BiTree<char>* biTree=new BiTree<char>();//a b d h # # i # # e j # # # c f # # g # #
	//biTree->CreateBiTree();
	//biTree->PrintTree();
	//biTree->InOrderTraversal();//h d i b j e a f c g
	//biTree->PostOrderTraversal();//h i d j e b f g c a
	//biTree->PreOrderTraversal();//a b d h i e j c f g
	//biTree->LevelOrderTraversal();
	//biTree->InOrderUsedByStack();
	//biTree->PostOrderUsedByStack();
	//biTree->PreOrderUsedByStack();
	//biTree->PreOrderPrintLeaves();
	//std::cout << "whether the tree is empty: " << biTree->IsEmpty() << std::endl;
	//std::cout << "the count of leaf node: " << biTree->LeafNodeCount() << std::endl;
	//std::cout << "the height of the tree is: " << biTree->PostOrderGetHeight() << std::endl;
	//char preOrderArray[] = { 'a', 'b', 'd', 'h', 'i', 'e','j', 'c', 'f', 'g' };
	//char inOrderArray[] = { 'h', 'd', 'i', 'b', 'j', 'e', 'a', 'f', 'c', 'g' };
	//biTree->GetPostOrderByPre_InOrderSeralize(preOrderArray, 10, inOrderArray, 10);
	//std::cout << std::endl;
	//delete biTree;
	//biTree = nullptr;
	#pragma endregion

	#pragma region test binary tree Isomorphic 同构
	
	//BinTreeArray<char>* bti = new BinTreeArray<char>();
	//bti->BuildTree();
	//BinTreeArray<char>* bti1 = new BinTreeArray<char>();
	//bti1->BuildTree();
	//std::cout << std::boolalpha << bti->Isomorphic(*bti1) << std::endl;
	//delete bti;
	//bti = nullptr;
	//delete bti1;
	//bti1 = nullptr;
	#pragma endregion

	#pragma region test BinSearchTree
	//BinSearchTree<int>* binSearchTree = new BinSearchTree<int>();//0 1 2 3 # # 4 # # 5 6 # # # 7 8 # # 9 # #
	//int array[] = {0,1,2,3,4,5,6,7,8,9 };
	//for (int i = 0; i <= 15; ++i)
	//	binSearchTree->Insert(i);
	//binSearchTree->PrintTree();
	//int* completeBinTreeArray = new int[10];
	//binSearchTree->GetCompleteBinTree(array, 10, completeBinTreeArray);
	//printArray(completeBinTreeArray, 10);
	//delete binSearchTree;
	//binSearchTree = nullptr;
	//BinSearchTree<int>* bst = new BinSearchTree<int>();
	//bst->BuildBSTTree(6);
	//bst->PrintTree();
	//delete bst;
	//bst = nullptr;
	//BalanceBinTree<int>* bbt = new BalanceBinTree<int>();
	//for (int i = 0; i <= 15; ++i)
	//	bbt->Insert(i);
	//bbt->PrintTree();
	//bbt->InOrderTraversal();
	//bbt->PreOrderTraversal();
	//bbt->LevelOrderTraversal();
	//std::cout << bbt->FindMax()->data << std::endl;
	//std::cout << bbt->FindMin()->data << std::endl;
	//bool res = bbt->JugeSame(16);//7 3 11 1 5 9 13 0 2 4 6 8 10 12 14 15
	//std::cout << std::boolalpha << res << std::endl;
	//bbt->Remove(5);
	//bbt->PrintTree();
	//bbt->Remove(7);
	//bbt->PrintTree();
	//std::cout << bbt->Find(3)->data << std::endl;
	//res = bbt->JugeSame(16);//7 3 11 1 5 9 13 0 2 4 6 8 10 12 14 15
	//std::cout << std::boolalpha << res << std::endl;
	//delete bbt;
	//bbt = nullptr;
	
	#pragma endregion

	#pragma region test sort
	//int a[] = { 12,45,32,46,78,3,56,32,33,89,12 };
	//Bubble_Sort(a, 11);
	//printArray(a, 11);
	//DoubleSelection_Sort(a, 11);
	//printArray(a, 11);
	//Selection_Sort(a, 11);
	//printArray(a, 11);
	//Insertion_Sort(a, 11);
	//printArray(a, 11);
	//CockTail_Sort(a, 11);
	//printArray(a, 11);
	//Shell_Sort(a, 11);
	//printArray(a, 11);
	//Quick_Sort(a, 11);
	//printArray(a, 11);
	//Bucket_Sort(a, 11);
	//printArray(a, 11);
	//Radix_Sort(a, 11);
	//printArray(a, 11);
	//Heap_Sort(a, 11);
	//printArray(a, 11);
	//Merge_Sort(a, 11);
	//printArray(a, 11);
	//MergeSort(a, 11);
	//printArray(a, 11);
	//int* table = new int[11];
	//Table_Sort(a, 11, table);
	//printArray(table, 11);
	//for (int i = 0; i < 11; ++i)
	//	std::cout << a[table[i]] << " ";
	//std::cout << std::endl;
	//Physical_Sort(a, 11, table);
	//printArray(a, 11);
	//delete[] table;
	//table = nullptr;
	//Radix_Sort(a, 11);
	//printArray(a, 11);
	//Bucket_Sort(a, 11);
	//printArray(a, 11);
	#pragma endregion

	#pragma region Insert or Merge
//插入排序前面有序，后面没有变化
//归并排序：分段排序
//int arrayLength;
//std::cin >> arrayLength;
//int* array = new int[arrayLength];
//int* sortArray = new int[arrayLength];
//for (int i = 0; i < arrayLength; ++i)
//	std::cin >> array[i];
//for (int i = 0; i < arrayLength; ++i)
//	std::cin >> sortArray[i];
//bool isInsertSort = false;
//int i = 0;
//for (; i < arrayLength; ++i)
//{
//	if (sortArray[i] > sortArray[i + 1])
//		break;
//}
//if (i != arrayLength)
//{
//	for (i+=1; i < arrayLength; ++i)
//	{
//		if (array[i] != sortArray[i])
//			break;
//	}
//}
//if (i == arrayLength)
//	isInsertSort = true;
//int mergeCount = 0;
//if (!isInsertSort)
//{
//	int mergeStep = 1;
//	while (mergeStep <= arrayLength)
//	{
//		for (i = mergeStep; i < arrayLength; i += 2*mergeStep)
//		{
//			if (sortArray[i] < sortArray[i - 1])
//				break;
//		}
//		if (i < arrayLength)
//			break;
//		mergeStep *= 2;
//		mergeCount++;
//	}
//}
//if (isInsertSort)
//{
//	std::cout << "Insertion Sort" << std::endl;
//	printArray(sortArray, arrayLength);
//}
//else
//{
//	std::cout << "Merge Sort" << std::endl;
//	printArray(sortArray, arrayLength);
//	std::cout << "归并次数：" << mergeCount << std::endl;
//}
//
//delete[] array;
//delete[] sortArray;
//array = nullptr;
//sortArray = nullptr;
	#pragma endregion

	#pragma region 电话狂人
	//#define MAXD 5//参与哈希函数计算的字符个数
	//#define KEYLENGTH 11//关键字符串长度，电话号码长度为11
	//int PhoneDataCount;
	//std::cout << "please input phone number Count:\n";
	//std::cin >> PhoneDataCount;
	//hashTable hashtbl(PhoneDataCount * 2);
	//char* str=new char[12];
	//for (int i = 0; i < PhoneDataCount; i++)
	//{
	//	scanf("%s", str); 
	//	hashtbl.Insert(str + KEYLENGTH - MAXD);
	//	scanf("%s", str); 
	//	hashtbl.Insert(str + KEYLENGTH - MAXD);
	//}
	////扫描整个表确定那个电话号码呼叫次数最多
	//List<char*>res = hashtbl.MaxCountData();
	//std::cout << res;
	//res.Release();
	//delete[] str;
	//str = nullptr;
	#pragma endregion

	#pragma region Hard Version
	//int hashTableSize;
	//std::cin >> hashTableSize;
	//int* hashTable = new int[hashTableSize];
	//for (int i = 0; i < hashTableSize; ++i)
	//{
	//	int num;
	//	std::cin >> num;
	//	hashTable[i] = num;
	//}
	//TGraph<int>* graph = new TGraph<int>(hashTableSize,true);
	//for (int i = 0; i < hashTableSize; ++i)
	//{
	//	int index = Hash(hashTable[i], hashTableSize);
	//	if (hashTable[i] < 0 || index == i)
	//		continue;
	//	int testIndex = index;
	//	while (testIndex != i && hashTable[testIndex] > 0)
	//	{
	//		graph->Insert(EdgeNode(testIndex, i));
	//		testIndex++;
	//		if (testIndex > hashTableSize - 1)
	//			testIndex -= hashTableSize;
	//	}
	//}
	//int* indegree = new int[hashTableSize];//每个顶点的入度
	//for (int i = 0; i < hashTableSize; ++i)
	//	indegree[i] = 0;
	//for (int i = 0; i < hashTableSize; ++i)
	//{
	//	AdjVNode<int>* head = graph->mGraphTable[i].next;
	//	while (head)
	//	{
	//		++indegree[head->mAdjv];
	//		head = head->next;
	//	}
	//}
	//int* sortArray = new int[hashTableSize];
	//int index = 0;
	////可以用最小堆来做会更快
	//while (index < hashTableSize)
	//{
	//	int minValue = INT_MAX;
	//	int minValueIndex = 0;
	//	for (int i = 0; i < hashTableSize; ++i)
	//	{
	//		if (indegree[i] == 0)
	//		{
	//			if (hashTable[i] < minValue)
	//			{
	//				minValue = hashTable[i];
	//				minValueIndex = i;
	//			}
	//		}
	//	}
	//	if (minValue > 0)
	//		std::cout << minValue << " ";
	//	--indegree[minValueIndex];
	//	AdjVNode<int>* head = graph->mGraphTable[minValueIndex].next;
	//	while (head)
	//	{
	//		--indegree[head->mAdjv];
	//		head = head->next;
	//	}
	//	index ++;
	//}
	//std::cout << std::endl;
	//delete[] indegree;
	//delete graph;
	//delete[] hashTable;
	//indegree = nullptr;
	//graph = nullptr;
	//hashTable = nullptr;
	#pragma endregion

	#pragma region test heap
	/*c: a  e  i  s t sp nl
	f: 10 15 12 3 4 13 1
					  58
				/           \
			   25           33
			  / \        /     \
			 12 13      15     18
							 /    \
							 8    10
						   /  \
						   4   4
							  /  \
							  1  3
	a:111 e:10 i:00 s:11011 t:1100 sp:01 nl:11010*/
	//int array[] = { 10,15,12,3,4,13,1 };
	//MinHeap<HuffmanTreeNode<int>*>* minHeap=new MinHeap<HuffmanTreeNode<int>*>(array, 7);
	//std::cout << *minHeap;
	//HuffmanTree<int>* huffmanTree = new HuffmanTree<int>(*minHeap);
	//huffmanTree->PreOrderTraversal();
	//huffmanTree->HuffmanCoded();
	#pragma endregion

	#pragma region test set
	//int array[] = { 1,2,3,4,5 };
	//Set<int>* set=new Set<int>(array, 5);
	//std::cout << std::boolalpha <<set->CheckConnection(3, 2)<<std::endl;//false
	//set->Union(3, 2);
	//std::cout << std::boolalpha << set->CheckConnection(1, 5) << std::endl;//false
	//set->Union(4,5);
	//set->Union(2,4);
	//std::cout << std::boolalpha << set->CheckConnection(3, 5) << std::endl;//true
	//std::cout << set->SetCount() << std::endl;//2
	#pragma endregion

	#pragma region test graph
//MGraph<int>* mGraph = new MGraph<int>(7);
//mGraph->Insert(EdgeNode(0, 1, 2));
//mGraph->Insert(EdgeNode(0, 3, 1));
//mGraph->Insert(EdgeNode(0, 2, 4));
//mGraph->Insert(EdgeNode(1, 3, 3));
//mGraph->Insert(EdgeNode(1, 4, 10));
//mGraph->Insert(EdgeNode(2, 3, 2));
//mGraph->Insert(EdgeNode(2, 5, 5));
//mGraph->Insert(EdgeNode(3, 4, 7));
//mGraph->Insert(EdgeNode(3, 5, 8));
//mGraph->Insert(EdgeNode(3, 6, 4));
//mGraph->Insert(EdgeNode(4, 6, 6));
//mGraph->Insert(EdgeNode(5, 6, 1));
//std::cout << std::boolalpha << mGraph->BFS(0) << std::endl;
//std::cout << std::boolalpha << mGraph->DFS(0) << std::endl;
//mGraph->Dijkstra(0);
//for (int i = 0; i < 7; ++i)
//	std::cout << mGraph->mShortestDist[i] << " ";
//std::cout << std::endl;
//for (int i = 0; i < 7; ++i)
//	std::cout << mGraph->mShortestPathLastIndex[i] << " ";
//std::cout << std::endl;
//mGraph->MinHeapDijkstra(0);
//for (int i = 0; i < 7; ++i)
//	std::cout << mGraph->mShortestDist[i] << " ";
//std::cout << std::endl;
//for (int i = 0; i < 7; ++i)
//	std::cout << mGraph->mShortestPathLastIndex[i] << " ";
//std::cout << std::endl;
//mGraph->Floyd();
//for (int i = 0; i < 7; ++i)
//{
//	for (int j = 0; j < 7; ++j)
//		std::cout << mGraph->mShortestDistMatrix[i][j] << " ";
//	std::cout << "\n";
//}
//for (int i = 0; i < 7; ++i)
//{
//	for (int j = 0; j < 7; ++j)
//		std::cout << mGraph->mShortestPathLastIndexMatrix[i][j] << " ";
//	std::cout << "\n";
//}
//if (mGraph->Prim(0))
//{
//	for (int i = 0; i < 7; ++i)
//		std::cout << mGraph->mMSTParent[i] << " ";
//	std::cout << std::endl;
//}
//mGraph->Kruskal();
//delete mGraph;
//mGraph = nullptr;
//
//std::cout << "=========================" << std::endl;
//std::cout << "=========================" << std::endl;
//
//TGraph<int>* tGraph = new TGraph<int>(7);
//tGraph->Insert(EdgeNode(0, 1, 2));
//tGraph->Insert(EdgeNode(0, 3, 1));
//tGraph->Insert(EdgeNode(0, 2, 4));
//tGraph->Insert(EdgeNode(1, 3, 3));
//tGraph->Insert(EdgeNode(1, 4, 10));
//tGraph->Insert(EdgeNode(2, 3, 2));
//tGraph->Insert(EdgeNode(2, 5, 5));
//tGraph->Insert(EdgeNode(3, 4, 7));
//tGraph->Insert(EdgeNode(3, 5, 8));
//tGraph->Insert(EdgeNode(3, 6, 4));
//tGraph->Insert(EdgeNode(4, 6, 6));
//tGraph->Insert(EdgeNode(5, 6, 1));
//std::cout << std::boolalpha << tGraph->BFS(0) << std::endl;
//std::cout << std::boolalpha << tGraph->DFS(0) << std::endl;
//tGraph->Dijkstra(0);
//for (int i = 0; i < 7; ++i)
//	std::cout << tGraph->mShortestDist[i] << " ";
//std::cout<< std::endl;
//for (int i = 0; i < 7; ++i)
//	std::cout << tGraph->mShortestPathLastIndex[i] << " ";
//std::cout << std::endl;
//tGraph->MinHeapDijkstra(0);
//for (int i = 0; i < 7; ++i)
//	std::cout << tGraph->mShortestDist[i] << " ";
//std::cout << std::endl;
//for (int i = 0; i < 7; ++i)
//	std::cout << tGraph->mShortestPathLastIndex[i] << " "; 
//std::cout<< std::endl;
//if (tGraph->Prim(0))
//{
//	for (int i = 0; i < 7; ++i)
//		std::cout << tGraph->mMSTParent[i] << " ";
//	std::cout << std::endl;
//}
//tGraph->Kruskal();
//delete tGraph;
//tGraph = nullptr;
	#pragma endregion

	#pragma region save 007
	#pragma region input data
	//std::cin >> crocodileCount >> maxJumpDistance;
	//for (int i = 0; i < crocodileCount; i++)
	//{
	//	std::cin >> cNodeArray[i].x >> cNodeArray[i].y;
	//}
	#pragma endregion
	//bool ans = false;
	#pragma region use DFS method
	//for (int i = 0; i < crocodileCount; i++)
	//{
	//	if (Distance(cNodeArray[i].x, cNodeArray[i].y, 0, 0) - 15.0f / 2.0f <= maxJumpDistance)
	//	{
	//		isVisitdArray[i] = true;
	//		ans=DFS(i);
	//		if (ans) break;
	//	}
	//}
	#pragma endregion
	#pragma region use BFS method
	//int minPath = INT_MAX;
	//stack<int>* stackPath = new stack<int>();
	//for (int i = 0; i < crocodileCount; i++)
	//{
	//	for (int j = 0; j < crocodileCount; j++)
	//	{
	//		distance[j] = -1;
	//		path[j] = 0;
	//	}
	//	if (Distance(cNodeArray[i].x, cNodeArray[i].y, 0, 0) - 15.0f / 2.0f <= maxJumpDistance)
	//	{
	//		distance[i] = 0;
	//		cqueue->push(i);
	//		ans = ShorterPath();// BFS();
	//		if (ans)
	//		{
	//			if (distance[lastLeavelIndex] < minPath)
	//			{
	//				minPath = distance[lastLeavelIndex];
	//				stackPath->Clear();
	//				int backPathIndex = lastLeavelIndex;
	//				do {
	//					stackPath->Push(backPathIndex);
	//					backPathIndex = path[backPathIndex];
	//				} while (backPathIndex != i);
	//			}
	//			//break;
	//		}
	//	}
	//}
	#pragma endregion
	delete cqueue;
	cqueue = nullptr;
	#pragma region ouput result
	//if (minPath != INT_MAX)
	//{
	//	std::cout << "Yes" << std::endl;
		//std::cout << "最短路径为" << minPath << std::endl;
		//std::cout << "所经过的路径结点为:";
		//while (!stackPath->IsEmpty())
		//{
		//	std::cout << stackPath->Pop() << " ";
		//}
		//std::cout << std::endl;
	//}
	//else std::cout << "No" << std::endl;
	//stackPath->Clear();
	//delete stackPath;
	#pragma endregion
	#pragma endregion

	#pragma region six degrees of separation 六度空间
	//std::cin >> nodeCount >> edgeCount;
	//for (int i = 0; i < nodeCount; i++)
	//	for (int j = 0; j < nodeCount; j++)
	//		AdjMatrix[i][j] = 0;
	//for (int i = 0; i < edgeCount; i++)
	//{
	//	int v1, v2;
	//	std::cin >> v1 >> v2;
	//	AdjMatrix[v1 - 1][v2 - 1] = AdjMatrix[v2 - 1][v1 - 1] = 1;
	//}
	//for (int i = 0; i < nodeCount; i++)
	//{
	//	for (int i = 0; i < nodeCount; i++)
	//		isVisitdArray[i] = false;
	//	int count = SDS_BFS(i);
	//	float ans = count * 1.0f / (nodeCount * 1.0f) * 100;
	//	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) << ans << "%" << std::endl;
	//}
	#pragma endregion

	#pragma region test key Path
	//int vertexCount = 9;
	//int edgeCount = 12;
	//TGraph<AOE>* keyPath=new TGraph<AOE>(vertexCount,true);
	//(*keyPath).Insert(EdgeNode(0, 1, 6));
	//(*keyPath).Insert(EdgeNode(0, 2, 4));
	//(*keyPath).Insert(EdgeNode(1, 4, 1));
	//(*keyPath).Insert(EdgeNode(2, 4, 1));
	//(*keyPath).Insert(EdgeNode(4, 6, 9));
	//(*keyPath).Insert(EdgeNode(4, 7, 7));
	//(*keyPath).Insert(EdgeNode(6, 8, 2));
	//(*keyPath).Insert(EdgeNode(7, 8, 4));
	//(*keyPath).Insert(EdgeNode(0, 3, 5));
	//(*keyPath).Insert(EdgeNode(3, 5, 2));
	//(*keyPath).Insert(EdgeNode(5, 7, 4));
	//(*keyPath).Insert(EdgeNode(5, 4, 0));//特别增加
	//(*keyPath).mDataArray = new AOE[vertexCount];
	//for (int i = 0; i < vertexCount; ++i)
	//{
	//	(*keyPath).mDataArray[i].earliestTime = 0;
	//	(*keyPath).mDataArray[i].latestTime = MaxValue;
	//}
	//int* indegree = new int[vertexCount];//每个顶点的入度
	//int* outdegree = new int[vertexCount];
	//for (int i = 0; i < vertexCount; ++i)
	//{
	//	outdegree[i]=indegree[i] = 0;
	//}
	//queue<int>* vertexQueue = new queue<int>();
	////stack<int>* vertexStack = new stack<int>();
	//int* vertexArray = new int[vertexCount + edgeCount];
	//int* weightArray = new int[edgeCount];
	//for (int i = 0; i < vertexCount; ++i)
	//{
	//	AdjVNode<int>* head = keyPath->mGraphTable[i].next;
	//	while (head)
	//	{
	//		++indegree[head->mAdjv];
	//		++outdegree[i];
	//		head = head->next;
	//	}
	//}
	//for (int i = 0; i < vertexCount; ++i)
	//{
	//	if (!indegree[i])
	//		vertexQueue->push(i);
	//}
	//int popVertex = 0;
	//int vertexIndex = 0;
	//int weightIndex = 0;
	//while (!vertexQueue->isEmpty())
	//{
	//	popVertex = vertexQueue->front();
	//	vertexQueue->pop();
	//	AdjVNode<int>* head = keyPath->mGraphTable[popVertex].next;
	//	while (head)
	//	{
	//		int directedVertex = head->mAdjv;
	//		//vertexStack->Push(directedVertex);
	//		vertexArray[vertexIndex++] = directedVertex;
	//		weightArray[weightIndex++] = head->mWeight;
	//		if (keyPath->mDataArray[directedVertex].earliestTime < head->mWeight + (*keyPath).mDataArray[popVertex].earliestTime)
	//			keyPath->mDataArray[directedVertex].earliestTime = head->mWeight + (*keyPath).mDataArray[popVertex].earliestTime;
	//		if ((--indegree[directedVertex]) == 0)
	//			vertexQueue->push(directedVertex);
	//		head = head->next;
	//	}
	//	if (keyPath->mGraphTable[popVertex].next)
	//		//vertexStack->Push(popVertex);
	//		vertexArray[vertexIndex++] = popVertex;
	//}
	//delete[] indegree;
	//delete vertexQueue;
	//indegree = nullptr;
	//vertexQueue = nullptr;
	//std::cout << keyPath->mDataArray[popVertex].earliestTime << std::endl;
	//keyPath->TopSort();
	//keyPath->mDataArray[popVertex].latestTime = keyPath->mDataArray[popVertex].earliestTime;
	////vertexStack->PrintStack();
	//printArray(vertexArray, vertexIndex - 1);
	//int vertexArrayIndex = --vertexIndex;
	//int weightArrayIndex = --weightIndex;
	//while (vertexIndex >= 0)//!vertexStack->IsEmpty()
	//{
	//	popVertex = vertexArray[vertexIndex--];//vertexStack->Pop();
	//	for (int i = 1; i <= outdegree[popVertex]; ++i)
	//	{
	//		int directedVertex = vertexArray[vertexIndex--];//vertexStack->Pop();
	//		int weight = weightArray[weightIndex--];
	//		if (keyPath->mDataArray[popVertex].latestTime > keyPath->mDataArray[directedVertex].latestTime - weight)
	//			keyPath->mDataArray[popVertex].latestTime = keyPath->mDataArray[directedVertex].latestTime - weight;
	//	}
	//}
	//for (int i = 0; i < vertexCount; ++i)
	//	std::cout << keyPath->mDataArray[i].latestTime << " ";std::cout << std::endl;
	//while (vertexArrayIndex >= 0)
	//{
	//	popVertex = vertexArray[vertexArrayIndex--];
	//	for (int i = 1; i <= outdegree[popVertex]; ++i)
	//	{
	//		int directedVertex = vertexArray[vertexArrayIndex--];
	//		int weight = weightArray[weightArrayIndex--];
	//		int maneuverTime = keyPath->mDataArray[directedVertex].latestTime - keyPath->mDataArray[popVertex].earliestTime - weight;
	//		if (maneuverTime > 0)
	//			std::cout << directedVertex << "的机动时间：" << maneuverTime << std::endl;
	//	}
	//}
	//delete[] outdegree;
	////delete vertexStack;
	//delete[] vertexArray;
	//delete[] weightArray;
	//delete keyPath;
	//outdegree = nullptr;
	////vertexStack = nullptr;
	//vertexArray = nullptr;
	//weightArray = nullptr;
	//keyPath = nullptr;
	#pragma endregion

	#pragma region test travel Plan

	//int vertexCount, edgeCount, source, dest;
	//std::cin >> vertexCount >> edgeCount >> source >> dest;
	//TravelPlanGraphic* tpGraphic = new TravelPlanGraphic(vertexCount);
	//int v1, v2, length, cost;
	//for (int i = 0; i < edgeCount; i++)
	//{
	//	std::cin >> v1 >> v2 >> length >> cost;;
	//	tpGraphic->Insert(RoadEdgeNode(v1, v2, length, cost));
	//}
	//tpGraphic->Dijkstra(source, dest);
	//delete tpGraphic;
	//tpGraphic = nullptr;
	#pragma endregion

	#pragma region HarryPotter Test
	//int vertexCount, edgeCount;
	//std::cin >> vertexCount >> edgeCount;
	//MGraph<int>* graph = new MGraph<int>(vertexCount);
	//for (int i = 0; i < edgeCount; ++i)
	//{
	//	int v1, v2, weight;
	//	std::cin >> v1 >> v2 >> weight;
	//	graph->Insert(EdgeNode(v1 - 1, v2 - 1, weight));
	//}
	//int index = graph->FindMinPoint2OtherPoint() + 1;
	////if (index != 0)
	//	std::cout << graph->FindMinPoint2OtherPoint() + 1 << std::endl;
	////else std::cout << "找不到这样的动物！" << std::endl;
	//delete graph;
	//graph = nullptr;
	#pragma endregion

	#pragma region test KMP
//char str[] = "bbc abcdab abcdabcdabde";//"asasghjebjefhbajdenf";
//char pattern[] = "dab";//"gh";
//std::cout << KMP(str, pattern) << std::endl;
//std::cout << Kmp(str, pattern) << std::endl;

#pragma endregion
	return 0;
}

void printArray(int a[],unsigned int length)
{
	for (size_t i = 0; i < length; i++)
	{	
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}
void printArray(char a[], unsigned int length)
{
	for (size_t i = 0; i < length; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

