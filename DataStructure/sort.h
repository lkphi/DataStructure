#pragma once
#ifndef _SORT_H
#define _SORT_H
#include "Node.h"
#include "Queue.h"
#include "Heap.h"

#pragma region Swap 
template<typename T>
void Swap(T& firstElement, T& secondElement) noexcept
{
	T temp = firstElement;
	firstElement = secondElement;
	secondElement = temp;
}

template<typename T>
void Swap(T* firstElement, T* secondElement) noexcept
{
	Swap(*firstElement, *secondElement);
}

template<typename T>
void Swap(Node<T>* firstElement, Node<T>* secondElement) noexcept
{
	T temp = firstElement->data;
	firstElement->data = secondElement->data;
	secondElement->data = temp;
}
#pragma endregion

#pragma region Bubble Sort
///
///冒泡排序，最好情况：顺序O(N),最坏情况逆序O(N^2)
///
template<typename T>
void Bubble_Sort(T array[], int arrayLength)
{
	int flag = 0;
	for (int i = arrayLength - 1; i >= 0; i--)
	{
		flag= 0;
		for (int j = 0; j < i; j++)
		{
			if (array[j] > array[j + 1])
			{
				Swap(array[j], array[j + 1]);
					flag = 1;
			}
		}
		if (flag == 0) break;
	}
}

///
///鸡尾酒排序，最好情况：顺序O(N),最坏情况逆序O(N^2)
///
template<typename T>
void CockTail_Sort(T array[], int arrayLength)
{
	int flag = 0;
	for (int i = 0; i <= arrayLength / 2; i++)
	{
		flag = 0;
		//从左向右找出最大值
		for (int j = i; j < arrayLength - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				Swap(array[j], array[j + 1]);
				flag = 1;
			}
		}
		if (flag == 0) break;
		//flag = 0;
		//从右向左找出最小值
		for (int j = arrayLength - 1 - i; j > i; j--)
		{
			if (array[j] < array[j - 1])
			{
				Swap(array[j], array[j - 1]);
				flag = 1;
			}
		}
		if (flag == 0) break;
	}
}

//template<typename T>
//void Bubble_Sort(Node<T>& list)
//{
//	Node<T>* headi = list.next;
//	Node<T>* headj = nullptr;
//	int flag = 0;
//	while (headi->next)
//	{
//		flag = 0;
//		headj = headi->next;
//		while (headj)
//		{
//			if (headi->data > headj->data)
//			{
//				Swap(headi, headj);
//				flag = 1;
//			}
//			headj = headj->next;
//		}
//		if (flag == 0) break;
//	}
//	headi = headi->next;
//}
#pragma endregion

#pragma region Insertion Sort
///
///插入排序，最好情况：顺序O(N),最坏情况逆序O(N^2),小规模排序效果比较好
///
template<typename T>
void Insertion_Sort(T array[], int arrayLength)
{
	int j = 0;
	T insertElement;
	for (int i = 1; i < arrayLength; i++)
	{
		insertElement = array[i];
		j = i;
		for (; j > 0 && array[j - 1] > insertElement; j--)
		{
			array[j] = array[j - 1];//移出空位
		}
		array[j] = insertElement;//插入该元素
	}
}

template<typename T>
void Insertion_Sort(T array[], int left, int right)
{
	Insertion_Sort(array, right - left + 1);
}
#pragma endregion

#pragma region Shell Sort
///
///希尔排序，最好情况：,最坏情况O(N^2)
///
template<typename T>
void Shell_Sort(T array[], int arrayLength)
{
	int j = 0;
	T insertElement;
	for (int interval = arrayLength / 2; interval > 0; interval /= 2)
	{
		for (int i = interval; i < arrayLength; i++)
		{
			insertElement = array[i];
			j = i;
			for (; j >= interval && array[j - 1] > insertElement; j -= interval)
			{
				array[j] = array[j - interval];
			}
			array[j] = insertElement;
		}
	}
}
#pragma endregion

