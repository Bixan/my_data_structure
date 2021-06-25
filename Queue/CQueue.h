#pragma once
#include"MyList_iterator.h"

template<typename T>
class CQueue
{
public:
	// Լ���������ͷ�ڵ�Ϊ����ͷ�������β���Ϊ����β

	// ���
	void push(const T& val);

	// ����
	void pop();

	// ���ʶ���Ԫ��
	T front();

	// ��ȡ�����е�Ԫ�ظ���
	int QueueElementSize();

	// �ж϶����Ƿ�Ϊ��
	bool empty();

	// ��ն����е�����
	void clear();
private:
	CList<T> m_list;
};

template<typename T>
inline void CQueue<T>::push(const T& val)
{
	m_list.AddTail(val); // ���ʱ�Ӷ�β����
}

template<typename T>
inline void CQueue<T>::pop()
{
	m_list.RemoveHead(); // ����ʱ���Ӷ�ͷ����
}

template<typename T>
inline T CQueue<T>::front()
{
	return *m_list.begin();	// ���ʶ��� ��ͷ����ֵ
}

template<typename T>
inline int CQueue<T>::QueueElementSize()
{
	return m_list.NodeSize();
}

template<typename T>
inline bool CQueue<T>::empty()
{
	return m_list.IsNull();
}

template<typename T>
inline void CQueue<T>::clear()
{
	m_list.Clear();
}