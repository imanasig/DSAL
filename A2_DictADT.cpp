// Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with / without replacement.

#include <iostream>
#include <list>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

// Each entry in the dictionary
class Dictionary {
private:
    list<pair<string, string>> table[TABLE_SIZE];  // Hash table using chaining

    // Hash function - simple modulo based
    int hashFunction(const string& key) {
        int sum = 0;
        for (char ch : key)
            sum += ch;
        return sum % TABLE_SIZE;
    }

public:
    // Insert key-value pair
    void insert(const string& key, const string& value) {
        int index = hashFunction(key);
        for (auto& item : table[index]) {
            if (item.first == key) {
                cout << "Key already exists. Updating value.\n";
                item.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
        cout << "Inserted successfully.\n";
    }

    // Search for a key
    void search(const string& key) {
        int index = hashFunction(key);
        for (const auto& item : table[index]) {
            if (item.first == key) {
                cout << "Key found: " << item.first << " => " << item.second << endl;
                return;
            }
        }
        cout << "Key not found.\n";
    }

    // Delete a key
    void remove(const string& key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                cout << "Key deleted successfully.\n";
                return;
            }
        }
        cout << "Key not found. Cannot delete.\n";
    }

    // Display the entire hash table
    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Bucket " << i << ": ";
            if (table[i].empty()) {
                cout << "Empty\n";
            } else {
                for (const auto& item : table[i]) {
                    cout << "[" << item.first << " : " << item.second << "] -> ";
                }
                cout << "NULL\n";
            }
        }
    }
};

int main() {
    Dictionary dict;
    int choice;
    string key, value;

    do {
        cout << "\n--- Dictionary ADT Using Hashing (Chaining) ---\n";
        cout << "1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin.ignore();  // Clear the newline character from the input buffer
                getline(cin, value); // Use getline to allow spaces in the value
                dict.insert(key, value);
                break;

            case 2:
                cout << "Enter key to search: ";
                cin >> key;
                dict.search(key);
                break;

            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                dict.remove(key);
                break;

            case 4:
                dict.display();
                break;

            case 5:
                cout << "ThankYou!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
