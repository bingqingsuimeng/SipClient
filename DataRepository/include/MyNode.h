/**
*
*	description:	Node of fifo
*
*	date:			20170517
*	modified:		20170529	use Templet
*	author:			dyang
*
*/

#pragma once

#ifndef __MYNODE_H__
#define __MYNODE_H__

#include <iostream>
using namespace std;


template <class T>
class CMyNode
{
public:
	CMyNode();
	~CMyNode();

	void release();

	void setData(T data);
	T getData();

	//void showData();
private:
	T m_data;

public:
	CMyNode<T>* next;
};


template <class T>
CMyNode<T>::CMyNode()
{
}


template <class T>
CMyNode<T>::~CMyNode()
{
}


template <class T>
void CMyNode<T>::release()
{
	if (NULL != this)
	{
		delete this;
	}
}


template <class T>
void CMyNode<T>::setData(T data)
{
	m_data = data;
}


template <class T>
T CMyNode<T>::getData()
{
	return m_data;
}

#endif