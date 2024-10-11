#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX;
typedef long long ll;
typedef pair<ll, ll> edge;

// bellmanFord returns a bool indicating if there is a negative cycle which is reachable from v. In addition, it calculates the min distance from all the vertices to v.
// It is important to note that we have to eliminate all the vertices and edges which are not reachable from the desired vertex in the transposed graph. This is because there might be a negative cycle in the graph but it isn't part of the path from v to w.
bool bellmanFord(int v, int n, vector<pair<ll, edge>> &edges, vector<ll> &distances){
    distances[v] = 0;
    int m = edges.size();
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

