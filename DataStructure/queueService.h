#pragma once
#ifndef _QUEUESERVICE_H
#define _QUEUESERVICE_H

template<class T>
class QueueService
{
	virtual bool isEmpty()const =0;
	virtual int size()const =0;
	virtual bool push(T data) =0;
	virtual bool pop() =0;
	virtual T front()const =0;//����ָ���Ԫ��
	virtual void print() =0;
};
#endif // !_QUEUESERVICE_H
