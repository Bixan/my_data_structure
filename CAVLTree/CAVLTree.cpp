#include "CAVLTree.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

/*=======================================================
*	CAVLTree::CAVLTree() -- �޲ι��죬��ʼ����
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
CAVLTree::CAVLTree()
{
	m_pRoot = nullptr;
}

/*=======================================================
*	CAVLTree::CAVLTree(const CAVLTree& bst) -- ��������
*
*	�������ѳ�ʼ���������
*
*	����ֵ��Nothing
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
CAVLTree::CAVLTree(const CAVLTree& bst)
{
	*this = bst;
}


/*=======================================================
*	CAVLTree& CAVLTree::operator=(const CAVLTree& bst) -- ��������� =
*
*	�������ѳ�ʼ���������
*
*	����ֵ��*this
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
CAVLTree& CAVLTree::operator=(const CAVLTree& bst)
{
	if (this == &bst)
	{
		return *this;	// ����Լ����Լ���ֵ��ʲôҲ����
	}

	Clear();	// ����Լ��ĸ����������

	if (bst.m_pRoot == nullptr)
	{
		return *this;	// �����ֵ��Ϊ�����������и�ֵ
	}

	// ��ֵ
	queue<PNODE> queTemp;	// ��ʼ��һ������
	queTemp.push(bst.m_pRoot);	// ��������

	while (!queTemp.empty())		// ����Ϊ�գ��˳�ѭ��
	{
		PNODE pNode = queTemp.front();	// �����׸�ֵ�� pNode
		queTemp.pop();		// �����׵���
		Insert(pNode->m_val);

		if (pNode->m_pLeft != nullptr)	// ���ӵĽ������Ӳ�Ϊ�գ��ͽ����������
		{
			queTemp.push(pNode->m_pLeft);
		}
		if (pNode->m_pRight != nullptr)	// ���ӵĽ����Һ��Ӳ�Ϊ�գ��ͽ����Һ������
		{
			queTemp.push(pNode->m_pRight);
		}
	}

	return *this;
}


/*=======================================================
*	CAVLTree::~CAVLTree() -- ������������� Clear() �����ͷŶ�Ӧ������
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
CAVLTree::~CAVLTree()
{
	Clear();
}


/*=======================================================
*	bool CAVLTree::Insert(int val) -- ��������
*
*	������val -- ���������ֵ
*
*	����ֵ��true -- ���ݲ���ɹ���false -- ���ݲ���ʧ��
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
bool CAVLTree::Insert(int val)
{
	if (m_pRoot == nullptr)
	{
		// �����Ϊ�գ������������Ϊ����㣬ͬʱ���ڵ�ĸ߶���Ϊ0
		m_pRoot = (PNODE)new NODE(val, 0, nullptr, nullptr, nullptr);
	}

	// �����ǰ����Ϊ�գ��ͽ���ǰ���ĸ�������ݸ�ֵ����ʱ�� pTempNode
	PNODE pTempNode = m_pRoot;

	// �������ҿ��Բ����λ�ã����������ĸ�����ʼ
	while (true)
	{
		// ��������������ֵС�ڵ�ǰ��㣬��ȡ�����Ӳ��ֲ��Һ��ʵ�λ��
		if (val < pTempNode->m_val)
		{
			// ����˽��û�����ӣ����²������ֵ��Ϊ��ǰ��������
			if (pTempNode->m_pLeft == nullptr)
			{
				// �²���Ľ��ĸ߶���0����ʱ������ĸ߶ȼ�1
				pTempNode->m_pLeft = new NODE(val, 0, pTempNode, nullptr, nullptr);

				// ÿ�β����µĽ�㣬��Ҫ�ж������ִ����Ƿ�ƽ�⣬�����ƽ�⣬������Ӧ�ĵ���
				AdjustHeight(pTempNode);

				return true;
			}
			else
			{
				// �˽�������ӣ���Ȼ�ý��ָ��ý������ӣ���������Ѱ�ҿ�λ��
				pTempNode = pTempNode->m_pLeft;
			}
		}
		// ��������������ֵ���ڵ�ǰ��㣬��ȡ���Һ����ж�
		else if (val > pTempNode->m_val)
		{
			if (pTempNode->m_pRight == nullptr)
			{
				pTempNode->m_pRight = new NODE(val, 0, pTempNode, nullptr, nullptr);

				// ÿ�β����µĽ�㣬��Ҫ�ж������ִ����Ƿ�ƽ�⣬�����ƽ�⣬������Ӧ�ĵ���
				AdjustHeight(pTempNode);
				return true;
			}
			else
			{
				// �˽�����Һ��ӣ���Ȼ�ý��ָ��ý����Һ��ӣ���������Ѱ�ҿ�λ��
				pTempNode = pTempNode->m_pRight;
			}
		}
		else
		{
			return false;	// ��ʱ��������ȵ����
		}
	}
	return true;
}


/*=======================================================
*	bool CAVLTree::Remove(T val) -- ɾ��ָ��������
*
*	������val -- ɾ��������ֵ
*
*	����ֵ��true -- ����ɾ���ɹ���false -- ����ɾ��ʧ��
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
bool CAVLTree::Remove(int val)
{
	PNODE pNodeTodel = FindNode(val);	// ���ҽ�Ҫ��ɾ���Ľ��

	if (pNodeTodel == nullptr)
	{
		return false;	// pNodeTodel Ϊ�� ����ʧ�� ���� false
	}

	DelNode(pNodeTodel);	// ���ҳɹ������ݽ������������һ������
	return true;
}


/*=======================================================
*	bool CAVLTree::Updata(int valSrc, int valDst) -- �޸�����
*
*	������valSrc -- ���޸ĵ�����ֵ��valDst -- �޸ĺ������ֵ
*
*	����ֵ��false -- ���ݲ���/�޸�ʧ�ܣ�true -- �����޸ĳɹ�
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
bool CAVLTree::Updata(int valSrc, int valDst)
{
	if (m_pRoot == nullptr)
	{
		return false;	// �����ǰ��Ϊ�գ�����false
	}

	PNODE pChangeNode = FindNode(valSrc);	// �����Ƿ���� valSrc

	if (pChangeNode == nullptr)
	{
		return false;	// pNodeTodel Ϊ�� ����ʧ�� ���� false
	}

	//pChangeNode->m_val = valDst;	// ֱ���޸ģ�����ȡ���ᵼ�¸�������һ��������

	Remove(valSrc);	// ��ֵ���ҳɹ���ɾ�����
	Insert(valDst);		// ���µ���ֵ���²��뵽������

	return true;
}


/*=======================================================
*	bool CAVLTree::Find(int val) -- ����ָ��������ֵ
*
*	������val -- ���ҵ�����ֵ
*
*	����ֵ��true -- ���ݲ��ҳɹ���false -- ���ݲ���ʧ��
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
bool CAVLTree::Find(int val)
{
	if (m_pRoot == nullptr)
	{
		return false;	// �����ǰ��Ϊ�գ�����false
	}

	PNODE pChangeNode = FindNode(val);		// ���������Ƿ������ֵ val
	if (pChangeNode == nullptr)
	{
		return false;	// pNodeTodel Ϊ�� ����ʧ�� ���� false
	}
	return true;			// pNodeTodel ��Ϊ�� ���ҳɹ� ���� true
}


/*=======================================================
*	void CAVLTree::Clear() -- �������������Ч�Ľ��
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
void CAVLTree::Clear()
{
	while (m_pRoot != nullptr)
	{
		DelNode(m_pRoot);	// ���н��ɾ����Ϻ�ѭ����ֹ
	}
}


/*=======================================================
*	void CAVLTree::MLR() -- �ݹ� ǰ�� ����	������Ϊ�գ�����MLR()������
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
void CAVLTree::MLR()
{
	if (m_pRoot != nullptr)
	{
		MLR(m_pRoot);	// ���� ǰ�� ����
	}
}

/*=======================================================
*	void CAVLTree::LMR() -- �ݹ� ���� ����	������Ϊ�գ�����LMR()������
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
void CAVLTree::LMR()
{
	if (m_pRoot != nullptr)
	{
		LMR(m_pRoot);	// ���� ���� ����
	}
}

/*=======================================================
*	void CAVLTree::LRM() -- �ݹ� ���� ����	������Ϊ�գ�����LRM()������
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
void CAVLTree::LRM()
{
	if (m_pRoot != nullptr)
	{
		LRM(m_pRoot);	// ���� ���� ����
	}
}


/*=======================================================
*	void CAVLTree::MLRUseLoop() -- ǰ��������ǵݹ飩
*
*	��������
*
*	����ֵ����
*
*	���������������Ч�����洢������ֵ
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::MLRUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;		// ���Ϊ�����������б���
	}

	stack<PNODE> stkTemp;		// ��ʼ��һ��ջ
	PNODE pNode = m_pRoot;	// �洢�����

	while (true)
	{
		while (pNode != nullptr)
		{
			cout << pNode->m_val << " ";	// �������
			stkTemp.push(pNode->m_pRight);	// ������ݽ����Һ�����ջ
			pNode = pNode->m_pLeft;			// ���� pNode ��㣬һֱ���������ջ
		}

		if (stkTemp.empty())
		{
			break;		// ջΪ�գ����е��Һ��������ϣ�����ѭ��
		}

		pNode = stkTemp.top();	// ���������ϣ������ָ��ջ��
		stkTemp.pop();	// ͬʱ��ջ�������ݽ��е���
	}
}


/*=======================================================
*	void CAVLTree::LMRUseLoop() -- ����������ǵݹ飩
*
*	��������
*
*	����ֵ����
*
*	���������������Ч�����洢������ֵ
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::LMRUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;		// �����Ϊ�գ������б���
	}

	stack<PNODE> stkTemp;		// ��ʼ��һ��ջ
	PNODE pNode = m_pRoot;	// �����ڵ㸳ֵ�� pNode

	while (true)
	{
		while (pNode != nullptr)
		{
			stkTemp.push(pNode);		// ���������ջ
			pNode = pNode->m_pLeft;	// pNode ָ��������
		}

		if (stkTemp.empty())
		{
			break;	// ջ��ѭ������
		}

		// ���û�����ӿ�����ջ���ͽ�ջ�ڵ����ݵ�����һ��
		pNode = stkTemp.top();	// pNode ָ�� ջ��
		stkTemp.pop();	// ��ջ������һ������
		cout << pNode->m_val << " ";	// �������������

		// ������������ݵ��Һ���
		pNode = pNode->m_pRight;
	}
}


/*=======================================================
*	void CAVLTree::LRMUseLoop() -- ����������ǵݹ飩
*
*	��������
*
*	����ֵ����
*
*	���������������Ч�����洢������ֵ
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::LRMUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;		// �����Ϊ�գ������б���
	}

	stack<PNODE> stkTemp;		// ��ʼ��һ��ջ
	PNODE pNode = m_pRoot;	// �� �� m_pRoot ��ֵ�� pNode
	PNODE pPreDisposeNode = nullptr;	// ������һ�δ���Ľ��

	while (true)
	{
		while (pNode != nullptr)
		{
			stkTemp.push(pNode);		// ���ĸ������ջ
			pNode = pNode->m_pLeft;	// ���� pNode ��㣬һֱ���������ջ
		}

		if (stkTemp.empty())
		{
			break;		// ջΪ�գ����е��Һ��������ϣ�����ѭ��
		}

		pNode = stkTemp.top();	// ָ��ջ��

		if (pNode->m_pRight == pPreDisposeNode || pNode->m_pRight == nullptr)
		{
			cout << pNode->m_val << " ";

			pPreDisposeNode = pNode;		// ���洦���Ľ��
			stkTemp.pop();		// �������Ľ�㵯��

			pNode = nullptr;	// ����Ľ�㴦�����˵�����Һ����Ѿ����������
			continue;		// ���ﲻ��Ҫ�ٽ� pNode ָ��ý����Һ���
		}
		pNode = pNode->m_pRight;		// �����Һ���
	}
}


/*=======================================================
*	void CAVLTree::Level() -- �������
*
*	��������
*
*	����ֵ����
*
*	���������������Ч�����洢������ֵ
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::Level()
{
	if (m_pRoot == nullptr)
	{
		return;		// ���Ϊ�����������б���
	}

	queue<PNODE> queTemp;		// ��ʼ��һ������
	queTemp.push(m_pRoot);		// ��������

	while (!queTemp.empty())		// ����Ϊ�գ��˳�ѭ��
	{
		PNODE pNode = queTemp.front();	// �����׸�ֵΪ pNode
		queTemp.pop();	// �����׵���
		cout << pNode->m_val << " ";	// �����������ݽ������

		if (pNode->m_pLeft != nullptr)	// ���ӵĽ������Ӳ�Ϊ�գ��ͽ����������
		{
			queTemp.push(pNode->m_pLeft);
		}
		if (pNode->m_pRight != nullptr)	// ���ӵĽ����Һ��Ӳ�Ϊ�գ��ͽ����Һ������
		{
			queTemp.push(pNode->m_pRight);
		}
#if 0
		if (pNode != nullptr)
		{
			cout << pNode->m_val << " ";			// ����������
			queTemp.push(pNode->m_pLeft);		// ���ӽ������� �� �Һ������
			queTemp.push(pNode->m_pRight);
		}
#endif // ���ӽ��� ���� �� �Һ���  ��ӣ���д����
	}
}


/*=======================================================
*	void CAVLTree::Destroy(PNODE pNode) -- ʹ�õݹ����������Ч�����н��
*
*	������PNODE pNode -- ���ĸ����
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::Destroy(PNODE pNode)
{
	if (pNode != nullptr)
	{
		Destroy(pNode->m_pLeft);	// ���ٸ�������
		Destroy(pNode->m_pRight);	// ���ٸ����Һ���

		delete pNode;	// ���ٸ�
		pNode = nullptr;
	}
}


/*=======================================================
*	PNODE CAVLTree::FindNode(T val)
*	-- �������������ֵ���������Ƿ���ڶ�Ӧ������
*	������val -- ���ҵ�����ֵ
*
*	����ֵ��pTempNode ���ز鵽�Ĵ洢�����ݵĽ��
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
typename CAVLTree::PNODE CAVLTree::FindNode(int val)
{
	// �Ӹ����ĸ���㿪ʼ����
	PNODE pTempNode = m_pRoot;

	while (pTempNode != nullptr)
	{
		// ������ҵ����ݺ͵�ǰ������ֵ��ȣ��ͷ��ظý��
		if (val == pTempNode->m_val)
		{
			return pTempNode;
		}
		// ������ҵ����ݴ��ڵ�ǰ������ֵ����ȥ�ý����Ҳ��ֽ��в���
		else if (val > pTempNode->m_val)
		{
			pTempNode = pTempNode->m_pRight;
		}
		else
		{
			// ������ҵ�����С�ڵ�ǰ������ֵ����ȥ�ý����󲿷ֽ��в���
			pTempNode = pTempNode->m_pLeft;
		}
	}
	return nullptr;
}


/*=======================================================
*	void CAVLTree::DelNode(PNODE pNode)
*	-- ɾ����㣬���ݽ�����ͽ��ж�Ӧ��ɾ��
*	������PNODE pNode -- Ҫɾ������������Ӧ�Ľ��
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::DelNode(PNODE pNode)
{
	// ��Ҫɾ���Ľ����н��λ���ж�

	// Ҷ�ӽ��
	if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr)
	{
		DelLeaf(pNode);
		return;
	}
	// ����֧���
	else if (pNode->m_pLeft == nullptr || pNode->m_pRight == nullptr)
	{
		DelSingleChildNode(pNode);
		return;
	}
	// ˫��֧���
	else
	{
		DelDoubleChildNode(pNode);
	}
}


/*=======================================================
*	void CAVLTree::DelLeaf(PNODE pNode)
*	-- ɾ���Ľ��ΪҶ�ӽ�㣨�ý��û�����Һ��ӣ�
*	������PNODE pNode -- Ҫɾ������������Ӧ�Ľ��
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::DelLeaf(PNODE pNode)
{
	PNODE pParent = pNode->m_pParent;	// ���浱ǰ���ĸ����

	if (pNode == m_pRoot)		// �����ǰ����Ǹ���㣬��ɾ���ý��
	{
		delete m_pRoot;
		m_pRoot = nullptr;
		return;
	}

	// �ж�Ҫɾ���Ľ���Ǹ�����µ� ���� ���� �Һ���
	if (pParent->m_pLeft == pNode)
	{
		pParent->m_pLeft = nullptr;		// ��������ӣ��������ӵĽ���ÿ�
	}
	else
	{
		pParent->m_pRight = nullptr;	// ������Һ��ӣ������Һ��ӵĽ���ÿ�
	}

	delete pNode;	// ɾ���˽��
	pNode = nullptr;

	// ���ɾ���󣬴�ɾ�����ĸ���㿪ʼ���������е����߶�
	AdjustHeight(pParent);
}


/*=======================================================
*	void CAVLTree::DelSingleChildNode(PNODE pNode)
*	-- ɾ���Ľ��Ϊ����֧��㣨�ý����һ������ ����/�Һ��ӣ�
*	������PNODE pNode -- Ҫɾ������������Ӧ�Ľ��
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::DelSingleChildNode(PNODE pNode)
{
	PNODE pParent = pNode->m_pParent;	// ���浱ǰ���ĸ����

	PNODE pChild = pNode->m_pLeft;		// Ĭ�ϱ��浱ǰ��������

	if (pChild == nullptr)
	{
		pChild = pNode->m_pRight;	// �������Ϊ�գ�˵���õ���֧���ֻ���Һ��ӣ������к���
	}

	// �жϴ˽���Ƿ��Ǹ����
	if (pNode == m_pRoot)
	{
		m_pRoot = pChild;		// ���ý������ӻ����к�����Ϊ�����
		pChild->m_pParent = nullptr;		// �ÿ�
		delete pNode;		// ɾ����ǰ���
		pNode = nullptr;
		return;
	}

	// ɾ����������
	if (pParent->m_pLeft == pNode)
	{
		pParent->m_pLeft = pChild;
	}
	// ɾ�������Һ���
	else
	{
		pParent->m_pRight = pChild;
	}

	// ɾ�����ĺ��ӽ��ָ��ɾ�����ĸ��׽��
	pChild->m_pParent = pParent;

	// ɾ���ý��
	delete pNode;
	pNode = nullptr;

	// ���ɾ���󣬴�ɾ�����ĸ���㿪ʼ���������е����߶�
	AdjustHeight(pParent);
}


/*=======================================================
*	void CAVLTree::DelSingleChildNode(PNODE pNode)
*	-- ɾ���Ľ��Ϊ˫��֧��㣨�ý������������ ���Ӻ��Һ��ӣ�
*	������PNODE pNode -- Ҫɾ�����ݶ�Ӧ�Ľ��
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::DelDoubleChildNode(PNODE pNode)
{
	// ����Ҫɾ�����������������ֵ��Ҫɾ����������ֵ���н���
	PNODE pTempNode = pNode->m_pLeft;

	while (pTempNode->m_pRight != nullptr)
	{
		// �ҵ������������ҽ�㣬�ý�㱣�������Ϊ�������е�ֵ��������
		pTempNode = pTempNode->m_pRight;
	}

	// �ҵ��������е����ֵ��������ֵ
	int nTempNum = pNode->m_val;
	pNode->m_val = pTempNode->m_val;
	pTempNode->m_val = nTempNum;

	// ɾ�� pTempNode����ʱ����Ҫ�жϽ�����Ľ�㴦���������
	DelNode(pTempNode);
}


/*=======================================================
*	void CAVLTree::MLR(PNODE pNode) -- �ݹ� ǰ�� ����
*
*	������PNODE pNode -- ��ʼ�����ĸ����
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::MLR(PNODE pNode)
{
	// �ݹ�ĳ���
	if (pNode == nullptr)
	{
		return;
	}
	cout << pNode->m_val << " ";	// ���Լ�
	MLR(pNode->m_pLeft);	// ������
	MLR(pNode->m_pRight);	// ���Һ���
}


/*=======================================================
*	void CAVLTree::LMR(PNODE pNode) -- �ݹ� ���� ����
*
*	������PNODE pNode -- ��ʼ�����ĸ����
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::LMR(PNODE pNode)
{
	// �ݹ�ĳ���
	if (pNode == nullptr)
	{
		return;
	}

	LMR(pNode->m_pLeft);	// ������
	cout << pNode->m_val << " ";	// ���Լ�
	LMR(pNode->m_pRight);	// ���Һ���
}


/*=======================================================
*	void CAVLTree::LRM(PNODE pNode) -- �ݹ� ���� ����
*
*	������PNODE pNode -- ��ʼ�����ĸ����
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/

void CAVLTree::LRM(PNODE pNode)
{
	// �ݹ�ĳ���
	if (pNode == nullptr)
	{
		return;
	}

	LRM(pNode->m_pLeft);	// ������
	LRM(pNode->m_pRight);	// ���Һ���
	cout << pNode->m_val << " ";	// ���Լ�
}


/*=======================================================
*	void CAVLTree::AdjustHeight(PNODE pNode)
*	-- ÿ�β������ݣ��жϵ�ǰ���Ƿ�ƽ��ͬʱ���������߶�
*	������PNODE pNode -- ��������ݵĸ����
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::AdjustHeight(PNODE pNode)
{
	PNODE pTempNode = pNode;		// ������Ľ�����ݸ�ֵ����ʱ���pTempNode

	// ��ʱ��Ҫ���Ų���Ľ�������ж������㣨���ڵ�ĸ��ڵ㣩�Ƿ���ƽ��״̬
	while (pTempNode != nullptr)
	{
		// ��ȡ��ǰ���ĸ߶�
		pTempNode->m_nNodeHeight = CalcNodeHeight(pTempNode);

		// �жϴ˽���Ƿ�ƽ�⣬�ж����ݣ��˽������ӵĸ߶ȼ�ȥ�Һ��ӵĸ߶Ȳ�ľ���ֵ���ܴ���1
		int nTempNodeLeftHeight = GetNodeHeight(pTempNode->m_pLeft);
		int nTempNodeRightHeight = GetNodeHeight(pTempNode->m_pRight);

		// ���� AND ��˫��
		if (nTempNodeLeftHeight - nTempNodeRightHeight < -1)
		{
			/*
			1����ȡ��ƽ�����������
			2������ƽ����������������Ӹ߶�С�ڵ����Һ��ӵĸ߶Ⱦ� ��������
			3����֮�����н�����˫��
			*/
			PNODE pTempNodeRightChild = pTempNode->m_pRight;

			if (GetNodeHeight(pTempNodeRightChild->m_pLeft) <=
				GetNodeHeight(pTempNodeRightChild->m_pRight))
			{
				/*
				ʾ����P --> ���ڵ� A ��ͷ�ڵ㣬 X Ϊ�²���Ľ�㣬���Կ�����ʱ��� A ���ֲ�ƽ��
								��תǰ																	��ת��
									P																			P
									A																			B
							T				B							----->						A				D
										C		D													T		C				X
													X
				ע�⣺��תǰ����� B ���Һ��� C����С�� B ������ݵ�
						  ������ת��B ��Ϊ���ڵ㣬C �����ڸ��ڵ� B ���Ҳ��֣�����Ϊ��� A ���Һ���
				*/
				RotateLeft(pTempNode);
			}
			else
			{
				/*
				ʾ����P --> ����� A �ĸ���㣬 X Ϊ�²���Ľ�㣬���Կ�����ʱ��� A ���ֲ�ƽ��
								��תǰ								�ҵ�����											������
									P											P													P
									A											A													C
							T				B							T				C									A				B
										C		D									X			B						T		X					D
									X																	D

				ע�⣺��תǰ����� A ���ֲ�ƽ�⣬�жϷ������Һ��ӵ�����߶ȸ����ҽ��ĸ߶ȣ�
						  ��ʱ��Ҫ������ͼ�� B ������ �ҵ�����Ȼ�����Խ�� A ��������
						  ��˫���󣬴�ʱ��ǰ������ƽ��״̬
				*/

				// ��ȡ��ת�Ľ��
				PNODE pNodeA = pTempNode;
				PNODE pNodeB = pTempNode->m_pRight;

				// ���Խ�� pNodeB �����ҵ�����֮������ pNodeA ���� ����
				RotateRight(pNodeB);
				RotateLeft(pNodeA);
			}
		}
		// ���� AND ��˫��
		else if (nTempNodeLeftHeight - nTempNodeRightHeight > 1)
		{
			PNODE pTempNodeLiftChild = pTempNode->m_pLeft;
			/*
			1����ȡ��ƽ�����������
			2������ƽ����������������Ӹ߶ȴ��ڵ����Һ��ӵĸ߶Ⱦ� �����ҵ���
			3����֮�����н�����˫��
			*/
			if (GetNodeHeight(pTempNodeLiftChild->m_pLeft) >=
				GetNodeHeight(pTempNodeLiftChild->m_pRight))
			{
				/*
				ʾ����P --> ����� B �ĸ���㣬 X Ϊ�²���Ľ�㣬���Կ�����ʱ��� B ���ֲ�ƽ��
								��תǰ												��ת��
									P														P
									B														A
							A				D										T				B
						T		C												X				C		D
					X
				ע�⣺��תǰ����� A ���Һ��� C���Ǵ��� A ������ݵ�
						  ������ת��A ��Ϊ���ڵ㣬C �����ڸ��ڵ� A ���󲿷֣�ӦΪ���B������
				*/
				RotateRight(pTempNode);
			}
			else
			{
				/*
				ʾ����P --> ����� B �ĸ���㣬 X Ϊ�²���Ľ�㣬���Կ�����ʱ��� B ���ֲ�ƽ��
								��תǰ								������										�ҵ�����
									P										P													P
									B										B													C
							A				D						C				D									A				B
						T		C								A		X											T				X		D
									X						T

				ע�⣺��תǰ����� B ���ֲ�ƽ�⣬�жϷ��������ӵ��ҽ��߶ȸ�������ĸ߶ȣ�
						  ��ʱ��Ҫ������ͼ�� A ������ ������Ȼ�����Խ�� B �����ҵ���
						  ��˫���󣬴�ʱ��ǰ������ƽ��״̬
				*/

				// ��ȡ��ת�Ľ��
				PNODE pNodeB = pTempNode;
				PNODE pNodeA = pTempNode->m_pLeft;

				RotateLeft(pNodeA);		// ������
				RotateRight(pNodeB);	// ������
			}
		}
		// �����ǰ���ƽ�⣬�����ж��丸����Ƿ���ƽ��״̬
		pTempNode = pTempNode->m_pParent;
	}
}


