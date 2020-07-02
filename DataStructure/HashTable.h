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
///例如：字符串“abcd”，长度为4，它的哈希函数为
///h(key)=a的ASCII码值*32^3+b的ASCII码值*32^2+c的ASCII码值^32+d的ASCII码值
///h(key)=(∑key[n-i-1]*32^i)mod tablesize,求和i从0到n-1
///
Index Hash(const char* key, int tableSize)
{
	unsigned int hashFuncValue = 0;//哈希函数值。初始化为0
	while (*key != '\0')
		hashFuncValue = (hashFuncValue << 5) + *key++;
	return hashFuncValue % tableSize;
}

//除留取余法哈希函数
Index Hash(int key, int tableSize)
{
	return key % tableSize;
}

enum ElementInfo
{
	Empty=0,
	Deleted,
	Legitimate,//占用
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

///返回大于num的最小素数
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
///采用的是平方探测法的查找,如果哈希表的长度是某个4K+3（k是正整数）形式的素数，
///平方探测法就可以探测到整个哈希表
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
	int conflictCount = 0;//冲突次数
	while (mCells[currentPos].mInfo != ElementInfo.Empty 
		&& mCells[currentPos].mData != key)
	{
		if (++conflictCount % 2)//判断冲突次数的奇偶性,偶数向前找，奇数向后找
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
	if (mCells[pos].mInfo != ElementInfo.Legitimate)//检查key是否已存在
	{
		mCells[pos].mInfo = Legitimate;
		mCells[pos].mData = key;
	}
	else {
		//已存在
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
///分离链接法:将相应位置上有冲突的所有关键字存储在同一个单链表中
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
		//已存在
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

