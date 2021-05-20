// list.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <list>
#include "MyLinkedList.h"
using namespace std;

int main()
{
	CList<int> list;
	list.AddHead(6);
	list.AddHead(7);
	list.AddHead(8);
	list.AddHead(9);
	list.AddHead(10);
	list.AddTail(20);
	list.AddTail(30);
	list.AddTail(50);
	list.AddTail(60);

	CList<int>::iterator itr = list.begin();
	list.Insert(itr, 666);
	list.Insert(itr, 777);
	list.Insert(itr, 888);
	list.Insert(itr, 999);
	list.Insert(itr, 678);

	cout << list.NodeSize() << endl;

	list.RemoveTail();
	cout << list.NodeSize() << endl;


	for (auto itr = list.begin(); itr != list.end(); ++itr)
	{
		cout << *itr << " ";
	}

	cout << endl;

	for (auto val : list)
	{
		cout << val << " ";
		// ����д������������������ǽ������д��չ��Ϊ�����forѭ����ʽ
		/*
		auto val:lst == auto itr = lst.begin(); itr != lst.end(); itr++
		val == *itr
		*/
	}
	cout << endl;


#if 0
	list<int> ls;
	for (int i = 0; i < 20; i++)
	{
		ls.push_back(i);
	}

	for (auto itr = ls.begin(); itr != ls.end(); ++itr)
	{
		cout << *itr << " ";
	}
	cout << endl;

	for (auto itr = ls.rbegin(); itr != ls.rend(); ++itr)
	{
		cout << *itr << " ";
}
#endif // ���� list �� rbegin() and rend()


	CList<int> lst;
	for (int i = 0; i <= 9; i++)
	{
		lst.AddHead(i);
	}

	for (auto itr = lst.begin(); itr != lst.end(); ++itr)
	{
		cout << *itr << " ";
	}

	cout << endl;


	// ʵ�� rbegin() rend()

	for (auto itr = lst.rbegin(); itr != lst.rend(); --itr)
	{
		cout << *itr << " ";
	}
	cout << endl;

	cout << list.NodeSize() << endl;

	return 0;
}