#include <bits/stdc++.h>
using namespace std;

const long long UNDEFINED = -1;

void bfs(int v, vector<vector<int>> &adjList, vector<int> &parents){
    int n = adjList.size();
    vector<bool> visited(n, false);

    visited[v] = true;
    parents[v] = v;

    queue<int> q;
    q.push(v);

    while (!q.empty()){
        int u = q.front();
        q.pop();

        for (int i = 0; i < adjList[u].size(); i++){
            int w = adjList[u][i];
            if (!visited[w]){
                parents[w] = u;
                visited[w] = true;
                q.push(w);
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adjList(n);
    vector<int> parents(n, UNDEFINED);

    for (int i = 0; i < m; i++) {
        int v, w;
        cin >> v >> w;
        v-=1;
        w-=1;

        adjList[v].push_back(w);
        adjList[w].push_back(v);
    }

    bfs(0, adjList, parents);

    if (parents[n-1] == UNDEFINED){
        cout << "IMPOSSIBLE" << "\n";
        return 0;
    }

    int v = n-1;
    vector<int> inversePath;
    inversePath.push_back(v);

    while(v != 0){
        v = parents[v];
        inversePath.push_back(v);
    } 

    cout << inversePath.size() << "\n";

    for (int i = inversePath.size()-1; i >= 0; i--){
        cout << inversePath[i]+1 << " ";
    }

    cout << "\n";
}
