#pragma once
/*=======================================================
*		o(*������*)o
*		Project Name����̬����
*		FileName��CArray.h
*		Start Date��2020/06/05
*		Last UpDate��2020/06/08
========================================================*/
#include <cassert>
template<typename T>
class CArrary
{
	// ������
	class iterator
	{
		friend class CArrary;
	public:
		// ���� ǰ�� ++ �����
		iterator& operator++()
		{
			assert(m_pElement != m_pTailElement);
			m_pElement++;
			return *this;
		}

		// ���� ���� ++ �����
		iterator operator++(int)
		{
			assert(m_pElement != m_pTailElement);
			T* pTemp = m_pElement;
			m_pElement++;
			return iterator(pTemp, m_pHeadElement, m_pTailElement);
		}

		// ���� ǰ�� -- �����
		iterator& operator--()
		{
			assert(m_pElement != m_pHeadElement);
			m_pElement--;
			return *this;
		}

		// ���� ���� -- �����
		iterator operator--(int)
		{
			assert(m_pElement != m_pHeadElement);
			T* pTemp = m_pElement;

			m_pElement--;
			return iterator(pTemp, m_pHeadElement, m_pTailElement);
		}

		// ���� == �����
		bool operator==(const iterator& itr)
		{
			return m_pElement == itr.m_pElement;
		}

		// ���� != �����
		bool operator!=(const iterator& itr)
		{
			return m_pElement != itr.m_pElement;
		}

		// ���� *(ȡ����) �����
		T& operator*()
		{
			return *m_pElement;
		}

	private:
		// ˽�й���
		iterator(T* pElement, 
			T* pHeadElement, 
			T* pTailElement) :
			m_pElement(pElement),
			m_pHeadElement(pHeadElement),
			m_pTailElement(pTailElement)
		{
		}
	private:
		T* m_pElement;
		T* m_pHeadElement;
		T* m_pTailElement;
	};
public:
	/*
	��� rbegin() rend()
	�������
	*/
	iterator begin()
	{
		return iterator(m_pBuff,
			m_pBuff - 1,
			m_pBuff + m_nElementSize);
	}
	iterator end()
	{
		return iterator(m_pBuff + m_nElementSize,
			m_pBuff - 1,
			m_pBuff + m_nElementSize);
	}
	/*
	��� rbegin() rend()
	�������
	*/
	iterator rbegin()
	{
		return iterator(m_pBuff + m_nElementSize - 1,
			m_pBuff + m_nElementSize - 1,
			m_pBuff - 1);
	}
	iterator rend()
	{
		return iterator(m_pBuff - 1,
			m_pBuff + m_nElementSize - 1,
			m_pBuff - 1);
	}
public:
	CArrary();	// �޲ι���
	CArrary(const CArrary& ary); // ��������
	virtual ~CArrary();	// ������

public:
	bool AddHead(T val); // ͷ�� ��������
	bool AddTail(T val); // β�� ��������
	bool Insert(int nIdx, T val); // ָ��λ�� ��������

	bool RemoveHead(); // ͷ�� ɾ������
	bool RemoveTail(); // β�� ɾ������
	bool Remove(int nIdx); // ָ��λ��  ɾ������

	bool SetVal(int nIdx, T val);
	T& operator[](int nIdx); // �˴����׳��쳣

	CArrary& operator+=(const CArrary& ary); // ��������� +=
	CArrary& operator=(const CArrary& ary); // ��������� =

	int Find(T val); // ��ѯָ������
	int ElementCount()const; // ��ȡ����Ԫ�صĸ���
	void Clear(); // ���
private:
	T* m_pBuff; // �������Ԫ�صĻ�����
	int m_nBuffSize; // �������Ĵ�С
	int m_nElementSize;	// ������Ԫ�صĸ���
};