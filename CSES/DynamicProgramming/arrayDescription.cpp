#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const long long MOD = pow(10,9) + 7;
const long long UNDEFINED = -1;
ll n, m;

ll arrayDescriptionTD(vector<int> &A, vector<vector<ll>> &memo, int i, int j){
    if (i == -1){ // Base case: when I finished my iterations
        return 1;
    }

    if (A[i] != 0 && abs(A[i] - j) > 1){ // Failed case: invalidad array
        return 0;
    }

    if (memo[i][j] == UNDEFINED){ // Recursive case:
        memo[i][j] = 0;

        if (A[i] != 0){ // I don't have to change anything
            memo[i][j] = arrayDescriptionTD(A, memo, i-1, A[i]);
        } else { // I have three options
            memo[i][j] += arrayDescriptionTD(A, memo, i-1, j);

            if (j-1 > 0){
                memo[i][j] += arrayDescriptionTD(A, memo, i-1, j-1);
            }
            if (j+1 <= m){
                memo[i][j] += arrayDescriptionTD(A, memo, i-1, j+1);
            }
        }
        
        memo[i][j] %= MOD;
    }

    return memo[i][j];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    vector<int> A(n);
    vector<vector<ll>> memo(n, vector<ll> (m+1, UNDEFINED));

    for(int i = 0; i < n; i++) cin >> A[i];

    ll res = 0;

    if (A[n-1] == 0){
        for (int i = 1; i <= m; i++){
            res += arrayDescriptionTD(A, memo, n-2, i);
        }

        res %= MOD;
    } else {
        res = arrayDescriptionTD(A, memo, n-2, A[n-1]);
    }

    cout << res << "\n";
}
