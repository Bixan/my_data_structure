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
	cout << "ǰ��-�õݹ飺";
	bst.MLR();
	cout << endl;
	cout << "ǰ��-�ǵݹ飺";
	bst.MLRUseLoop();
	cout << endl;

	cout << "����-�õݹ飺";
	bst.LMR();
	cout << endl;
	cout << "ǰ��-�ǵݹ飺";
	bst.LMRUseLoop();
	cout << endl;

	cout << "����-�õݹ飺";
	bst.LRM();
	cout << endl;
	cout << "����-�ǵݹ飺";
	bst.LRMUseLoop();
	cout << endl;


	cout << "���������";
	bst.Level();
	cout << endl;

	// ɾ���ڵ�
	bst.Remove(2);
	bst.Remove(10);
	bst.Remove(80);
	bst.Remove(56);
	bst.MLR();
	cout << endl;


	// ��ѯ
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
	cout << "ǰ��-�õݹ飺";
	bst.MLR();
	cout << endl;
	cout << "ǰ��-�ǵݹ飺";
	bst.MLRUseLoop();
	cout << endl;

	cout << "����-�õݹ飺";
	bst.LMR();
	cout << endl;
	cout << "ǰ��-�ǵݹ飺";
	bst.LMRUseLoop();
	cout << endl;

	cout << "����-�õݹ飺";
	bst.LRM();
	cout << endl;
	cout << "����-�ǵݹ飺";
	bst.LRMUseLoop();
	cout << endl;


	cout << "���������";
	bst.Level();
	cout << endl;

	// ɾ���ڵ�
	bst.Remove(2);
	bst.Remove(10);
	bst.Remove(80);
	bst.Remove(56);
	bst.MLR();
	cout << endl;


	// ��ѯ
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

	//��bug���Ѹ�
#if 1
	CBinarySearchTree<int> bstTest1;
	bstTest1.Insert(56);
	bstTest1.Remove(56);	 // bug ������
	bstTest1.Insert(40);
	cout << endl;
#endif // ����ֻ�и��ڵ�ʱ��ɾ�������

	//��bug���Ѹ�
#if 1
	CBinarySearchTree<int> bstTest2;
	bstTest2.Insert(56);
	bstTest2.Insert(60);
	bstTest2.Insert(57);
	bstTest2.Remove(56);
	bstTest2.Insert(69);
	cout << endl;


	//��bug���Ѹ�
	CBinarySearchTree<int> bstTest3;
	bstTest3.Insert(56);
	bstTest3.Insert(40);
	bstTest3.Insert(30);
	bstTest3.Remove(56);
	cout << endl;
#endif // ���Ե���֧��㣬ɾ�������

	return 0;
}