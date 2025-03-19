//============================================================================
// Name        : Tree_Assignment_1.cpp
// Author      : vivek Mane
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
	int data;
	Node *left;
	Node *right;
	Node(int d)
	{
		data = d;
		left = nullptr;
		right = nullptr;
	}
};
Node *createBT()
{
	queue<Node *> q;
	cout << "Enter value of root" << endl;
	int n;
	cin >> n;
	if (n == -1)
		return nullptr;
	//	bool start  =1;
	Node *curr = new Node(n);
	Node *root = new Node(n);
	q.push(root);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		cout << "enter values of left and right nodes of" << curr->data << endl;
		int leftval, rightval;
		cin >> leftval >> rightval;
		if (leftval == -1)
		{
			curr->left = nullptr;
		}
		else
		{
			curr->left = new Node(leftval);
			q.push(curr->left);
		}
		if (rightval == -1)
		{
			curr->right = nullptr;
		}
		else
		{
			curr->right = new Node(rightval);
			q.push(curr->right);
		}
	}
	return root;
}

void inorder(Node *root, vector<int> &arr)
{
	if (!root)
		return;
	inorder(root->left, arr);
	arr.push_back(root->data);
	inorder(root->right, arr);
}

void preorder(Node *root, vector<int> &arr)
{
	if (!root)
		return;
	arr.push_back(root->data);
	preorder(root->left, arr);
	preorder(root->right, arr);
}
void postorder(Node *root, vector<int> &arr)
{
	if (!root)
		return;
	postorder(root->left, arr);
	postorder(root->right, arr);
	arr.push_back(root->data);
}

void swaptree(Node *root)
{
	if (!root)
		return;
	swap(root->left, root->right);
	swaptree(root->left);
	swaptree(root->right);
}

void copytree(Node *root, Node *newroot)
{
	if (!root)
	{
		return;
	}
	if (root->left)
	{
		newroot->left = new Node(root->left->data);
	}
	if (root->right)
	{
		newroot->right = new Node(root->right->data);
	}
	copytree(root->left, newroot->left);
	copytree(root->right, newroot->right);
}

int maxheight(Node *root)
{
	if (!root)
		return 0;
	int lh = maxheight(root->left);
	int rh = maxheight(root->right);
	return 1 + max(lh, rh);
}

int countnodes(Node *root, int &height)
{
	if (!root)
		return 0;
	height++;
	int lh = countnodes(root->left, height);
	int rh = countnodes(root->right, height);
	if (!lh && !rh)
		return 1;
	return lh + rh;
}
void inorderiterative(Node *root, vector<int> &arr)
{
	stack<Node *> st;
	while (true)
	{
		if (root)
		{
			st.push(root);
			root = root->left;
		}
		else
		{
			if (st.empty())
				break;
			Node *curr = st.top();
			st.pop();
			arr.push_back(curr->data);
			root = curr->right;
		}
	}
}

void iterativepreorder(Node *root, vector<int> &arr)
{
	stack<Node *> st;
	st.push(root);
	while (!st.empty())
	{
		Node *curr = st.top();
		st.pop();
		arr.push_back(curr->data);
		if (curr->right)
		{
			st.push(curr->right);
		}
		if (curr->left)
		{
			st.push(curr->left);
		}
	}
}
void iterativepostorder(Node *root, vector<int> &arr)
{
	stack<Node *> st1;
	stack<Node *> st2;
	st1.push(root);
	while (!st1.empty())
	{
		Node *curr = st1.top();
		st1.pop();
		st2.push(curr);
		if (curr->left)
		{
			st1.push(curr->left);
		}
		if (curr->right)
		{
			st1.push(curr->right);
		}
	}
	while (!st2.empty())
	{
		arr.push_back(st2.top()->data);
		st2.pop();
	}
}

