#pragma once
/*=======================================================
*		o(*������*)o
*		Project Name������ƽ���� ������
*		FileName��AVLTree.h
*		Start Date��2020/06/08
*		Last UpDate��2020/06/10
========================================================*/

class CAVLTree
{
private:
	typedef struct tagNode
	{
		// ���������
		tagNode(int val, 
			int nNodeHeight, 
			tagNode* pParent, 
			tagNode* pLeft, 
			tagNode* pRight) :
			m_val(val),
			m_nNodeHeight(nNodeHeight),
			m_pParent(pParent),
			m_pLeft(pLeft),
			m_pRight(pRight)
		{}
		int m_val; // ��ǰ��㱣�������
		int m_nNodeHeight; // ���н��ĸ߶�
		tagNode* m_pParent; // ָ�򸸽��
		tagNode* m_pLeft; // ��ǰ��������
		tagNode* m_pRight; // ��ǰ�����Һ���
	}NODE, *PNODE;

public:
	CAVLTree();
	CAVLTree(const  CAVLTree& bst);

	CAVLTree& operator=(const CAVLTree& bst);
	virtual ~CAVLTree();

public:
	// ��������
	bool Insert(int val); // �������� val
	bool Remove(int val); // ɾ������ val
	bool Updata(int valSrc, int valDst); // ��ԭ������ϵ���ֵ�����µ���ֵ
	bool Find(int val);	// ���� ���� val
	void Clear();

	// ʹ�õݹ�������ݣ�ǰ�����򡢺�����
	void MLR();	// ǰ��������ݹ飩middle left right
	void LMR();	// ����������ݹ飩left middle right
	void LRM();	// ����������ݹ飩left right middle

	// ʹ�÷ǵݹ飨ʹ��ѭ�����������ݣ�ǰ�����򡢺�����
	void MLRUseLoop(); // ǰ��������ǵݹ飩middle left right
	void LMRUseLoop(); // ����������ǵݹ飩left middle right
	void LRMUseLoop(); // ����������ǵݹ飩left right middle

	void Level(); // �������

private:
	void Destroy(PNODE pNode); // ������
	PNODE FindNode(int val); // ���ҽ��
	void DelNode(PNODE pNode); // ���ݴ�ɾ����������λ�ý��ж�Ӧ��ɾ������

	void DelLeaf(PNODE pNode); // Ҷ�ӽ��
	void DelSingleChildNode(PNODE pNode); // ����֧���
	void DelDoubleChildNode(PNODE pNode); // ˫��֧���

	void MLR(PNODE pNode); // �ݹ� ǰ�� ����
	void LMR(PNODE pNode); // �ݹ� ���� ����
	void LRM(PNODE pNode); // �ݹ� ���� ����

private:
	void AdjustHeight(PNODE pNode);	// ���ݽ�����Һ��Ӹ߶Ȳ�ж����Ƿ�ƽ�⣬��ƽ��������Ӧ�Ĵ���
	int CalcNodeHeight(PNODE pNode); // ������߶�
	int GetNodeHeight(PNODE pNode)const; // ��ȡ���߶�
	void RotateLeft(PNODE pNode); // ����
	void RotateRight(PNODE pNode); // �ҵ���
private:
	PNODE m_pRoot; // ��ǰ���ĸ����
};