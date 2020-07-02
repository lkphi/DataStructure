#pragma once
#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <iostream>
#include <cstring>
#include "LinearList.h"

#pragma warning (disable:4996)

using Index=unsigned int;
#define minTableSize 3
#define MaxTableSize 1000
///
///���磺�ַ�����abcd��������Ϊ4�����Ĺ�ϣ����Ϊ
///h(key)=a��ASCII��ֵ*32^3+b��ASCII��ֵ*32^2+c��ASCII��ֵ^32+d��ASCII��ֵ
///h(key)=(��key[n-i-1]*32^i)mod tablesize,���i��0��n-1
///
Index Hash(const char* key, int tableSize)
{
	unsigned int hashFuncValue = 0;//��ϣ����ֵ����ʼ��Ϊ0
	while (*key != '\0')
		hashFuncValue = (hashFuncValue << 5) + *key++;
	return hashFuncValue % tableSize;
}

//����ȡ�෨��ϣ����
Index Hash(int key, int tableSize)
{
	return key % tableSize;
}

enum ElementInfo
{
	Empty=0,
	Deleted,
	Legitimate,//ռ��
};

template<typename T>
class Cell{
public:
	ElementInfo mInfo;
	T mData;
	Cell() :mInfo(ElementInfo.Empty) {}
	Cell(ElementInfo info) :mInfo(info) {}
	bool& operator==(const char* cstr)const
	{
		if (strcmp(mData, cstr) == 0)
			return true;
		else return false;
	}
};


int NextPrimer(int num);

template<typename T>
class HashTable {
private:
	int mTableSize;
	Cell<T>* mCells;
public:
	HashTable() {};
	HashTable(int tableSize);
	Index Find(const T& key);
	HashTable<T>& Insert(const T& key);
	~HashTable();
	
};
#endif // !_HASHTABLE_H

template<typename T>
inline HashTable<T>::HashTable(int tableSize)
{
	try
	{
		if (tableSize < minTableSize)
		{
			std::cout << "table size is too small" << std::endl;
			return;
		}
		mTableSize = NextPrimer(tableSize);
		mCells = new Cell[mTableSize];
		if (!mCells) throw FailedApplyForSpace();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

}

///���ش���num����С����
int NextPrimer(int num)
{
	int evenNum = num % 2 ? num + 2 : num + 1;
	int i = evenNum, j;
	for (; i < MaxTableSize; i += 2)
	{
		for (j = (int)sqrt(i); j >=2; j--)
		{
			if (!(i % j)) break;
		}
		if (j == 1) break;
	}
	return i;
}

///
///���õ���ƽ��̽�ⷨ�Ĳ���,�����ϣ��ĳ�����ĳ��4K+3��k������������ʽ��������
///ƽ��̽�ⷨ�Ϳ���̽�⵽������ϣ��
///
template<typename T>
inline Index HashTable<T>::Find(const T& key)
{
	Index currentPos = Hash(key,mTableSize);
	if (mCells[currentPos].mInfo == ElementInfo.Empty)
	{
		std::cout << "the key is not exist" << std::endl;
		return -1;
	}
	int conflictCount = 0;//��ͻ����
	while (mCells[currentPos].mInfo != ElementInfo.Empty 
		&& mCells[currentPos].mData != key)
	{
		if (++conflictCount % 2)//�жϳ�ͻ��������ż��,ż����ǰ�ң����������
		{
			currentPos = currentPos + (conflictCount + 1) / 2 * (conflictCount + 1) / 2;
			while (currentPos >= mTableSize)
				currentPos -= mTableSize;
		}
		else {
			currentPos = currentPos - (conflictCount) / 2 * (conflictCount) / 2;
			while (currentPos < 0)
				currentPos += mTableSize;
		}
	}
	return currentPos;
}

template<typename T>
inline HashTable<T>& HashTable<T>::Insert(const T& key)
{
	Index pos = Find(key);
	if (pos == -1)
	{
		pos = Hash(key);
	}
	if (mCells[pos].mInfo != ElementInfo.Legitimate)//���key�Ƿ��Ѵ���
	{
		mCells[pos].mInfo = Legitimate;
		mCells[pos].mData = key;
	}
	else {
		//�Ѵ���
		std::cout << "the key is already exist" << std::endl;
	}
	return *this;
}

template<typename T>
inline HashTable<T>::~HashTable()
{
	if (mCells)
	{
		delete[] mCells;
		mCells = nullptr;
	}
}


///
///�������ӷ�:����Ӧλ�����г�ͻ�����йؼ��ִ洢��ͬһ����������
///
template<typename T>
class tblNode
{
public:
	int count;
	tblNode* next;
	T data;
	tblNode() :count(0),next(nullptr) {};
};

class hashTable {
private:
	int mTableSize;
	tblNode<char*>* mList;
public:
	//hashTable() {}
	hashTable(int tableSize);
	tblNode<char*>* Find(const char* key);
	hashTable& Insert(const char* key);
	List<char*> MaxCountData();
	~hashTable();
};

inline hashTable::hashTable(int tableSize)
{
	try
	{
		if (tableSize < minTableSize)
		{
			std::cout << "table size is too small" << std::endl;
			return;
		}
		mTableSize = NextPrimer(tableSize);
		mList = new tblNode<char*>[mTableSize];
		if (!mList) throw FailedApplyForSpace();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

inline tblNode<char*>* hashTable::Find(const char* key)
{
	Index idx= Hash(atoi(key), mTableSize);
	tblNode<char*>* head = mList[idx].next;
	while (head && strcmp(head->data, key))
	{
		head = head->next;
	}
	return head;
}

inline hashTable& hashTable::Insert(const char* key)
{
	tblNode<char*>* pos=Find(key);
	Index idx;
	if (!pos)
	{
		tblNode<char*>* newNode = new tblNode<char*>();
		newNode->data = new char[strlen(key)];
		strcpy(newNode->data, key);
		idx = Hash(atoi(key), mTableSize);
		newNode->next = mList[idx].next;
		mList[idx].next = newNode;
		return *this;
	}
	else {
		//�Ѵ���
		pos->count++;
		//std::cout << "the key is already exist" << std::endl;
		return *this;
	}

}

inline List<char*> hashTable::MaxCountData()
{
	int maxCount = 0;
	List<char*> maxCountData;
	tblNode<char*>* head = nullptr;
	char* mcdata = nullptr;
	for (int i = 0; i < mTableSize; i++) 
	{
		 head= mList[i].next;
		 while (head)
		 {
			 if (head->count > maxCount)
			 {
				 mcdata = head->data;
				 maxCountData.Release();
				 maxCountData.PushBack(mcdata);
				 maxCount = head->count;
			 }
			 else if (head->count == maxCount) {
				 mcdata = head->data;
				 maxCountData.PushBack(mcdata);
			 }
			 head = head->next;
		 }
	}
	return maxCountData;
}

inline hashTable::~hashTable()
{
	if (mList)
	{
		delete[] mList;
		mList = nullptr;
	}
}

