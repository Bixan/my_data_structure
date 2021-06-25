/*=======================================================
*		o(*������*)o
*		Project Name����ϣ��
*		FileName��CHashTable.h
*		Programmer��ileemi
*		Start Date��2020/06/10
*		Last UpDate��2020/06/11
*=======================================================*/
#include "CHashTable.h"
#include <memory.h>

/*=======================================================
*	�������ã��޲ι��죬��ʼ����ϣ��
*	��������
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
CHashTable::CHashTable()
{
	memset(m_aryTable, 0, sizeof(m_aryTable));
}


/*=======================================================
*	�������ã�����
*	��������
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
CHashTable::~CHashTable()
{
}


/*=======================================================
*	�������ã����ݹؼ��� nKey ��������ֵ dblVal
*	������
		int nKey -- �ؼ���
		double dblVal -- ֵ
*	����ֵ������ɹ�����true
*	���棺��
*	���£�2020/06/10
========================================================*/
bool CHashTable::Insert(int nKey, double dblVal)
{
	// �ж� nKey �Ƿ����
	PNODE pNode = Findkey(nKey);
	if (pNode != nullptr)
	{
		// pNode ��Ϊ�գ��ؼ��ֶ�Ӧ�����ݴ��ڣ�ֱ���޸����ݼ���
		pNode->m_dblVal = dblVal;
		return true;
	}

	// ��ȡHashֵ
	int nIdx = nKey % MAX_TABLE_SIZE;

	// �����µĽ��
	PNODE pNewNode = new NODE(nKey, dblVal, nullptr);

	//�жϴ洢����λ���Ƿ�Ϊ�գ����Ϊ�գ�ֱ�Ӳ���
	if (m_aryTable[nIdx] == nullptr)
	{
		m_aryTable[nIdx] = pNewNode;
		return true;
	}

	// �����Ϊ�գ����½ڵ���뵽�����ͷ��
	pNewNode->m_pNext = m_aryTable[nIdx]; // �½ڵ����һ�������Ϊ�ִ��ͷ���
	m_aryTable[nIdx] = pNewNode; // ���½����Ϊ	ͷ�ڵ�
	return true;
}


/*=======================================================
*	�������ã����ݹؼ��� nKey ɾ���������ж�Ӧ�Ľ������
*	������int nKey -- �ؼ���
*	����ֵ��ɾ��/����ʧ�ܣ�����false  ɾ���ɹ�������true
*	���棺��
*	���£�2020/06/10
========================================================*/
bool CHashTable::Remove(int nKey)
{
	// ͨ���ؼ��ֲ�ѯ�����Ƿ����Ҫɾ���Ĺؼ���
	PNODE pNode = Findkey(nKey);
	if (pNode == nullptr)
	{
		return false; // û���ҵ�������false
	}

	// �ҵ��ˣ��ͽ�ͷ����ϵ����ݿ�����Ҫɾ���Ĺؼ���λ����
	// ֮��ɾ��ͷ���
	int nIdx = nKey % MAX_TABLE_SIZE; // ��ȡ���ж�Ӧ������
	pNode->m_nKey = m_aryTable[nIdx]->m_nKey; // m_aryTable[nIdx]->m_nKey -- ͷ����Ӧ�Ĺؼ���
	pNode->m_dblVal = m_aryTable[nIdx]->m_dblVal; // m_aryTable[nIdx]->m_dblVal -- ͷ����Ӧ������ֵ

	// ɾ��ͷ���
	PNODE pHead = m_aryTable[nIdx]; // ��ͷ������ݸ�ֵ�� pHead
	m_aryTable[nIdx] = pHead->m_pNext; // ԭͷ������һ�������Ϊ�����ͷ���
	delete pHead;
	pHead = nullptr;
	return true;
}


/*=======================================================
*	�������ã����������[]��ͨ���±��ȡ��Ӧ�ؼ�������
*	������int nKey -- �ؼ���
*	����ֵ��
		ͨ���ؼ��ֽ����±���ʣ����ڣ��������Ӧ������
*		�����ڣ������µĹؼ��֣���ֵ��ʼ�� 0.0
*	���棺��
*	���£�2020/06/10
========================================================*/
double& CHashTable::operator[](int nKey)
{
	// ͨ���ؼ��ֻ�ȡ Hash ֵ
	int nIdx = nKey % MAX_TABLE_SIZE;

	// �ж� nKey �Ƿ����
	PNODE pNode = Findkey(nKey);
	if (pNode != nullptr)
	{
		return pNode->m_dblVal;
	}

	// û���ҵ��������µĶ�Ӧ�ؼ��֣�ֵΪ 0.0
	Insert(nKey, 0.0);

	// �����µĹؼ��֣����ؽ���ϵ���ֵ
	return Findkey(nKey)->m_dblVal;
}


/*=======================================================
*	�������ã�ͨ���ؼ��� nKey  �ڱ��в����Ǵ���
*	������int nKey -- �ؼ���
*	����ֵ������ Findkey ���������ҳɹ����ض�Ӧ�Ľ�����ݣ�����ʧ�ܷ��� false
*	���棺��
*	���£�2020/06/10
========================================================*/
bool CHashTable::Find(int nKey) const
{
	// �ж� nKey �Ƿ����
	//return Findkey(nKey) != nullptr;

	return Findkey(nKey) == nullptr ? false : Findkey(nKey)->m_dblVal;
}


/*=======================================================
*	�������ã�ͨ���ؼ��� nKey  �ڱ��в����Ǵ���
*	������int nKey -- �ؼ���
*	����ֵ�����ҳɹ����ض�Ӧ�Ľ�����ݣ�����ʧ�ܷ��� false
*	���棺��
*	���£�2020/06/10
========================================================*/
CHashTable::PNODE CHashTable::Findkey(int nKey) const
{
	// ͨ���ؼ��ֻ�ȡ Hash ֵ
	int nIdx = nKey % MAX_TABLE_SIZE;

	// ͨ�� Hash ֵ����ȡ��Ӧ�����ͷ���
	PNODE pNode = m_aryTable[nIdx];

	// ���������ѯ�Ƿ������ؼ����йص�����
	while (pNode != nullptr)
	{
		if (pNode->m_nKey == nKey)
		{
			return pNode;
		}
		// ��ȡ�����е���һ�����
		pNode = pNode->m_pNext;
	}
	return nullptr;
}