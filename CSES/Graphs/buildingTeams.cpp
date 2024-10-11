#include <bits/stdc++.h>
using namespace std;

const long long UNDEFINED = -1;

void bfs(int v, vector<vector<int>> &adjList, vector<int> &teams){
    int n = adjList.size();
    teams[v] = 1;

    queue<int> q;
    q.push(v);

    while (!q.empty()){
        int u = q.front();
        q.pop();

        for (int i = 0; i < adjList[u].size(); i++){
            int w = adjList[u][i];
            if (teams[w] == 0){
                if (teams[u] == 1){
                    teams[w] = 2;
                } else {
                    teams[w] = 1;
                }
                q.push(w);
            } else {
                if (teams[w] == teams[u]){ // The graph isn't bipartite
                    teams[w] = UNDEFINED;
                    break;
                }
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;

    vector<vector<int>> adjList(n);
    vector<int> teams(n, 0);

    for (int i = 0; i < m; i++){
        int v, w;
        cin >> v >> w;

        v-=1;
        w-=1;

        adjList[v].push_back(w);
        adjList[w].push_back(v);
    }

    for (int i = 0; i < n; i++){
        if (teams[i] == 0){
            bfs(i, adjList, teams);
        }
    } 

    for (int i = 0; i < n; i++){
        if (teams[i] == UNDEFINED){
            cout << "IMPOSSIBLE" << "\n";
            return 0;
        }
    } 

    for (int i = 0; i < n; i++){
        cout << teams[i] << " ";
    } 

    cout << "\n";
}