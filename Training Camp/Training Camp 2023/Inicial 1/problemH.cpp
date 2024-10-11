#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll zero = 0;
const ll INF = LLONG_MAX;

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

ll makeEquals(vector<vector<ll>>& distances, int v, int w){
    ll res = INF;

    for (int i = 0; i < 26; i++){
        ll distance = distances[v][i] + distances[w][i];
        res = min(res, distance);
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    vector<vector<pair<ll, ll>>> adjList(26);
    vector<vector<ll>> distances(26, vector<ll>(26, INF));
    map<char, int> codification;
    string s;
    int k = 0;

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            ll v;
            cin >> v;

            if (i != j){
                adjList[i].push_back({v, j});
                distances[i][j] = v;
            } else {
                distances[i][i] = 0;
            }
        }
    }

    for (char c = 'a'; c <= 'z'; c++) {
        codification[c] = k;
        k++;
    }

    cin >> s;
    ll res = 0;
    int i = 0;
    int j = s.size()-1;

    floydWarshall(distances);

    while (i < j){
        if (s[i] != s[j]){
            int c1 = codification[s[i]];
            int c2 = codification[s[j]];
            res += makeEquals(distances, c1, c2);
        }

        i++;
        j--;
    }

    cout << res << "\n";
}
