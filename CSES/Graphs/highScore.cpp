#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> edge;
const ll INF = LLONG_MAX;

void bfs(int v, vector<vector<pair<ll, ll>>> &adjList, vector<bool> &visited){
    int n = adjList.size();
    visited[v] = true;

    queue<int> q;
    q.push(v);

    while (!q.empty()){
        int u = q.front();
        q.pop();

        for (int i = 0; i < adjList[u].size(); i++){
            int w = adjList[u][i].second;
            
            if (!visited[w]){
                visited[w] = true;
                q.push(w);
            }
        }
    }
}

bool bellmanFord(int v, vector<pair<ll, edge>> &edges, vector<ll> &distances){
    int n = distances.size();
    int m = edges.size();
    distances[v] = 0;
    bool res = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            ll weight = edges[j].first;
            edge e = edges[j].second;
            int v = e.first;
            int u = e.second;

            if (distances[v] != INF){
                ll newDistance = (ll) distances[v] + weight; 
                distances[u] = min(distances[u], newDistance);
            }
        }
    }

    for (int j = 0; j < m; j++){
        ll weight = edges[j].first;
        edge e = edges[j].second;
        int v = e.first;
        int u = e.second;

        if (distances[v] != INF){
            ll newDistance = (ll) distances[v] + weight;
            if (newDistance < distances[u]){
                res = true;
                break;
            }
        }
    }

    return res;
}



int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    
    vector<vector<pair<ll, ll>>> adjListTrans(n);
    vector<pair<ll, edge>> edgesTrans;
    vector<pair<ll, edge>> edges;
    vector<ll> distances(n, INF);
    vector<bool> visited(n, false);

    for (int i = 0; i < m; i++) {
        ll v, u , w;
        cin >> v >> u >> w;
        w *= -1;
        v -= 1;
        u -= 1;

        edge e = {u, v};
        adjListTrans[u].push_back({w, v});
        edgesTrans.push_back({w, e});
    }
    
    bfs(n-1, adjListTrans, visited);

    for (int i = 0; i < edgesTrans.size(); i++) {
        ll weight = edgesTrans[i].first;
        edge e = edgesTrans[i].second;
        ll v = e.first;

        if (visited[v]){
            ll u = e.second;
            edge newEdge = {u, v};
            edges.push_back({weight, newEdge});
        }
    }

    bool existsNegativeCycle = bellmanFord(0, edges, distances);
    if (existsNegativeCycle){
        cout << -1 << "\n";
        return 0;
    }

    if (distances[n-1] > 0){
        cout << distances[n-1]*(-1) << "\n";
    } else {
        cout << abs(distances[n-1]) << "\n";
    }
}
