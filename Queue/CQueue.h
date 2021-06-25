#pragma once
#include"MyList_iterator.h"

template<typename T>
class CQueue
{
public:
	// 约定：链表的头节点为队列头，链表的尾结点为队列尾

	// 入队
	void push(const T& val);

	// 出队
	void pop();

	// 访问队首元素
	T front();

	// 获取队列中的元素个数
	int QueueElementSize();

	// 判断队列是否为空
	bool empty();

	// 清空队列中的数据
	void clear();
private:
	CList<T> m_list;
};

template<typename T>
inline void CQueue<T>::push(const T& val)
{
	m_list.AddTail(val); // 入队时从队尾进入
}

template<typename T>
inline void CQueue<T>::pop()
{
	m_list.RemoveHead(); // 出队时，从队头出队
}

template<typename T>
inline T CQueue<T>::front()
{
	return *m_list.begin();	// 访问队列 对头的数值
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