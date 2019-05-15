#include "BST.h"
#include<iostream>
#include<queue>
#include<map>
#include<fstream>
#include<vector>
#include <functional>
#include<set>

using namespace std;


namespace customUtil
{
	struct Huffman_Compare
	{
		bool operator() (const HuffmanNode* lhs, const HuffmanNode* rhs)
		{
			return lhs->count > rhs->count;
		}
	};
	

};

int main()
{
	
	priority_queue<HuffmanNode*,vector<HuffmanNode*>,customUtil::Huffman_Compare> h_table;
	map <char, int>table;
	
	vector<char> text;
	BS_Tree bst;
	ifstream ifs("input.txt", ios_base::in);
	char a;
	ifs >> noskipws;
	
	while (ifs >> a)
	{
		
		text.emplace_back(a);

	}
	for (auto c : text)
	{
		table[c]++;
	}
	
	for (auto entry : table)
	{
		HuffmanNode* n = new HuffmanNode;
		n->ch = entry.first;
		n->count = entry.second;
		n->left = n->right = nullptr;
		h_table.push(n);
	}
	
	vector<HuffmanNode*> headPtrs;
	HuffmanNodePtr temp;
	int i = 0;
	while (h_table.size() > 0)
	{
		HuffmanNodePtr h1 = new HuffmanNode;
		h1 = h_table.top();
		h1->left = nullptr;
		h1->right = nullptr;
		h_table.pop();
		HuffmanNodePtr h2 = new HuffmanNode;
		h2 = h_table.top();
		h2->left = nullptr;
		h2->right = nullptr;
		h_table.pop();
		HuffmanNodePtr t = new HuffmanNode;
		if (h1->count == 1 && h2->count == 1)
		{
			
			t->left = h1;
			t->right = h2;
			t->ch = '\0';
			t->count = h1->count + h2->count;
			headPtrs.push_back(t);
		}
		else
		{
			if (i == headPtrs.size())
			{
				i = 0;
			}
				if (headPtrs[i]->count == h1->count)
				{
					//HuffmanNodePtr t2 = new HuffmanNode;
					t->left = headPtrs[i];
					t->right = h1;
					t->count = headPtrs[i]->count + h1->count;
					t->ch = '\0';
					headPtrs[i] = t;
					
					if (i != headPtrs.size())
					{
						//HuffmanNodePtr t3 = new HuffmanNode;
						t = new HuffmanNode;
						t->left = headPtrs[i+1];
						t->right = h2;
						t->count = headPtrs[i+1]->count + h2->count;
						t->ch = '\0';
						headPtrs[i+1] = t;
					}
					else
					{
						//HuffmanNodePtr t3 = new HuffmanNode;
						t = new HuffmanNode;
						t->left = headPtrs[0];
						t->right = h2;
						t->count = headPtrs[0]->count + h2->count;
						t->ch = '\0';
						headPtrs[0] = t;
					}
					i++;
					
				}
				else if (headPtrs[i]->count > h1->count)
				{
					t = new HuffmanNode;
					//HuffmanNodePtr t3 = new HuffmanNode;
					t->left = h1;
					t->right = h2;
					t->count = h1->count + h2->count;
					t->ch = '\0';
					temp = new HuffmanNode;
					temp->count = headPtrs[i]->count + t->count;
					temp->ch = '\0';
					if (t->count > headPtrs[i]->count)
					{
						temp->right = t;
						temp->left = headPtrs[i];
					}
					else
					{
						temp->right = headPtrs[i];
						temp->left = t;
					}
					headPtrs[i] = temp;
					i++;
					
				}
				else 
				{
					
					//HuffmanNodePtr t4 = new HuffmanNode;
					t = new HuffmanNode;
					t->left = headPtrs[i];
					t->right = h1;
					t->count = headPtrs[i]->count + h1->count;
					t->ch = '\0';
					headPtrs[i] = t;
					i++;
					if (i + 1 >= headPtrs.size())
					{
						i = 0;
					}
					 temp = new HuffmanNode;
					temp->left = headPtrs[i];
					temp->right = h1;
					temp->count = headPtrs[i]->count + h1->count;
					temp->ch = '\0';
					headPtrs[i] = temp;
					i++;
					

				}
				
			}
		
	}
	//combine huffmannodeptr's under one root pointer
	
	if (headPtrs.size() % 2 == 0)
	{
		for (int i = headPtrs.size() -1 ; i >= 0; i -= 2)
		{
			temp = new HuffmanNode;
			temp->count = headPtrs[i]->count + headPtrs[i-1]->count;
			if (headPtrs[i]->count > headPtrs[i - 1]->count)
			{
				temp->right = headPtrs[i];
				temp->left = headPtrs[i - 1];
			}
			else
			{
				temp->right = headPtrs[i-1];
				temp->left = headPtrs[i];
			}
			temp->ch = '\0';
			if (bst.root == nullptr)
			{
				bst.root = temp;
			}
			else
			{
				HuffmanNodePtr t = new HuffmanNode;
				if (temp->count > bst.root->count)
				{
					t->right = temp;
					t->left = bst.root;
					
				}
				else
				{
					t->right = bst.root;
					t->left = temp;
				}
				t->count = temp->count + bst.root->count;
				t->ch = '\0';
				bst.root = nullptr;
				bst.root = new	HuffmanNode;
				bst.root = t;
			}

		}
	}
	else
	{
		for (int i = headPtrs.size() - 2; i >= 0; i -= 2)
		{
			HuffmanNodePtr temp = new HuffmanNode;
			temp->count = headPtrs[i]->count + headPtrs[i - 1]->count;
			if (headPtrs[i]->count > headPtrs[i - 1]->count)
			{
				temp->right = headPtrs[i];
				temp->left = headPtrs[i - 1];
			}
			else
			{
				temp->right = headPtrs[i - 1];
				temp->left = headPtrs[i];
			}
			temp->ch = '\0';
			if (bst.root == nullptr)
			{
				bst.root = temp;
			}
			else
			{
				HuffmanNodePtr t6 = new HuffmanNode;
				if (temp->count > bst.root->count)
				{
					t6->right = temp;
					t6->left = bst.root;

				}
				else
				{
					t6->right = bst.root;
					t6->left = temp;
				}
				t6->count = temp->count + bst.root->count;
				t6->ch = '\0';
				bst.root = nullptr;
				bst.root = new	HuffmanNode;
				bst.root = t6;
			}

		}
		HuffmanNodePtr t6 = new HuffmanNode;
		if ( headPtrs.back() ->count > bst.root->count)
		{
			t6->right = headPtrs.back();
			t6->left = bst.root;

		}
		else
		{
			t6->right = bst.root;
			t6->left = headPtrs.back();
		}
		t6->count = headPtrs.back()->count + bst.root->count;
		t6->ch = '\0';
		bst.root = nullptr;
		bst.root = new	HuffmanNode;
		bst.root = t6;
	}
	
	code table1[256] = { 0 };
	code c = { 0 };
	bst.CreatebitTable(bst.root, table1, c);


	// this functions intented to print out huffman encoding results of corresponding letter according to example txt from huffman table
	for (auto elem : text)
	{
		bst.code_print(&table1[elem]);
		cout << " ";
	}

	cout << bst.totalbits << endl;
	
	system("pause");
	return 0;
}
