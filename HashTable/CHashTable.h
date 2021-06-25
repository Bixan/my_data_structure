#pragma once

/*=======================================================
*		o(*������*)o
*		Project Name����ϣ��
*		FileName��CHashTable.h
*		Programmer��ileemi
*		Start Date��2020/06/10
*		Last UpDate��2020/06/11
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
		int m_nKey; // �ؼ���
		double m_dblVal; // ֵ
		tagNode* m_pNext; // ָ����һ�����
	}NODE, *PNODE;
public:
	CHashTable();
	virtual ~CHashTable();
public:
	bool Insert(int nKey, double dblVal); // nKey -- ����dblVal -- ֵ
	bool Remove(int nKey); // ͨ���ؼ���ɾ��
	double& operator[](int nKey); // ��������� [] ������������±����
	bool Find(int nKey)const; // ����
private:
	PNODE Findkey(int nKey)const; // ͨ���ؼ��ֲ��ұ����Ƿ���ڶ�Ӧ������
private:
	PNODE m_aryTable[MAX_TABLE_SIZE]; // ��ϣ���洢�������
};