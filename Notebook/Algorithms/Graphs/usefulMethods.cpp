#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> edge;

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

vector<pair<ll, edge>> eliminateNegativeCycleUnreachables(ll v, ll n, vector<pair<ll, edge>> &edges){
    vector<pair<ll, edge>> res;
    vector<vector<pair<ll, ll>>> adjTrans;

    for (int i = 0; i < edges.size(); i++){
        ll weight = edges[i].first;
        edge e = edges[i].second;
        ll u = e.first;
        ll v = e.second;
        adjTrans[v].push_back({weight, u});
    }

    vector<bool> visited(n, false);

    bfs(v, adjTrans, visited);

    for (int i = 0; i < edges.size(); i++){
        ll weight = edges[i].first;
        edge e = edges[i].second;
        ll u = e.first;

        if (visited[u]){
            ll v = e.second;
            edge normalEdge = {v, u};
            res.push_back({weight, normalEdge});
        }
    }

    return res;
}

void printPath(int start, int end, vector<int> &parents){
    vector<int> inversePath;

    while (end != start){
        inversePath.push_back(end);
        end = parents[end];
    }

    inversePath.push_back(start);

    for (int i = inversePath.size()-1; i >= 0; i--){
        cout << inversePath[i] << " ";
    }

    cout << "\n";
}

void printNeighboorhoods(vector<vector<int>> &adjList){
    int n = adjList.size();

    for (int i = 0; i < n; i++){
        cout << "Vertex: " << i << "\n";

        for (int j = 0; j < adjList[i].size(); j++){
            if (j == adjList[i].size() - 1){
                cout << adjList[i][j] << "\n";
            } else {
                cout << adjList[i][j] << " ";
            }
        }
    }
}

void printDistances(vector<vector<ll>> &distances){
    int n = distances.size();

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << "Distance from " << i << " to " << j << ": "<< distances[i][j] << "\n";
        }
    }
}