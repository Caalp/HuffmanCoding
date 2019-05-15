#pragma once

#include <stdint.h>
typedef struct HuffmanNode
{
	char ch;
	int count = 1;
	HuffmanNode* left;
	HuffmanNode* right;

}*HuffmanNodePtr;
typedef struct code {
	size_t code_length;
	uint32_t code;
} code;
class BS_Tree
{
public:
	BS_Tree() :root(NULL) {}
	void insert(HuffmanNodePtr head);
	void CreatebitTable(HuffmanNodePtr node, code *t, code c);
	void code_print(code *c);

public:
	int totalbits;
	HuffmanNodePtr root;

};
