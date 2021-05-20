#include "CBinarySearchTree.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

/*=======================================================
*	CBinarySearchTree::CBinarySearchTree() -- �޲ι��죬��ʼ����
*
*	��������
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
CBinarySearchTree::CBinarySearchTree()
{
	m_pRoot = nullptr;
}


/*=======================================================
*	CBinarySearchTree(const CBinarySearchTree& bst) -- ��������
*
*	�������ѳ�ʼ���������
*
*	����ֵ��Nothing
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
CBinarySearchTree::CBinarySearchTree(const CBinarySearchTree& bst)
{
	*this = bst;
}


/*=======================================================
*	CBinarySearchTree::operator=(const CBinarySearchTree& bst) -- ��������� =
*
*	�������ѳ�ʼ���������
*
*	����ֵ��*this
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
CBinarySearchTree& CBinarySearchTree::operator=(const CBinarySearchTree& bst)
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

	while (!queTemp.empty())	// ����Ϊ�գ��˳�ѭ��
	{
		PNODE pNode = queTemp.front();	// �����׸�ֵ�� pNode
		queTemp.pop();	// �����׵���
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
*	~CBinarySearchTree() -- ������������� Clear() �����ͷŶ�Ӧ������
*
*	��������
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
CBinarySearchTree::~CBinarySearchTree()
{
	Clear();
}


/*=======================================================
*	bool CBinarySearchTree::Insert(int val) -- ��������
*
*	������val -- ���������ֵ
*
*	����ֵ��true -- ���ݲ���ɹ���false -- ���ݲ���ʧ��
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
bool CBinarySearchTree::Insert(int val)
{
	if (m_pRoot == nullptr)
	{
		// �����Ϊ�գ������������Ϊ����㣬ͬʱ���ڵ�ĸ߶���Ϊ0
		m_pRoot = (PNODE)new NODE(val, nullptr, nullptr, nullptr);
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
				pTempNode->m_pLeft = new NODE(val, pTempNode, nullptr, nullptr);

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
				pTempNode->m_pRight = new NODE(val, pTempNode, nullptr, nullptr);

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
*	bool CBinarySearchTree::Remove(int val) -- ɾ��ָ��������
*
*	������val -- ɾ��������ֵ
*
*	����ֵ��true -- ����ɾ���ɹ���false -- ����ɾ��ʧ��
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
bool CBinarySearchTree::Remove(int val)
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
*	bool CBinarySearchTree::Updata(int valSrc, int valDst) -- �޸�����
*
*	������valSrc -- ���޸ĵ�����ֵ��valDst -- �޸ĺ������ֵ
*
*	����ֵ��false -- ���ݲ���/�޸�ʧ�ܣ�true -- �����޸ĳɹ�
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
// �����д��ڵ���ֵ valSrc �޸�Ϊ valDst
bool CBinarySearchTree::Updata(int valSrc, int valDst)
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
	Insert(valDst);	// ���µ���ֵ���²��뵽������

	return true;
}


/*=======================================================
*	bool CBinarySearchTree::Find(int val) -- ����ָ��������ֵ
*
*	������val -- ���ҵ�����ֵ
*
*	����ֵ��true -- ���ݲ��ҳɹ���false -- ���ݲ���ʧ��
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
bool CBinarySearchTree::Find(int val)
{
	if (m_pRoot == nullptr)
	{
		return false;	// �����ǰ��Ϊ�գ�����false
	}

	PNODE pChangeNode = FindNode(val);	// ���������Ƿ������ֵ val
	if (pChangeNode == nullptr)
	{
		return false;	// pNodeTodel Ϊ�� ����ʧ�� ���� false
	}
	return true;		// pNodeTodel ��Ϊ�� ���ҳɹ� ���� true
}


/*=======================================================
*	void CBinarySearchTree::Clear() -- �������������Ч�Ľ��
*
*	��������
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::Clear()
{
	while (m_pRoot != nullptr)
	{
		DelNode(m_pRoot);	// ���н��ɾ����Ϻ�ѭ����ֹ
	}
}

/*=======================================================
*	void CBinarySearchTree::MLR() -- �ݹ� ǰ�� ����������Ϊ�գ�����MLR()������
*
*	��������
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::MLR()
{
	if (m_pRoot != nullptr)
	{
		MLR(m_pRoot);	// ���� ǰ�� ����
	}
}

/*=======================================================
*	void CBinarySearchTree::LMR() -- �ݹ� ���� ����������Ϊ�գ�����LMR()������
*
*	��������
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::LMR()
{
	if (m_pRoot != nullptr)
	{
		LMR(m_pRoot);	// ���� ���� ����
	}
}

/*=======================================================
*	void CBinarySearchTree::LRM() -- �ݹ� ���� ����������Ϊ�գ�����LRM()������
*
*	��������
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::LRM()
{
	if (m_pRoot != nullptr)
	{
		LRM(m_pRoot);	// ���� ���� ����
	}
}


/*=======================================================
*	void CBinarySearchTree::MLRUseLoop() -- ǰ��������ǵݹ飩
*
*	��������
*
*	����ֵ����
*
*	���������������Ч�����洢������ֵ
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::MLRUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;	// ���Ϊ�����������б���
	}

	stack<PNODE> stkTemp;	// ��ʼ��һ��ջ
	PNODE pNode = m_pRoot;	// �洢�����

	while (true)
	{
		while (pNode != nullptr)
		{
			cout << pNode->m_val << " ";	// �������
			stkTemp.push(pNode->m_pRight);	// ������ݽ����Һ�����ջ
			pNode = pNode->m_pLeft;	// ���� pNode ��㣬һֱ���������ջ
		}

		if (stkTemp.empty())
		{
			break;	// ջΪ�գ����е��Һ��������ϣ�����ѭ��
		}

		pNode = stkTemp.top();	// ���������ϣ������ָ��ջ��
		stkTemp.pop();	// ͬʱ��ջ�������ݽ��е���
	}
}


/*=======================================================
*	void CBinarySearchTree::LMRUseLoop() -- ����������ǵݹ飩
*
*	��������
*
*	����ֵ����
*
*	���������������Ч�����洢������ֵ
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::LMRUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;	// �����Ϊ�գ������б���
	}

	stack<PNODE> stkTemp;	// ��ʼ��һ��ջ
	PNODE pNode = m_pRoot;	// �����ڵ㸳ֵ�� pNode

	while (true)
	{
		while (pNode != nullptr)
		{
			stkTemp.push(pNode);	// ���������ջ
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
*	void CBinarySearchTree::LRMUseLoop() -- ����������ǵݹ飩
*
*	��������
*
*	����ֵ����
*
*	���������������Ч�����洢������ֵ
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::LRMUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;	// �����Ϊ�գ������б���
	}

	stack<PNODE> stkTemp;	// ��ʼ��һ��ջ
	PNODE pNode = m_pRoot;	// �� �� m_pRoot ��ֵ�� pNode
	PNODE pPreDisposeNode = nullptr;	// ������һ�δ���Ľ��

	while (true)
	{
		while (pNode != nullptr)
		{
			stkTemp.push(pNode);	// ���ĸ������ջ
			pNode = pNode->m_pLeft;	// ���� pNode ��㣬һֱ���������ջ
		}

		if (stkTemp.empty())
		{
			break;	// ջΪ�գ����е��Һ��������ϣ�����ѭ��
		}

		pNode = stkTemp.top();	// ָ��ջ��

		if (pNode->m_pRight == pPreDisposeNode || pNode->m_pRight == nullptr)
		{
			cout << pNode->m_val << " ";

			pPreDisposeNode = pNode;	// ���洦���Ľ��
			stkTemp.pop();	// �������Ľ�㵯��

			pNode = nullptr;	// ����Ľ�㴦�����˵�����Һ����Ѿ����������
			continue;	// ���ﲻ��Ҫ�ٽ� pNode ָ��ý����Һ���
		}
		pNode = pNode->m_pRight;	// �����Һ���
	}
}

/*=======================================================
*	void CBinarySearchTree::Level() -- �������
*
*	��������
*
*	����ֵ����
*
*	���������������Ч�����洢������ֵ
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::Level()
{
	if (m_pRoot == nullptr)
	{
		return;	// ���Ϊ�����������б���
	}

	queue<PNODE> queTemp;	// ��ʼ��һ������
	queTemp.push(m_pRoot);	// ��������

	while (!queTemp.empty())	// ����Ϊ�գ��˳�ѭ��
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
*	void CBinarySearchTree::Destroy(PNODE pNode)
*	-- ʹ�õݹ����������Ч�����н��
*	������PNODE pNode -- ���ĸ����
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::Destroy(PNODE pNode)
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
*	PNODE CBinarySearchTree::FindNode(int val)
*	-- �������������ֵ���������Ƿ���ڶ�Ӧ������
*	������val -- ���ҵ�����ֵ
*
*	����ֵ��pTempNode ���ز鵽�Ĵ洢�����ݵĽ��
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
typename CBinarySearchTree::PNODE CBinarySearchTree::FindNode(int val)
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
*	void CBinarySearchTree::DelNode(PNODE pNode)
*	-- ɾ����㣬���ݽ�����ͽ��ж�Ӧ��ɾ��
*	������PNODE pNode -- Ҫɾ������������Ӧ�Ľ��
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::DelNode(PNODE pNode)
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
*	void CBinarySearchTree::DelLeaf(PNODE pNode)
*	-- ɾ���Ľ��ΪҶ�ӽ�㣨�ý��û�����Һ��ӣ�
*	������PNODE pNode -- Ҫɾ������������Ӧ�Ľ��
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::DelLeaf(PNODE pNode)
{
	PNODE pParent = pNode->m_pParent;	// ���浱ǰ���ĸ����

	if (pNode == m_pRoot)	// �����ǰ����Ǹ���㣬��ɾ���ý��
	{
		delete m_pRoot;
		m_pRoot = nullptr;
		return;
	}

	// �ж�Ҫɾ���Ľ���Ǹ�����µ� ���� ���� �Һ���
	if (pParent->m_pLeft == pNode)
	{
		pParent->m_pLeft = nullptr;	// ��������ӣ��������ӵĽ���ÿ�
	}
	else
	{
		pParent->m_pRight = nullptr;	// ������Һ��ӣ������Һ��ӵĽ���ÿ�
	}

	delete pNode;	// ɾ���˽��
	pNode = nullptr;
}


/*=======================================================
*	void CBinarySearchTree::DelSingleChildNode(PNODE pNode)
*	-- ɾ���Ľ��Ϊ����֧��㣨�ý����һ������ ����/�Һ��ӣ�
*	������PNODE pNode -- Ҫɾ������������Ӧ�Ľ��
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::DelSingleChildNode(PNODE pNode)
{
	PNODE pParent = pNode->m_pParent;	// ���浱ǰ���ĸ����

	PNODE pChild = pNode->m_pLeft;	// Ĭ�ϱ��浱ǰ��������

	if (pChild == nullptr)
	{
		pChild = pNode->m_pRight;	// �������Ϊ�գ�˵���õ���֧���ֻ���Һ��ӣ������к���
	}

	// �жϴ˽���Ƿ��Ǹ����
	if (pNode == m_pRoot)
	{
		m_pRoot = pChild;	// ���ý������ӻ����к�����Ϊ�����
		pChild->m_pParent = nullptr;	// �ÿ�
		delete pNode;	// ɾ����ǰ���
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
}


/*=======================================================
*	void CBinarySearchTree::DelSingleChildNode(PNODE pNode)
*	-- ɾ���Ľ��Ϊ˫��֧��㣨�ý������������ ���Ӻ��Һ��ӣ�
*	������PNODE pNode -- Ҫɾ�����ݶ�Ӧ�Ľ��
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::DelDoubleChildNode(PNODE pNode)
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
*	void CBinarySearchTree::MLR(PNODE pNode) -- �ݹ� ǰ�� ����
*
*	������PNODE pNode -- ��ʼ�����ĸ����
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::MLR(PNODE pNode)
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
*	void CBinarySearchTree::LMR(PNODE pNode) -- �ݹ� ���� ����
*
*	������PNODE pNode -- ��ʼ�����ĸ����
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::LMR(PNODE pNode)
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
*	void CBinarySearchTree::LRM(PNODE pNode) -- �ݹ� ���� ����
*
*	������PNODE pNode -- ��ʼ�����ĸ����
*
*	����ֵ����
*
*	���棺��
*
*	���£�2020/06/08
*
========================================================*/
void CBinarySearchTree::LRM(PNODE pNode)
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