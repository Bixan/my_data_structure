#pragma once
/*=======================================================
*			o(*������*)o
****************************************************************************************
*			Project Name����ϣ��
*
*			FileName��MyCHashTable.h
*
*			Programmer��ileemi
*
*			Start Date��2020/06/10
*
*			Last UpDate��2020/06/11
*
*=======================================================*/
#include "CHashTable.h"
#include <memory.h>
#define MAX_TABLE_SIZE 8

template<typename T>
class CHashTable
{
	typedef struct tagNode
	{
		tagNode(T Key, T Val, tagNode* pNext) :
			m_Key(Key),
			m_Val(Val),
			m_pNext(pNext)
		{}
		T m_Key;	// �ؼ���
		T m_Val;	// ֵ
		tagNode* m_pNext;	// ָ����һ�����
	}NODE, * PNODE;
public:
	CHashTable();
	virtual ~CHashTable();
public:
	bool Insert(T Key, T Val);	// Key -- ����Val -- ֵ
	bool Remove(T Key);			// ͨ���ؼ���ɾ��
	double& operator[](T Key);	// ��������� [] ������������±����
	bool Find(T Key)const;		// ����
private:
	PNODE Findkey(T Key)const;	// ͨ���ؼ��ֲ��ұ����Ƿ���ڶ�Ӧ������
private:
	PNODE m_aryTable[MAX_TABLE_SIZE];	// ��ϣ���洢�������
};


/*=======================================================
*	CHashTable::CHashTable() -- �޲ι��죬��ʼ����ϣ��
*
*	��������
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
template<typename T>
CHashTable<T>::CHashTable()
{
	memset(m_aryTable, 0, sizeof(m_aryTable));
}


/*=======================================================
*	CHashTable::~CHashTable() -- ����
*
*	��������
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
template<typename T>
CHashTable<T>::~CHashTable()
{
}


/*=======================================================
*	bool CHashTable::Insert(int Key, double Val) -- ���ݹؼ��� Key ��������ֵ Val
*
*	������int Key -- �ؼ��֣�double Val -- ֵ
*
*	����ֵ������ɹ�����true
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
template<typename T>
bool CHashTable<T>::Insert(T Key, T Val)
{
	// �ж� Key �Ƿ����
	PNODE pNode = Findkey(Key);
	if (pNode != nullptr)
	{
		// pNode ��Ϊ�գ��ؼ��ֶ�Ӧ�����ݴ��ڣ�ֱ���޸����ݼ���
		pNode->m_Val = Val;
		return true;
	}

	// ��ȡHashֵ
	int nIdx = Key % MAX_TABLE_SIZE;

	// �����µĽ��
	PNODE pNewNode = new NODE(Key, Val, nullptr);

	//�жϴ洢����λ���Ƿ�Ϊ�գ����Ϊ�գ�ֱ�Ӳ���
	if (m_aryTable[nIdx] == nullptr)
	{
		m_aryTable[nIdx] = pNewNode;
		return true;
	}

	// �����Ϊ�գ����½ڵ���뵽�����ͷ��
	pNewNode->m_pNext = m_aryTable[nIdx];	// �½ڵ����һ�������Ϊ�ִ��ͷ���
	m_aryTable[nIdx] = pNewNode;	// ���½����Ϊ	ͷ�ڵ�
	return true;
}


/*=======================================================
*	bool CHashTable::Remove(int Key) -- ���ݹؼ��� Key ɾ���������ж�Ӧ�Ľ������
*
*	������int Key -- �ؼ���
*
*	����ֵ��ɾ��/����ʧ�ܣ�����false  ɾ���ɹ�������true
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
template<typename T>
bool CHashTable<T>::Remove(T Key)
{
	// ͨ���ؼ��ֲ�ѯ�����Ƿ����Ҫɾ���Ĺؼ���
	PNODE pNode = Findkey(Key);
	if (pNode == nullptr)
	{
		return false;	// û���ҵ�������false
	}

	// �ҵ��ˣ��ͽ�ͷ����ϵ����ݿ�����Ҫɾ���Ĺؼ���λ����
	// ֮��ɾ��ͷ���
	int nIdx = Key % MAX_TABLE_SIZE;	// ��ȡ���ж�Ӧ������
	pNode->m_Key = m_aryTable[nIdx]->m_Key;	// m_aryTable[nIdx]->m_Key -- ͷ����Ӧ�Ĺؼ���
	pNode->m_Val = m_aryTable[nIdx]->m_Val;		// m_aryTable[nIdx]->m_Val -- ͷ����Ӧ������ֵ

	// ɾ��ͷ���
	PNODE pHead = m_aryTable[nIdx];			// ��ͷ������ݸ�ֵ�� pHead
	m_aryTable[nIdx] = pHead->m_pNext;	// ԭͷ������һ�������Ϊ�����ͷ���
	delete pHead;
	pHead = nullptr;
	return true;
}


/*=======================================================
*	double& CHashTable::operator[](int Key)
*	-- ���������[]��ͨ���±��ȡ��Ӧ�ؼ�������
*	������int Key -- �ؼ���
*
*	����ֵ��ͨ���ؼ��ֽ����±���ʣ����ڣ��������Ӧ������
*		�����ڣ������µĹؼ��֣���ֵ��ʼ�� 0.0
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
template<typename T>
double& CHashTable<T>::operator[](T Key)
{
	// ͨ���ؼ��ֻ�ȡ Hash ֵ
	int nIdx = Key % MAX_TABLE_SIZE;

	// �ж� Key �Ƿ����
	PNODE pNode = Findkey(Key);
	if (pNode != nullptr)
	{
		return pNode->m_Val;
	}

	// û���ҵ��������µĶ�Ӧ�ؼ��֣�ֵΪ 0.0
	Insert(Key, 0.0);

	// �����µĹؼ��֣����ؽ���ϵ���ֵ
	return Findkey(Key)->m_Val;
}


/*=======================================================
*	bool CHashTable::Find(int Key) const -- ͨ���ؼ��� Key  �ڱ��в����Ǵ���
*
*	������int Key -- �ؼ���
*
*	����ֵ������ Findkey ���������ҳɹ����ض�Ӧ�Ľ�����ݣ�����ʧ�ܷ��� false
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
template<typename T>
bool CHashTable<T>::Find(T Key) const
{
	// �ж� Key �Ƿ����
	//return Findkey(Key) != nullptr;

	return Findkey(Key) == nullptr ? false : Findkey(Key)->m_Val;
}


/*=======================================================
*	CHashTable::PNODE CHashTable::Findkey(int Key) const
*	-- ͨ���ؼ��� Key  �ڱ��в����Ǵ���
*	������int Key -- �ؼ���
*
*	����ֵ�����ҳɹ����ض�Ӧ�Ľ�����ݣ�����ʧ�ܷ��� false
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
template<typename T>
typename CHashTable<T>::PNODE CHashTable<T>::Findkey(T Key) const
{
	// ͨ���ؼ��ֻ�ȡ Hash ֵ
	int nIdx = Key % MAX_TABLE_SIZE;

	// ͨ�� Hash ֵ����ȡ��Ӧ�����ͷ���
	PNODE pNode = m_aryTable[nIdx];

	// ���������ѯ�Ƿ������ؼ����йص�����
	while (pNode != nullptr)
	{
		if (pNode->m_Key == Key)
		{
			return pNode;
		}
		// ��ȡ�����е���һ�����
		pNode = pNode->m_pNext;
	}
	return nullptr;
}