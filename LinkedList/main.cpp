// list.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
		// 这种写法，编译器会帮助我们将这里的写法展开为上面的for循环形式
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
#endif // 测试 list 的 rbegin() and rend()


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


	// 实现 rbegin() rend()

	for (auto itr = lst.rbegin(); itr != lst.rend(); --itr)
	{
		cout << *itr << " ";
	}
	cout << endl;

	cout << list.NodeSize() << endl;

	return 0;
}