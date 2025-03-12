#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl
#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define all(c) (c).begin(),(c).end()

// Show vector
template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v) {
    os << "[";
    forn(i, v.size()) {
        if (i > 0) os << ",";
        os << v[i];
    }
    return os << "]";
}

// Show pair
template <typename T1, typename T2>
ostream & operator <<(ostream &os, const pair<T1, T2> &p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

// Show set
template <typename T>
ostream & operator <<(ostream &os, const set<T> &s) {
    os << "{";
    for(auto it = s.begin(); it != s.end(); it++){
        if(it != s.begin()) os << ",";
        os << *it;
    }
    return os << "}";
}


// ############################################################### //

bool isBipartite(ll v, vector<vector<ll>> &adjList, vector<ll> &teams){
    bool res = true;
    ll n = adjList.size();
    teams[v] = 1;

    queue<ll> q;
    q.push(v);

    while (!q.empty()){
        ll u = q.front();
        q.pop();

        for (int i = 0; i < adjList[u].size(); i++){
            ll w = adjList[u][i];
            if (teams[w] == 0){ // If the node isn't painted, paint it.
                if (teams[u] == 1){
                    teams[w] = 2;
                } else {
                    teams[w] = 1;
                }
                q.push(w);
            } else {
                if (teams[w] == teams[u]){ // If the node is painted, I check that its color is different from the v.
                    res = false;
                    break;
                }
            }
        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;

    vector<int> colors(n);
    vector<int> connectedComponents(5001, 0);
    forn(i,n) cin >> colors[i];

    int currentColor = colors[0];

    forsn(i,1,n){
        if (colors[i] != currentColor){
            connectedComponents[currentColor]++;
            currentColor = colors[i];
        } 
    }

    if (colors[n-1] == currentColor){
        connectedComponents[currentColor]++;
    }

    ll moreComponents = 0;
    ll totalComponents = 0;

    forsn(i, 1, 5001){
        if (connectedComponents[i] > moreComponents){
            moreComponents = connectedComponents[i];
        }

        totalComponents += connectedComponents[i];
    }

    ll res = totalComponents - moreComponents;

    cout << res << "\n";
}