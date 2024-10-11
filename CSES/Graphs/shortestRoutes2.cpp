#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX;
typedef long long ll;
typedef pair<ll, ll> edge;

void floydWarshall(vector<vector<ll>> &distances){
    int n = distances.size();

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (distances[i][k] != INF && distances[k][j] != INF){
                    ll newDistance = (ll) distances[i][k] + distances[k][j];
                    distances[i][j] = min(distances[i][j], newDistance);
                }
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n,m,q;
    cin >> n >> m >> q;

    vector<vector<ll>> distances(n, vector<ll>(n, INF));

    for (int i = 0; i < m; i++){
        ll v, u, w;
        cin >> v >> u >> w;
        v -= 1;
        u -= 1;
        distances[v][u] = min(distances[v][u], w);
        distances[u][v] = min(distances[v][u], w);
    }

    for (int i = 0; i < n; i++){
        distances[i][i] = 0;
    }

    floydWarshall(distances);
    
    for (int i = 0; i < q; i++){
        ll v, w;
        cin >> v >> w;
        v -= 1;
        w -= 1;

        if (distances[v][w] == INF){
            cout << -1 << "\n";
        } else {
            cout << distances[v][w] << "\n";
        }
    }
}