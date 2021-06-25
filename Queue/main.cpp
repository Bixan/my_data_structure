
#include <iostream>
#include "CQueue.h"
using namespace std;

int main()
{
	CQueue<int> queue;
	// �������
	for (int i = 1; i <= 20; i++)
	{
		queue.push(i);
	}

	cout << "��ǰ�����е�������Ԫ�أ�" 
		<< queue.QueueElementSize() 
		<< " ��" 
		<< endl;

	while (!queue.empty())
	{
		cout << queue.front() 
			<< " ";
		queue.pop();
	}
	cout << endl;
	cout << "��ǰ�����е�������Ԫ�أ�" 
		<< queue.QueueElementSize() 
		<< " ��" 
		<< endl;
	return 0;
}