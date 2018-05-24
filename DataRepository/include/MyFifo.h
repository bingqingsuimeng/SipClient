/**
*
*	description:	my fifo data struct 
*
*	date:			20170517
*	modified:		20170529	use Templet
*	author:			dyang
*
*/

#pragma once
#ifndef __MYFIFO_H__
#define __MYFIFO_H__
#include "MyNode.h"

using namespace std;

template <class T>
class CMyFifo
{
public:
	CMyFifo(int capacity = 100);
	~CMyFifo();

	CMyNode<T>* pop();
	bool push(CMyNode<T>* pnode);
	bool push(T data);
	bool forcePush(CMyNode<T>* pnode);
	bool forcePush(T data);

	void clean();
	int size();// return m_size
	int capacity(); 
	void setCapacity(int capacity);

	bool IsEmpty();
	bool IsFull();

private:
	int m_size;//current size
	int m_capacity; // max size

	CMyNode<T>* m_phead;
	CMyNode<T>* m_ptail;

	bool m_isEmpty;
};



template <class T>
CMyFifo<T>::CMyFifo(int capacity)
{
	m_size = 0;
	m_capacity = capacity;

	m_ptail = m_phead = NULL;

	m_isEmpty = true;
}


template <class T>
CMyFifo<T>::~CMyFifo()
{
	clean();
}


template <class T>
CMyNode<T>* CMyFifo<T>::pop()
{
	CMyNode<T>* pNode = NULL;
	if (!IsEmpty())
	{
		pNode = m_phead;
		m_phead = m_phead->next;
		m_size--;
	}

	if (IsEmpty())
	{
		m_phead = m_ptail = NULL;
	}
	return pNode;
}


template <class T>
bool CMyFifo<T>::push(CMyNode<T>* pnode)
{
	if ((NULL != pnode))
	{
		if (!IsFull())
		{
			if (NULL != m_ptail)
			{
				m_ptail->next = pnode;
				m_ptail = pnode;

				m_size++;
				return true;
			}
			else //first insert data
			{
				m_phead = m_ptail = pnode;
				m_size++;
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


template <class T>
bool CMyFifo<T>::push(T data)
{
	if (!IsFull())
	{
		CMyNode<T>* pNode = new CMyNode<T>();
		if (NULL != pNode)
		{
			pNode->setData(data);
			if (NULL != m_ptail)
			{
				m_ptail->next = pNode;
				m_ptail = pNode;

				m_size++;
				return true;
			}
			else //first insert data
			{
				m_phead = m_ptail = pNode;
				m_size++;
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


template <class T>
bool CMyFifo<T>::forcePush(CMyNode<T>* pnode)
{
	CMyNode<T>* pNode = NULL;
	if (!IsFull())
	{
		return push(pnode);
	}
	else //full
	{
		pNode = pop();
		if (NULL != pNode)
		{
			delete pNode;
			pNode = NULL;
		}
		return push(pnode);
	}
}


template <class T>
bool CMyFifo<T>::forcePush(T data)
{
	CMyNode<T>* pNode = NULL;
	if (!IsFull())
	{
		return push(data);
	}
	else //full
	{
		pNode = pop();
		if (NULL != pNode)
		{
			delete pNode;
			pNode = NULL;
		}
		return push(data);
	}
}


template <class T>
void CMyFifo<T>::clean()
{
	CMyNode<T>* pNode = NULL;
	while (!IsEmpty())
	{
		pNode = pop();
		if (NULL != pNode)
		{
			delete pNode;
			pNode = NULL;
		}
	}
	m_phead = m_ptail = NULL;
}


template <class T>
int CMyFifo<T>::size()
{
	return m_size;
}


template <class T>
int CMyFifo<T>::capacity()
{
	return m_capacity;
}


template <class T>
bool CMyFifo<T>::IsEmpty()
{
	if (0 == m_size)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template <class T>
bool CMyFifo<T>::IsFull()
{
	if (m_capacity > 0 && m_size >= m_capacity)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template <class T>
void CMyFifo<T>::setCapacity(int capacity)
{
	m_capacity = capacity;
}

#endif // !__MYFIFO_H__

