#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    bool lbit; // True if left points to a child, False if thread
    bool rbit; // True if right points to a child, False if thread
    Node(int val) : data(val), lbit(0), rbit(0), left(nullptr), right(nullptr) {}
};

class ThreadedBinaryTree
{
private:
    Node *header; // Header node to simplify traversal

public:
    ThreadedBinaryTree()
    {
        header = new Node(-1);  // Header node
        header->left = header;  // Left points to itself initially
        header->right = header; // Right points to itself
        header->lbit = 0;
        header->rbit = 1; // Right points to header (circular)
    }

    // Insert a new node into the tree
    void insert(int val)
    {
        Node *newnode = new Node(val);
        if (header->lbit == 0)
        {                                   // Tree is empty
            newnode->left = header->left;   // Thread to header
            newnode->right = header->right; // Thread to header
            newnode->lbit = newnode->rbit = 0;
            header->left = newnode;
            header->lbit = 1; // Header's left is now a child
        }
        else
        {
            Node *curr = header->left;
            Node *parent = header;
            // Find the correct position
            while (true)
            {
                if (curr->data > val)
                {
                    if (curr->lbit == 0)
                        break;
                    parent = curr;
                    curr = curr->left;
                }
                else if (curr->data < val)
                {
                    if (curr->rbit == 0)
                        break;
                    parent = curr;
                    curr = curr->right;
                }
                else
                {
                    cout << "Duplicate value ignored: " << val << endl;
                    delete newnode;
                    return;
                }
            }
            // Insert new node
            if (val < curr->data)
            {
                newnode->left = curr->left;
                newnode->right = curr;
                newnode->lbit = newnode->rbit = 0;
                curr->left = newnode;
                curr->lbit = 1;
            }
            else
            {
                newnode->right = curr->right;
                newnode->left = curr;
                newnode->lbit = newnode->rbit = 0;
                curr->right = newnode;
                curr->rbit = 1;
            }
        }
    }

    // Inorder Traversal
    void inorder()
    {
        Node *curr = header->left; // Start at root
        if (curr == header)
        {
            cout << "Tree is empty!" << endl;
            return;
        }
        // Move to leftmost node
        while (curr->lbit == 1)
        {
            curr = curr->left;
        }
        // Traverse using threads
        while (curr != header)
        {
            cout << curr->data << " ";
            if (curr->rbit == 0)
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->right;
                while (curr->lbit == 1)
                {
                    curr = curr->left;
                }
            }
        }
        cout << endl;
    }

    // Preorder Traversal
    void preorder()
    {
        Node *curr = header->left; // Start at root
        if (curr == header)
        {
            cout << "Tree is empty!" << endl;
            return;
        }
        while (curr != header)
        {
            cout << curr->data << " ";
            if (curr->lbit == 1)
            {
                curr = curr->left;
            }
            else if (curr->rbit == 1)
            {
                curr = curr->right;
            }
            else
            {
                while (curr != header && curr->rbit == 0)
                {
                    curr = curr->right;
                }
                if (curr != header)
                {
                    curr = curr->right;
                }
            }
        }
        cout << endl;
    }
};

int main()
{
    ThreadedBinaryTree tbt;

    // Insert elements
    tbt.insert(50);
    tbt.insert(30);
    tbt.insert(70);
    tbt.insert(20);
    tbt.insert(40);
    tbt.insert(60);
    tbt.insert(80);

    // Traversals
    cout << "Inorder Traversal: ";
    tbt.inorder(); // Output: 20 30 40 50 60 70 80

    cout << "Preorder Traversal: ";
    tbt.preorder(); // Output: 50 30 20 40 70 60 80

    return 0;
}