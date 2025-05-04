// Given sequence k = k1 < … < kn of n sorted keys, with a search probability pi for each key ki. Build  the Binary search tree that has the least search cost given the access probability for each key.
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

float optimalBST(vector<int> keys, vector<float> prob, int n) {
    float cost[n][n];

    // Initialize cost[i][i]
    for (int i = 0; i < n; i++)
        cost[i][i] = prob[i];

    // Chain length l = 2 to n
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            cost[i][j] = INT_MAX;

            // Try all roots from i to j
            for (int r = i; r <= j; r++) {
                float leftCost = (r > i) ? cost[i][r - 1] : 0;
                float rightCost = (r < j) ? cost[r + 1][j] : 0;

                // Sum of probabilities
                float sumProb = 0;
                for (int k = i; k <= j; k++)
                    sumProb += prob[k];

                float totalCost = leftCost + rightCost + sumProb;

                if (totalCost < cost[i][j])
                    cost[i][j] = totalCost;
            }
        }
    }

    return cost[0][n - 1];
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    while (true) {
        cout << "Enter number of keys (positive integer): ";
        cin >> n;
        if (cin.fail() || n <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a positive integer.\n";
        } else {
            break;
        }
    }

    vector<int> keys(n);
    vector<float> prob(n);

    cout << "Enter " << n << " sorted keys:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Key " << i + 1 << ": ";
        cin >> keys[i];
    }

    cout << "Enter " << n << " corresponding search probabilities (between 0 and 1):\n";
    for (int i = 0; i < n; ++i) {
        float p;
        while (true) {
            cout << "Probability for key " << keys[i] << ": ";
            cin >> p;

            if (cin.fail() || p < 0 || p > 1) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Probability must be a number between 0 and 1.\n";
            } else {
                prob[i] = p;
                break;
            }
        }
    }

    float minCost = optimalBST(keys, prob, n);
    cout << "\nMinimum cost of Optimal BST: " << minCost << endl;

    return 0;
}
