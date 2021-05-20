#include <iostream>
#include "MyCBinarySearchTree.h"

int main()
{

#if 0
	CBinarySearchTree bst;
	bst.Insert(56);
	bst.Insert(20);
	bst.Insert(80);
	bst.Insert(10);
	bst.Insert(30);
	bst.Insert(70);
	bst.Insert(90);
	bst.Insert(2);
	bst.Insert(14);
	bst.Insert(25);
	bst.Insert(35);
	bst.Insert(60);
	bst.Insert(75);
	bst.Insert(85);
	bst.Insert(100);
	cout << "前序-用递归：";
	bst.MLR();
	cout << endl;
	cout << "前序-非递归：";
	bst.MLRUseLoop();
	cout << endl;

	cout << "中序-用递归：";
	bst.LMR();
	cout << endl;
	cout << "前序-非递归：";
	bst.LMRUseLoop();
	cout << endl;

	cout << "后序-用递归：";
	bst.LRM();
	cout << endl;
	cout << "后序-非递归：";
	bst.LRMUseLoop();
	cout << endl;


	cout << "层序遍历：";
	bst.Level();
	cout << endl;

	// 删除节点
	bst.Remove(2);
	bst.Remove(10);
	bst.Remove(80);
	bst.Remove(56);
	bst.MLR();
	cout << endl;


	// 查询
	cout << bst.Find(80) << endl;

	CBinarySearchTree bst3;
	bst3.Insert(38);
	bst3.Insert(56);
	bst3.Insert(37);
	bst3.Insert(52);
	bst3.Insert(69);
	bst3.MLRUseLoop();
	bst3 = bst3;

	CBinarySearchTree bst5(bst);
	CBinarySearchTree bst6(bst);
	bst6 = bst3;

	cout << endl;
#endif // 0

#if 1
	CBinarySearchTree<int> bst;
	bst.Insert(56);
	bst.Insert(20);
	bst.Insert(80);
	bst.Insert(10);
	bst.Insert(30);
	bst.Insert(70);
	bst.Insert(90);
	bst.Insert(2);
	bst.Insert(14);
	bst.Insert(25);
	bst.Insert(35);
	bst.Insert(60);
	bst.Insert(75);
	bst.Insert(85);
	bst.Insert(100);
	cout << "前序-用递归：";
	bst.MLR();
	cout << endl;
	cout << "前序-非递归：";
	bst.MLRUseLoop();
	cout << endl;

	cout << "中序-用递归：";
	bst.LMR();
	cout << endl;
	cout << "前序-非递归：";
	bst.LMRUseLoop();
	cout << endl;

	cout << "后序-用递归：";
	bst.LRM();
	cout << endl;
	cout << "后序-非递归：";
	bst.LRMUseLoop();
	cout << endl;


	cout << "层序遍历：";
	bst.Level();
	cout << endl;

	// 删除节点
	bst.Remove(2);
	bst.Remove(10);
	bst.Remove(80);
	bst.Remove(56);
	bst.MLR();
	cout << endl;


	// 查询
	cout << bst.Find(80) << endl;

	CBinarySearchTree<int> bst3;
	bst3.Insert(38);
	bst3.Insert(56);
	bst3.Insert(37);
	bst3.Insert(52);
	bst3.Insert(69);
	bst3.MLRUseLoop();
	bst3 = bst3;

	CBinarySearchTree<int> bst5(bst);
	CBinarySearchTree<int> bst6(bst);
	bst6 = bst3;

	cout << endl;
#endif // 0

	//有bug，已改
#if 1
	CBinarySearchTree<int> bstTest1;
	bstTest1.Insert(56);
	bstTest1.Remove(56);	 // bug 出发点
	bstTest1.Insert(40);
	cout << endl;
#endif // 测试只有根节点时，删除根结点

	//有bug，已改
#if 1
	CBinarySearchTree<int> bstTest2;
	bstTest2.Insert(56);
	bstTest2.Insert(60);
	bstTest2.Insert(57);
	bstTest2.Remove(56);
	bstTest2.Insert(69);
	cout << endl;


	//有bug，已改
	CBinarySearchTree<int> bstTest3;
	bstTest3.Insert(56);
	bstTest3.Insert(40);
	bstTest3.Insert(30);
	bstTest3.Remove(56);
	cout << endl;
#endif // 测试单分支结点，删除根结点

	return 0;
}