#include <bits/stdc++.h>
using namespace std;

int number_of_paths(vector<vector<char>>& grid, vector<vector<int>>& memo, int i, int j){
    int n = grid.size();

    if (i == n-1 && j == n-1 && grid[i][j] != '*'){
        return 1;
    }
    if (grid[i][j] == '*'){
        return 0;
    }

    if (memo[i][j] == -1){
        int m = pow(10,9) + 7;

        if (i == n-1 && j < n-1){
            memo[i][j] = number_of_paths(grid, memo, i, j+1) % m;
        } else if (i < n-1 && j == n-1){
            memo[i][j] = number_of_paths(grid, memo, i+1, j) % m;
        } else {
            memo[i][j] = (number_of_paths(grid, memo, i+1, j) + number_of_paths(grid, memo, i, j+1)) % m;
        }
    }

    return memo[i][j]; 
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;

    vector<vector<int>> memo(n, vector<int>(n, -1));
    vector<vector<char>> grid(n, vector<char>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            grid[i][j] = c;
        }
    }

    cout << number_of_paths(grid, memo, 0, 0) << "\n";
}