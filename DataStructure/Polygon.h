#pragma once
#ifndef _POLYGON_H
#define _POLYGON_H
#include <ostream>
#include <cmath>

template<class T>
class PolyNode
{
public:
	T coef;//系数
	int expon;//指数
	PolyNode* next;
	PolyNode() :expon(0), next(nullptr) {}
	PolyNode(T coef, int expon) :coef(coef), expon(expon), next(nullptr) {}
};

template<class T>
class Polygon
{
public:
template<class U>
friend std::ostream& operator <<(std::ostream& os, const Polygon<U>& polygon);
Polygon<T> operator +(const Polygon<T>& polygon);
Polygon<T> operator -(const Polygon<T>& polygon);
Polygon<T> operator *(const Polygon<T>& polygon);
const Polygon<T> operator -()const;
Polygon<T>& operator +=(const Polygon<T>& polygon);
Polygon<T>& operator -=(const Polygon<T>& polygon);
Polygon<T>& operator *=(const Polygon<T>& polygon);
Polygon<T>& operator =(const Polygon<T>& polygon);
double operator()(float n);
Polygon();
Polygon(T coefArray[], int coefArrayLength, int exponArray[], int exponArrayLength);
Polygon(const Polygon<T>& polygon);
~Polygon();
private:
	PolyNode<T>* mHead;
	void ClearData(PolyNode<T>* head);
};

template<class U>
inline std::ostream& operator<<(std::ostream& os, const Polygon<U>& polygon)
{
	if (!polygon.mHead) return os;
	PolyNode<U>* head = polygon.mHead->next;
	while (head->next)
	{
		os << "(" << head->coef << ")x^" << head->expon << "+";
		head = head->next;
	}
	if (head->expon == 0)
		os << head->coef;
	else if (head->expon == 1)
	{
		os << "(" << head->coef << ")x";
	}
	else os << "(" << head->coef << ")x^" << head->expon;
	return os;
}

template<class T>
inline Polygon<T> Polygon<T>::operator+(const Polygon<T>& polygon)
{
	Polygon<T>* tmp =new Polygon<T>(*this);
	return *tmp += polygon;
}

template<class T>
inline Polygon<T> Polygon<T>::operator-(const Polygon<T>& polygon)
{
	return operator+(-polygon);
}

template<class T>
inline Polygon<T> Polygon<T>::operator*(const Polygon<T>& polygon)
{
	Polygon<T>* tmp = new Polygon<T>(*this);
	return *tmp *= polygon;
}

template<class T>
inline const Polygon<T> Polygon<T>::operator-()const
{
	if (!this->mHead) return *this;
	Polygon<T>* newPolygon = new Polygon<T>(*this);
	PolyNode<T>* head = newPolygon->mHead->next;
	while (head)
	{
		head->coef = -head->coef;
		head = head->next;
	}
	return *newPolygon;
}

template<class T>
inline Polygon<T>& Polygon<T>::operator+=(const Polygon<T>& polygon)
{
#pragma region solution 1
	//PolyNode<T>* thisPolygonData = this->mHead->next;
	//this->mHead->next = nullptr;
	//PolyNode<T>* head1 = polygon.mHead->next;
	//PolyNode<T>* head2 = thisPolygonData;
	//PolyNode<T>* curNode = this->mHead;
	//while (head1 && head2)
	//{
	//	PolyNode<T>* newPolygonNode = new PolyNode<T>();
	//	if (head1->expon == head2->expon)
	//	{
	//		newPolygonNode->expon = head1->expon;
	//		newPolygonNode->coef = head1->coef + head2->coef;
	//		if (!newPolygonNode->coef)
	//		{
	//			delete newPolygonNode;
	//			newPolygonNode = nullptr;
	//			continue;
	//		}
	//		head1 = head1->next;
	//		head2 = head2->next;
	//	}
	//	else if (head1->expon > head2->expon)
	//	{
	//		newPolygonNode->expon = head1->expon;
	//		newPolygonNode->coef = head1->coef;
	//		head1 = head1->next;
	//	}
	//	else {
	//		newPolygonNode->expon = head2->expon;
	//		newPolygonNode->coef = head2->coef;
	//		head2 = head2->next;
	//	}
	//	curNode->next = newPolygonNode;
	//	curNode = newPolygonNode;
	//}
	//while (head1)
	//{
	//	PolyNode<T>* newPolygonNode = new PolyNode<T>(head1->coef, head1->expon);
	//	curNode->next = newPolygonNode;
	//	curNode = newPolygonNode;
	//	head1 = head1->next;
	//}
	//while (head2)
	//{
	//	PolyNode<T>* newPolygonNode = new PolyNode<T>(head2->coef, head2->expon);
	//	curNode->next = newPolygonNode;
	//	curNode = newPolygonNode;
	//	head2 = head2->next;
	//}
	//ClearData(thisPolygonData);
	//return *this;
#pragma endregion 

	PolyNode<T>* head1 = polygon.mHead->next;
	PolyNode<T>* head2 = this->mHead;
	while (head1)
	{
		while (head2->next && head2->next->expon > head1->expon)
			head2 = head2->next;
		if (head2->next && head2->next->expon == head1->expon)
		{
			head2->next->coef += head1->coef;
			if (!head2->next->coef)
			{
				PolyNode<T>* deleteNode = head2->next;
				head2->next = deleteNode->next;
				delete deleteNode;
				deleteNode = nullptr;
			}
		}
		else {
			PolyNode<T>* newNode = new PolyNode<T>(head1->coef, head1->expon);
			newNode->next = head2->next;
			head2->next = newNode;
		}
		head1 = head1->next;
	}
	return *this;
}

