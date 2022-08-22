#include "bintree.h"
#include <stdlib.h>
#include <stdio.h>

void	preorderTraversalBinTree(BinTreeNode* pNode)
{
	printf("%d", pNode->data);
	pNode->visited = 1;
	if (getLeftChildNodeBT(pNode) && getLeftChildNodeBT(pNode)->visited == 0)
		preorderTraversalBinTree(getLeftChildNodeBT(pNode));
	if (getRightChildNodeBT(pNode) && getRightChildNodeBT(pNode)->visited == 0)
		preorderTraversalBinTree(getRightChildNodeBT(pNode));
}

void	inorderTraversalBinTree(BinTreeNode* pNode)
{
	if (getLeftChildNodeBT(pNode) && getLeftChildNodeBT(pNode)->visited == 0)
		inorderTraversalBinTree(getLeftChildNodeBT(pNode));
	printf("%d", pNode->data);
	pNode->visited = 1;
	if (getRightChildNodeBT(pNode) && getRightChildNodeBT(pNode)->visited == 0)
		inorderTraversalBinTree(getRightChildNodeBT(pNode));
}

void	levelOrderTraversalBinTree(BinTreeNode* pNode)
{
	if (getLeftChildNodeBT(pNode) && getLeftChildNodeBT(pNode)->visited == 0)
		levelOrderTraversalBinTree(getLeftChildNodeBT(pNode));
	if (getRightChildNodeBT(pNode) && getRightChildNodeBT(pNode)->visited == 0)
		levelOrderTraversalBinTree(getRightChildNodeBT(pNode));
	printf("%d", pNode->data);
	pNode->visited = 1;
}

BinTree* makeBinTree(BinTreeNode rootNode)
{
	BinTree	*temp;

	temp = (BinTree *)malloc(sizeof(BinTree));
	if (!temp)
		exit (12);
	temp->pRootNode = (BinTreeNode *)malloc(sizeof(BinTreeNode));
	if (!temp->pRootNode)
		exit (12);
	*temp->pRootNode = rootNode;
	return (temp);
}

BinTreeNode* getRootNodeBT(BinTree* pBinTree)
{
	if (!pBinTree)
		return (NULL);
	else
		return (pBinTree->pRootNode);
}

BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
	BinTreeNode	*temp;

	if (!pParentNode || pParentNode->pLeftChild)
		return (NULL);
	temp = malloc(sizeof(BinTreeNode));
	if (!temp)
		exit (12);
	*temp = element;
	pParentNode->pLeftChild = temp;
	return (pParentNode->pLeftChild);
}

BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
	BinTreeNode	*temp;

	if (!pParentNode || pParentNode->pRightChild)
		return (NULL);
	temp = malloc(sizeof(BinTreeNode));
	if (!temp)
		exit (12);
	*temp = element;
	pParentNode->pRightChild = temp;
	return (pParentNode->pRightChild);
}

BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode)
{
	if (!pNode)
		return (NULL);
	return (pNode->pLeftChild);
}

BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode)
{
	if (!pNode)
		return (NULL);
	return (pNode->pRightChild);
}

void deleteBinTree(BinTree* pBinTree)
{
	if (!pBinTree)
		return ;
	else
		clearBinTreeNode(getRootNodeBT(pBinTree));
}

void clearBinTreeNode(BinTreeNode* pNode)
{
	if (getLeftChildNodeBT(pNode))
		clearBinTreeNode(getLeftChildNodeBT(pNode));
	if (getRightChildNodeBT(pNode))
		clearBinTreeNode(getRightChildNodeBT(pNode));
	free(pNode);
	pNode = NULL;
}

int	serch_data(BinTree *pBinTree, int key)
{
	BinTreeNode	*temp;

	if (!pBinTree)
		return (0);
	temp = getRootNodeBT(pBinTree);
	while (!temp)
	{
		if (temp->data == key)
			return (0);
		else if (temp->data > key)
			temp = getLeftChildNodeBT(temp);
		else
			temp = getRightChildNodeBT(temp);
	}
	return (1);
}

void deleteBinTreeNode2(BinTreeNode **pNode, BinTreeNode* left, BinTreeNode* right)
{
	if (!left && !right)
	{
		free(*pNode);
		*pNode = NULL;
	}
	else if (!right && left)
	{
		free(*pNode);
		*pNode = left;
	}
	else if (right && !left)
	{
		free(*pNode);
		*pNode = right;
	}
}

void deleteBinTreeNode(BinTreeNode **temp)
{
	BinTreeNode	*child;
	BinTreeNode	*right;
	BinTreeNode	*left;
	BinTreeNode	*parent;
	BinTreeNode	*pNode;

	pNode = *temp;
	if (!pNode)
		return ;
	left = getLeftChildNodeBT(pNode);
	right = getRightChildNodeBT(pNode);
	parent = pNode;
	child = left;
	if (!left || !right)
		return (deleteBinTreeNode2(temp, left, right));
	else if (!left->pLeftChild && !left->pRightChild)
	{
		parent->pLeftChild = NULL;
		child->pLeftChild = pNode->pLeftChild;
		child->pRightChild = pNode->pRightChild;
		*pNode = *child;
		free(child);
	}
	else
	{
		while (getRightChildNodeBT(child))
		{
			parent = child;
			child = getRightChildNodeBT(parent);
		}
		parent->pRightChild = child->pLeftChild;
		child->pLeftChild = pNode->pLeftChild;
		child->pRightChild = pNode->pRightChild;
		*pNode = *child;
		free(child);
	}
}

BinTree	*make_tree(void)
{
	BinTree	*tree;
	BinTreeNode	temp[13];
	BinTreeNode	*right1;
	BinTreeNode	*left1;
	BinTreeNode	*right2_1;
	BinTreeNode	*right2_2;
	BinTreeNode	*left2_1;
	BinTreeNode	*left2_2;
	int	input;
	int i;

	i = 0;
	input = 0;
	while (i < 13)
	{
		temp[i].data = input++;
		temp[i].visited = 0;
		temp[i].pLeftChild = NULL;
		temp[i++].pRightChild = NULL;
	}
	tree = makeBinTree(temp[6]);
	left1= insertLeftChildNodeBT(getRootNodeBT(tree),temp[3]);
	right1 = insertRightChildNodeBT(getRootNodeBT(tree), temp[8]);
	left2_1 = insertLeftChildNodeBT(left1, temp[1]);
	left2_2 = insertRightChildNodeBT(left1, temp[5]);
	right2_1 = insertLeftChildNodeBT(right1, temp[7]);
	right2_2 = insertRightChildNodeBT(right1, temp[9]);
	insertLeftChildNodeBT(left2_1, temp[0]);
	insertRightChildNodeBT(left2_1, temp[2]);
	insertLeftChildNodeBT(left2_2, temp[4]);
/*	insertRightChildNodeBT(right2_1, temp[10]);
	insertLeftChildNodeBT(right2_2, temp[11]);
	insertRightChildNodeBT(right2_2, temp[12]);*/
//	deleteBinTreeNode(&right2_2->pLeftChild);
//	deleteBinTreeNode(&left2_1);
	return (tree);
}

int	main(void)
{
	BinTree	*tree;
	BinTreeNode *temp;

	tree = make_tree();
	temp = getRootNodeBT(tree);
	deleteBinTreeNode(&temp);
	printf("preorder\n");
	inorderTraversalBinTree(getRootNodeBT(tree));
	deleteBinTree(tree);
}