#include "pch.h"
#include "HuffTree.h"


HuffTree::HuffTree(HuffToken * value, HuffTree * left, HuffTree * right) :
	Tree(value, left, right)
{}

HuffTree::HuffTree(HuffDict & huffTokens) : Tree(0)
{
	size_t n = huffTokens.size;
	HuffTree ** nodes = new HuffTree * [n];
	
	for (size_t i = 0; i < n; i++) nodes[i] = new HuffTree(huffTokens[i]);
	while (--n) reduceNodes(nodes, n);

	*this = *nodes[0];
}

void HuffTree::modifyCode(HuffTree * node, char prefix)
{
	if (node->left) modifyCode(static_cast<HuffTree *>(node->left), prefix);
	if (node->right) modifyCode(static_cast<HuffTree *>(node->right), prefix);
	node->value->code = prefix + node->value->code;

}

void HuffTree::combineLastNodes(HuffTree ** nodes, size_t lastNodeNum)
{
	modifyCode(nodes[lastNodeNum], '0');
	modifyCode(nodes[lastNodeNum - 1], '1');

	HuffToken * newValue = new HuffToken('0',
		nodes[lastNodeNum]->value->freq + nodes[lastNodeNum - 1]->value->freq);

	nodes[lastNodeNum - 1] = new HuffTree(newValue, nodes[lastNodeNum], nodes[lastNodeNum - 1]);
}

void HuffTree::reduceNodes(HuffTree ** nodes, size_t lastNodeNum)
{
	combineLastNodes(nodes, lastNodeNum);
	size_t i = lastNodeNum - 1;
	while (i && nodes[i - 1]->value->freq < nodes[i]->value->freq)
	{
		swapNodes(nodes[i - 1], nodes[i]), i--;
	}
}

void HuffTree::swapNodes(HuffTree * a, HuffTree * b)
{
	HuffTree t = *a;
	*a = *b;
	*b = t;
}
