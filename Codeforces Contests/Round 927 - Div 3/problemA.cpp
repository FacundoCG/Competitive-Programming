#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        string s;
        cin >> n >> s;

        int res = 0;
        vector<int> memo(n);

        memo[0] = 0;

        for (int j = 1; j < n; j++) {
            if (s[j] == '*'){
                memo[j] = 0;
            } else if (s[j] == '.'){
                if (j > 1){
                    memo[j] = max(memo[j-1], memo[j-2]);
                } 
            } else {
                if (j > 1){
                    if (s[j-1] == '*' && s[j-2] == '*'){
                        memo[j] = 0;
                    } else {
                        memo[j] = 1 + max(memo[j-1], memo[j-2]);
                    }
                } else {
                    memo[j] = 1;
                }
            }
        }

        for (int j = 1; j < n; j++) {
            res = max(res, memo[j]);
        }

        cout << res << "\n";
    }
}