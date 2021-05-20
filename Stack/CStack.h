#pragma once
#include "MyList_iterator.h"

template<typename T>
class CStack
{
public:
	// Լ���������ͷ��Ϊջ�ף������β��Ϊջ��

	// ��ջ
	void push(T val);

	// ��ջ��֮����ջ�����ݣ������ʣ�
	void pop();

	// ����ջ��Ԫ�أ�ȡ����ֵ
	T top();

	// ջ�ռ��Ƿ�Ϊ��
	bool empty();

	// ջ��Ԫ�صĸ���
	int StackElementSize();

	// ���ջ
	void clear();

private:
	CList<T> m_list;
};

template<typename T>
inline void CStack<T>::push(T val)
{
	m_list.AddTail(val);	// �������β���洢����
}

template<typename T>
inline void CStack<T>::pop()
{
	m_list.RemoveTail();	// �������β����������
}

template<typename T>
inline T CStack<T>::top()
{
	return *(--m_list.end());	// ����ջ��Ԫ�أ�����β���ڱ���ǰһ�����
}

template<typename T>
inline bool CStack<T>::empty()
{
	return m_list.IsNull();		// ջ�ռ��Ƿ�Ϊ��
}

template<typename T>
inline int CStack<T>::StackElementSize()
{
	return m_list.NodeSize();	// ջ�ռ�Ԫ�صĸ���
}

template<typename T>
inline void CStack<T>::clear()
{
	m_list.Clear();	// ���ջ�ռ�����
}
