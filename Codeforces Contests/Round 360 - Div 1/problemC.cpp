#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> coins(n);

    for (int i = 0; i < n; i++){
        int j;
        cin >> j;
        coins[i] = j;
    }

    vector<vector<bool>> existsSum(n, vector<bool>(k+1));

    for (int i = 0; i < n; i++){
        existsSum[i][0] = true;
    }

    existsSum[0][coins[0]] = true;

    for (int i = 1; i < n; i++){
        for (int j = 1; j <= k; j++){
            existsSum[i][j] = existsSum[i-1][j] || (j - coins[i] >= 0 && existsSum[i-1][j-coins[i]]);
        }
    }

    vector<int> subset;
    int value = k;

    for (int i = n-1; i >= 0; i--){
        // existsSum[i][k] = true = existsSum[i-1][k] || existsSum[i-1][j-coins[i]]
        if (i == 0 && value != 0){
            //cout << "I need to use the coin " << coins[i] << "\n";
            subset.push_back(coins[i]);            
            value -= coins[i];
            //cout << "My value is " << value << "\n";
        } else if (i > 0 && !existsSum[i-1][value]){
            //cout << "I need to use the coin " << coins[i] << "\n";
            subset.push_back(coins[i]);            
            value -= coins[i];
            //cout << "My value is " << value << "\n";
        }
    }

    int m = subset.size();
    int maxSum = 0;

/*     cout << "I use the coins: " << "\n";

    for (int i = 0; i < m; i++){
        cout << subset[i] << " ";
    }

    cout << "\n"; */

    for (int i = 0; i < m; i++){
        maxSum += subset[i];
    }

    vector<vector<bool>> existsPossibleSums(m, vector<bool>(maxSum+1));

    for (int i = 0; i < m; i++){
        existsPossibleSums[i][0] = true;
    }

    existsPossibleSums[0][subset[0]] = true;

    for (int i = 1; i < m; i++){
        for (int j = 1; j <= maxSum; j++){
            existsPossibleSums[i][j] = existsPossibleSums[i-1][j] || (j - subset[i] >= 0 && existsPossibleSums[i-1][j-subset[i]]);
        }
    }

    set<int> differentSums;

    for (int i = 0; i < m; i++){
        for (int j = 0; j <= maxSum; j++){
            if (existsPossibleSums[i][j]){
                differentSums.insert(j);
            }
        }
    }

    cout << differentSums.size() << "\n";

    for (const int& k : differentSums){
        cout << k << " ";
    }

    cout << "\n";
}