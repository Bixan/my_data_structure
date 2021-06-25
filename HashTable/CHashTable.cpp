/*=======================================================
*		o(*￣▽￣*)o
*		Project Name：哈希表
*		FileName：CHashTable.h
*		Programmer：ileemi
*		Start Date：2020/06/10
*		Last UpDate：2020/06/11
*=======================================================*/
#include "CHashTable.h"
#include <memory.h>

/*=======================================================
*	函数作用：无参构造，初始化哈希表
*	参数：无
*	返回值：无
*	警告：无
*	更新：2020/06/10
========================================================*/
CHashTable::CHashTable()
{
	memset(m_aryTable, 0, sizeof(m_aryTable));
}


/*=======================================================
*	函数作用：析构
*	参数：无
*	返回值：无
*	警告：无
*	更新：2020/06/10
========================================================*/
CHashTable::~CHashTable()
{
}


/*=======================================================
*	函数作用：根据关键字 nKey 插入数据值 dblVal
*	参数：
		int nKey -- 关键字
		double dblVal -- 值
*	返回值：插入成功返回true
*	警告：无
*	更新：2020/06/10
========================================================*/
bool CHashTable::Insert(int nKey, double dblVal)
{
	// 判断 nKey 是否存在
	PNODE pNode = Findkey(nKey);
	if (pNode != nullptr)
	{
		// pNode 不为空，关键字对应的数据存在，直接修改数据即可
		pNode->m_dblVal = dblVal;
		return true;
	}

	// 获取Hash值
	int nIdx = nKey % MAX_TABLE_SIZE;

	// 插入新的结点
	PNODE pNewNode = new NODE(nKey, dblVal, nullptr);

	//判断存储结点的位置是否为空，如果为空，直接插入
	if (m_aryTable[nIdx] == nullptr)
	{
		m_aryTable[nIdx] = pNewNode;
		return true;
	}

	// 如果不为空，将新节点插入到链表的头部
	pNewNode->m_pNext = m_aryTable[nIdx]; // 新节点的下一个结点设为现存的头结点
	m_aryTable[nIdx] = pNewNode; // 将新结点设为	头节点
	return true;
}


/*=======================================================
*	函数作用：根据关键字 nKey 删除在链表中对应的结点数据
*	参数：int nKey -- 关键字
*	返回值：删除/查找失败，返回false  删除成功，返回true
*	警告：无
*	更新：2020/06/10
========================================================*/
bool CHashTable::Remove(int nKey)
{
	// 通过关键字查询表中是否存在要删除的关键字
	PNODE pNode = Findkey(nKey);
	if (pNode == nullptr)
	{
		return false; // 没有找到，返回false
	}

	// 找到了，就将头结点上的数据拷贝到要删除的关键字位置上
	// 之后删除头结点
	int nIdx = nKey % MAX_TABLE_SIZE; // 获取表中对应的索引
	pNode->m_nKey = m_aryTable[nIdx]->m_nKey; // m_aryTable[nIdx]->m_nKey -- 头结点对应的关键字
	pNode->m_dblVal = m_aryTable[nIdx]->m_dblVal; // m_aryTable[nIdx]->m_dblVal -- 头结点对应的数据值

	// 删除头结点
	PNODE pHead = m_aryTable[nIdx]; // 将头结点数据赋值给 pHead
	m_aryTable[nIdx] = pHead->m_pNext; // 原头结点的下一个结点做为链表的头结点
	delete pHead;
	pHead = nullptr;
	return true;
}


/*=======================================================
*	函数作用：重载运算符[]，通过下标获取对应关键的数据
*	参数：int nKey -- 关键字
*	返回值：
		通过关键字进行下标访问，存在，返回其对应的数据
*		不存在，插入新的关键字，数值初始化 0.0
*	警告：无
*	更新：2020/06/10
========================================================*/
double& CHashTable::operator[](int nKey)
{
	// 通过关键字获取 Hash 值
	int nIdx = nKey % MAX_TABLE_SIZE;

	// 判断 nKey 是否存在
	PNODE pNode = Findkey(nKey);
	if (pNode != nullptr)
	{
		return pNode->m_dblVal;
	}

	// 没有找到，插入新的对应关键字，值为 0.0
	Insert(nKey, 0.0);

	// 插入新的关键字，返回结点上的数值
	return Findkey(nKey)->m_dblVal;
}


/*=======================================================
*	函数作用：通过关键字 nKey  在表中查找是存在
*	参数：int nKey -- 关键字
*	返回值：调用 Findkey 方法，查找成功返回对应的结点数据，查找失败返回 false
*	警告：无
*	更新：2020/06/10
========================================================*/
bool CHashTable::Find(int nKey) const
{
	// 判断 nKey 是否存在
	//return Findkey(nKey) != nullptr;

	return Findkey(nKey) == nullptr ? false : Findkey(nKey)->m_dblVal;
}


/*=======================================================
*	函数作用：通过关键字 nKey  在表中查找是存在
*	参数：int nKey -- 关键字
*	返回值：查找成功返回对应的结点数据，查找失败返回 false
*	警告：无
*	更新：2020/06/10
========================================================*/
CHashTable::PNODE CHashTable::Findkey(int nKey) const
{
	// 通过关键字获取 Hash 值
	int nIdx = nKey % MAX_TABLE_SIZE;

	// 通过 Hash 值，获取对应链表的头结点
	PNODE pNode = m_aryTable[nIdx];

	// 遍历链表查询是否存在与关键字有关的数据
	while (pNode != nullptr)
	{
		if (pNode->m_nKey == nKey)
		{
			return pNode;
		}
		// 获取链表中的下一个结点
		pNode = pNode->m_pNext;
	}
	return nullptr;
}