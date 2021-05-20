#pragma once
#include "MyList_iterator.h"

template<typename T>
class CStack
{
public:
	// 约定：链表的头部为栈底，链表的尾部为栈顶

	// 入栈
	void push(T val);

	// 出栈（之弹出栈顶数据，不访问）
	void pop();

	// 访问栈顶元素，取出数值
	T top();

	// 栈空间是否为空
	bool empty();

	// 栈内元素的个数
	int StackElementSize();

	// 清空栈
	void clear();

private:
	CList<T> m_list;
};

template<typename T>
inline void CStack<T>::push(T val)
{
	m_list.AddTail(val);	// 从链表的尾部存储数据
}

template<typename T>
inline void CStack<T>::pop()
{
	m_list.RemoveTail();	// 从链表的尾部弹出数据
}

template<typename T>
inline T CStack<T>::top()
{
	return *(--m_list.end());	// 访问栈顶元素，链表尾部哨兵的前一个结点
}

template<typename T>
inline bool CStack<T>::empty()
{
	return m_list.IsNull();		// 栈空间是否为空
}

template<typename T>
inline int CStack<T>::StackElementSize()
{
	return m_list.NodeSize();	// 栈空间元素的个数
}

template<typename T>
inline void CStack<T>::clear()
{
	m_list.Clear();	// 清空栈空间数据
}
