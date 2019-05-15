#include "BST.h"
#include<iostream>


//Insert function written for creating huffman tree based on pairing two smallest element in prior condition
//Also this function adds up frequency of leafs and creates a node for further insertion
void BS_Tree::insert(HuffmanNodePtr head)
{
	if (root == NULL)
	{
		root = new HuffmanNode;
		root->ch = head->ch;
		root->count = head->count;
		root->left = head->left;
		root->right = head->right;
	}
	else
	{
		HuffmanNodePtr temp = new HuffmanNode;
		temp->ch = '\0';
		temp->count = root->count + head->count;
		temp->right = root;
		temp->left = head;
		root = temp;

	}
	
}

//from tree creation of table is done by this function in order to enhance better performance and fast access to elements when neeeded
void BS_Tree::CreatebitTable(HuffmanNodePtr node, code* t, code c)
{
	if (node->left == NULL)
		t[node->ch] = c;
	else {
		c.code_length++;
		c.code <<= 1;
		CreatebitTable(node->left, t, c);
		c.code += 1;
		CreatebitTable(node->right, t, c);
	}
}
// fucntion print outs back tracked huffman branches we've passed through 1 for right 0 for left according to algorithm
void BS_Tree::code_print(code * c)
{
	size_t n = c->code_length;
	while (n-- > 0)
	{
		totalbits++;
		putchar('0' + ((c->code >> n) & 1));
	}
}
