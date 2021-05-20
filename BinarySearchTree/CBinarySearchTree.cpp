#include "CBinarySearchTree.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

/*=======================================================
*	CBinarySearchTree::CBinarySearchTree() -- 无参构造，初始化树
*
*	参数：无
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
CBinarySearchTree::CBinarySearchTree()
{
	m_pRoot = nullptr;
}


/*=======================================================
*	CBinarySearchTree(const CBinarySearchTree& bst) -- 拷贝构造
*
*	参数：已初始化的类对象
*
*	返回值：Nothing
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
CBinarySearchTree::CBinarySearchTree(const CBinarySearchTree& bst)
{
	*this = bst;
}


/*=======================================================
*	CBinarySearchTree::operator=(const CBinarySearchTree& bst) -- 重载运算符 =
*
*	参数：已初始化的类对象
*
*	返回值：*this
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
CBinarySearchTree& CBinarySearchTree::operator=(const CBinarySearchTree& bst)
{
	if (this == &bst)
	{
		return *this;	// 如果自己给自己赋值，什么也不做
	}

	Clear();	// 清除自己的各个结点数据

	if (bst.m_pRoot == nullptr)
	{
		return *this;	// 如果赋值方为空树，不进行赋值
	}

	// 赋值
	queue<PNODE> queTemp;	// 初始化一个队列
	queTemp.push(bst.m_pRoot);	// 根结点进队

	while (!queTemp.empty())	// 队列为空，退出循环
	{
		PNODE pNode = queTemp.front();	// 将队首赋值给 pNode
		queTemp.pop();	// 将队首弹出
		Insert(pNode->m_val);

		if (pNode->m_pLeft != nullptr)	// 出队的结点的左孩子不为空，就将其左孩子入队
		{
			queTemp.push(pNode->m_pLeft);
		}
		if (pNode->m_pRight != nullptr)	// 出队的结点的右孩子不为空，就将其右孩子入队
		{
			queTemp.push(pNode->m_pRight);
		}
	}

	return *this;
}


/*=======================================================
*	~CBinarySearchTree() -- 程序结束，调用 Clear() 方法释放对应的数据
*
*	参数：无
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
CBinarySearchTree::~CBinarySearchTree()
{
	Clear();
}


/*=======================================================
*	bool CBinarySearchTree::Insert(int val) -- 插入数据
*
*	参数：val -- 插入的数据值
*
*	返回值：true -- 数据插入成功，false -- 数据插入失败
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
bool CBinarySearchTree::Insert(int val)
{
	if (m_pRoot == nullptr)
	{
		// 如果树为空，插入的数据作为根结点，同时根节点的高度置为0
		m_pRoot = (PNODE)new NODE(val, nullptr, nullptr, nullptr);
	}

	// 如果当前树不为空，就将当前树的根结点数据赋值给临时树 pTempNode
	PNODE pTempNode = m_pRoot;

	// 遍历查找可以插入的位置，遍历从树的根部开始
	while (true)
	{
		// 如果插入的数据数值小于当前结点，则取其左孩子部分查找合适的位置
		if (val < pTempNode->m_val)
		{
			// 如果此结点没有左孩子，则新插入的数值作为当前结点的左孩子
			if (pTempNode->m_pLeft == nullptr)
			{
				// 新插入的结点的高度置0，此时其根结点的高度加1
				pTempNode->m_pLeft = new NODE(val, pTempNode, nullptr, nullptr);

				return true;
			}
			else
			{
				// 此结点有左孩子，就然该结点指向该结点的左孩子，继续往下寻找空位置
				pTempNode = pTempNode->m_pLeft;
			}
		}
		// 如果插入的数据数值大于当前结点，则取其右孩子判断
		else if (val > pTempNode->m_val)
		{
			if (pTempNode->m_pRight == nullptr)
			{
				pTempNode->m_pRight = new NODE(val, pTempNode, nullptr, nullptr);

				return true;
			}
			else
			{
				// 此结点有右孩子，就然该结点指向该结点的右孩子，继续往下寻找空位置
				pTempNode = pTempNode->m_pRight;
			}
		}
		else
		{
			return false;	// 暂时不考虑相等的情况
		}
	}
	return true;
}


/*=======================================================
*	bool CBinarySearchTree::Remove(int val) -- 删除指定的数据
*
*	参数：val -- 删除的数据值
*
*	返回值：true -- 输入删除成功，false -- 数据删除失败
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
bool CBinarySearchTree::Remove(int val)
{
	PNODE pNodeTodel = FindNode(val);	// 查找将要被删除的结点

	if (pNodeTodel == nullptr)
	{
		return false;	// pNodeTodel 为空 查找失败 返回 false
	}

	DelNode(pNodeTodel);	// 查找成功，根据结点的情况进行下一步操作
	return true;
}


/*=======================================================
*	bool CBinarySearchTree::Updata(int valSrc, int valDst) -- 修改数据
*
*	参数：valSrc -- 被修改的数据值，valDst -- 修改后的数据值
*
*	返回值：false -- 数据查找/修改失败，true -- 数据修改成功
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
// 将树中存在的数值 valSrc 修改为 valDst
bool CBinarySearchTree::Updata(int valSrc, int valDst)
{
	if (m_pRoot == nullptr)
	{
		return false;	// 如果当前树为空，返回false
	}

	PNODE pChangeNode = FindNode(valSrc);	// 查找是否存在 valSrc

	if (pChangeNode == nullptr)
	{
		return false;	// pNodeTodel 为空 查找失败 返回 false
	}

	//pChangeNode->m_val = valDst;	// 直接修改，不可取，会导致该树不是一颗排序树

	Remove(valSrc);	// 数值查找成功，删除结点
	Insert(valDst);	// 将新的数值从新插入到该树中

	return true;
}


/*=======================================================
*	bool CBinarySearchTree::Find(int val) -- 查找指定的数据值
*
*	参数：val -- 查找的数据值
*
*	返回值：true -- 数据查找成功，false -- 数据查找失败
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
bool CBinarySearchTree::Find(int val)
{
	if (m_pRoot == nullptr)
	{
		return false;	// 如果当前树为空，返回false
	}

	PNODE pChangeNode = FindNode(val);	// 查找树中是否存在数值 val
	if (pChangeNode == nullptr)
	{
		return false;	// pNodeTodel 为空 查找失败 返回 false
	}
	return true;		// pNodeTodel 不为空 查找成功 返回 true
}


/*=======================================================
*	void CBinarySearchTree::Clear() -- 清空树中所有有效的结点
*
*	参数：无
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::Clear()
{
	while (m_pRoot != nullptr)
	{
		DelNode(m_pRoot);	// 树中结点删除完毕后，循环终止
	}
}

/*=======================================================
*	void CBinarySearchTree::MLR() -- 递归 前序 遍历（树不为空，调用MLR()方法）
*
*	参数：无
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::MLR()
{
	if (m_pRoot != nullptr)
	{
		MLR(m_pRoot);	// 调用 前序 遍历
	}
}

/*=======================================================
*	void CBinarySearchTree::LMR() -- 递归 中序 遍历（树不为空，调用LMR()方法）
*
*	参数：无
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::LMR()
{
	if (m_pRoot != nullptr)
	{
		LMR(m_pRoot);	// 调用 中序 遍历
	}
}

/*=======================================================
*	void CBinarySearchTree::LRM() -- 递归 后序 遍历（树不为空，调用LRM()方法）
*
*	参数：无
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::LRM()
{
	if (m_pRoot != nullptr)
	{
		LRM(m_pRoot);	// 调用 后序 遍历
	}
}


/*=======================================================
*	void CBinarySearchTree::MLRUseLoop() -- 前序遍历（非递归）
*
*	参数：无
*
*	返回值：无
*
*	输出：树中所有有效根结点存储的数据值
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::MLRUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;	// 如果为空树，不进行遍历
	}

	stack<PNODE> stkTemp;	// 初始化一个栈
	PNODE pNode = m_pRoot;	// 存储根结点

	while (true)
	{
		while (pNode != nullptr)
		{
			cout << pNode->m_val << " ";	// 输出数据
			stkTemp.push(pNode->m_pRight);	// 输出数据结点的右孩子入栈
			pNode = pNode->m_pLeft;	// 更新 pNode 结点，一直向左进行入栈
		}

		if (stkTemp.empty())
		{
			break;	// 栈为空，所有的右孩子输出完毕，跳出循环
		}

		pNode = stkTemp.top();	// 左孩子输出完毕，将结点指向栈顶
		stkTemp.pop();	// 同时将栈顶的数据进行弹出
	}
}


/*=======================================================
*	void CBinarySearchTree::LMRUseLoop() -- 中序遍历（非递归）
*
*	参数：无
*
*	返回值：无
*
*	输出：树中所有有效根结点存储的数据值
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::LMRUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;	// 如果树为空，不进行遍历
	}

	stack<PNODE> stkTemp;	// 初始化一个栈
	PNODE pNode = m_pRoot;	// 将根节点赋值给 pNode

	while (true)
	{
		while (pNode != nullptr)
		{
			stkTemp.push(pNode);	// 将根结点入栈
			pNode = pNode->m_pLeft;	// pNode 指向其左孩子
		}

		if (stkTemp.empty())
		{
			break;	// 栈空循环结束
		}

		// 如果没有左孩子可以入栈，就将栈内的数据弹出来一个
		pNode = stkTemp.top();	// pNode 指向 栈顶
		stkTemp.pop();	// 从栈顶弹出一个数据
		cout << pNode->m_val << " ";	// 输出弹出的数据

		// 处理弹出结点数据的右孩子
		pNode = pNode->m_pRight;
	}

}


/*=======================================================
*	void CBinarySearchTree::LRMUseLoop() -- 后序遍历（非递归）
*
*	参数：无
*
*	返回值：无
*
*	输出：树中所有有效根结点存储的数据值
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::LRMUseLoop()
{
	if (m_pRoot == nullptr)
	{
		return;	// 如果树为空，不进行遍历
	}

	stack<PNODE> stkTemp;	// 初始化一个栈
	PNODE pNode = m_pRoot;	// 将 根 m_pRoot 赋值给 pNode
	PNODE pPreDisposeNode = nullptr;	// 保存上一次处理的结点

	while (true)
	{
		while (pNode != nullptr)
		{
			stkTemp.push(pNode);	// 树的根结点入栈
			pNode = pNode->m_pLeft;	// 更新 pNode 结点，一直向左进行入栈
		}

		if (stkTemp.empty())
		{
			break;	// 栈为空，所有的右孩子输出完毕，跳出循环
		}

		pNode = stkTemp.top();	// 指向栈顶

		if (pNode->m_pRight == pPreDisposeNode || pNode->m_pRight == nullptr)
		{
			cout << pNode->m_val << " ";

			pPreDisposeNode = pNode;	// 保存处理后的结点
			stkTemp.pop();	// 将处理后的结点弹出

			pNode = nullptr;	// 这里的结点处理完后，说明其右孩子已经被处理调了
			continue;	// 这里不需要再将 pNode 指向该结点的右孩子
		}
		pNode = pNode->m_pRight;	// 处理右孩子
	}
}

/*=======================================================
*	void CBinarySearchTree::Level() -- 层序遍历
*
*	参数：无
*
*	返回值：无
*
*	输出：树中所有有效根结点存储的数据值
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::Level()
{
	if (m_pRoot == nullptr)
	{
		return;	// 如果为空树，不进行遍历
	}

	queue<PNODE> queTemp;	// 初始化一个队列
	queTemp.push(m_pRoot);	// 根结点进队

	while (!queTemp.empty())	// 队列为空，退出循环
	{
		PNODE pNode = queTemp.front();	// 将队首赋值为 pNode
		queTemp.pop();	// 将队首弹出
		cout << pNode->m_val << " ";	// 将弹出的数据进行输出

		if (pNode->m_pLeft != nullptr)	// 出队的结点的左孩子不为空，就将其左孩子入队
		{
			queTemp.push(pNode->m_pLeft);
		}
		if (pNode->m_pRight != nullptr)	// 出队的结点的右孩子不为空，就将其右孩子入队
		{
			queTemp.push(pNode->m_pRight);
		}
#if 0
		if (pNode != nullptr)
		{
			cout << pNode->m_val << " ";			// 输出结点数据
			queTemp.push(pNode->m_pLeft);		// 出队结点的左孩子 和 右孩子入队
			queTemp.push(pNode->m_pRight);
		}
#endif // 出队结点的 左孩子 和 右孩子  入队（简单写法）
	}
}


/*=======================================================
*	void CBinarySearchTree::Destroy(PNODE pNode)
*	-- 使用递归清除树中有效的所有结点
*	参数：PNODE pNode -- 树的根结点
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::Destroy(PNODE pNode)
{
	if (pNode != nullptr)
	{
		Destroy(pNode->m_pLeft);	// 销毁根的左孩子
		Destroy(pNode->m_pRight);	// 销毁根的右孩子

		delete pNode;	// 销毁根
		pNode = nullptr;
	}
}


/*=======================================================
*	PNODE CBinarySearchTree::FindNode(int val)
*	-- 根据输入的数据值查找树中是否存在对应的数据
*	参数：val -- 查找的数据值
*
*	返回值：pTempNode 返回查到的存储该数据的结点
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
typename CBinarySearchTree::PNODE CBinarySearchTree::FindNode(int val)
{
	// 从该树的根结点开始查找
	PNODE pTempNode = m_pRoot;

	while (pTempNode != nullptr)
	{
		// 如果查找的数据和当前结点的数值相等，就返回该结点
		if (val == pTempNode->m_val)
		{
			return pTempNode;
		}
		// 如果查找的数据大于当前结点的数值，就去该结点的右部分进行查找
		else if (val > pTempNode->m_val)
		{
			pTempNode = pTempNode->m_pRight;
		}
		else
		{
			// 如果查找的数据小于当前结点的数值，就去该结点的左部分进行查找
			pTempNode = pTempNode->m_pLeft;
		}
	}
	return nullptr;
}


/*=======================================================
*	void CBinarySearchTree::DelNode(PNODE pNode)
*	-- 删除结点，根据结点类型进行对应的删除
*	参数：PNODE pNode -- 要删除的数据所对应的结点
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::DelNode(PNODE pNode)
{
	// 对要删除的结点进行结点位置判断

	// 叶子结点
	if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr)
	{
		DelLeaf(pNode);
		return;
	}
	// 单分支结点
	else if (pNode->m_pLeft == nullptr || pNode->m_pRight == nullptr)
	{
		DelSingleChildNode(pNode);
		return;
	}
	// 双分支结点
	else
	{
		DelDoubleChildNode(pNode);
	}
}


/*=======================================================
*	void CBinarySearchTree::DelLeaf(PNODE pNode)
*	-- 删除的结点为叶子结点（该结点没有左右孩子）
*	参数：PNODE pNode -- 要删除的数据所对应的结点
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::DelLeaf(PNODE pNode)
{
	PNODE pParent = pNode->m_pParent;	// 保存当前结点的父结点

	if (pNode == m_pRoot)	// 如果当前结点是根结点，就删除该结点
	{
		delete m_pRoot;
		m_pRoot = nullptr;
		return;
	}

	// 判断要删除的结点是父结点下的 左孩子 还是 右孩子
	if (pParent->m_pLeft == pNode)
	{
		pParent->m_pLeft = nullptr;	// 如果是左孩子，将其左孩子的结点置空
	}
	else
	{
		pParent->m_pRight = nullptr;	// 如果是右孩子，将其右孩子的结点置空
	}

	delete pNode;	// 删除此结点
	pNode = nullptr;
}


/*=======================================================
*	void CBinarySearchTree::DelSingleChildNode(PNODE pNode)
*	-- 删除的结点为单分支结点（该结点有一个孩子 左孩子/右孩子）
*	参数：PNODE pNode -- 要删除的数据所对应的结点
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::DelSingleChildNode(PNODE pNode)
{
	PNODE pParent = pNode->m_pParent;	// 保存当前结点的父结点

	PNODE pChild = pNode->m_pLeft;	// 默认保存当前结点的左孩子

	if (pChild == nullptr)
	{
		pChild = pNode->m_pRight;	// 如果左孩子为空，说明该单分支结点只有右孩子，保存有孩子
	}

	// 判断此结点是否是根结点
	if (pNode == m_pRoot)
	{
		m_pRoot = pChild;	// 将该结点的左孩子或者有孩子置为根结点
		pChild->m_pParent = nullptr;	// 置空
		delete pNode;	// 删除该前结点
		pNode = nullptr;
		return;
	}

	// 删除的是左孩子
	if (pParent->m_pLeft == pNode)
	{
		pParent->m_pLeft = pChild;
	}
	// 删除的是右孩子
	else
	{
		pParent->m_pRight = pChild;
	}

	// 删除结点的孩子结点指向删除结点的父亲结点
	pChild->m_pParent = pParent;

	// 删出该结点
	delete pNode;
	pNode = nullptr;
}


/*=======================================================
*	void CBinarySearchTree::DelSingleChildNode(PNODE pNode)
*	-- 删除的结点为双分支结点（该结点有两个孩子 左孩子和右孩子）
*	参数：PNODE pNode -- 要删除数据对应的结点
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::DelDoubleChildNode(PNODE pNode)
{
	// 查找要删除结点的左字数的最大值和要删除结点的数据值进行交换
	PNODE pTempNode = pNode->m_pLeft;

	while (pTempNode->m_pRight != nullptr)
	{
		// 找到左子树中最右结点，该结点保存的数据为左子树中的值最大的数据
		pTempNode = pTempNode->m_pRight;
	}

	// 找到左子树中的最大值，交换数值
	int nTempNum = pNode->m_val;
	pNode->m_val = pTempNode->m_val;
	pTempNode->m_val = nTempNum;

	// 删除 pTempNode，此时还需要判断交换后的结点处于那种情况
	DelNode(pTempNode);
}


/*=======================================================
*	void CBinarySearchTree::MLR(PNODE pNode) -- 递归 前序 遍历
*
*	参数：PNODE pNode -- 开始遍历的根结点
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::MLR(PNODE pNode)
{
	// 递归的出口
	if (pNode == nullptr)
	{
		return;
	}
	cout << pNode->m_val << " ";	// 先自己
	MLR(pNode->m_pLeft);	// 再左孩子
	MLR(pNode->m_pRight);	// 再右孩子
}


/*=======================================================
*	void CBinarySearchTree::LMR(PNODE pNode) -- 递归 中序 遍历
*
*	参数：PNODE pNode -- 开始遍历的根结点
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::LMR(PNODE pNode)
{
	// 递归的出口
	if (pNode == nullptr)
	{
		return;
	}

	LMR(pNode->m_pLeft);	// 先左孩子
	cout << pNode->m_val << " ";	// 再自己
	LMR(pNode->m_pRight);	// 再右孩子
}


/*=======================================================
*	void CBinarySearchTree::LRM(PNODE pNode) -- 递归 后序 遍历
*
*	参数：PNODE pNode -- 开始遍历的根结点
*
*	返回值：无
*
*	警告：无
*
*	更新：2020/06/08
*
========================================================*/
void CBinarySearchTree::LRM(PNODE pNode)
{
	// 递归的出口
	if (pNode == nullptr)
	{
		return;
	}

	LRM(pNode->m_pLeft);	// 先左孩子
	LRM(pNode->m_pRight);	// 再右孩子
	cout << pNode->m_val << " ";	// 再自己
}