#pragma once
#include <cassert>

template<typename T>
class CList
{
private:
	// ˫������Ľ��
	typedef struct tagNode
	{
		tagNode(T val) : m_val(val), m_pPre(nullptr), m_pNext(nullptr) {}
		tagNode() : m_pPre(nullptr), m_pNext(nullptr) {}
		T m_val;	// ���������
		tagNode* m_pPre;		// ָ����һ������ָ�룬ǰ��
		tagNode* m_pNext;	// ָ����һ������ָ�룬���
	}NODE, * PNODE;

public:
	class iterator
	{
	private:
		friend class CList;
	public:
		// ���� ǰ��++ �����
		iterator& operator++()
		{
			// �жϵ�ǰ��� �Ƿ��� β���ڱ����
			assert(m_pNode != m_pTailGuard);

			m_pNode = m_pNode->m_pNext;
			return *this;
		}

		// ���� ����++ �����
		iterator operator++(int)
		{
			// �жϵ�ǰ��� �Ƿ��� β���ڱ����
			assert(m_pNode != m_pTailGuard);

			m_pNode = m_pNode->m_pNext;

			// �����޸�ǰ�Ľ��
			return iterator(m_pNode->m_pPre, m_pHeadGuard, m_pTailGuard);
		}

		// ���� ǰ��-- �����
		iterator& operator--()
		{
			// �жϵ�ǰ�ڵ� �Ƿ��� ͷ���ڱ����
			assert(m_pNode->m_pPre != m_pHeadGuard);

			m_pNode = m_pNode->m_pPre;
			return *this;
		}

		// ���� ǰ��-- �����
		iterator operator--(int)
		{
			assert(m_pNode->m_pPre != m_pHeadGuard);
			m_pNode = m_pNode->m_pPre;

			// ���� -- ֮ǰ�Ľ��
			return iterator(m_pNode->m_pNext, m_pHeadGuard, m_pTailGuard);
		}

		// ���� * �����
		int& operator*()
		{
			return m_pNode->m_val;
		}

		// ���� == �����
		bool operator==(const iterator& itr)
		{
			return m_pNode == itr.m_pNode;
		}

		// ���� != �����
		bool operator!=(const iterator& itr)
		{
			return m_pNode != itr.m_pNode;
		}

	private:
		// ����ʹ���ߴ��� pNode ָ�룬���ù�������Ϊ˽��
		iterator(PNODE pNode, PNODE pHeadGuard, PNODE pTailGuard) :
			m_pNode(pNode),
			m_pHeadGuard(m_pHeadGuard),
			m_pTailGuard(pTailGuard)
		{
		}
	private:
		PNODE m_pNode;
		PNODE m_pHeadGuard;	// ͷ���ڱ�
		PNODE m_pTailGuard;	// β���ڱ�
	};

public:
	iterator begin();
	iterator end();
public:
	CList();
	/*
	���������Զ����ɿ��������Լ����������=
	Ĭ������Ϊǳ�������������������
	*/
	CList(const CList& list);	// ��������
	CList& operator=(const CList& list);	// ��������� =
	virtual ~CList();

public:
	// ����
	bool AddHead(T val);
	bool AddTail(T val);
	bool Insert(iterator pNode, T val);
	// �����˽���ָ�룬�����߿��Զ��������ϵ����ݽ���������޸ģ��ƻ�����ķ�װ��

	// �޸�
	bool SetVal(iterator pNode, T val);	// �����˽���ָ�룬�ƻ�����ķ�װ��

	// ɾ��
	bool RemoveHead();
	bool RemoveTail();
	bool Remove(iterator pNode);	// �����˽���ָ�룬�ƻ�����ķ�װ��

	// ��ѯ
	iterator Find(T val);	// ����ֵΪһ������ָ�� 

	// �жϸ������Ƿ���һ��������
	bool IsNull();

	// ���ĸ���
	int NodeSize();

	// �������
	void Clear();

private:
	void InitList();
private:
	PNODE m_pHeadGuard;	// ���������ͷ���ڱ�
	PNODE m_pTailGuard;	// ���������β���ڱ�
	int m_nNodeSize;	// �����н��ĸ���
};

template<typename T>
typename CList<T>::iterator CList<T>::begin()
{
	return iterator(m_pHeadGuard->m_pNext, m_pHeadGuard, m_pTailGuard);
}

template<typename T>
typename CList<T>::iterator CList<T>::end()
{
	return iterator(m_pTailGuard, m_pHeadGuard, m_pTailGuard);
}

template<typename T>
CList<T>::CList()
{
	InitList();
}

template<typename T>
CList<T>::CList(const CList& list)
{
	// ��Ҫ���ڱ��Ͷ�Ӧ�Ľ���������
	InitList();

	// ����������� =
	*this = list;
}

template<typename T>
CList<T>& CList<T>::operator=(const CList& list)
{
	// �ж��ǲ����Լ����Լ���ֵ
	if (this == &list)
	{
		return *this;
	}

	// ������Լ�
	Clear();

	// ѭ����������
	PNODE pNode = list.m_pHeadGuard->m_pNext;
	while (pNode != list.m_pTailGuard)
	{
		AddTail(pNode->m_val);	// ���Է���������ӵ��Լ���������

		pNode = pNode->m_pNext;	// ָ����һ�����
	}
	return *this;
}

