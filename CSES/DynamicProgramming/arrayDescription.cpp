#include <bits/stdc++.h>

using namespace std;

const long long MOD = 10e9 + 7;


int arrayDescriptionBU(vector<int>& A, int m){
    int n = A.size();
    int lastElement = A[n-1];
    vector<vector<int>> memo(n, vector<int>(101));

    if (A[0] == 0){
        for (int i = 0; i < 101; i++){
            memo[0][i] = 1;
        }
    } else {
        memo[0][A[0]] = 1;
    }

    for (int i = 1; i < n; i++){
        for (int j = 0; j <= 100; j++) {
                memo[i][j] = memo[i-1][j];

                if (1 <= j-1){
                    memo[i][j] += memo[i-1][j-1];
                }

                if (j+1 <= m){
                    memo[i][j] += memo[i][j+1];
                }
        }
    }

    return memo[n-1][lastElement];
}


/* int arrayDescription(vector<int>& A, vector<vector<int>>& memo, int i, int j, int m){
    if (i == -1){
        return 1;
    }

    if (memo[i][j] != -1){
        return memo[i][j];
    }
    
    memo[i][j] = 0;
    int n = A.size();

    if (i != n-1 && abs(A[i] - j) > 1 && A[i] != 0){
        return 0;
    } else if (A[i] != 0){
        memo[i][j] = arrayDescription(A, memo, i-1, A[i], m);
    } else if (A[i] == 0){
        if (i == n-1){
            for (int k = 1; k <= m; k++){
                memo[i][j] += arrayDescription(A, memo, i-1, k, m);
            }
        } else {
            memo[i][j] = arrayDescription(A, memo, i-1, j, m);

            if (1 <= j-1){
                memo[i][j] += arrayDescription(A, memo, i-1, j-1, m);
            }

            if (j+1 <= m){
                memo[i][j] += arrayDescription(A, memo, i-1, j+1, m);
            }
        }
    }

    memo[i][j] %= MOD;

    return memo[i][j];
} */

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> A(n);
    vector<vector<int>> memo(n, vector<int> (101, -1));

    for(int &c : A) cin >> c;

    cout << arrayDescriptionBU(A, m) << "\n";
}
