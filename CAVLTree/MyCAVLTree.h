#pragma once
/*=======================================================
*		o(*������*)o
*		Project Name������ƽ���� ������
*		FileName��AVLTree.h
*		Start Date��2020/06/08
*		Last UpDate��2020/06/10
========================================================*/

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template<typename T>
class CAVLTree	
{
private:
	// ���������
	typedef struct tagNode
	{
		tagNode(T val, 
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
		T m_val; // ��ǰ��㱣�������
		int m_nNodeHeight; // ���н��ĸ߶�
		tagNode* m_pParent; // ָ�򸸽��
		tagNode* m_pLeft; // ��ǰ��������
		tagNode* m_pRight; // ��ǰ�����Һ���
	}NODE, * PNODE;

public:
	CAVLTree();
	CAVLTree(const  CAVLTree& bst);

	CAVLTree& operator=(const CAVLTree& bst);
	virtual ~CAVLTree();

public:
	// ��������
	bool Insert(T val);	// �������� val
	bool Remove(T val);	// ɾ������ val
	bool Updata(T valSrc, T valDst); // ��ԭ������ϵ���ֵ�����µ���ֵ
	bool Find(T val); // ���� ���� val
	void Clear();

	// ʹ�õݹ�������ݣ�ǰ�����򡢺�����
	void MLR();	// ǰ��������ݹ飩middle left right
	void LMR();	// ����������ݹ飩left middle right
	void LRM();	// ����������ݹ飩left right middle

	// ʹ�÷ǵݹ飨ʹ��ѭ�����������ݣ�ǰ�����򡢺�����
	void MLRUseLoop(); // ǰ��������ǵݹ飩middle left right
	void LMRUseLoop(); // ����������ǵݹ� left middle right
	void LRMUseLoop(); // ����������ǵݹ� left right middle

	void Level(); // �������

	int GetNodeSize()const;	// ��ȡ���н�����
private:
	void Destroy(PNODE pNode); // ������
	PNODE FindNode(T val); // ���ҽ��
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
	static int m_pNodeSize;	// ���н�����
};

template<typename T>
int CAVLTree<T>::m_pNodeSize = 0; // ��ʼ�����н�����

/*=======================================================
*	�������ܣ��޲ι��죬��ʼ����
*	��������
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
CAVLTree<T>::CAVLTree()
{
	m_pRoot = nullptr;
}


/*=======================================================
*	�������ܣ���������
*	�������ѳ�ʼ���������
*	����ֵ��Nothing
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
CAVLTree<T>::CAVLTree(const CAVLTree& bst)
{
	*this = bst;
}


/*=======================================================
*	�������ܣ���������� =
*	�������ѳ�ʼ���������
*	����ֵ��*this
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
CAVLTree<T>& CAVLTree<T>::operator=(const CAVLTree& bst)
{
	if (this == &bst)
	{
		return *this; // ����Լ����Լ���ֵ��ʲôҲ����
	}

	// ����Լ��ĸ����������
	Clear();

	if (bst.m_pRoot == nullptr)
	{
		return *this; // �����ֵ��Ϊ�����������и�ֵ
	}

	// ��ֵ
	queue<PNODE> queTemp; // ��ʼ��һ������
	queTemp.push(bst.m_pRoot); // ��������

	// ����Ϊ�գ��˳�ѭ��
	while (!queTemp.empty())
	{
		PNODE pNode = queTemp.front(); // �����׸�ֵ�� pNode
		queTemp.pop();	// �����׵���
		Insert(pNode->m_val);

		if (pNode->m_pLeft != nullptr) // ���ӵĽ������Ӳ�Ϊ�գ��ͽ����������
		{
			queTemp.push(pNode->m_pLeft);
		}
		if (pNode->m_pRight != nullptr) // ���ӵĽ����Һ��Ӳ�Ϊ�գ��ͽ����Һ������
		{
			queTemp.push(pNode->m_pRight);
		}
	}

	return *this;
}


/*=======================================================
*	�������ܣ�������������� Clear() �����ͷŶ�Ӧ������
*	��������
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
CAVLTree<T>::~CAVLTree()
{
	Clear();
}


/*=======================================================
*	�������ܣ���������
*	������val -- ���������ֵ
*	����ֵ��
		true -- ���ݲ���ɹ�
		false -- ���ݲ���ʧ��
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
bool CAVLTree<T>::Insert(T val)
{
	if (m_pRoot == nullptr)
	{
		// �����Ϊ�գ������������Ϊ����㣬ͬʱ���ڵ�ĸ߶���Ϊ0
		m_pRoot = (PNODE)new NODE(val, 0, nullptr, nullptr, nullptr);
		m_pNodeSize++;
		return 0;
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
				m_pNodeSize++;
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
				m_pNodeSize++;
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
			cout << "ID�Ѵ���" << endl;
			return false; // ��ʱ��������ȵ����
		}
	}
	return true;
}


/*=======================================================
*	�������ܣ�ɾ��ָ��������
*	������val -- ɾ��������ֵ
*	����ֵ��
		true -- ����ɾ���ɹ�
		false -- ����ɾ��ʧ��
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
bool CAVLTree<T>::Remove(T val)
{
	// ���ҽ�Ҫ��ɾ���Ľ��
	PNODE pNodeTodel = FindNode(val);

	if (pNodeTodel == nullptr)
	{
		// pNodeTodel Ϊ�� ����ʧ�� ���� false
		return false;
	}

	// ���ҳɹ������ݽ������������һ������
	DelNode(pNodeTodel);
	return true;
}


/*=======================================================
*	�������ܣ������д��ڵ���ֵ valSrc �޸�Ϊ valDst
*	������
		valSrc -- ���޸ĵ�����ֵ
		valDst -- �޸ĺ������ֵ
*	����ֵ��
		false -- ���ݲ���/�޸�ʧ��
		true -- �����޸ĳɹ�
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
bool CAVLTree<T>::Updata(T valSrc, T valDst)
{
	if (m_pRoot == nullptr)
	{
		return false; // �����ǰ��Ϊ�գ�����false
	}

	PNODE pChangeNode = FindNode(valSrc); // �����Ƿ���� valSrc

	if (pChangeNode == nullptr)
	{
		return false; // pNodeTodel Ϊ�� ����ʧ�� ���� false
	}

	//pChangeNode->m_val = valDst; // ֱ���޸ģ�����ȡ���ᵼ�¸�������һ��������

	Remove(valSrc);	// ��ֵ���ҳɹ���ɾ�����
	Insert(valDst);	// ���µ���ֵ���²��뵽������

	return true;
}


/*=======================================================
*	�������ܣ�����ָ��������ֵ
*	������val -- ���ҵ�����ֵ
*	����ֵ��
		true -- ���ݲ��ҳɹ�
		false -- ���ݲ���ʧ��
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
bool CAVLTree<T>::Find(T val)
{
	if (m_pRoot == nullptr)
	{
		return false; // �����ǰ��Ϊ�գ�����false
	}

	PNODE pChangeNode = FindNode(val); // ���������Ƿ������ֵ val
	if (pChangeNode == nullptr)
	{
		return false; // pNodeTodel Ϊ�� ����ʧ�� ���� false
	}
	return true; // pNodeTodel ��Ϊ�� ���ҳɹ� ���� true
}


/*=======================================================
*	�������ܣ��������������Ч�Ľ��
*	��������
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::Clear()
{
	while (m_pRoot != nullptr)
	{
		DelNode(m_pRoot); // ���н��ɾ����Ϻ�ѭ����ֹ
	}
}


/*=======================================================
*	�������ܣ��ݹ� ǰ�� ���� ������Ϊ�գ�����MLR()������
*	��������
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::MLR()
{
	if (m_pRoot != nullptr)
	{
		MLR(m_pRoot); // ���� ǰ�� ����
	}
}


/*=======================================================
*	�������ܣ��ݹ� ���� ���� ������Ϊ�գ�����LMR()������
*	��������
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::LMR()
{
	if (m_pRoot != nullptr)
	{
		LMR(m_pRoot); // ���� ���� ����
	}
}


/*=======================================================
*	�������ܣ��ݹ� ���� ���� ������Ϊ�գ�����LRM()������
*	��������
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::LRM()
{
	if (m_pRoot != nullptr)
	{
		LRM(m_pRoot); // ���� ���� ����
	}
}


/*=======================================================
*	�������ܣ�ǰ��������ǵݹ飩
*	��������
*	����ֵ����
*	���������������Ч�����洢������ֵ
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::MLRUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;	// ���Ϊ�����������б���
	}

	stack<PNODE> stkTemp; // ��ʼ��һ��ջ
	PNODE pNode = m_pRoot; // �洢�����

	while (true)
	{
		while (pNode != nullptr)
		{
			cout << pNode->m_val << " "; // �������
			stkTemp.push(pNode->m_pRight); // ������ݽ����Һ�����ջ
			pNode = pNode->m_pLeft;	// ���� pNode ��㣬һֱ���������ջ
		}

		if (stkTemp.empty())
		{
			break; // ջΪ�գ����е��Һ��������ϣ�����ѭ��
		}

		pNode = stkTemp.top(); // ���������ϣ������ָ��ջ��
		stkTemp.pop(); // ͬʱ��ջ�������ݽ��е���
	}
}


/*=======================================================
*	�������ܣ�����������ǵݹ飩
*	��������
*	����ֵ����
*	���������������Ч�����洢������ֵ
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::LMRUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;	// �����Ϊ�գ������б���
	}

	stack<PNODE> stkTemp; // ��ʼ��һ��ջ
	PNODE pNode = m_pRoot;// �����ڵ㸳ֵ�� pNode

	while (true)
	{
		while (pNode != nullptr)
		{
			stkTemp.push(pNode); // ���������ջ
			pNode = pNode->m_pLeft;	// pNode ָ��������
		}

		if (stkTemp.empty())
		{
			break; // ջ��ѭ������
		}

		// ���û�����ӿ�����ջ���ͽ�ջ�ڵ����ݵ�����һ��
		pNode = stkTemp.top(); // pNode ָ�� ջ��
		stkTemp.pop(); // ��ջ������һ������
		cout << pNode->m_val << " "; // �������������

		// ������������ݵ��Һ���
		pNode = pNode->m_pRight;
	}

}


/*=======================================================
*	�������ܣ�����������ǵݹ飩
*	��������
*	����ֵ����
*	���������������Ч�����洢������ֵ
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::LRMUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;	// �����Ϊ�գ������б���
	}

	stack<PNODE> stkTemp; // ��ʼ��һ��ջ
	PNODE pNode = m_pRoot; // �� �� m_pRoot ��ֵ�� pNode
	PNODE pPreDisposeNode = nullptr; // ������һ�δ���Ľ��

	while (true)
	{
		while (pNode != nullptr)
		{
			stkTemp.push(pNode); // ���ĸ������ջ
			pNode = pNode->m_pLeft;	// ���� pNode ��㣬һֱ���������ջ
		}

		if (stkTemp.empty())
		{
			break; // ջΪ�գ����е��Һ��������ϣ�����ѭ��
		}

		pNode = stkTemp.top(); // ָ��ջ��

		if (pNode->m_pRight == pPreDisposeNode || pNode->m_pRight == nullptr)
		{
			cout << pNode->m_val << " ";

			pPreDisposeNode = pNode; // ���洦���Ľ��
			stkTemp.pop(); // �������Ľ�㵯��

			pNode = nullptr; // ����Ľ�㴦�����˵�����Һ����Ѿ����������
			continue; // ���ﲻ��Ҫ�ٽ� pNode ָ��ý����Һ���
		}
		pNode = pNode->m_pRight; // �����Һ���
	}
}

/*=======================================================
*	�������ܣ��������
*	��������
*	����ֵ����
*	���������������Ч�����洢������ֵ
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::Level()
{
	if (m_pRoot == nullptr)
	{
		return;	// ���Ϊ�����������б���
	}

	queue<PNODE> queTemp; // ��ʼ��һ������
	queTemp.push(m_pRoot); // ��������

	// ����Ϊ�գ��˳�ѭ��
	while (!queTemp.empty())	
	{
		PNODE pNode = queTemp.front(); // �����׸�ֵΪ pNode
		queTemp.pop();	// �����׵���
		cout << pNode->m_val << " "; // �����������ݽ������

		if (pNode->m_pLeft != nullptr) // ���ӵĽ������Ӳ�Ϊ�գ��ͽ����������
		{
			queTemp.push(pNode->m_pLeft);
		}
		if (pNode->m_pRight != nullptr) // ���ӵĽ����Һ��Ӳ�Ϊ�գ��ͽ����Һ������
		{
			queTemp.push(pNode->m_pRight);
		}
#if 0
		if (pNode != nullptr)
		{
			cout << pNode->m_val << " "; // ����������
			queTemp.push(pNode->m_pLeft); // ���ӽ������� �� �Һ������
			queTemp.push(pNode->m_pRight);
		}
#endif // ���ӽ��� ���� �� �Һ���  ��ӣ���д����
	}
}

template<typename T>
inline int CAVLTree<T>::GetNodeSize() const
{
	return m_pNodeSize;
}


/*=======================================================
*	�������ܣ�ʹ�õݹ����������Ч�����н��
*	������PNODE pNode -- ���ĸ����
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::Destroy(PNODE pNode)
{
	if (pNode != nullptr)
	{
		Destroy(pNode->m_pLeft); // ���ٸ�������
		Destroy(pNode->m_pRight); // ���ٸ����Һ���

		delete pNode; // ���ٸ�
		pNode = nullptr;
	}
}


/*=======================================================
*	�������ܣ��������������ֵ���������Ƿ���ڶ�Ӧ������
*	������val -- ���ҵ�����ֵ
*	����ֵ��pTempNode ���ز鵽�Ĵ洢�����ݵĽ��
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
typename CAVLTree<T>::PNODE CAVLTree<T>::FindNode(T val)
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
*	�������ܣ�ɾ����㣬���ݽ�����ͽ��ж�Ӧ��ɾ��
*	������PNODE pNode -- Ҫɾ������������Ӧ�Ľ��
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::DelNode(PNODE pNode)
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
*	�������ܣ�ɾ���Ľ��ΪҶ�ӽ�㣨�ý��û�����Һ��ӣ�
*	������PNODE pNode -- Ҫɾ������������Ӧ�Ľ��
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::DelLeaf(PNODE pNode)
{
	PNODE pParent = pNode->m_pParent; // ���浱ǰ���ĸ����

	if (pNode == m_pRoot)// �����ǰ����Ǹ���㣬��ɾ���ý��
	{
		delete m_pRoot;
		m_pRoot = nullptr;
		m_pNodeSize--;
		return;
	}

	// �ж�Ҫɾ���Ľ���Ǹ�����µ� ���� ���� �Һ���
	if (pParent->m_pLeft == pNode)
	{
		pParent->m_pLeft = nullptr; // ��������ӣ��������ӵĽ���ÿ�
	}
	else
	{
		pParent->m_pRight = nullptr; // ������Һ��ӣ������Һ��ӵĽ���ÿ�
	}

	delete pNode; // ɾ���˽��
	pNode = nullptr;
	m_pNodeSize--;

	// ���ɾ���󣬴�ɾ�����ĸ���㿪ʼ���������е����߶�
	AdjustHeight(pParent);
}


/*=======================================================
*	�������ܣ�ɾ���Ľ��Ϊ����֧��㣨�ý����һ������ ����/�Һ��ӣ�
*	������PNODE pNode -- Ҫɾ������������Ӧ�Ľ��
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::DelSingleChildNode(PNODE pNode)
{
	PNODE pParent = pNode->m_pParent; // ���浱ǰ���ĸ����

	PNODE pChild = pNode->m_pLeft; // Ĭ�ϱ��浱ǰ��������

	if (pChild == nullptr)
	{
		pChild = pNode->m_pRight; // �������Ϊ�գ�˵���õ���֧���ֻ���Һ��ӣ������к���
	}

	// �жϴ˽���Ƿ��Ǹ����
	if (pNode == m_pRoot)
	{
		// ���ý������ӻ����к�����Ϊ�����
		m_pRoot = pChild;
		// �ÿ�
		pChild->m_pParent = nullptr;
		// ɾ����ǰ���
		delete pNode;
		pNode = nullptr;
		m_pNodeSize--;
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
	m_pNodeSize--;

	// ���ɾ���󣬴�ɾ�����ĸ���㿪ʼ���������е����߶�
	AdjustHeight(pParent);
}


/*=======================================================
*	�������ܣ�ɾ���Ľ��Ϊ˫��֧��㣨�ý������������ ���Ӻ��Һ��ӣ�
*	������PNODE pNode -- Ҫɾ�����ݶ�Ӧ�Ľ��
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::DelDoubleChildNode(PNODE pNode)
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
*	�������ܣ��ݹ� ǰ�� ����
*	������PNODE pNode -- ��ʼ�����ĸ����
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::MLR(PNODE pNode)
{
	// �ݹ�ĳ���
	if (pNode == nullptr)
	{
		return;
	}
	cout << pNode->m_val << " "; // ���Լ�
	MLR(pNode->m_pLeft); // ������
	MLR(pNode->m_pRight); // ���Һ���
}


/*=======================================================
*	�������ܣ��ݹ� ���� ����
*	������PNODE pNode -- ��ʼ�����ĸ����
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::LMR(PNODE pNode)
{
	// �ݹ�ĳ���
	if (pNode == nullptr)
	{
		return;
	}

	LMR(pNode->m_pLeft); // ������
	cout << pNode->m_val << " "; // ���Լ�
	LMR(pNode->m_pRight); // ���Һ���
}


/*=======================================================
*	�������ܣ��ݹ� ���� ����
*	������PNODE pNode -- ��ʼ�����ĸ����
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::LRM(PNODE pNode)
{
	// �ݹ�ĳ���
	if (pNode == nullptr)
	{
		return;
	}

	LRM(pNode->m_pLeft); // ������
	LRM(pNode->m_pRight); // ���Һ���
	cout << pNode->m_val << " "; // ���Լ�
}


/*=======================================================
*	�������ܣ�ÿ�β������ݣ��жϵ�ǰ���Ƿ�ƽ��ͬʱ���������߶�
*	������PNODE pNode -- ��������ݵĸ����
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::AdjustHeight(PNODE pNode)
{
	// ������Ľ�����ݸ�ֵ����ʱ���pTempNode
	PNODE pTempNode = pNode;	

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
					��ʱ��Ҫ������ͼ�� B ������ �ҵ�����Ȼ�����Խ�� A ����������
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
					��ʱ��Ҫ������ͼ�� A ������ ������Ȼ�����Խ�� B �����ҵ�����
					��˫���󣬴�ʱ��ǰ������ƽ��״̬
				*/

