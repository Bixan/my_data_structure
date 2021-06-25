// list.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <list>
#include "MyList_iterator.h"
using namespace std;

#if 0
int main()
{
	CList<int> lst;
	lst.AddHead(6);
	lst.AddHead(7);
	lst.AddHead(8);
	lst.AddHead(9);
	lst.AddHead(10);
	lst.AddTail(20);
	lst.AddTail(30);
	lst.AddTail(50);
	lst.AddTail(60);

	CList<int>::iterator itr = lst.begin();
	lst.Insert(itr, 666);
	lst.Insert(itr, 777);
	lst.Insert(itr, 888);
	lst.Insert(itr, 999);
	lst.Insert(itr, 678);


	for (auto itr = lst.begin(); itr != lst.end(); ++itr)
	{
		cout << *itr << " ";
	}

	cout << endl;

	for (auto val : lst)
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

	cout << endl;
	return 0;
}

#endif // 迭代器测试


int main()
{
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
	return 0;
}
