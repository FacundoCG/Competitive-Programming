#include <bits/stdc++.h>
using namespace std;

int MOD = 1e9+7;

int counting_ordered_sums_BU(vector<int>& coins, int x){
    int n = coins.size();
    vector<vector<int>> memo(n, vector<int>(x+1, 0));
    memo[0][0] = 1;

    
    for (int i = 0; i < x+1; i++){
        if (i - coins[0] >= 0){
            memo[0][i] = memo[0][i - coins[0]];
        }
    }
    

    for (int j = 1; j < n; j++){
        for (int i = 0; i < x+1; i++){
            memo[j][i] = memo[j-1][i];
            if (i - coins[j] >= 0){
                memo[j][i] += memo[j][i - coins[j]];
            }
            memo[j][i] %= MOD;
        }
    }

    return memo[n-1][x];
} 

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int i = 0; i < n; i++){
        int k;
        cin >> k;
        coins[i] = k;
    }

    cout << counting_ordered_sums_BU(coins, x) << "\n";
}