				// ��ȡ��ת�Ľ��
				PNODE pNodeB = pTempNode;
				PNODE pNodeA = pTempNode->m_pLeft;

				RotateLeft(pNodeA); // ������
				RotateRight(pNodeB); // ������
			}
		}
		// �����ǰ���ƽ�⣬�����ж��丸����Ƿ���ƽ��״̬
		pTempNode = pTempNode->m_pParent;
	}
}


/*=======================================================
*	�������ܣ����㴫����ĸ߶�
*	������PNODE pNode -- ��Ҫ����߶ȵĽ��
*	����ֵ�����ؽ��ĸ߶�ֵ
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
int CAVLTree<T>::CalcNodeHeight(PNODE pNode)
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
*	�������ܣ���ȡ���߶�
*	������PNODE pNode -- ��Ҫ��ȡ�߶ȵĽ��
*	����ֵ�����ؽ��ĸ߶�ֵ
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
int CAVLTree<T>::GetNodeHeight(PNODE pNode) const
{
	if (pNode == nullptr)
	{
		return -1; // ���Ϊ�գ����� -1
	}
	return pNode->m_nNodeHeight;
}


/*=======================================================
*	�������ܣ���������������ƽ��
*	������PNODE pNode -- ��Ҫ������ת�Ľ��
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::RotateLeft(PNODE pNode)
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
		pNodeB->m_pParent = nullptr; // ��ʱ��� B ��ͷ���Ϊ nullptr
	}
	// ���Ǹ��ڵ�
	else
	{
		/*
		1) �����תǰ��������丸�������ӣ��ͽ���ת��ĸ���� pNodeB
			��Ϊ pNodeA ���������ӣ���֮��Ϊ�Һ���
		2) ��ת���޸���ת�����Ľ��ĸ����
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
*	�������ܣ��ҵ�������������ƽ��
*	������PNODE pNode -- ��Ҫ������ת�Ľ��
*	����ֵ����
*	���棺��
*	���£�2020/06/10
========================================================*/
template<typename T>
void CAVLTree<T>::RotateRight(PNODE pNode)
{
	/*
	��ʱ�ӵ�ǰ��㴦��ʼ��ƽ��
	ʾ����P --> ���ڵ� B ��ͷ�ڵ㣬 X Ϊ�²���Ľ�㣬���Կ�����ʱ��� B ���ֲ�ƽ��
	��������ӵĸ߶ȼ�ȥ�Һ��ӵĸ߶Ȳ�ľ���ֵС�� -1 ʱ����Ҫ��������ת���Ӳ�ƽ��㿪ʼ��ת��
			��תǰ					��ת��
				P						P
				B						A
			A		D				T		B
		T		C(RA)			X		C(lB)	D(RB)
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
		pNodeA->m_pParent = nullptr; // ����� pNodeA �ĸ����Ϊ nullptr
	}
	else
	{
		/*
		1) �����תǰ��������丸�������ӣ��ͽ���ת��ĸ���� pNodeA
			��ΪpNodeB���������ӣ���֮��Ϊ�Һ���
		2) �����ӵĸ���� �޸�Ϊ ��ǰ���ĸ����
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