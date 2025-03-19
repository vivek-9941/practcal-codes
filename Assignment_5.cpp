#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string key, value;
    Node* next;
    
    Node(string k, string v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class Dictionary {
    Node** table;
    int tablesize;

public:
    Dictionary(int n) {
        tablesize = n;
        table = new Node*[n];
        for (int i = 0; i < n; i++) {
            table[i] = nullptr;
        }
    }

    ~Dictionary() {
        for (int i = 0; i < tablesize; i++) {
            Node* curr = table[i];
            while (curr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }

    int hash(string s) {
        int asciisum = 0;
        for (char c : s) {
            asciisum += c;
        }
        return asciisum % tablesize;
    }

    void insert(string key, string value) {
        int h = hash(key);
        if (table[h] == nullptr) {
            table[h] = new Node(key, value);
        } else {
            insertLL(table[h], key, value);
        }
    }

    void insertLL(Node*& head, string key, string value) {
        if (!head) {
            head = new Node(key, value);
            return;
        }
        Node* curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = new Node(key, value);
    }

    void display() {
        for (int i = 0; i < tablesize; i++) {
            cout << i << ": ";
            printLL(table[i]);
            cout << endl;
        }
    }

    void printLL(Node* head) {
        Node* curr = head;
        while (curr) {
            cout << "[" << curr->key << ": " << curr->value << "] -> ";
            curr = curr->next;
        }
        cout << "NULL";
    }

    void search(string key) {
        int h = hash(key);
        Node* findnode = findLL(table[h], key);
        if (!findnode) {
            cout << "No entry found for key: " << key << endl;
        } else {
            cout << "KEY: " << key << " VALUE: " << findnode->value << endl;
        }
    }

    Node* findLL(Node* head, string key) {
        while (head) {
            if (head->key == key) {
                return head;
            }
            head = head->next;
        }
        return nullptr;
    }

    void del(string key) {
        int h = hash(key);
        deleteLL(table[h], key);
    }

    void deleteLL(Node*& head, string key) {
        if (!head) return;

        if (head->key == key) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* curr = head;
        Node* prev = nullptr;
        while (curr && curr->key != key) {
            prev = curr;
            curr = curr->next;
        }

        if (curr) {
            prev->next = curr->next;
            delete curr;
        }
    }
};

int main() {
    Dictionary dict(10);

    dict.insert("abcd", "1000");
    dict.insert("cdba", "2000");
    dict.insert("dbca", "5000");

    dict.insert("laal", "1000");
    dict.insert("lala", "2000");
    dict.insert("aall", "5000");

    dict.insert("dwupd", "1000");
    dict.insert("puddw", "2000");

    while (true) {
        cout << "\n1. Insert key:value pair" << endl;
        cout << "2. Search for value with key" << endl;
        cout << "3. Delete the key:value pair" << endl;
        cout << "4. Display the dictionary" << endl;
        cout << "Enter your choice (any other input to exit): ";
        
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                string key, value;
                cout << "Enter key: "; cin >> key;
                cout << "Enter corresponding value: "; cin >> value;
                dict.insert(key, value);
                break;
            }
            case 2: {
                string key;
                cout << "Enter key: "; cin >> key;
                dict.search(key);
                break;
            }
            case 3: {
                string key;
                cout << "Enter key: "; cin >> key;
                dict.del(key);
                break;
            }
            case 4: {
                dict.display();
                break;
            }
            default:
                return 0;
        }
    }
}
