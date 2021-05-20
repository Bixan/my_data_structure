#pragma once

/*=======================================================
*							o(*������*)o
****************************************************************************************
*				Project Name������������
*
*				FileName��CBinarySearchTree.h
*
*				Start Date��2020/06/05
*
*				Last UpDate��2020/06/08
*
****************************************************************************************
========================================================*/

class CBinarySearchTree
{
private:
	typedef struct tagNode
	{
		// ���������
		tagNode(int val, tagNode* pParent, tagNode* pLeft, tagNode* pRight) :
			m_val(val),
			m_pParent(pParent),
			m_pLeft(pLeft),
			m_pRight(pRight)
		{}
		int m_val;	// ��ǰ��㱣�������
		tagNode* m_pParent;	// ָ�򸸽��
		tagNode* m_pLeft;		// ��ǰ��������
		tagNode* m_pRight;	// ��ǰ�����Һ���
	}NODE, * PNODE;

public:
	CBinarySearchTree();
	CBinarySearchTree(const  CBinarySearchTree& bst);

	CBinarySearchTree& operator=(const CBinarySearchTree& bst);
	virtual ~CBinarySearchTree();

public:
	// ��������
	bool Insert(int val);	// �������� val
	bool Remove(int val);	// ɾ������ val
	bool Updata(int valSrc, int valDst);	// ��ԭ������ϵ���ֵ�����µ���ֵ
	bool Find(int val);	// ���� ���� val 
	void Clear();

	// ʹ�õݹ�������ݣ�ǰ�����򡢺�����
	void MLR();	// ǰ��������ݹ飩middle left right
	void LMR();	// ����������ݹ飩 left middle right
	void LRM();	// ����������ݹ飩 left right middle

	// ʹ�÷ǵݹ飨ʹ��ѭ�����������ݣ�ǰ�����򡢺�����
	void MLRUseLoop();	// ǰ��������ǵݹ飩middle left right
	void LMRUseLoop();	// ����������ǵݹ飩 left middle right
	void LRMUseLoop();	// ����������ǵݹ飩 left right middle

	void Level();	// �������

private:
	void Destroy(PNODE pNode);	// ������
	PNODE FindNode(int val);	// ���ҽ��
	void DelNode(PNODE pNode);	// ���ݴ�ɾ����������λ�ý��ж�Ӧ��ɾ������

	void DelLeaf(PNODE pNode);	// Ҷ�ӽ��
	void DelSingleChildNode(PNODE pNode);		// ����֧���
	void DelDoubleChildNode(PNODE pNode);	// ˫��֧���

	void MLR(PNODE pNode);	// �ݹ� ǰ�� ����
	void LMR(PNODE pNode);	// �ݹ� ���� ����
	void LRM(PNODE pNode);	// �ݹ� ���� ����

private:
	PNODE m_pRoot;	// ��ǰ���ĸ����
};