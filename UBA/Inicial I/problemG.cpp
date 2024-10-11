#include <bits/stdc++.h>
using namespace std;

vector<int> jumps;
vector<int> slips;
vector<bool> visited;

int minimum_jumps_TD(int n){
    vector<int> memo(n+1);
    
    for (int j = 1; j <= n; j++){
        if (j - jumps[j] <= 0){
            memo[j] = 1;
        }
    }

    return memo[n];
}



long long minimum_jumps_TD(int i, int j, vector<long long>& memo, vector<pair<int,int>>& path){
    if (i <= 0){
        return 0;
    } else if (i - jumps[i] <= 0){
        return 1;
    }

    if (memo[i] == -1){
        int maxJump = jumps[i];
        memo[i] = INT_MAX;

        for (int k = 1; k <= maxJump; k++){
            int newPosition = i - k + slips[i-k];
            if (newPosition != i){
                long long minimumJumps = 1 + minimum_jumps_TD(newPosition, j+1, memo, path);
                if (memo[i] > minimumJumps){
                    memo[i] = minimumJumps;
                    path[i] = {i-k, newPosition};
                } 
            }
        }
    }

    return memo[i];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    jumps.resize(n+1);
    slips.resize(n+1);
    visited.resize(n+1);

    for (int i = 1; i <= n; i++) {
        int j;
        cin >> j;
        jumps[i] = j;
    }

    for (int i = 1; i <= n; i++) {
        int j;
        cin >> j;
        slips[i] = j;
    }

    vector<long long> memo (n+1, -1);
    vector<pair<int,int>> path(n+1, {-1,-1});

    int res = minimum_jumps_TD(n, 0, memo, path);
    
    if (res == INT_MAX){
        cout << -1 << "\n";
    } else {
        cout << res << "\n";
        
        int j = n;
        
        while (j > 0){
            if (path[j].first != -1){
                cout << path[j].first << " ";
            }

            j = path[j].second;
        }

        cout << 0 << "\n";

    }
}