template<typename T>
CList<T>::~CList()
{
	// ��������е�������Ч���
	Clear();

	// ��ʱ�������ʹ�ã������ڱ����
	delete m_pHeadGuard;
	delete m_pTailGuard;
	m_pHeadGuard = nullptr;
	m_pTailGuard = nullptr;
	m_nNodeSize = 0;
}

// ��ͷ�ڵ�ǰ��ӽ��
template<typename T>
bool CList<T>::AddHead(T val)
{
	// �µĽ����뵽ͷ���ڱ��ĺ���
	return Insert(begin(), val);
}

// ��β�ڵ�ǰ��ӽ��
template<typename T>
bool CList<T>::AddTail(T val)
{
	// ����Ľ��Ϊβ��㣬���뵽β���ڱ���ǰ��Ϳ���
	return Insert(end(), val);
}

/*
PNODE pNode��Ҫ����Ľ��λ�ã������λ���Ǹýڵ��ǰ�棩
T val�����������
*/
template<typename T>
bool CList<T>::Insert(iterator itr, T val)
{
	// ������Ҫ�ж�ͷ����β����Ƿ�Ϊ�գ���Ҫ����˼·
	// �����������(�ڱ����)��һ������ͷ�ڵ��ǰ�棬һ������β���ĺ���
	// ��������㲻��洢���ݣ���������ݶ��洢�����������֮�䣬�����ڽ��б���

	// ����һ���µĽ��
	PNODE pNewNode = new NODE(val);

	// �����µĽ��
	PNODE pOldPre = itr.m_pNode->m_pPre;	// ����������ǰһ�����

	// �½�����һ�����ָ��pNode���
	pNewNode->m_pNext = itr.m_pNode;
	// �½���ǰһ�����ָ��pNode����ǰһ�����
	pNewNode->m_pPre = itr.m_pNode->m_pPre;	

	// ������Ľ�� �� ԭ�ȵ����������й���
	//pNode->m_pPre->m_pNext = pNewNode;
	//pNode->m_pPre = pNewNode;

	itr.m_pNode->m_pPre = pNewNode;
	pOldPre->m_pNext = pNewNode;

	// Ԫ�صĸ�������
	m_nNodeSize++;

	return true;
}

template<typename T>
bool CList<T>::SetVal(iterator itr, T val)
{
	// ��ֱ���޸ĸýڵ��ϵ����ݣ�����������ǰ������Ч��飬�������Ѿ�����
	itr.m_pNode->m_val = val;
	return true;
}

// ɾ��ͷ���
template<typename T>
bool CList<T>::RemoveHead()
{
	return Remove(begin());
}

// ɾ��β���
template<typename T>
bool CList<T>::RemoveTail()
{
	return Remove(--end());
}

// ɾ��ָ�����
template<typename T>
bool CList<T>::Remove(iterator itr)
{
	// �޸�ǰ���ͺ�̽��
	PNODE pOldPre = itr.m_pNode->m_pPre;
	PNODE pOldNext = itr.m_pNode->m_pNext;

	pOldPre->m_pNext = pOldNext;	// �ý��ǰ�����ĺ�̽�� ָ�� �ý��ĺ�̽��
	pOldNext->m_pPre = pOldPre;	// �ý���̽���ǰ����� ָ�� �ý���ǰ�����

	delete itr.m_pNode;	// ɾ���ý��
	m_nNodeSize--;	// ��������1

	return true;
}

template<typename T>
typename CList<T>::iterator CList<T>::Find(T val)
{
	// ����һ��ָ��ͷ�ڵ����ʱ���
	PNODE pNewTemp = m_pHeadGuard->m_pNext;
	// ��������������ͷ�ڵ㵽β���
	while (pNewTemp != m_pTailGuard)
	{
		if (pNewTemp->m_val == val)
		{
			return iterator(pNewTemp, m_pHeadGuard, m_pTailGuard);	// �ҵ����ظý��
		}
		// ƥ��ʧ�ܣ�ָ����һ�����
		pNewTemp = pNewTemp->m_pNext;
	}

	return iterator(m_pTailGuard, m_pHeadGuard, m_pTailGuard);
}

template<typename T>
bool CList<T>::IsNull()
{
	return m_nNodeSize == 0;
}

template<typename T>
int CList<T>::NodeSize()
{
	return m_nNodeSize;
}

// �������(�ڱ������ʱ����Ҫ�����ͷ�����)
// ��������ʱ��Ӧ���ڱ�Ҳ��������
template<typename T>
void CList<T>::Clear()
{
	while (!IsNull())
	{
		RemoveHead();	// ����������������Ҫ���� ��1����
	}
}

template<typename T>
void CList<T>::InitList()
{
	m_pHeadGuard = new NODE();
	m_pTailGuard = new NODE();

	// ������ռλ���ڱ�����ָ��
	m_pHeadGuard->m_pNext = m_pTailGuard;
	m_pTailGuard->m_pPre = m_pHeadGuard;
	m_nNodeSize = 0;
}