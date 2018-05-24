/**
*
*	description:	use fifo data struct to storage msg, if the counter of msg larger than
*					the capacity of fifo, delete msg on front of fifo then insert the new 
*					msg.  
*
*	date:			20170517
*	author:			dyang
*	modified:		20170529,dyang.		use c++ template class to add usability
*
*/

#pragma once

#ifndef __DATAREPOSITORY_H__
#define __DATAREPOSITORY_H__

#include "MyFifo.h"

template <class T>
class CDataRepository
{
public:
	CDataRepository(int capacity = 100);
	~CDataRepository();

	bool putData(T data);
	T getData();

	void clean();
	bool setCapacity(int capacity);

	int getCount();
	int getCapacity();

private:
	CMyFifo<T>* m_pfifo;
};


template <class T>
CDataRepository<T>::CDataRepository(int capacity)
{
	m_pfifo = new CMyFifo<T>(capacity);
}


template <class T>
CDataRepository<T>::~CDataRepository()
{
}


template <class T>
bool CDataRepository<T>::putData(T data)
{
	if (NULL != m_pfifo)
	{
		return m_pfifo->forcePush(data);
	}
	else
	{
		return false;
	}
}


template <class T>
T CDataRepository<T>::getData()
{
	if (NULL != m_pfifo)
	{
		CMyNode<T>* pNode = m_pfifo->pop();
		if (NULL != pNode)
		{
			return pNode->getData();
		}
		else
		{
			return T();
		}
	}
	else
	{
		return T();
	}
}


template <class T>
void CDataRepository<T>::clean()
{
	if (NULL != m_pfifo)
	{
		m_pfifo->clean();
	}
}


template <class T>
bool CDataRepository<T>::setCapacity(int capacity)
{
	if (NULL != m_pfifo)
	{
		m_pfifo->setCapacity(capacity);
		return true;
	}
	else
	{
		return false;
	}
}


template <class T>
int CDataRepository<T>::getCount()
{
	if (NULL != m_pfifo)
	{
		return m_pfifo->size();
	}
	else
	{
		return 0;
	}
}


template <class T>
int CDataRepository<T>::getCapacity()
{
	if (NULL != m_pfifo)
	{
		return m_pfifo->capacity();
	}
	else
	{
		return 0;
	}
}


#endif // !__DATAREPOSITORY_H__
