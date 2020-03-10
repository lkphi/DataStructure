#pragma once
#ifndef _SET_H
#define _SET_H

template<typename T>
class SetType
{
	T mData;
	int mParent;//���ڵ���±�,mParent=-X��Ϊ���ڵ�,XΪ�ü���Ԫ�ظ���
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
	for (index = 0; index < mSize && mSetArray[index].mData != data; index++) {}//�ҵ���Ԫ��
	if (index >= mSize) return -1;//û���ҵ�,�Ż�-1;
	for (; mSetArray[index].mParent >= 0; index = mSetArray[index].mParent) {}
	return index;
}

///�ҵ�data��data2����Ԫ�����ڼ������ĸ��ڵ�
///������Ǹ���ͬ����С���ϸ��ڵ�ĸ��ڵ�ָ�����ó���һ�����ڵ�������±꣬
///�����ļ��ϲ���С���лᷢ����Խ��Խ��,�����Ӳ����Ѷ�
template<typename T>
inline void Set<T>::Union(const T& data1, const T& data2)
{
	int root1 = Find(data1);
	int root2 = Find(data2);
	if (root1 == root2 || root1 == -1 || root2 == -1) return;
	//ע�⼯�ϵ�Ԫ�ظ����Ǹ������ȴ�Сʱ��ʱ���������෴
	//���ȹ鲢
	if (mSetArray[root2].mParent > mSetArray[root1].mParent)//����ͬ,��������ͬ˵������ͬһ������
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
///���޼��ϵ�����������������ȡֵ��һ����Χ�ڣ�������������±���Ϊdata���ݣ�
///��Ҫע�ⷶΧ���ܳ���int���͵���ֵ��Χ
template<>
class SetType<int>
{
public:
	int mParent;//���ڵ���±�,mParent=-X��Ϊ���ڵ�,XΪ�ü���Ԫ�ظ���
	SetType() :mParent(SETRANGEMAX + 1) {};
};
template<>
class Set<int>
{
public:
	Set(int array[],int arrayLength);
	int Find(const int& data);
	int Find(const int& data)const;
	int FindUsePathCompression(const int& data);//����·��ѹ��
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
		//·��ѹ���ķ���
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
	if (mSetArray[root2].mParent > mSetArray[root1].mParent)//����ͬ,��������ͬ˵������ͬһ������
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