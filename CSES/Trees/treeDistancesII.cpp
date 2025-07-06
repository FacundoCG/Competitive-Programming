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


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //
vector<vector<int>> adjList;
vector<bool> visited;
vector<int> subtreeSize;
int n;

ll totalDistances(int v, int currentDepth){
    visited[v] = true;
    ll res = 0;

    for (int u : adjList[v]){
        if (!visited[u]) res += currentDepth + totalDistances(u, currentDepth+1);
    }

    return res;
}

void calculateNumberOfDescendants(int v){
    visited[v] = true;
	subtreeSize[v] = 1;
	
    for (int u : adjList[v]){
        if (!visited[u]){
            calculateNumberOfDescendants(u);
            subtreeSize[v] += subtreeSize[u];
        }
    }
}

void solve(int v, int parent, vector<ll> &res){
    visited[v] = true;

    if (v != 0){
        ll nodesThatIAmFarNow = (ll) n - subtreeSize[v];
        res[v] = (ll) res[parent] - subtreeSize[v] + nodesThatIAmFarNow; 
    }

    for (int u : adjList[v]){
        if (!visited[u]){
            solve(u, v, res);
        }
    }
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;

    adjList.resize(n);
    visited.resize(n);
    subtreeSize.resize(n);
    vector<ll> res(n);

    forn(i,n-1){
        int w, v;
        cin >> w >> v;
        w-=1;
        v-=1;

        adjList[w].pb(v);
        adjList[v].pb(w);
    }

    res[0] = totalDistances(0, 1); // The sum of all the distances from 0 to the rest of the vertices
	visited.assign(n, false);
    calculateNumberOfDescendants(0);

    forn(i, n) visited[i] = false;
    solve(0, 0, res);

    forn(i, n){
        cout << res[i] << " ";
    }

    cout << "\n";
}
