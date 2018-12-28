#include "pch.h"
#include "HuffTree.h"

HuffTree::HuffTree(HuffToken value, HuffTree * left, HuffTree * right) :
	Tree(value, left, right)
{}

HuffTree::HuffTree(HuffDict & huffTokens) : Tree(HuffToken())
{
	if (!huffTokens.size) return;
	size_t n = huffTokens.size;
	HuffTree * nodes = createNodes(huffTokens);
	while (--n) reduceNodes(nodes, n, huffTokens);

	*this = *nodes;
	delete[] nodes;
}

HuffTree * HuffTree::createNodes(HuffDict & huffTokens)
{
	HuffTree * nodes = new HuffTree[huffTokens.size];
	for (size_t i = 0; i < huffTokens.size; i++) nodes[i] = HuffTree(*huffTokens[i]);
	return nodes;
}

void HuffTree::reduceNodes(HuffTree * nodes, size_t lastNodeNum, HuffDict & huffTokens)
{
	combineLastNodes(nodes, lastNodeNum, huffTokens);
	size_t i = lastNodeNum - 1;
	while (i && nodes[i - 1].value.freq < nodes[i].value.freq)
	{
		swapNodes(nodes[i - 1], nodes[i]), i--;
	}
}

void HuffTree::combineLastNodes(HuffTree * nodes, size_t lastNodeNum, HuffDict & huffTokens)
{
	modifyCode(nodes + lastNodeNum, '0', huffTokens);
	modifyCode(nodes + lastNodeNum - 1, '1', huffTokens);

	HuffToken newValue('0', nodes[lastNodeNum].value.freq + nodes[lastNodeNum - 1].value.freq);
	HuffTree * newLeft = new HuffTree(nodes[lastNodeNum]);
	HuffTree * newRight = new HuffTree(nodes[lastNodeNum - 1]);

	nodes[lastNodeNum - 1] = HuffTree(newValue, newLeft, newRight);
}

void HuffTree::modifyCode(HuffTree * node, char prefix, HuffDict & huffTokens)
{
	if (node->left) modifyCode(static_cast<HuffTree *>(node->left), prefix, huffTokens);
	if (node->right) modifyCode(static_cast<HuffTree *>(node->right), prefix, huffTokens);
	node->value.code = prefix + node->value.code;
	if (!node->left && !node->right) huffTokens(node->value.symbol)->code = node->value.code;
}

void HuffTree::swapNodes(HuffTree & a, HuffTree & b)
{
	HuffTree t = a;
	a = b;
	b = t;
}
