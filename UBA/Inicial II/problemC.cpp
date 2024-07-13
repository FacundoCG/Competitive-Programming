#include <bits/stdc++.h>
using namespace std;

bool isRedInTheRow (vector<vector<char>>& grid, int row){
    bool res = true;

    for (int i = 0; i < 7; i++){
        if (grid[row][i] != 'R' || grid[row][i] != grid[row][i+1]){
            res = false;
        }
    }

    return res;
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<long long> warriors(n);
    vector<long long> minutes(q);
    vector<long long> prefixSum(n);

    for (int i = 0; i < n; i++){
        long long v;
        cin >> v;
        warriors[i] = v;
    }

    for (int i = 0; i < q; i++){
        long long arrows;
        cin >> arrows;
        minutes[i] = arrows;
    }

    prefixSum[0] = warriors[0];

    for (int i = 0; i < n; i++){
        prefixSum[i] = prefixSum[i-1] + warriors[i];
    }
}