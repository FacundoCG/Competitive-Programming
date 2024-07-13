#include <bits/stdc++.h>
using namespace std;

void distinctSums(vector<int>& coins, int maxSum){
    int n = coins.size();

    vector<int> memo(maxSum+1, 0);
    memo[0] = 1;
    memo[coins[0]] = 1;

    for (int i = 1; i < n; i++){
        for (int j = maxSum; j >= 0; j--){
            memo[j] = memo[j] || (j - coins[i] >= 0 && memo[j - coins[i]]);
        }
    }

    int res = 0;

    for (int i = 1; i < maxSum + 1; i++){
        if (memo[i] == 1){
            res ++;
        }
    }

    cout << res << "\n";

    for (int i = 1; i < maxSum+1; i++){
        if (memo[i] == 1){
            cout << i << " ";
        }
    }
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;
    
    int maxSum = 0;

    vector <int> coins(n);
    for (int&c : coins) cin >> c;
    for(int i = 0; i < n; i++) maxSum += coins[i];

    distinctSums(coins, maxSum);
}   