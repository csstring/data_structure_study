#include "bintree.h"
#include <stdlib.h>
#include <stdio.h>

void	preorderTraversalBinTree(BinTreeNode* pNode)
{
	printf("%c", pNode->data);
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
	printf("%c", pNode->data);
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
	printf("%c", pNode->data);
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
//	printf("free_node data : %c\n", pNode->data);
	free(pNode);
	pNode = NULL;
}
void deleteBinTreeNode2(BinTreeNode* pNode, BinTreeNode* left, BinTreeNode* right)
{
	if (!left && !right)
	{
		free(pNode);
		pNode = NULL;
	}
	else if (!right && left)
	{
		*pNode = *left;
		free(left);
	}
	else if (right && !left)
	{
		*pNode = *right;
		free(right);
	}
}
void deleteBinTreeNode(BinTreeNode* pNode)
{
	BinTreeNode	*child;
	BinTreeNode	*right;
	BinTreeNode	*left;
	BinTreeNode	*parent;

	if (!pNode)
		return ;
	left = getLeftChildNodeBT(pNode);
	right = getRightChildNodeBT(pNode);
	parent = pNode;
	child = left;
	if (!left || !right)
		return (deleteBinTreeNode2(pNode, left, right));
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
		while (1)
		{
			if (getRightChildNodeBT(child))
			{
				parent = child;
				child = getRightChildNodeBT(parent);
				continue;
			}
			if (getLeftChildNodeBT(child))
			{
				parent = child;
				child = getLeftChildNodeBT(parent);
				continue;
			}
			break;
		}
		if (getRightChildNodeBT(parent))
			parent->pRightChild = NULL;
		else
			parent->pLeftChild = NULL;
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
	input = 65;
	while (i < 13)
	{
		temp[i].data = input++;
		temp[i].visited = 0;
		temp[i].pLeftChild = NULL;
		temp[i++].pRightChild = NULL;
	}
	tree = makeBinTree(temp[0]);
	left1= insertLeftChildNodeBT(getRootNodeBT(tree),temp[1]);
	right1 = insertRightChildNodeBT(getRootNodeBT(tree), temp[2]);
	left2_1 = insertLeftChildNodeBT(left1, temp[3]);
	left2_2 = insertRightChildNodeBT(left1, temp[4]);
	right2_1 = insertLeftChildNodeBT(right1, temp[5]);
	right2_2 = insertRightChildNodeBT(right1, temp[6]);
	insertLeftChildNodeBT(left2_1, temp[7]);
	insertRightChildNodeBT(left2_1, temp[8]);
	insertLeftChildNodeBT(left2_2, temp[9]);
	insertRightChildNodeBT(right2_1, temp[10]);
	insertLeftChildNodeBT(right2_2, temp[11]);
	insertRightChildNodeBT(right2_2, temp[12]);
	deleteBinTreeNode(right2_2->pLeftChild);
	right2_2->pLeftChild = NULL;
	return (tree);
}

int	main(void)
{
	BinTree	*tree;

	tree = make_tree();
	printf("preorder\n");
	preorderTraversalBinTree(getRootNodeBT(tree));
//	printf("\ninorder\n");
//	inorderTraversalBinTree(getRootNodeBT(tree));
//	levelOrderTraversalBinTree(getRootNodeBT(tree));
	deleteBinTree(tree);
}