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
///ð��������������˳��O(N),��������O(N^2)
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
///��β��������������˳��O(N),��������O(N^2)
///
template<typename T>
void CockTail_Sort(T array[], int arrayLength)
{
	int flag = 0;
	for (int i = 0; i <= arrayLength / 2; i++)
	{
		flag = 0;
		//���������ҳ����ֵ
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
		//���������ҳ���Сֵ
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
///����������������˳��O(N),��������O(N^2),С��ģ����Ч���ȽϺ�
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
			array[j] = array[j - 1];//�Ƴ���λ
		}
		array[j] = insertElement;//�����Ԫ��
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
///ϣ��������������,����O(N^2)
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
///ѡ��������������,����O(N^2)
///
template<typename T>
void Selection_Sort(T array[], int arrayLength)
{
	int minPosition = 0;
	for (int i = 0; i < arrayLength - 1; i++)
	{
		//��array[i]��array[arrayLength-1]���ҵ���С��Ԫ�أ�������λ�ø�minPosition
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
			//������ֵ��ѭ����ʼֵ��ͬ������֮ǰ��������Сֵʱ��array[i]��array[minPosition]������
			//������ʵ�����ֵ�±�ΪminPosition
			if (maxPosition == i)
				maxPosition = minPosition;
			Swap(array[arrayLength - i - 1], array[maxPosition]);
		}
	}
}
#pragma endregion

#pragma region Heap Sort
///
///�����򣬴���N����ͬԪ�ص�������е�ƽ��������2NlogN-O(NloglogN)
///��Ȼ������������ƽ��ʱ�临�Ӷȣ���ʵ��Ч��������sedgewick�������е�ϣ������
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
	for (int i = arrayLength / 2; i >= 0; i--)	//�ȴ����һ���ж��ӵĽڵ㿪ʼ����
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
///��������:������O(NlogN),�O(N^2),��ѡȡ�Ļ�׼���йأ������Ż���׼����Խ���������
///����С��ģ�����ݣ�����N����100�����ܻ������������죬�ʶԴ������Ż�
///
#define QuickSortAarrayLenCutOff 100
template<typename T>
void Quick_Sort(T array[], int low, int high)
{
	//if (low < high)
	while (low < high)//β�ݹ�ʱ
	{
		int left = low, right = high;
		if (high - low + 1 < QuickSortAarrayLenCutOff)
		{
			Insertion_Sort(array, high - low + 1);
			break;
		}
		//int selectedPosition = round(1.0 * rand() / RAND_MAX) * (right - left) + left);
		//Swap(array[left], array[selectedPosition]);
		//�Ż���׼��
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
		//β�ݹ�
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
	int leftEndi = rightStarti - 1;//��������Ϊ���Ұ���һ��������յ�λ��
	int sortArrayStarti = leftStarti;
	int firstArrayi = leftStarti, secondArrayi = rightStarti;
	int numCount = rightEndi - leftStarti + 1;
	while (firstArrayi <= leftEndi && secondArrayi <= rightEndi)
	{
		if (array[firstArrayi] <= array[secondArrayi])
			sortArray[sortArrayStarti++] = array[firstArrayi++];
		else sortArray[sortArrayStarti++] = array[secondArrayi++];
	}
	while (firstArrayi <= leftEndi)//�������ʣ�µ�
		sortArray[sortArrayStarti++] = array[firstArrayi++];
	while (secondArrayi <= rightEndi)//�����ұ�ʣ�µ�
		sortArray[sortArrayStarti++] = array[secondArrayi++];
	for (int i = 0; i < numCount; ++i, rightEndi--)
		array[rightEndi] = sortArray[rightEndi];
}

///
///merge:leftstartiΪ�����ʼλ�� rightstartiΪ�ұ���ʼλ�� rightendiΪ�ұ��յ�λ��
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
///ʱ�临�Ӷȵ��ƹ�ϵ��T(N)=T(N/2)+T(N/2)+O(N)=>T(N)=O(NlogN)���ȶ�
///ȱ�㣺��Ҫ����Ŀռ�
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

///�ǵݹ�鲢�����㷨 
///lengthΪ��ǰ�����г���,ÿ�ν���������length���ȵ������й鲢
///
template<typename T>
void Merge_Pass(T* array, T* tempArray, int arrayLength, int length)
{
	int i = 0;
	for (; i <= arrayLength - 2 * length; i += 2 * length)
	{
		Merge(array, tempArray, i, i + length, i + 2 * length - 1);
	}
	if (i + length < arrayLength)//�鲢�������������
		MergeS(array, tempArray, i, i + length, arrayLength - 1);
	else//ֻʣ��һ������
		for (int j = i; j < arrayLength; j++)
		{
			tempArray[j] = array[j];
		}
}

///
///�ȶ�
///
template<typename T>
void MergeSort(T array[], int arrayLength)
{
	int length = 1;//��ʼ�������г���
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
///�����򣺲��ı����ݵ��ڴ��ַ��ͨ���ı�ָ�����ݵ�λ������������
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
///���������ǻ��ڱ�����Ļ����ϸı��ڴ��ַ,��õ��������ʼ����
///����������|_N/2_|������ÿ��������2��Ԫ�أ���Ҫ|_3N/2_|��Ԫ���ƶ� T=O(mN),m��ÿ��Ԫ�ظ��Ƶ�ʱ��
///
template<typename T>
void Physical_Sort(T array[], int arrayLength, int* table)
{
	Table_Sort(array, arrayLength, table);
	for (int i = 0; i < arrayLength; i++)
	{
		T temp = array[i];
		int curIndex = i;
		while (table[curIndex] != curIndex)//�ж�һ�����Ƿ����
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
///Ͱ���򣺼��������Ԫ����ĳ������Ԫ�صļ���,�ȶ�
///T(N,M)=O(M+N��,N������M��Ͱ,��N=Mʱ,ÿ��Ͱֻ��һ������,Ͱ����Ч�ʿ��ԴﵽO(N)
///����ͨ����ϣ����ӳ�䵽ÿ��Ͱ��
///
void Bucket_Sort(int array[], int arrayLength)
{
	int bucketNum = 1000;//INT_MAX - INT_MIN;Ҫ�㹻��Ҫ�������п��ܵ�ֵ
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
///�������򣺲��ô�λ���ȵ�˼��,�ȶ�
///

//������Ԫ�ص����λ��
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
	int bitPower = 1;//ÿλ��Ȩ��
	int maxBit = MaxBit(array, arrayLength);
	int indexInArray = 0;
	for (int i = 0; i < maxBit; i++)
	{
		for (int j = 0; j < arrayLength; j++)
		{
			//�����ÿ�����ݵ��ڸ���Ȩ��λ���ϵ���ֵ
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
