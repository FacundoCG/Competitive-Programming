#include <bits/stdc++.h>
using namespace std;

void fillGrid(vector<vector<char>>& grid, int row, int way){
    int n = grid.size();
    bool hashtag;

    if(way == 1){
        hashtag = true;
    } else {
        hashtag = false;
    }

    for (int i = 0; i < n; i+=2){
        if (hashtag){
            grid[row][i] = '#';
            grid[row][i+1] = '#';
            hashtag = false;
        } else {
            grid[row][i] = '.';
            grid[row][i+1] = '.';
            hashtag = true;
        }
    }
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n;
        cin >> n;

        int way = 1;
        vector<vector<char>> grid(2*n, vector<char>(2*n));

        for (int j = 0; j < 2*n; j+=2){
            fillGrid(grid, j, way);
            fillGrid(grid, j+1, way);

            if (way == 1){
                way--;
            } else {
                way++;
            }
        }

        for (int j = 0; j < 2*n; j++){
            for (int k = 0; k < 2*n; k++){
                cout << grid[j][k];
            }
            cout << "\n";
        }
    }
}