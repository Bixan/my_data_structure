#pragma once

/*=======================================================
*		o(*￣▽￣*)o
*		Project Name：哈希表
*		FileName：CHashTable.h
*		Programmer：ileemi
*		Start Date：2020/06/10
*		Last UpDate：2020/06/11
*=======================================================*/
#define MAX_TABLE_SIZE 8
class CHashTable
{
	typedef struct tagNode
	{
		tagNode(int nKey, double dblVal, tagNode* pNext):
			m_nKey(nKey),
			m_dblVal(dblVal),
			m_pNext(pNext)
		{}
		int m_nKey; // 关键字
		double m_dblVal; // 值
		tagNode* m_pNext; // 指向下一个结点
	}NODE, *PNODE;
public:
	CHashTable();
	virtual ~CHashTable();
public:
	bool Insert(int nKey, double dblVal); // nKey -- 键，dblVal -- 值
	bool Remove(int nKey); // 通过关键字删除
	double& operator[](int nKey); // 重载运算符 [] ，方便其进行下标访问
	bool Find(int nKey)const; // 查找
private:
	PNODE Findkey(int nKey)const; // 通过关键字查找表中是否存在对应的数据
private:
	PNODE m_aryTable[MAX_TABLE_SIZE]; // 哈希表，存储结点数据
};