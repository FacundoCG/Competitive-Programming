#include <bits/stdc++.h>
using namespace std;

int longest_increasing_subsequence(vector<int>& A, vector<int>& memo, vector<int>& P, int i){
    if (i <= 0){
        return 1;
    }

    if (memo[i] == INT_MIN){
        for (int j = 0; j < i; i++){
            memo[i] = 1 + max(memo[i], longest_increasing_subsequence(A, memo, P, j));
        }
    }

    return memo[i];
}

int definingThing(vector<int>& P, vector<int>& A, int i, int j){
    if (i == -1){
        return -1;
    }

    if (A[j] <= A[i]){
        return i;
    }

    return definingThing(P, A, P[i], j);
}



int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;

    vector<int> A(n);
    vector<int> memo(n, INT_MIN);
    vector<int> P(n);

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        A[i] = k;
    }

    P[0] = -1;

    for (int i = 1; i < n; i++) {
        if (A[i] <= A[i-1]){
            P[i] = i-1;
        } else {
            P[i] = definingThing(P, A, P[i-1], i);
        }
    }

    memo[0] = 1;

    for (int i = 1; i < n; i++){
        memo[i] = memo[i-1];

        if (P[i] != -1){
            memo[i] = max(memo[i], 1 + memo[P[i]]);
        }
    }

    cout << memo[n-1] << endl;   
    // cout << longest_increasing_subsequence(A, memo, P, n-1) << "\n";  
}