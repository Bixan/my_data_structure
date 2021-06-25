#pragma once
/*=======================================================
*		o(*￣▽￣*)o
*		Project Name：动态数组
*		FileName：CArray.h
*		Start Date：2020/06/05
*		Last UpDate：2020/06/08
========================================================*/
#include <memory.h>
#include <stdexcept>
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
		iterator(T* pElement, T* pHeadElement, T* pTailElement) :
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
	反向遍历
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
	CArrary(); // 无参构造
	CArrary(const CArrary& ary); // 拷贝构造
	virtual ~CArrary(); //虚析构

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
	CArrary& operator=(const CArrary& ary); // 重载运算符 +=

	int Find(T val); // 查询指定数据
	int ElementCount()const; // 获取数组元素的个数
	void Clear(); // 清空
private:
	T* m_pBuff; // 存放数组元素的缓冲区
	int m_nBuffSize; // 缓冲区的大小
	int m_nElementSize; // 数组中元素的个数
};

/*=======================================================
*   函数作用：无参构造，初始化数据
*   参数：无
*   返回值：无
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
CArrary<T>::CArrary()
{
	m_pBuff = nullptr;
	m_nElementSize = 0;
	m_nBuffSize = 0;
}


/*=======================================================
*   函数作用：拷贝构造
*   参数：const CArrary& ary -- 已初始化类对象
*   返回值：无
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
CArrary<T>::CArrary(const CArrary& ary)
{
	*this = ary; // 运算符 = 两端为对象，会调用重载运算符 =
}


/*=======================================================
*   函数作用：析构，类对象声明周结束，自动调用该函数进行数据释放
*   参数：无
*   返回值：无
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
CArrary<T>::~CArrary()
{
	Clear();
}


/*=======================================================
*   函数作用：调用 Insert() 方法在动态数据头部添加数据
*   参数：val -- 添加的数据
*   返回值：调用Insert()方法 -- 添加成功返回 true，添加失败返回false
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::AddHead(T val)
{
	return Insert(0, val);
}


/*=======================================================
*   函数作用：调用 Insert() 方法在动态数据尾部添加数据
*   参数：val -- 添加的数据
*   返回值：调用Insert()方法 -- 添加成功返回 true，添加失败返回false
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::AddTail(T val)
{
	return Insert(m_nElementSize, val);
}


/*=======================================================
*   函数作用：在动态数组内的指定位置添加指定的数据
*   参数：val -- 添加的数据
*   返回值：无
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::Insert(int nIdx, T val)
{
	//判断是否为空
	if (m_pBuff == nullptr)
	{
		// 初始化
		const int nInitBuffSize = 4;
		m_nBuffSize = nInitBuffSize;
		m_pBuff = new T[m_nBuffSize];
		m_nElementSize = 0;
	}

	// 判断索引值是否合理
	if (nIdx < 0 || nIdx > m_nElementSize)
	{
		return false;
	}

	// 判断缓冲区是否足够使用，数组元素的个数超过缓冲区大小，申请新的缓冲区
	if (m_nElementSize >= m_nBuffSize)
	{
		//申请新的缓冲区，大小为原来缓冲区大小的两倍
		m_nBuffSize = m_nBuffSize * 2;
		T* pNewBuff = new T[m_nBuffSize];
		memcpy(pNewBuff, m_pBuff, m_nElementSize * sizeof(T)); //拷贝原来的数据
		delete[]m_pBuff; //删除原来的缓冲区
		m_pBuff = pNewBuff;
	}

	//添加新的元素
	//从nIdx开始的元素都向后移动
	memcpy(&m_pBuff[nIdx + 1], &m_pBuff[nIdx], (m_nElementSize - nIdx) * sizeof(T));
	m_pBuff[nIdx] = val; // 插入新值
	m_nElementSize++; // 元素个数加1

	return true;
}


/*=======================================================
*   函数作用：删除头结点
*   参数：无
*   返回值：调用Remove()方法，删除成功 返回true，删除失败 返回false
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::RemoveHead()
{
	return Remove(0);
}


/*=======================================================
*   函数作用：删除尾结点
*   参数：无
*   返回值：调用Remove()方法，删除成功 返回true，删除失败 返回false
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::RemoveTail()
{
	return Remove(m_nElementSize - 1);
}


/*=======================================================
*   函数作用：根据输入的索引值，删除指定索引上的数据
*   参数：int nIdx  -- 要删除元素的索引值
*   返回值：调用Remove()方法，删除成功 返回true，删除失败 返回false
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::Remove(int nIdx)
{
	// 数组为空则不删除
	if (m_pBuff == nullptr)
	{
		return false;
	}

	//判断索引值是否合理
	if (nIdx < 0 || nIdx >= m_nElementSize)
	{
		return false;
	}

	// 删除元素 将要删除的元素后面的元素向前移动
	memcpy(&m_pBuff[nIdx], &m_pBuff[nIdx + 1], (m_nElementSize - nIdx - 1) * sizeof(T));
	// 元素个数减1
	m_nElementSize--;

	return true;
}


/*=======================================================
*   函数作用：根据输入的索引值，删除指定索引上的数据
*   参数：int nIdx  -- 要修改元素的索引，val -- 修改后的数据
*   返回值：修改成功 返回true，修改失败 返回false
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::SetVal(int nIdx, T val)
{
	// 判断索引是否合理
	if (nIdx < 0 || nIdx >= m_nElementSize)
	{
		return false;
	}
	// 修改指定索引的数值
	m_pBuff[nIdx] = val;
	return true;
}


/*=======================================================
*   函数作用：重载运算符[]
*   参数：int nIdx  -- 要访问动态数组的下标
*   返回值：下标越界，抛出异常，没有越界，返回索引上对应的数值
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
T& CArrary<T>::operator[](int nIdx)
{
	// 检查下标是否越界以及缓冲区是否为空
	if (nIdx < 0 || nIdx >= m_nElementSize || m_pBuff == nullptr)
	{
		// 注意，当条件判断为真，这里会抛出异常
		throw std::out_of_range("访问越界，请检查你输入的下标索引值");
	}
	return m_pBuff[nIdx];
}


/*=======================================================
*   函数作用：重载运算符 +=
*   参数：const CArrary& ary -- 已初始化的类对象 ary
*   返回值：
*		拼接失败，返回 *this -- 返回被拼接方的数据，
*		拼接成功，返回拼接后的 *this
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
CArrary<T>& CArrary<T>::operator+=(const CArrary& ary)
{
	// 如果对方为空，就不拼接
	if (ary.m_pBuff == nullptr)
	{
		return *this;
	}

	// 如果自己为空，则直接拷贝
	if (m_pBuff == nullptr)
	{
		*this = ary;
		return *this;
	}

	// 上述的两个条件不成立的时，程序在这里申请新的内存，进行拷贝赋值
	T* pNewBuff = new T[m_nElementSize + ary.m_nElementSize];
	memcpy(pNewBuff, m_pBuff, (m_nElementSize) * sizeof(T));
	memcpy(pNewBuff + m_nElementSize, ary.m_pBuff, ary.m_nElementSize * sizeof(T));

	// 释放之前的缓冲区
	delete[] m_pBuff;
	m_pBuff = pNewBuff;
	m_nBuffSize = m_nElementSize + ary.m_nElementSize;
	m_nElementSize = m_nElementSize + ary.m_nElementSize;

	return *this;
}


/*=======================================================
*   函数作用：重载运算符 =
*   参数：const CArrary& ary -- 已初始化的类对象 ary
*   返回值：= 号两侧为同一个类对象的时候，赋值失败，返回 *this（被赋值的类对象地址）
*		赋值成功，返回赋值后的类对象 *this
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
CArrary<T>& CArrary<T>::operator=(const CArrary& ary)
{
	/*
	当运算符 = 的两侧为同一个对象的时候，不进行赋值操作（比较地址是否相等）
	*this == ary --> 这样写是不合理的，需要调用 重载运算符 ==，因为 == 两端为对象
	*/
	if (this == &ary)
	{
		return *this;
	}

	// 此处掉之前自己的数据
	Clear();

	// 拷贝目标对象的数据给自己
	m_pBuff = new T[ary.m_nBuffSize];
	memcpy(m_pBuff, ary.m_pBuff, ary.m_nElementSize * sizeof(T));
	m_nBuffSize = ary.m_nBuffSize;
	m_nElementSize = ary.m_nElementSize;
	return *this;
}


