#include <bits/stdc++.h>
using namespace std;


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    
    vector<vector<int>> grid(n, vector<int>(n, 1));
    int maximum = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            grid[i][j] = grid[i-1][j] + grid[i][j-1];
            maximum = max(maximum, grid[i][j]);
        }
    }

    cout << maximum << "\n";
}
