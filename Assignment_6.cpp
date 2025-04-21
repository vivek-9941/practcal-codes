/*
Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to
perform BFS. Use the map of the area around the college as the graph.
Identify the prominent land marks as nodes and perform DFS and BFS on that.
Functions to be implemented:
1. Read graph
2. Display adjacency list
3. DFS
4. BFSaj	 : 	4aj	 :
5. indegree & outdegree
6. isConnected
*/

#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    string name;
    Node *next;
    Node *down;

    Node(string n = "")
    {
        name = n;
        next = nullptr;
        down = nullptr;
    }
};

class Graph
{
public:
    Node *head = nullptr;
    void add(string A, string B)
    {
        if (head == nullptr)
        {
            Node *nodea = new Node(A);
            Node *nodeb = new Node(B);
            head = nodea;
            nodea->next = nodeb;
        }
        else
        {
            Node *curr = head;
            Node *prev = nullptr;
            bool found = false;
            while (curr != nullptr)
            {
                if (curr->name == A)
                {
                    found = 1;
                    Node *currlist = curr;
                    while (currlist->next != nullptr)
                    {
                        currlist = currlist->next;
                    }
                    currlist->next = new Node(B);
                    break;
                }
                prev = curr;
                curr = curr->down;
            }
            if (!found)
            {
                Node *nodea = new Node(A);
                Node *nodeb = new Node(B);
                prev->down = nodea;
                nodea->next = nodeb;
            }
        }
    }
    void addnode(string a, string b)
    {
        add(a, b);
        add(b, a);
    }

    void print()
    {
        Node *currentArrayNode = head;
        while (currentArrayNode != nullptr)
        {
            Node *currentListNode = currentArrayNode;
            while (currentListNode != nullptr)
            {
                cout << currentListNode->name << " -> ";
                currentListNode = currentListNode->next;
            }
            cout << endl;
            currentArrayNode = currentArrayNode->down;
        }
    }

    void outdegree()
    {
        Node *curr = head;
        while (curr != nullptr)
        {
            Node *currlist = curr;
            int deg = 0;
            while (currlist != nullptr)
            {
                deg++;
                currlist = currlist->next;
            }
            cout << curr->name << " " << deg << endl;
            curr = curr->down;
        }
    }
    void indegree()
    {
        Node *curr = head;
        while (curr != nullptr)
        {
            int count = 0;
            Node *temp = head;
            while (temp != nullptr)
            {
                Node *currlist = temp->next;
                while (currlist)
                {
                    if (currlist->name == curr->name)
                        count++;
                    currlist = currlist->next;
                }
                temp = temp->down;
            }
            cout << curr->name << " -> " << count << endl;
            curr = curr->down;
        }
    }

    void BFS(string node)
    {
        queue<string> q;
        unordered_set<string> visited;
        q.push(node);
        visited.insert(node);
        while (!q.empty())
        {   
            node = q.front();
            q.pop();
            cout << node << endl;
            Node *currnode = head;
            while (currnode != nullptr)
            {
                if (currnode->name == node)
                {
                    Node *currlist = currnode;
                    while (currlist != nullptr)
                    {
                        if (visited.find(currlist->name) == visited.end())
                        {
                            q.push(currlist->name);
                            visited.insert(currlist->name);
                        }
                        currlist = currlist->next;
                    }
                }
                currnode = currnode->down;
            }
        }
        cout << endl;
    }

    void DFS(string node)
    {
        stack<string> st;
        unordered_set<string> visited;
        st.push(node);
    
        while (!st.empty())
        {
            string currNode = st.top();
            st.pop();
    
            // Process only if not visited
            if (visited.find(currNode) == visited.end())
            {
                cout << currNode << endl;
                visited.insert(currNode);
    
                Node *curr = head;
                while (curr != nullptr)
                {
                    if (curr->name == currNode)
                    {
                        Node *currlist = curr->next;
                        while (currlist != nullptr)
                        {
                            if (visited.find(currlist->name) == visited.end())
                            {
                                st.push(currlist->name); // push but not visit yet
                            }
                            currlist = currlist->next;
                        }
                        break;
                    }
                    curr = curr->down;
                }
            }
        }
        cout << endl;
    }
    
};

int main()
{
    Graph g;

    while (1)
    {
        cout << "Enter choice" << endl;
        cout << "1.add nodes" << endl;
        cout << "2.print Indegree" << endl;
        cout << "3.print Outdegree" << endl;
        cout << "4.BFS" << endl;
        cout << "5.DFS" << endl;
        cout << "6.Print adj. list" << endl;
        cout << "7.break" << endl;

        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "enter Node1";
            string n1;
            cin >> n1;
            cout << "enter Node2";
            string n2;
            cin >> n2;
            g.addnode(n1, n2);
            break;

        case 2:
            cout << "printing indegrees" << endl;
            g.indegree();
            break;

        case 3:
            cout << "printing outdegree" << endl;
            g.outdegree();
            cout << endl;
            break;

        case 4:
            cout << "Enter starting node" << endl;
            string s2;
            cin >> s2;
            cout << "BFS:" << endl;
            g.BFS(s2);
            break;

        case 5:
            string s2;
            cin >> s2;
            cout << "DFS:" << endl;
            g.DFS(s2);
            break;
            
            case 6:
            
            g.print();
            cout << endl;
            break;
            
            default:
            break;
        }
    }
    return 0;
}