#pragma region Selection Sort
///
///选择排序，最好情况：,最坏情况O(N^2)
///
template<typename T>
void Selection_Sort(T array[], int arrayLength)
{
	int minPosition = 0;
	for (int i = 0; i < arrayLength - 1; i++)
	{
		//从array[i]到array[arrayLength-1]中找到最小的元素，并将其位置给minPosition
		//int minPosition = ScanForMin(array, i, arrayLength - 1);
		minPosition = i;
		for (int j = i + 1; j < arrayLength; j++)
		{
			if (array[j] < array[minPosition])
				minPosition = j;
		}
		if (minPosition != i)
			Swap(array[i], array[minPosition]);
	}
}

template<typename T>
void DoubleSelection_Sort(T array[], int arrayLength)
{
	int minPosition = 0, maxPosition = 0;
	for (int i = 0; i < arrayLength / 2 - 1; i++)
	{
		minPosition = i, maxPosition = arrayLength - i - 1;
		for (int j = i; j < arrayLength - i - 1; j++)
		{
			if (array[j] < array[minPosition])
				minPosition = j;
			if (array[j] > array[maxPosition])
				maxPosition = j;
		}
		if (minPosition != i)
			Swap(array[i], array[minPosition]);
		if (maxPosition != arrayLength - i - 1)
		{
			//如果最大值与循环起始值相同，由于之前交换了最小值时将array[i]与array[minPosition]交换了
			//现在真实的最大值下标为minPosition
			if (maxPosition == i)
				maxPosition = minPosition;
			Swap(array[arrayLength - i - 1], array[maxPosition]);
		}
	}
}
#pragma endregion

#pragma region Heap Sort
///
///堆排序，处理N个不同元素的随机排列的平均次数是2NlogN-O(NloglogN)
///虽然堆排序给出最佳平均时间复杂度，但实际效果不如用sedgewick增量序列的希尔排序
///
template<class T>
bool PercDown(T array[], int startIndex, int length)
{
	int child, parent;
	T adjustElement = array[startIndex];
	for (parent = startIndex + 1; parent * 2 < length; parent = child)
	{
		child = parent * 2;
		if (child != length && array[child + 1 - 1] > array[child - 1])
			child++;
		if (adjustElement >= array[child - 1]) break;
		else
			array[parent - 1] = array[child - 1];
	}
	array[parent - 1] = adjustElement;
	return true;
}

template<typename T>
void Heap_Sort(T array[], int arrayLength)
{
	for (int i = arrayLength / 2; i >= 0; i--)	//先从最后一个有儿子的节点开始调整
	{
		PercDown(array, i, arrayLength);
	}
	for (int i = arrayLength - 1; i > 0; i--)
	{
		Swap(array[0], array[i]);
		PercDown(array, 0, i);
	}
}

template<typename T>
void Heap_Sort2(T array[], int arrayLength)//O(NlogN)
{
	MinHeap<T>* minHeap = new MinHeap<T>(array, arrayLength);
	minHeap->BuildHeap();//O(N)
	for (int i = 0; i < arrayLength; i++)
	{
		array[i] = minHeap->RemoveRoot();//O(logN)
	}
}
#pragma endregion

#pragma region quick sort
///
///快速排序:最好情况O(NlogN),最坏O(N^2),与选取的基准点有关，经过优化基准点可以解决这个问题
///对于小规模的数据（例如N不到100）可能还不如插入排序快，故对此作了优化
///
#define QuickSortAarrayLenCutOff 100
template<typename T>
void Quick_Sort(T array[], int low, int high)
{
	//if (low < high)
	while (low < high)//尾递归时
	{
		int left = low, right = high;
		if (high - low + 1 < QuickSortAarrayLenCutOff)
		{
			Insertion_Sort(array, high - low + 1);
			break;
		}
		//int selectedPosition = round(1.0 * rand() / RAND_MAX) * (right - left) + left);
		//Swap(array[left], array[selectedPosition]);
		//优化基准点
		int mid = left + (right - left) / 2;
		if (array[left] > array[right])
			Swap(array[left], array[right]);
		if (array[mid] > array[right])
			Swap(array[mid], array[right]);
		if (array[mid] > array[left])
			Swap(array[left], array[mid]);

		T basePoint = array[left];
		while (left < right)
		{
			while (left < right && array[right] >= basePoint)
				right--;
			//Swap(array[lowp], array[highp]);
			array[left] = array[right];
			while (left < right && array[left] <= basePoint)
				left++;
			//(array[lowp], array[highp]);
			array[right] = array[left];
		}
		array[left] = basePoint;
		//Quick_Sort(array, low, left - 1);
		//Quick_Sort(array, left + 1, high);
		//尾递归
		if (left - low < high - left)
		{
			Quick_Sort(array, low, left - 1);
			low = left + 1;
		}
		else
		{
			Quick_Sort(array, left + 1, high);
			high = left - 1;
		}
	}
		
}

