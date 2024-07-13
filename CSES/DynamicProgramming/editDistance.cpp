#include <bits/stdc++.h>

using namespace std;

int edit_distance_TD(vector<char>& A, vector<char>& B, vector<vector<int>>& memo, int i, int j){
    if (i == 0 && j == 0 && A[i] == B[j]){
        return 0;
    } else if (i == 0 && j == 0 && A[i] != B[j]){
        return 1;
    } 

    if (memo[i][j] == INT_MAX){
        if (i == 0 && j > 0){
            if (A[i] == B[j]){
                memo[i][j] = j;
            } else {
                memo[i][j] = 1 + edit_distance_TD(A, B, memo, i, j-1);
            }
        } else if (i > 0 && j == 0){
            if (A[i] == B[j]){
                memo[i][j] = i;
            } else {
                memo[i][j] = 1 + edit_distance_TD(A, B, memo, i-1, j);
            }
        } else if (A[i] == B[j]){
            memo[i][j] = edit_distance_TD(A, B, memo, i-1, j-1);
        } else {
            memo[i][j] = 1 + min(edit_distance_TD(A, B, memo, i-1, j), min(edit_distance_TD(A, B, memo, i-1, j-1), edit_distance_TD(A, B, memo, i, j-1)));
        }
    }

    return memo[i][j];
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    string str1, str2;

    cin >> str1 >> str2;

    int n = str1.size();
    int m = str2.size();

    vector<char> A (n);
    vector<char> B (m);
    vector<vector<int>> memo(n, vector<int>(m, INT_MAX));

    for(int i = 0; i < n; i++){
        A[i] = str1[i];
    }

    for (int i = 0; i < m; i++){
        B[i] = str2[i];
    }

    cout << edit_distance_TD(A, B, memo, n-1, m-1) << "\n"; 
}