void deletebinarytree(Node *root)
{
	queue<Node *> q;
	q.push(root);
	while (!q.empty())
	{
		int n = q.size();
		for (int i = 0; i < n; i++)
		{
			Node *curr = q.front();
			q.pop();
			if (curr->left)
			{
				q.push(curr->left);
			}
			if (curr->right)
			{
				q.push(curr->right);
			}
			curr->left = nullptr;
			curr->right = nullptr;
			delete (curr);
		}
	}
}
int main()
{
	while (true)
	{
		cout << "1.create Binary Tree" << endl;
		cout << "2.traversals" << endl;
		cout << "3.swap Binary Tree" << endl;
		cout << "4.copy Binary Tree" << endl;
		cout << "5.Height of Binary Tree" << endl;
		cout << "6.Leaf and Non-Leaf Nodes in Binary Tree" << endl;
		cout << "7. Erase all Nodes" << endl;
		cout << "8.Exit" << endl;
		int ch;
		cout << "enter choice" << endl;
		cin >> ch;
		Node *root;
		if (ch == 1)
		{
			// creation of tree
			root = createBT();
		}

		else if (ch == 2)
		{

			vector<int> arr;
			inorder(root, arr);
			cout << "Inorder" << endl;
			for (int i = 0; i < arr.size(); i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
			arr.clear();
			// iterative
			inorderiterative(root, arr);
			cout << "Iterative Inorder" << endl;

			for (int i = 0; i < arr.size(); i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
			cout << endl;

			vector<int> arr1;

			preorder(root, arr1);
			cout << "preorder" << endl;
			for (int i = 0; i < arr1.size(); i++)
			{
				cout << arr1[i] << " ";
			}
			arr1.clear();
			cout << endl;

			iterativepreorder(root, arr1);
			cout << "Iterative preorder" << endl;
			for (int i = 0; i < arr1.size(); i++)
			{
				cout << arr1[i] << " ";
			}
			cout << endl;
			cout << endl;

			vector<int> arr2;

			postorder(root, arr2);
			cout << "postorder" << endl;
			for (int i = 0; i < arr2.size(); i++)
			{
				cout << arr2[i] << " ";
			}
			cout << endl;
			arr2.clear();

			iterativepostorder(root, arr2);
			cout << "Iterative postorder" << endl;
			for (int i = 0; i < arr2.size(); i++)
			{
				cout << arr2[i] << " ";
			}
			cout << endl;
			cout << endl;
		}

		else if (ch == 3)
		{

			// swap tree
			swaptree(root);
			vector<int> arr3;
			inorder(root, arr3);
			cout << "Inorder of swapped tree" << endl;
			for (int i = 0; i < arr3.size(); i++)
			{
				cout << arr3[i] << " ";
			}
			cout << endl;
		}

		else if (ch == 4)
		{
			// copying of tree
			Node *newroot = new Node(root->data);
			copytree(root, newroot);
			vector<int> arr4;
			inorder(newroot, arr4);
			cout << "Inorder of coppied tree" << endl;
			for (int i = 0; i < arr4.size(); i++)
			{
				cout << arr4[i] << " ";
			}
			cout << endl;
		}
		else if (ch == 5)
		{
			// height of binary tree
			int height = maxheight(root);
			cout << "Maximum height of binary tree is " << height << endl;
		}
		else if (ch == 6)
		{
			// count internal and leaf nodes
			int totalheight = 0;
			int leafs = countnodes(root, totalheight);
			cout << "Number of leaf nodes: " << leafs << endl;
			cout << "Number fof non leaf nodes:" << totalheight - leafs - 1 << endl;
		}
		else if (ch == 7)
		{
			// delete binary tree
			deletebinarytree(root);
			cout << "Deleted all Nodes of Tree" << endl;
			cout << root->data << endl;
			vector<int> arr;
			inorder(root, arr);
			cout << "Inorder" << endl;
			for (int i = 0; i < arr.size(); i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
		}
		else
			break;
	}

	return 0;
}