/*=======================================================
*	int CAVLTree::CalcNodeHeight(PNODE pNode) -- ���� ������ĸ߶�
*
*	������PNODE pNode -- ��Ҫ����߶ȵĽ��
*
*	����ֵ�����ؽ��ĸ߶�ֵ
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
int CAVLTree::CalcNodeHeight(PNODE pNode)
{
	/*
	1����ȡ�������ӵĸ߶ȣ����Ϊ�գ�����߶��� -1
	2����ȡ�����Һ��ӵĸ߶ȣ����Ϊ�գ�����߶��� -1
	3��ȡ���Һ��ӽ���и߶����ģ�Ȼ���ټ���1
	*/
	int nNodeLeftHeght = pNode->m_pLeft == nullptr ? -1 : pNode->m_pLeft->m_nNodeHeight;
	int nNodeRightHeight = pNode->m_pRight == nullptr ? -1 : pNode->m_pRight->m_nNodeHeight;

	return nNodeLeftHeght > nNodeRightHeight ? (nNodeLeftHeght + 1) : (nNodeRightHeight + 1);
}


/*=======================================================
*	int CAVLTree::GetNodeHeight(PNODE pNode) const -- ��ȡ���߶�
*
*	������PNODE pNode -- ��Ҫ��ȡ�߶ȵĽ��
*
*	����ֵ�����ؽ��ĸ߶�ֵ
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
int CAVLTree::GetNodeHeight(PNODE pNode) const
{
	if (pNode == nullptr)
	{
		return -1;	// ���Ϊ�գ����� -1
	}
	return pNode->m_nNodeHeight;
}


/*=======================================================
*	void CAVLTree::RotateLeft(PNODE pNode) --  ��������������ƽ��
*
*	������PNODE pNode -- ��Ҫ������ת�Ľ��
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::RotateLeft(PNODE pNode)
{
	/*
	��ʱ�ӵ�ǰ��㴦��ʼ��ƽ��
	ʾ����P --> ���ڵ� A ��ͷ�ڵ㣬 X Ϊ�²���Ľ�㣬���Կ�����ʱ��� A ���ֲ�ƽ��
	��������ӵĸ߶ȼ�ȥ�Һ��ӵĸ߶Ȳ�ľ���ֵС�� -1 ʱ����Ҫ��������ת���Ӳ�ƽ��㿪ʼ��ת��
					��תǰ																	��ת��
						P																			P
						A																			B
				T				B							----->						A				D
							C		D													T		C				X
										X
	ע�⣺��תǰ����� B ���Һ��� C����С�� B ������ݵ�
			  ������ת��B ��Ϊ���ڵ㣬C �����ڸ��ڵ� B ���Ҳ���
	*/

	// ����תʱ��Ӱ��Ľ��ȡ��
	PNODE pNodeA = pNode;
	PNODE pParent = pNode->m_pParent;
	PNODE pNodeB = pNodeA->m_pRight;
	PNODE pNodeC = pNodeB->m_pLeft;

	// �޸ĸ�����Ӱ��Ľ��
	if (pParent == nullptr)
	{
		m_pRoot = pNodeB;	// ��ʱ��� B ��Ϊ�µĸ����
		pNodeB->m_pParent = nullptr;	// ��ʱ��� B ��ͷ���Ϊ nullptr
	}
	// ���Ǹ��ڵ�
	else
	{
		/*
		1)		�����תǰ��������丸�������ӣ��ͽ���ת��ĸ���� pNodeB
				��Ϊ pNodeA ���������ӣ���֮��Ϊ�Һ���
		2)		��ת���޸���ת�����Ľ��ĸ����
				pNode->m_pRight->m_pParent = pNode->m_pParent;
		*/
		pParent->m_pRight == pNodeA ? pParent->m_pRight = pNodeB : pParent->m_pLeft = pNodeB;
		pNodeB->m_pParent = pParent;
	}

	// ������ pNodeB �������ӣ�����������ԭpNodeB�ĸ����pNodeA���ұ߿�£
	pNodeA->m_pRight = pNodeC;
	if (pNodeC != nullptr)
	{
		pNodeC->m_pParent = pNodeA;
	}

	pNodeA->m_pParent = pNodeB;
	pNodeB->m_pLeft = pNodeA;

	// �޸Ľ��߶�
	pNodeA->m_nNodeHeight = CalcNodeHeight(pNodeA);
	pNodeB->m_nNodeHeight = CalcNodeHeight(pNodeB);
}