template<typename T>
void Quick_Sort(T array[], int arrayLength)
{
	Quick_Sort(array, 0, arrayLength - 1);
}

#pragma endregion

#pragma region merge sort
template<typename T>
void MergeS(T* array, T* sortArray, int leftStarti, int rightStarti, int rightEndi)
{
	int leftEndi = rightStarti - 1;//假设两列为左右挨在一起，则左侧终点位置
	int sortArrayStarti = leftStarti;
	int firstArrayi = leftStarti, secondArrayi = rightStarti;
	int numCount = rightEndi - leftStarti + 1;
	while (firstArrayi <= leftEndi && secondArrayi <= rightEndi)
	{
		if (array[firstArrayi] <= array[secondArrayi])
			sortArray[sortArrayStarti++] = array[firstArrayi++];
		else sortArray[sortArrayStarti++] = array[secondArrayi++];
	}
	while (firstArrayi <= leftEndi)//复制左边剩下的
		sortArray[sortArrayStarti++] = array[firstArrayi++];
	while (secondArrayi <= rightEndi)//复制右边剩下的
		sortArray[sortArrayStarti++] = array[secondArrayi++];
	for (int i = 0; i < numCount; ++i, rightEndi--)
		array[rightEndi] = sortArray[rightEndi];
}

///
///merge:leftstarti为左边起始位置 rightstarti为右边起始位置 rightendi为右边终点位置
///
template<typename T>
void Merge(T* array, T* sortArray, int leftStarti, int rightStarti, int rightEndi)
{
	int ElementsCount = rightEndi - leftStarti + 1;
	MergeS(array, sortArray, leftStarti, rightStarti, rightEndi);
	for (int i = 0; i < ElementsCount; i++)
	{
		array[i] = sortArray[i];
	}
}

///
///时间复杂度递推关系：T(N)=T(N/2)+T(N/2)+O(N)=>T(N)=O(NlogN)，稳定
///缺点：需要额外的空间
template<typename T>
void Merge_Sort(T* array, T* sortArray, int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = left + (right - left) / 2;
		Merge_Sort(array, sortArray, left, mid);
		Merge_Sort(array, sortArray, mid + 1, right);
		Merge(array, sortArray, left, mid + 1, right);
	}
}

template<typename T>
void Merge_Sort(T array[], int arrayLength)
{
	T* tempArray = new T[arrayLength];
	if (tempArray)
	{
		Merge_Sort(array, tempArray, 0, arrayLength - 1);
		delete[] tempArray;
	}
	else throw;
}

///非递归归并排序算法 
///length为当前子序列长度,每次将相邻两个length长度的子序列归并
///
template<typename T>
void Merge_Pass(T* array, T* tempArray, int arrayLength, int length)
{
	int i = 0;
	for (; i <= arrayLength - 2 * length; i += 2 * length)
	{
		Merge(array, tempArray, i, i + length, i + 2 * length - 1);
	}
	if (i + length < arrayLength)//归并最后两个子序列
		MergeS(array, tempArray, i, i + length, arrayLength - 1);
	else//只剩下一个子列
		for (int j = i; j < arrayLength; j++)
		{
			tempArray[j] = array[j];
		}
}

///
///稳定
///
template<typename T>
void MergeSort(T array[], int arrayLength)
{
	int length = 1;//初始化子序列长度
	T* tempArray = new T[arrayLength];
	if (tempArray)
	{
		while (length < arrayLength)
		{
			Merge_Pass(array, tempArray, arrayLength, length);
			length *= 2;
			Merge_Pass(tempArray, array, arrayLength, length);
			length *= 2;
		}
		delete[] tempArray;
	}
	else throw;
}
#pragma endregion

