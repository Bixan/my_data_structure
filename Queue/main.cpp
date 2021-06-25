
#include <iostream>
#include "CQueue.h"
using namespace std;

int main()
{
	CQueue<int> queue;
	// 数据入队
	for (int i = 1; i <= 20; i++)
	{
		queue.push(i);
	}

	cout << "当前队列中的有数据元素：" 
		<< queue.QueueElementSize() 
		<< " 个" 
		<< endl;

	while (!queue.empty())
	{
		cout << queue.front() 
			<< " ";
		queue.pop();
	}
	cout << endl;
	cout << "当前队列中的有数据元素：" 
		<< queue.QueueElementSize() 
		<< " 个" 
		<< endl;
	return 0;
}