/*=======================================================
*	void CAVLTree::RotateRight(PNODE pNode) --  �ҵ�������������ƽ��
*
*	������PNODE pNode -- ��Ҫ������ת�Ľ��
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/10
*
========================================================*/
void CAVLTree::RotateRight(PNODE pNode)
{
	/*
	��ʱ�ӵ�ǰ��㴦��ʼ��ƽ��
	ʾ����P --> ���ڵ� B ��ͷ�ڵ㣬 X Ϊ�²���Ľ�㣬���Կ�����ʱ��� B ���ֲ�ƽ��
	��������ӵĸ߶ȼ�ȥ�Һ��ӵĸ߶Ȳ�ľ���ֵС�� -1 ʱ����Ҫ��������ת���Ӳ�ƽ��㿪ʼ��ת��
					��תǰ												��ת��
						P														P
						B														A
				A				D										T				B
			T		C												X				C		D
		X
	ע�⣺��תǰ����� A ���Һ��� C���Ǵ��� A ������ݵ�
			  ������ת��A ��Ϊ���ڵ㣬C �����ڸ��ڵ� A ���󲿷֣�ӦΪ���B������

	*/

	// ����תʱ���ܵ�Ӱ��ĵĽ��ȡ��
	PNODE pNodeB = pNode;
	PNODE pParent = pNodeB->m_pParent;
	PNODE pNodeA = pNodeB->m_pLeft;
	PNODE pNodeC = pNodeA->m_pRight;

	// �޸���Ӱ��ĸ������

	if (pParent == nullptr)
	{
		m_pRoot = pNodeA;	// ��� pNodeA ��Ϊ�����
		pNodeA->m_pParent = nullptr;	// ����� pNodeA �ĸ����Ϊ nullptr
	}
	else
	{
		/*
		1)		�����תǰ��������丸�������ӣ��ͽ���ת��ĸ���� pNodeA
				��ΪpNodeB���������ӣ���֮��Ϊ�Һ���
		2)		�����ӵĸ���� �޸�Ϊ ��ǰ���ĸ����
				pNode->m_pLeft->m_pParent = pNode->m_pParent;
		*/
		pParent->m_pLeft == pNodeB ? pParent->m_pLeft = pNodeA : pParent->m_pRight = pNodeA;
		pNodeA->m_pParent = pParent;
	}

	// ������ pNodeA �����Һ��ӣ���ת�������Һ��� pNodeC ��Ϊ pNodeB ������
	pNodeB->m_pLeft = pNodeC;
	if (pNodeC != nullptr)
	{
		pNodeC->m_pParent = pNodeB;
	}

	pNodeB->m_pParent = pNodeA;
	pNodeA->m_pRight = pNodeB;

	// ���¼�����Ӱ��Ľ��߶�ֵ
	pNodeA->m_nNodeHeight = CalcNodeHeight(pNodeA);
	pNodeB->m_nNodeHeight = CalcNodeHeight(pNodeB);
}