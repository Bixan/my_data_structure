#pragma once
/*=======================================================
*		o(*￣▽￣*)o
*		Project Name：动态数组
*		FileName：CArray.h
*		Start Date：2020/06/05
*		Last UpDate：2020/06/08
========================================================*/
#include <cassert>
template<typename T>
class CArrary
{
	// 迭代器
	class iterator
	{
		friend class CArrary;
	public:
		// 重载 前置 ++ 运算符
		iterator& operator++()
		{
			assert(m_pElement != m_pTailElement);
			m_pElement++;
			return *this;
		}

		// 重载 后置 ++ 运算符
		iterator operator++(int)
		{
			assert(m_pElement != m_pTailElement);
			T* pTemp = m_pElement;
			m_pElement++;
			return iterator(pTemp, m_pHeadElement, m_pTailElement);
		}

		// 重载 前置 -- 运算符
		iterator& operator--()
		{
			assert(m_pElement != m_pHeadElement);
			m_pElement--;
			return *this;
		}

		// 重载 后置 -- 运算符
		iterator operator--(int)
		{
			assert(m_pElement != m_pHeadElement);
			T* pTemp = m_pElement;

			m_pElement--;
			return iterator(pTemp, m_pHeadElement, m_pTailElement);
		}

		// 重载 == 运算符
		bool operator==(const iterator& itr)
		{
			return m_pElement == itr.m_pElement;
		}

		// 重载 != 运算符
		bool operator!=(const iterator& itr)
		{
			return m_pElement != itr.m_pElement;
		}

		// 重载 *(取内容) 运算符
		T& operator*()
		{
			return *m_pElement;
		}

	private:
		// 私有构造
		iterator(T* pElement, 
			T* pHeadElement, 
			T* pTailElement) :
			m_pElement(pElement),
			m_pHeadElement(pHeadElement),
			m_pTailElement(pTailElement)
		{
		}
	private:
		T* m_pElement;
		T* m_pHeadElement;
		T* m_pTailElement;
	};
public:
	/*
	添加 rbegin() rend()
	正向遍历
	*/
	iterator begin()
	{
		return iterator(m_pBuff,
			m_pBuff - 1,
			m_pBuff + m_nElementSize);
	}
	iterator end()
	{
		return iterator(m_pBuff + m_nElementSize,
			m_pBuff - 1,
			m_pBuff + m_nElementSize);
	}
	/*
	添加 rbegin() rend()
	正向遍历
	*/
	iterator rbegin()
	{
		return iterator(m_pBuff + m_nElementSize - 1,
			m_pBuff + m_nElementSize - 1,
			m_pBuff - 1);
	}
	iterator rend()
	{
		return iterator(m_pBuff - 1,
			m_pBuff + m_nElementSize - 1,
			m_pBuff - 1);
	}
public:
	CArrary();	// 无参构造
	CArrary(const CArrary& ary); // 拷贝构造
	virtual ~CArrary();	// 虚析构

public:
	bool AddHead(T val); // 头部 增加数据
	bool AddTail(T val); // 尾部 增加数据
	bool Insert(int nIdx, T val); // 指定位置 增加数据

	bool RemoveHead(); // 头部 删除数据
	bool RemoveTail(); // 尾部 删除数据
	bool Remove(int nIdx); // 指定位置  删除数据

	bool SetVal(int nIdx, T val);
	T& operator[](int nIdx); // 此处会抛出异常

	CArrary& operator+=(const CArrary& ary); // 重载运算符 +=
	CArrary& operator=(const CArrary& ary); // 重载运算符 =

	int Find(T val); // 查询指定数据
	int ElementCount()const; // 获取数组元素的个数
	void Clear(); // 清空
private:
	T* m_pBuff; // 存放数组元素的缓冲区
	int m_nBuffSize; // 缓冲区的大小
	int m_nElementSize;	// 数组中元素的个数
};