/*=======================================================
*   函数作用：在动态数组内查询指定的数据值 val
*   参数：val -- 查询的指定数据 ary
*   返回值：查询成功返回索引
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
int CArrary<T>::Find(T val)
{
	if (m_pBuff == nullptr)
	{
		return -1;
	}

	for (int nInx = 0; nInx < m_nElementSize; nInx++)
	{
		/*
		当运算符 == 两段的类型不匹配的时候，需要类对象中提供 重载运算符 ==
		二进制“==”:“T”不定义该运算符或到预定义运算符可接收的类型的转换
		*/
		if (m_pBuff[nInx] == val)
		{
			return nInx; // 找到返回索引
			//return m_pBuff[nInx];
		}
	}
	return -1;
}


/*=======================================================
*	函数作用：获取元素个数
*   参数：无
*   返回值：返回动态数组内的有效元素数量
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
int CArrary<T>::ElementCount() const
{
	return m_nElementSize;
}


/*=======================================================
*   函数作用：清除动态数组的数据
*   参数：无
*   返回值：无
*   警告：无
*   更新：2020/06/08
========================================================*/
template<typename T>
void CArrary<T>::Clear()
{
	if (m_pBuff != nullptr)
	{
		delete[] m_pBuff;
		m_pBuff = nullptr;
		m_nBuffSize = 0;
		m_nElementSize = 0;
	}
}