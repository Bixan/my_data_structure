// CAVLTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "MyCAVLTree.h"
using namespace std;

int main()
{
#if 0
    CAVLTree<int> avlRotateLeft;
    avlRotateLeft.Insert(1);
    avlRotateLeft.Insert(2);
    avlRotateLeft.Insert(4);
    avlRotateLeft.Insert(6);
    avlRotateLeft.Insert(7);
    avlRotateLeft.Insert(10);
    avlRotateLeft.Insert(12);
    avlRotateLeft.Insert(15);
    avlRotateLeft.Insert(17);
    avlRotateLeft.Level();
#endif // 测试 二叉平衡树 左旋

#if 0
    CAVLTree<int> avlRotateRight;
    avlRotateRight.Insert(12);
    avlRotateRight.Insert(10);
    avlRotateRight.Insert(8);
    avlRotateRight.Insert(7);
    avlRotateRight.Insert(6);
    avlRotateRight.Insert(3);
    avlRotateRight.Insert(2);
    avlRotateRight.Level();
#endif // 测试 二叉平衡树 右旋


#if 0
    CAVLTree<int> avlTest;
    avlTest.Insert(46);
    avlTest.Insert(33);
    avlTest.Insert(63);
    avlTest.Insert(19);
    avlTest.Insert(42);
    avlTest.Insert(59);
    avlTest.Insert(67);
    avlTest.Insert(20);
    avlTest.Insert(66);
    avlTest.Insert(69);
    avlTest.Insert(69);
    avlTest.Insert(64);
    avlTest.Insert(25);
    avlTest.Insert(26);

    avlTest.Remove(19);
    avlTest.Remove(20);
    avlTest.Remove(42);

    avlTest.Remove(63);
    avlTest.Remove(69);
    avlTest.Level();

    cout << endl;
    avlTest = avlTest;

    CAVLTree<int> avlTest2;
    avlTest2 = avlTest;

    avlTest2.Level();

    avlTest.Clear();
    CAVLTree<int> avlTest3(avlTest);
#endif // 0


    CAVLTree<int> avl;
    avl.Insert(1);
    cout << "当前节点数量为：" << avl.GetNodeSize() << endl;

    avl.LMR();

    for (int i = 1; i <= 100; i++)
    {
        avl.Insert(i);
    }

    cout << "当前节点数量为：" << avl.GetNodeSize() << endl;
    avl.Remove(1);
    avl.Remove(2);
    avl.Remove(3);

    cout << "当前节点数量为：" << avl.GetNodeSize() << endl;

    avl.Find(2);
    avl.LMR();
    return 0;
}