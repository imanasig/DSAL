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

    //Insert
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        return node;
    }

    //Count longest path (height)
    int longestPath(Node* node) {
        if (!node) return 0;
        int leftDepth = longestPath(node->left);
        int rightDepth = longestPath(node->right);
        return max(leftDepth, rightDepth) + 1;
    }

    //Find min value
    int minValue(Node* node) {
        if (!node) throw runtime_error("Tree is empty.");
        while (node->left)
            node = node->left;
        return node->data;
    }

    //Mirror tree
    void mirror(Node* node) {
        if (!node) return;
        swap(node->left, node->right);
        mirror(node->left);
        mirror(node->right);
    }

    //Search
    bool search(Node* node, int key) {
        if (!node) return false;
        if (node->data == key) return true;
        if (key < node->data)
            return search(node->left, key);
        return search(node->right, key);
    }

    //Delete node
    Node* deleteNode(Node* node, int key) {
        if (!node) return nullptr;

        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            // Node found
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
                // Two children
                int minVal = minValue(node->right);
                node->data = minVal;
                node->right = deleteNode(node->right, minVal);
            }
        }
        return node;
    }

    // Traversals
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

    // BFS
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
        cout << endl;
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
};

int main() {
    BST tree;
    int initial[] = {50, 30, 70, 20, 40, 60, 80};

    // Construct BST
    for (int val : initial)
        tree.insert(val);

    int choice, val;

    do {
        cout << "\n--- Binary Search Tree Operations ---\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Mirror Tree\n5. Longest Path\n";
        cout << "6. Minimum Value\n7. Inorder/Preorder/Postorder\n8. BFS\n9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                tree.insert(val);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> val;
                tree.deleteValue(val);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> val;
                tree.searchValue(val);
                break;
            case 4:
                tree.mirrorTree();
                break;
            case 5:
                tree.longestPathLength();
                break;
            case 6:
                tree.minData();
                break;
            case 7:
                tree.displayTraversals();
                break;
            case 8:
                tree.displayBFS();
                break;
            case 9:
                cout << "ThankYou\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 9);

    return 0;
}
