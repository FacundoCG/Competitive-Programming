#include <bits/stdc++.h>
using namespace std;

const long long INF = 10e7;
typedef long long ll;
typedef pair<ll, ll> edge;

// The matrix has to be initialized:
// d(s,v) = w(s,v) if exists
// d(s,s) = 0
// d(s,v) = INF otherwise
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
