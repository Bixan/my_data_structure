#pragma once

/*=======================================================
*							o(*￣▽￣*)o
****************************************************************************************
*				Project Name：二叉搜索树
*
*				FileName：CBinarySearchTree.h
*
*				Start Date：2020/06/05
*
*				Last UpDate：2020/06/08
*
****************************************************************************************
========================================================*/

class CBinarySearchTree
{
private:
	typedef struct tagNode
	{
		// 树结点数据
		tagNode(int val, tagNode* pParent, tagNode* pLeft, tagNode* pRight) :
			m_val(val),
			m_pParent(pParent),
			m_pLeft(pLeft),
			m_pRight(pRight)
		{}
		int m_val;	// 当前结点保存的数据
		tagNode* m_pParent;	// 指向父结点
		tagNode* m_pLeft;		// 当前结点的左孩子
		tagNode* m_pRight;	// 当前结点的右孩子
	}NODE, * PNODE;

public:
	CBinarySearchTree();
	CBinarySearchTree(const  CBinarySearchTree& bst);

	CBinarySearchTree& operator=(const CBinarySearchTree& bst);
	virtual ~CBinarySearchTree();

public:
	// 基本操作
	bool Insert(int val);	// 插入数据 val
	bool Remove(int val);	// 删除数据 val
	bool Updata(int valSrc, int valDst);	// 将原来结点上的数值更改新的数值
	bool Find(int val);	// 查找 数据 val 
	void Clear();

	// 使用递归遍历数据（前序、中序、后续）
	void MLR();	// 前序遍历（递归）middle left right
	void LMR();	// 中序遍历（递归） left middle right
	void LRM();	// 后序遍历（递归） left right middle

	// 使用非递归（使用循环）遍历数据（前序、中序、后续）
	void MLRUseLoop();	// 前序遍历（非递归）middle left right
	void LMRUseLoop();	// 中序遍历（非递归） left middle right
	void LRMUseLoop();	// 后序遍历（非递归） left right middle

	void Level();	// 层序遍历

private:
	void Destroy(PNODE pNode);	// 清理结点
	PNODE FindNode(int val);	// 查找结点
	void DelNode(PNODE pNode);	// 根据待删除结点的所处位置进行对应的删除操作

	void DelLeaf(PNODE pNode);	// 叶子结点
	void DelSingleChildNode(PNODE pNode);		// 单分支结点
	void DelDoubleChildNode(PNODE pNode);	// 双分支结点

	void MLR(PNODE pNode);	// 递归 前序 遍历
	void LMR(PNODE pNode);	// 递归 中序 遍历
	void LRM(PNODE pNode);	// 递归 后序 遍历

private:
	PNODE m_pRoot;	// 当前树的根结点
};