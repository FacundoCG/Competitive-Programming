#include <bits/stdc++.h>
using namespace std;

int cuttingRectangles(int a, int b){
    vector<vector<int>> memo (a+1, vector<int>(b+1, 0));

    for (int i = 1; i <= b; i++){
        memo[1][i] = i-1;
    }

    for (int i = 1; i <= a; i++){
        memo[i][1] = i-1;
    }

    for (int i = 2; i <= a; i++){
        for (int j = 2; j <= b; j++){
            if (i != j){
                memo[i][j] = INT_MAX;

                for (int k = 1; k < i; k++){
                    memo[i][j] = min(memo[i][j], memo[k][j] + memo[i - k][j]);
                }

                for (int k = 1; k < j; k++){
                    memo[i][j] = min(memo[i][j], memo[i][k] + memo[i][j-k]);
                }

                memo[i][j]++;
            }
        }
    }

    return memo[a][b];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int a, b;
    cin >> a >> b;

    cout << cuttingRectangles(a, b) << "\n";
}