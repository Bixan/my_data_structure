#include <iostream>
#include "CStack.h"
using namespace std;

int main()
{
	CStack<int> stack;
	for (int i = 1; i <= 20; i++)
	{
		stack.push(i);
	}

	cout << "当前栈空间元素数量为：" << stack.StackElementSize() << endl;

	while (!stack.empty())
	{
		cout << stack.top() << " ";
		stack.pop();
	}
	cout << endl;

	cout << "当前栈空间元素数量为：" << stack.StackElementSize() << endl;
	return 0;
}