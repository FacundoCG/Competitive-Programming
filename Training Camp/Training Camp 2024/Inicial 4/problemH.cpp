#include <bits/stdc++.h>
using namespace std;

bool areConnected(int u, int v, vector<vector<int>> &adj, vector<bool> &visited){
    if (u == v){
        return true;
    }

    bool res = false;

    visited[u] = true;

    for (int neighbor : adj[u]){
        if (!visited[neighbor]){
            res = res || areConnected(neighbor, v, adj, visited);
        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<vector<int>>> colorGraphs(m+1, vector<vector<int>>(n+1));

    for (int i = 0; i < m; i++){
        int v, w, color;
        cin >> v >> w >> color;

        colorGraphs[color][v].push_back(w);
        colorGraphs[color][w].push_back(v);
    }

    int q;
    cin >> q;
    
    for (int i = 0; i < q; i++){
        int u, v;
        cin >> u >> v;

        int res = 0;

        for (int j = 1; j <= m; j++) {
            vector<bool> visited(n+1, false);
            if(areConnected(u, v, colorGraphs[j], visited)){
                res++;
            }
        }

        cout << res << "\n";
    }
}