template<class T>
inline Polygon<T>& Polygon<T>::operator-=(const Polygon<T>& polygon)
{
	return operator+=(-polygon);
}

template<class T>
inline Polygon<T>& Polygon<T>::operator*=(const Polygon<T>& polygon)
{
	if (!this->mHead->next || !polygon.mHead->next) throw;
	PolyNode<T>* thisPolygonData = this->mHead->next;
	this->mHead->next = nullptr;
	PolyNode<T>* head1 = thisPolygonData;
	PolyNode<T>* head2 = polygon.mHead->next;
	PolyNode<T>* head = this->mHead;
	while (head2)
	{
		T coef = head1->coef * head2->coef;
		int expon = head1->expon + head2->expon;
		PolyNode<T>* newPolyNode = new PolyNode<T>(coef, expon);
		head->next = newPolyNode;
		head = newPolyNode;
		head2 = head2->next;
	}
	head1 = head1->next;
	while (head1)
	{
		head2 = polygon.mHead->next;
		while (head2)
		{
			T coef = head1->coef * head2->coef;
			int expon = head1->expon + head2->expon;
			head = this->mHead;
			while (head->next && head->next->expon > expon)
			{
				head = head->next;
			}
			if (head->next && head->next->expon == expon)
			{
				head->next->coef += coef;
				if (!head->next->coef)//系数为0
				{
					PolyNode<T>* deleteNode = head->next;
					head->next = deleteNode->next;
					delete deleteNode;
					deleteNode = nullptr;
				}
			}
			else {
				PolyNode<T>* newPolyNode = new PolyNode<T>(coef, expon);
				newPolyNode->next = head->next;
				head->next = newPolyNode;
			}
			head2 = head2->next;
		}
		head1 = head1->next;
	}
	ClearData(thisPolygonData);
	return *this;
}

template<class T>
inline Polygon<T>& Polygon<T>::operator=(const Polygon<T>& polygon)
{
	if (mHead == polygon.mHead) return *this;
	if (!polygon.mHead) return *this;
	ClearData(mHead->next);
	PolyNode<T>* head = polygon.mHead->next;
	PolyNode<T>* curNode = this->mHead;
	while (head)
	{
		PolyNode<T>* newPolygonNode = new PolyNode<T>(head->coef, head->expon);
		curNode->next = newPolygonNode;
		curNode = newPolygonNode;
		head = head->next;
	}
	return *this;
}

template<class T>
inline double Polygon<T>::operator()(float n)
{
	if (!mHead) throw;
	double result = 0;
	PolyNode<T>* head = mHead->next;
	while (head)
	{
		result += (head->coef * pow(n, head->expon));
		head = head->next;
	}
	return result;
}

template<class T>
inline Polygon<T>::Polygon()
{
	mHead = new PolyNode<T>(); 
	if (!mHead) throw;
}

template<class T>
inline Polygon<T>::Polygon(T coefArray[], int coefArrayLength, int exponArray[], int exponArrayLength)
{
	if (coefArrayLength != exponArrayLength || coefArrayLength < 0 || exponArrayLength < 0)
		throw;
	mHead = new PolyNode<T>();
	mHead->next = new PolyNode<T>(coefArray[0], exponArray[0]);
	PolyNode<T>* head = mHead;
	for (int i = 1; i < coefArrayLength; i++)
	{
		head = mHead;
		while (head->next && head->next->expon > exponArray[i])
		{
			head = head->next;
		}
		if (head->next && head->next->expon == exponArray[i])
		{
			head->next->coef += coefArray[i];
			if (!head->next->coef)//系数为0
			{
				PolyNode<T>* deleteNode = head->next;
				head->next = deleteNode->next;
				delete deleteNode;
				deleteNode = nullptr;
			}
		}
		else {
			PolyNode<T>* newPolygonNode = new PolyNode<T>(coefArray[i], exponArray[i]);
			newPolygonNode->next = head->next;
			head->next = newPolygonNode;
		}
	}
}

template<class T>
inline Polygon<T>::Polygon(const Polygon<T>& polygon)
{
	if (!polygon.mHead) return;
	mHead = new PolyNode<T>();
	//PolyNode<T>* head = polygon.mHead->next;
	//PolyNode<T>* travelNode = this->mHead;
	//while (head)
	//{
	//	PolyNode<T>* newPolygonNode = new PolyNode<T>(head->coef, head->expon);
	//	travelNode->next = newPolygonNode;
	//	travelNode = newPolygonNode;
	//	head = head->next;
	//}
	*this = polygon;
}

template<class T>
inline Polygon<T>::~Polygon()
{
	if (!mHead) return;
	if (!mHead->next)
	{
		delete mHead;
		mHead = nullptr;
	}
	while (mHead)
	{
		PolyNode<T>* deleteNode = mHead;
		mHead = mHead->next;
		delete deleteNode;
		deleteNode = nullptr;
	}
	mHead = nullptr;
}

template<class T>
inline void Polygon<T>::ClearData(PolyNode<T>* head)
{
	while (head)
	{
		PolyNode<T>* deleteNode = head;
		head = head->next;
		delete deleteNode;
		deleteNode = nullptr;
	}
}

#endif // !_POLYGON_H