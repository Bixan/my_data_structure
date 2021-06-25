#define _CRT_SECURE_NO_WARNINGS
#include "CArray.h"
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <stdexcept>


/*=======================================================
*   �������ã��޲ι��죬��ʼ������
*   ��������
*   ����ֵ����
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
CArrary<T>::CArrary()
{
	m_pBuff = nullptr;
	m_nElementSize = 0;
	m_nBuffSize = 0;
}


/*=======================================================
*   �������ã���������
*   ������const CArrary& ary -- �ѳ�ʼ�������
*   ����ֵ����
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
CArrary<T>::CArrary(const CArrary& ary)
{
	*this = ary;	// ����� = ����Ϊ���󣬻������������� =
}


/*=======================================================
*   �������ã�����������������ܽ������Զ����øú������������ͷ�
*   ��������
*   ����ֵ����
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
CArrary<T>::~CArrary()
{
	Clear();
}


/*=======================================================
*   �������ã����� Insert() �����ڶ�̬����ͷ���������
*   ������val -- ��ӵ�����
*   ����ֵ������Insert()���� -- ��ӳɹ����� true�����ʧ�ܷ���false
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::AddHead(T val)
{
	return Insert(0, val);
}


/*=======================================================
*   �������ã����� Insert() �����ڶ�̬����β���������
*   ������val -- ��ӵ�����
*   ����ֵ������Insert()���� -- ��ӳɹ����� true�����ʧ�ܷ���false
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::AddTail(T val)
{
	return Insert(m_nElementSize, val);
}


/*=======================================================
*   �������ã��ڶ�̬�����ڵ�ָ��λ�����ָ��������
*   ������val -- ��ӵ�����
*   ����ֵ����
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::Insert(int nIdx, T val)
{
	//�ж��Ƿ�Ϊ��
	if (m_pBuff == nullptr)
	{
		// ��ʼ��
		const int nInitBuffSize = 4;
		m_nBuffSize = nInitBuffSize;
		m_pBuff = new T[m_nBuffSize];
		m_nElementSize = 0;
	}

	// �ж�����ֵ�Ƿ����
	if (nIdx < 0 || nIdx > m_nElementSize)
	{
		return false;
	}

	// �жϻ������Ƿ��㹻ʹ�ã�����Ԫ�صĸ���������������С�������µĻ�����
	if (m_nElementSize >= m_nBuffSize)
	{
		//�����µĻ���������СΪԭ����������С������
		m_nBuffSize = m_nBuffSize * 2;
		T* pNewBuff = new T[m_nBuffSize];
		memcpy(pNewBuff, m_pBuff, m_nElementSize * sizeof(T)); //����ԭ��������
		delete[]m_pBuff; //ɾ��ԭ���Ļ�����
		m_pBuff = pNewBuff;
	}

	//����µ�Ԫ��
	//��nIdx��ʼ��Ԫ�ض�����ƶ�
	memcpy(&m_pBuff[nIdx + 1], &m_pBuff[nIdx], (m_nElementSize - nIdx) * sizeof(T));
	m_pBuff[nIdx] = val; // ������ֵ
	m_nElementSize++; // Ԫ�ظ�����1

	return true;
}


/*=======================================================
*   �������ã�ɾ��ͷ���
*   ��������
*   ����ֵ������Remove()������ɾ���ɹ� ����true��ɾ��ʧ�� ����false
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::RemoveHead()
{
	return Remove(0);
}


/*=======================================================
*   �������ã�ɾ��β���
*   ��������
*   ����ֵ������Remove()������ɾ���ɹ� ����true��ɾ��ʧ�� ����false
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::RemoveTail()
{
	return Remove(m_nElementSize - 1);
}


/*=======================================================
*   �������ã��������������ֵ��ɾ��ָ�������ϵ�����
*   ������int nIdx  -- Ҫɾ��Ԫ�ص�����ֵ
*   ����ֵ������Remove()������ɾ���ɹ� ����true��ɾ��ʧ�� ����false
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::Remove(int nIdx)
{
	// ����Ϊ����ɾ��
	if (m_pBuff == nullptr)
	{
		return false;
	}

	//�ж�����ֵ�Ƿ����
	if (nIdx < 0 || nIdx >= m_nElementSize)
	{
		return false;
	}

	// ɾ��Ԫ�� ��Ҫɾ����Ԫ�غ����Ԫ����ǰ�ƶ�
	memcpy(&m_pBuff[nIdx], &m_pBuff[nIdx + 1], (m_nElementSize - nIdx - 1) * sizeof(T));
	// Ԫ�ظ�����1
	m_nElementSize--;

	return true;
}


/*=======================================================
*   �������ã��������������ֵ��ɾ��ָ�������ϵ�����
*   ������int nIdx  -- Ҫ�޸�Ԫ�ص�������val -- �޸ĺ������
*   ����ֵ���޸ĳɹ� ����true���޸�ʧ�� ����false
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
bool CArrary<T>::SetVal(int nIdx, T val)
{
	// �ж������Ƿ����
	if (nIdx < 0 || nIdx >= m_nElementSize)
	{
		return false;
	}
	// �޸�ָ����������ֵ
	m_pBuff[nIdx] = val;
	return true;
}


/*=======================================================
*   �������ã����������[]
*   ������int nIdx  -- Ҫ���ʶ�̬������±�
*   ����ֵ���±�Խ�磬�׳��쳣��û��Խ�磬���������϶�Ӧ����ֵ
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
T& CArrary<T>::operator[](int nIdx)
{
	// ����±��Ƿ�Խ���Լ��������Ƿ�Ϊ��
	if (nIdx < 0 || nIdx >= m_nElementSize || m_pBuff == nullptr)
	{
		throw std::out_of_range("����Խ�磬������������±�����ֵ");	// ע�⣬�������ж�Ϊ�棬������׳��쳣
	}
	return m_pBuff[nIdx];
}


/*=======================================================
*   �������ã���������� +=
*   ������const CArrary& ary -- �ѳ�ʼ��������� ary
*   ����ֵ��
*		ƴ��ʧ�ܣ����� *this -- ���ر�ƴ�ӷ������ݣ�
*		ƴ�ӳɹ�������ƴ�Ӻ�� *this
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
CArrary<T>& CArrary<T>::operator+=(const CArrary& ary)
{
	// ����Է�Ϊ�գ��Ͳ�ƴ��
	if (ary.m_pBuff == nullptr)
	{
		return *this;
	}

	// ����Լ�Ϊ�գ���ֱ�ӿ���
	if (m_pBuff == nullptr)
	{
		*this = ary;
		return *this;
	}

	// ����������������������ʱ�����������������µ��ڴ棬���п�����ֵ
	T* pNewBuff = new T[m_nElementSize + ary.m_nElementSize];
	memcpy(pNewBuff, m_pBuff, (m_nElementSize) * sizeof(T));
	memcpy(pNewBuff + m_nElementSize, ary.m_pBuff, ary.m_nElementSize * sizeof(T));

	// �ͷ�֮ǰ�Ļ�����
	delete[] m_pBuff;
	m_pBuff = pNewBuff;
	m_nBuffSize = m_nElementSize + ary.m_nElementSize;
	m_nElementSize = m_nElementSize + ary.m_nElementSize;

	return *this;
}


/*=======================================================
*   �������ã���������� =
*   ������const CArrary& ary -- �ѳ�ʼ��������� ary
*   ����ֵ��= ������Ϊͬһ��������ʱ�򣬸�ֵʧ�ܣ����� *this������ֵ��������ַ��
*		��ֵ�ɹ������ظ�ֵ�������� *this
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
CArrary<T>& CArrary<T>::operator=(const CArrary& ary)
{
	/*
	������� = ������Ϊͬһ�������ʱ�򣬲����и�ֵ�������Ƚϵ�ַ�Ƿ���ȣ�
	*this == ary --> ����д�ǲ�����ģ���Ҫ���� ��������� ==����Ϊ == ����Ϊ����
	*/
	if (this == &ary)
	{
		return *this;
	}

	// �˴���֮ǰ�Լ�������
	Clear();

	// ����Ŀ���������ݸ��Լ�
	m_pBuff = new T[ary.m_nBuffSize];
	memcpy(m_pBuff, ary.m_pBuff, ary.m_nElementSize * sizeof(T));
	m_nBuffSize = ary.m_nBuffSize;
	m_nElementSize = ary.m_nElementSize;
	return *this;
}


