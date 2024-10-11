#include <bits/stdc++.h>
using namespace std;



int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n , vector<char>(m));
    pair<int, int> A;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            char c;
            cin >> c;
            grid[i][j] = c;

            if (c == 'A'){
                A = {i, j};
            }
        }
    }
}
