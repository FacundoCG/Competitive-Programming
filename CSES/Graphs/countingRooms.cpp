#include <bits/stdc++.h>
using namespace std;

int n, m;

void special_dfs(int i, int j, vector<string>& map){
    map[i][j] = '#';

    if (i+1 < n && map[i+1][j] == '.'){
        special_dfs(i+1, j, map);
    }

    if (0 <= i-1 && map[i-1][j] == '.'){
        special_dfs(i-1, j, map);
    }

    if (j+1 < m && map[i][j+1] == '.'){
        special_dfs(i, j+1, map);
    }

    if (0 <= j-1 && map[i][j-1] == '.'){
        special_dfs(i, j-1, map);
    }
}

void dfs(int vertex, vector<bool>& visited, vector<vector<int>>& adjacencyList){
    visited[vertex] = true;

    for (int &neighbor: adjacencyList[vertex]){
        if (!visited[neighbor]){
            dfs(neighbor, visited, adjacencyList);
        }
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    vector<string> map(n);

    for (string &row : map){
        cin >> row;
    }

    int connectedComponents = 0;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (map[i][j] == '.'){
                special_dfs(i, j, map);
                connectedComponents++;
            }
        }
    }

    cout << connectedComponents << "\n";
}
