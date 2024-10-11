#include <bits/stdc++.h>
using namespace std;

const long long INF = 10e7;
typedef long long ll;
typedef pair<ll, ll> edge;

struct LexicographicalComparator {
    bool operator()(const pair<ll, ll> & a, const pair<ll, ll> & b) const {
        return a > b; // Use operator > for min-heap
    }
};

vector<ll> djikstra (ll v, vector<vector<pair<ll, ll>>> &adjList){ // Time complexity: O(|E| * log(|V|))
    int n = adjList.size();
    vector<ll> distances(n, INF);
    vector<ll> visited(n, false);
    priority_queue<pair<ll, ll>, vector<pair<ll,ll>>, LexicographicalComparator> q;
    distances[v] = 0;
    q.push({0, v});
 
    while (!q.empty()){
        ll u = q.top().second;
        q.pop();
 
        if (visited[u]){
            continue;
        }
 
        visited[u] = true;
 
        for (ll i = 0; i < adjList[u].size(); i++){
            ll weightEdge = (ll) adjList[u][i].first;
            ll w = (ll) adjList[u][i].second;
            ll oldDistance = (ll) distances[w];
            ll newDistance = (ll) weightEdge + distances[u];
 
            if (oldDistance > newDistance){
                distances[w] = (ll) newDistance;
                q.push({distances[w], w});
            }
        }
    }
 
    return distances;
}

