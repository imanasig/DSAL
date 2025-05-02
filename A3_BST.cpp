#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        return node;
    }

    int longestPath(Node* node) {
        if (!node) return 0;
        int leftDepth = longestPath(node->left);
        int rightDepth = longestPath(node->right);
        return max(leftDepth, rightDepth) + 1;
    }

    int minValue(Node* node) {
        if (!node) throw runtime_error("Tree is empty.");
        while (node->left)
            node = node->left;
        return node->data;
    }

    void mirror(Node* node) {
        if (!node) return;
        swap(node->left, node->right);
        mirror(node->left);
        mirror(node->right);
    }

    bool search(Node* node, int key) {
        if (!node) return false;
        if (node->data == key) return true;
        if (key < node->data)
            return search(node->left, key);
        return search(node->right, key);
    }

    Node* deleteNode(Node* node, int key) {
        if (!node) return nullptr;

        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                int minVal = minValue(node->right);
                node->data = minVal;
                node->right = deleteNode(node->right, minVal);
            }
        }
        return node;
    }

    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    void bfs(Node* node) {
        if (!node) {
            cout << "Tree is empty.\n";
            return;
        }

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";
            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    void deleteValue(int key) {
        root = deleteNode(root, key);
    }

    void searchValue(int key) {
        if (search(root, key))
            cout << key << " found in the tree.\n";
        else
            cout << key << " not found.\n";
    }

    void displayTraversals() {
        cout << "\nInorder Traversal: ";
        inorder(root);
        cout << "\nPreorder Traversal: ";
        preorder(root);
        cout << "\nPostorder Traversal: ";
        postorder(root);
        cout << endl;
    }

    void displayBFS() {
        cout << "\nBFS (Level Order): ";
        bfs(root);
        cout<< endl;
    }

    void mirrorTree() {
        mirror(root);
        cout << "Tree mirrored successfully.\n";
    }

    void longestPathLength() {
        cout << "Longest path (height) is: " << longestPath(root) << endl;
    }

    void minData() {
        try {
            cout << "Minimum value in the tree is: " << minValue(root) << endl;
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    }

    void insertMultiple() {
        int n, val;
        cout << "How many values do you want to insert? ";
        cin >> n;
        cout << "Enter values: ";
        for (int i = 0; i < n; i++) {
            cin >> val;
            insert(val);
        }
    }
};

int main() {
    BST tree;
    int choice, val;

    do {
        cout << "\n--- Binary Search Tree Operations ---\n";
        cout << "1. Insert Single Value\n2. Insert Multiple Values\n3. Delete\n4. Search\n5. Mirror Tree\n";
        cout << "6. Longest Path\n7. Minimum Value\n8. Inorder/Preorder/Postorde\n9. Display BFS\n 10. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                tree.insert(val);
                break;
            case 2:
                tree.insertMultiple();
                break;
            case 3:
                cout << "Enter value to delete: ";
                cin >> val;
                tree.deleteValue(val);
                break;
            case 4:
                cout << "Enter value to search: ";
                cin >> val;
                tree.searchValue(val);
                break;
            case 5:
                tree.mirrorTree();
                break;
            case 6:
                tree.longestPathLength();
                break;
            case 7:
                tree.minData();
                break;
            case 8:
                tree.displayTraversals();
                break;
            case 9:
                tree.displayBFS();
                break;
            case 10:
                cout << "Thank you!\n";
                break;
            
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 10);

    return 0;
}