/*=======================================================
*   �������ã��ڶ�̬�����ڲ�ѯָ��������ֵ val
*   ������val -- ��ѯ��ָ������ ary
*   ����ֵ����ѯ�ɹ���������
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
int CArrary<T>::Find(T val)
{
	if (m_pBuff == nullptr)
	{
		return -1;
	}

	for (int nInx = 0; nInx < m_nElementSize; nInx++)
	{
		/*
		������� == ���ε����Ͳ�ƥ���ʱ����Ҫ��������ṩ ��������� ==
		�����ơ�==��:��T����������������Ԥ����������ɽ��յ����͵�ת��
		*/
		if (m_pBuff[nInx] == val)
		{
			return nInx; // �ҵ���������
			//return m_pBuff[nInx];
		}
	}
	return -1;
}


/*=======================================================
*	�������ã���ȡԪ�ظ���
*   ��������
*   ����ֵ�����ض�̬�����ڵ���ЧԪ������
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
int CArrary<T>::ElementCount() const
{
	return m_nElementSize;
}


/*=======================================================
*   �������ã������̬���������
*   ��������
*   ����ֵ����
*   ���棺��
*   ���£�2020/06/08
========================================================*/
template<typename T>
void CArrary<T>::Clear()
{
	if (m_pBuff != nullptr)
	{
		delete[] m_pBuff;
		m_pBuff = nullptr;
		m_nBuffSize = 0;
		m_nElementSize = 0;
	}
}