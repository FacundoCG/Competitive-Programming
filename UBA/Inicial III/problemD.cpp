#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n, m;
        cin >> n >> m;

        vector<vector<int>> grid(n, vector<int>(m, 0));

        for (int j = 0; j < n; j++){
            for (int k = 0; k < m; k++){
                int v;
                cin >> v;
                grid[j][k] = v;
            }
        }

        int res = 0;

        for (int j = 0; j < n; j++){
            if (j+1 < n){
                for (int k = 0; k < m-1; k++){
                    if (grid[j][k] >= 0 && grid[j+1][k] >= 0){
                        // Don't do anything
                    } 
                }
            } else{

            }
        }

    }

/*     for (int j = 0; j-1 < n; j++){
           doBestOption(grid, j);
        } 
        
        void doBestOption(vector<vector<int>>& grid, int row){
            int n = grid[0].size();
            for (int i = 0; i < n-1; i++){
                // I will do something if some of them is negative
                if (grid[row][i] < 0 || grid[row][i+1] < 0 || grid[row+1][i]){
                    int absCurrent = abs(grid[row][i]);
                    int absNext = abs(grid[row][i+1]);
                    int absBottom = abs(grid[row+1][i]);
                }
            }
        }
        */


















}