#pragma once
#ifndef _SET_H
#define _SET_H

template<typename T>
class SetType
{
	T mData;
	int mParent;//父节点的下标,mParent=-X就为根节点,X为该集合元素个数
};

template<typename T>
class Set
{
public:
	Set(T array[], int arrayLength);
	int Find(const T& data)const;
	void Union(const T& data1,const T& data2);
	~Set()
	{
		if (!mSetArray)
		{
			delete[] mSetArray; 
			mSetArray = nullptr; 
		}
		mSize = 0;
	}
private:
	SetType<T>* mSetArray;
	int mSize;
};

template<typename T>
inline Set<T>::Set(T array[], int arrayLength)
{
	try
	{
		mSetArray = new SetType[arrayLength];
		if (!mSetArray) throw FailedApplyForSpace();
		mSize = arrayLength;
		for (int i = 0; i < mSize; i++)
		{
			mSetArray[i].data = array[i];
			mSetArray[i].mParent = -1;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

}

template<typename T>
inline int Set<T>::Find(const T& data)const
{
	int index;
	for (index = 0; index < mSize && mSetArray[index].mData != data; index++) {}//找到该元素
	if (index >= mSize) return -1;//没有找到,放回-1;
	for (; mSetArray[index].mParent >= 0; index = mSetArray[index].mParent) {}
	return index;
}

///找到data和data2两个元素所在集合树的根节点
///如果它们根不同，则将小集合根节点的父节点指针设置成另一个根节点的数组下标，
///如果大的集合插入小的中会发生树越来越长,会增加查找难度
template<typename T>
inline void Set<T>::Union(const T& data1, const T& data2)
{
	int root1 = Find(data1);
	int root2 = Find(data2);
	if (root1 == root2 || root1 == -1 || root2 == -1) return;
	//注意集合的元素个数是负数，比大小时的时候与正数相反
	//按秩归并
	if (mSetArray[root2].mParent > mSetArray[root1].mParent)//不相同,做处理，相同说明就是同一个集合
	{
		int root2SetCount = mSetArray[root2].mParent;
		mSetArray[root2].mParent = root1;
		mSetArray[root1].mParent += root2SetCount;
	}
	else {
		int root1SetCount = mSetArray[root1].mParent;
		mSetArray[root1].mParent = root2;
		mSetArray[root2].mParent += root1SetCount;
	}
}

#define SETRANGEMAX 100
///有限集合的整数集合由于它的取值在一定范围内，可以以数组的下标作为data数据，
///但要注意范围不能超过int类型的数值范围
template<>
class SetType<int>
{
public:
	int mParent;//父节点的下标,mParent=-X就为根节点,X为该集合元素个数
	SetType() :mParent(SETRANGEMAX + 1) {};
};
template<>
class Set<int>
{
public:
	Set(int array[],int arrayLength);
	int Find(const int& data);
	int Find(const int& data)const;
	int FindUsePathCompression(const int& data);//采用路径压缩
	void Union(const int& data1, const int& data2);
	int SetCount();
	bool CheckConnection(const int& data1, const int& data2);
	~Set()
	{
		if (!mSetArray)
		{
			delete[] mSetArray;
			mSetArray = nullptr;
		}
		mSize = 0;
	}
private:
	SetType<int>* mSetArray;
	int mSize;
};

inline Set<int>::Set(int array[], int arrayLength)
{
	try
	{
		mSetArray = new SetType<int>[SETRANGEMAX];
		if (!mSetArray) throw FailedApplyForSpace();
		mSize = arrayLength;
		for (int i = 0; i < mSize; i++)
		{
			mSetArray[array[i]].mParent = -1;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

}

inline int Set<int>::Find(const int& data)
{
	if (data >= 0 && data <= SETRANGEMAX && mSetArray[data].mParent != SETRANGEMAX + 1)
	{
		//路径压缩的方法
		return FindUsePathCompression(data);
	}
	else return -1;
}

inline int Set<int>::Find(const int& data) const
{
	if (data >= 0 && data <= SETRANGEMAX && mSetArray[data].mParent != SETRANGEMAX + 1)
	{
		int index = data;
		for (; mSetArray[index].mParent >= 0; index = mSetArray[index].mParent) {}
		return index;
	}
	else return -1;
}

inline int Set<int>::FindUsePathCompression(const int& data)
{
	if (mSetArray[data].mParent < 0)
		return data;
	else
		return mSetArray[data].mParent = FindUsePathCompression(mSetArray[data].mParent);
}

inline void Set<int>::Union(const int& data1, const int& data2)
{
	int root1 = Find(data1);
	int root2 = Find(data2);
	if (root1 == root2 || root1 == -1 || root2 == -1) return;
	if (mSetArray[root2].mParent > mSetArray[root1].mParent)//不相同,做处理，相同说明就是同一个集合
	{
		int root2SetCount = mSetArray[root2].mParent;
		mSetArray[root2].mParent = root1;
		mSetArray[root1].mParent += root2SetCount;
	}
	else {
		int root1SetCount = mSetArray[root1].mParent;
		mSetArray[root1].mParent = root2;
		mSetArray[root2].mParent += root1SetCount;
	}
}

inline int Set<int>::SetCount()
{
	int count = 0;
	for (int i = 0; i < SETRANGEMAX; i++)
	{
		if (mSetArray[i].mParent < 0) count++;
	}
	return count;
}

inline bool Set<int>::CheckConnection(const int& data1, const int& data2)
{
	int root1 = Find(data1);
	int root2 = Find(data2);
	if (root1 == root2 && root1 != -1 && root2 != -1)
		return true;
	return false;
}

#endif // !_SET_H