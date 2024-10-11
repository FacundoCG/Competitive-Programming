#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX;
typedef long long ll;
typedef pair<ll, ll> edge;

struct LexicographicalComparator {
    bool operator()(const pair<ll, ll> & a, const pair<ll, ll> & b) const {
        return a > b; // Use operator > for min-heap
    }
};

vector<ll> djikstra (ll v, vector<vector<pair<ll, ll>>> &adjList){
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

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    
    vector<vector<pair<ll, ll>>> adjList(n);
    vector<vector<pair<ll, ll>>> adjListTrans(n);
    vector<pair<ll, edge>> edges;

    for (int i = 0; i < m; i++) {
        ll v, u , w;
        cin >> v >> u >> w;
        v -= 1;
        u -= 1;
        edge e = {v, u};

        adjList[v].push_back({w, u});
        adjListTrans[u].push_back({w, v});
        edges.push_back({w, e});
    }

    vector<ll> distances1 = djikstra(0, adjList);
    vector<ll> distancesN = djikstra(n-1, adjListTrans);
    ll res = INF;

    for (int i = 0; i < edges.size(); i++){
        edge e = edges[i].second;
        ll w = edges[i].first;
        ll v = e.first;
        ll u = e.second;
        ll option1 = (ll) INF;

        if (distances1[v] != INF && distancesN[u] != INF){
            option1 = (ll) distances1[v] + w/2 + distancesN[u];
        }
        res = min(res, option1);
    }

    cout << res << "\n";
}
