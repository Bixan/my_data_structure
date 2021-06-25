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

	cout << "��ǰջ�ռ�Ԫ������Ϊ��" << stack.StackElementSize() << endl;

	while (!stack.empty())
	{
		cout << stack.top() << " ";
		stack.pop();
	}
	cout << endl;

	cout << "��ǰջ�ռ�Ԫ������Ϊ��" << stack.StackElementSize() << endl;
	return 0;
}