#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string key;
    string meaning;
    Node* left;
    Node* right;
    Node(string k, string v) {
        key = k;
        meaning = v;
        left = right = nullptr;
    }
};

Node* insert(Node* root, string key, string val) {
    if (!root) {
        return new Node(key, val);
    }
    if (root->key > key) {
        root->left = insert(root->left, key, val);
    } else if (root->key < key) {
        root->right = insert(root->right, key, val);
    }
    return root;
}

bool update(Node* root, string key, string mean) {
    if (!root) return false;
    if (root->key > key) {
        return update(root->left, key, mean);
    } else if (root->key < key) {
        return update(root->right, key, mean);
    } else {
        root->meaning = mean;
        return true;
    }
}

Node* findlast(Node* root) {
    if (!root) return nullptr;
    while (root->right) {
        root = root->right;
    }
    return root;
}

Node* deletenode(Node* root, string key) {
    if (!root) return nullptr;
    if (root->key > key) {
        root->left = deletenode(root->left, key);
    } else if (root->key < key) {
        root->right = deletenode(root->right, key);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findlast(root->left);
        root->key = temp->key;
        root->meaning = temp->meaning;
        root->left = deletenode(root->left, temp->key);
    }
    return root;
}

string findinBST(Node* root, string key, int& cnt) {
    while (root != nullptr) {
        cnt++;
        if (root->key == key) {
            return root->meaning;
        } else if (root->key > key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return "NOT FOUND";
}

void inorder(Node* root, vector<pair<string, string>>& arr) {
    if (!root) return;
    inorder(root->left, arr);
    arr.emplace_back(root->key, root->meaning);
    inorder(root->right, arr);
}

int main() {
    cout << "!!!Hello World!!!" << endl;

    Node* root = nullptr;
    while (true) {
        cout << "Enter Choice" << endl;
        cout << "1. Add keyword" << endl;
        cout << "2. Delete Keyword" << endl;
        cout << "3. Update keyword and meaning" << endl;
        cout << "4. Display Data in Ascending and Descending Order" << endl;
        cout << "5. Number of comparisons for finding keyword" << endl;
        cout << "6. Break" << endl;

        int n;
        cin >> n;
        if (n == 1) {
            cout << "Enter key and value: ";
            string k, v;
            cin >> k >> v;
            root = insert(root, k, v);
            cout << "INSERTED" << endl;
        } else if (n == 2) {
            cout << "Enter key: ";
            string key;
            cin >> key;
            root = deletenode(root, key);
        } else if (n == 3) {
            cout << "Enter key and value: ";
            string k, v;
            cin >> k >> v;
            if (update(root, k, v)) {
                cout << "UPDATED" << endl;
            } else {
                cout << "Keyword not found" << endl;
            }
        } else if (n == 4) {
            vector<pair<string, string>> arr;
            inorder(root, arr);
            cout << "Ascending order" << endl;
            for (int i = 0; i < arr.size(); i++) {
                cout << arr[i].first << ": " << arr[i].second << endl;
            }
            cout << endl;
            cout << "Descending order" << endl;
            for (int i = arr.size() - 1; i >= 0; i--) {
                cout << arr[i].first << ": " << arr[i].second << endl;
            }
            cout << endl;
        } else if (n == 5) {
            cout << "Enter key: ";
            string key;
            cin >> key;
            int count = 0;
            cout << findinBST(root, key, count) << endl;
            cout << "Count: " << count << endl;
            cout << endl;
        } else {
            break;
        }
    }
    return 0;
}