#pragma region table sort

///
///表排序：不改变数据的内存地址，通过改变指向数据的位置来进行排序
///
template<typename T>
void Table_Sort(T array[], int arrayLength,int* table)
{
	if (!table)
		table = new int[arrayLength];
	if (!table) return;
	for (int i = 0; i < arrayLength; i++)
		table[i] = i;
	int j, insertElementIndex;
	for (int i = 1; i < arrayLength; i++)
	{
		insertElementIndex = table[i];
		j = i;
		for (; j > 0 && array[table[j - 1]] > array[insertElementIndex]; j--)
		{
			table[j] = table[j - 1];
		}
		table[j] = insertElementIndex;
	}	
}
#pragma endregion

#pragma region physical sort
///
///物理排序是基于表排序的基础上改变内存地址,最好的情况：初始有序
///最坏的情况：有|_N/2_|个环，每个环包含2个元素，需要|_3N/2_|次元素移动 T=O(mN),m是每个元素复制的时间
///
template<typename T>
void Physical_Sort(T array[], int arrayLength, int* table)
{
	Table_Sort(array, arrayLength, table);
	for (int i = 0; i < arrayLength; i++)
	{
		T temp = array[i];
		int curIndex = i;
		while (table[curIndex] != curIndex)//判断一个环是否结束
		{
			int nextIndex = table[curIndex];
			if (table[nextIndex] == nextIndex)
				array[curIndex] = temp;
			else 
				array[curIndex] = array[table[curIndex]];
			table[curIndex] = curIndex;
			curIndex = nextIndex;
		}
	}
}
#pragma endregion

#pragma region Bucket Sort
///
///桶排序：假如数组的元素是某个有限元素的集合,稳定
///T(N,M)=O(M+N）,N个数据M个桶,当N=M时,每个桶只有一个数据,桶排序效率可以达到O(N)
///可以通过哈希函数映射到每个桶内
///
void Bucket_Sort(int array[], int arrayLength)
{
	int bucketNum = 1000;//INT_MAX - INT_MIN;要足够大，要容纳所有可能的值
	Node<int>* bucketArray = new Node<int>[bucketNum];
	for (int i = 0; i < arrayLength; i++)
	{
		Node<int>* node=new Node<int>(array[i]);
		node->next = bucketArray[array[i]].next;
		bucketArray[array[i]].next = node;
	}
	int index = 0;
	for (int i = 0; i < bucketNum; i++)
	{
		Node<int>* head = bucketArray[i].next;
		if (!head) continue;
		while (head)
		{
			array[index++] = head->data;
			head = head->next;
		}
	}
	delete[] bucketArray;
	bucketArray = nullptr;
}
#pragma endregion

#pragma region Radix Sort
///
///基数排序：采用次位优先的思想,稳定
///

//数组中元素的最大位数
int MaxBit(int array[], int arrayLength)
{
	int maxData = abs(array[0]);
	for (int i = 1; i < arrayLength; i++)
	{
		if (abs(array[i]) > maxData)
			maxData = abs(array[i]);
	}
	int bitNum = 0;
	while (maxData) {
		bitNum++;
		maxData /= 10;
	}
	return bitNum;
}
void Radix_Sort(int array[], int arrayLength)
{
	queue<int>* bucket = new queue<int>[10];
	if (!bucket) return;
	int bitPower = 1;//每位的权重
	int maxBit = MaxBit(array, arrayLength);
	int indexInArray = 0;
	for (int i = 0; i < maxBit; i++)
	{
		for (int j = 0; j < arrayLength; j++)
		{
			//数组的每个数据的在各个权重位置上的数值
			int digitalOfArrayElement = (array[j] / bitPower) % 10;
			bucket[digitalOfArrayElement].push(array[j]);
		}
		indexInArray = 0;
		for (int j = 0; j < 10; j++)
		{
			while (!bucket[j].isEmpty())
			{
				array[indexInArray++] = bucket[j].front();
				bucket[j].pop();
			}
		}
		bitPower *= 10;
	}
	delete[] bucket;
	bucket = nullptr;
}

#pragma endregion

#endif // !_SORT_H
