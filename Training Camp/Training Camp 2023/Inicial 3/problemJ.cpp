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

bool canMakeName(vector<ll> &lettersAvailable, vector<ll> &name){
    bool res = true;

    for (int i = 0; i < 26; i++){
        if (name[i] > lettersAvailable[i]){
            res = false;
        }
    }

    return res;
}

ll binarySearch(vector<vector<ll>> &arr, vector<ll> &name){
    int a = -1; // extremo izquierdo del rango de búsqueda -1
    int b = arr.size(); // extremo derecho del rango de búsqueda +1
    while(b - a > 1) { // mientras que la distancia entre las fronteras sea >1 (es decir, mientras que no estén contiguas)
        int m = (a + b) / 2; // punto medio
        if(!canMakeName(arr[m], name)) {
            a = m; // dependiendo del caso 1 o 2, vamos a intercambiar si seteamos a o b, muy fácil de razonar!
        } else {
            b = m; // acá simplemente seteamos la otra frontera!
        }
    }

    return b;
}


// ############################################################### //

void dfs(ll start, ll end, vector<vector<ll>> &adjList, vector<bool> &visited, vector<ll> &parents){
    if (start == end){
        return;
    }
    
    visited[start] = true;

    for (int i = 0; i < adjList[start].size(); i++){
        ll w = adjList[start][i];

        if (!visited[w]){
            parents[w] = start;
            dfs(w, end, adjList, visited, parents);
        }
    }
}

ll numberOfVerticesInConnectedComponent(ll v, vector<vector<ll>> &adjList, vector<bool> &visited){
    ll n = adjList.size();
    visited[v] = true;
    ll res = 1;

    queue<ll> q;
    q.push(v);

    while (!q.empty()){
        ll w = q.front();
        q.pop();

        for (int i = 0; i < adjList[w].size(); i++){
            ll u = adjList[w][i];

            if (!visited[u]){
                q.push(u);
                visited[u] = true;
                res++;
            }
        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    // Reading input
    ll n, x, y;
    cin >> n >> x >> y;

    vector<vector<ll>> adjList(n);
    x -= 1;
    y -= 1;

    forn(i, n-1){
        ll u, v;
        cin >> u >> v;

        u -= 1;
        v -= 1;
        adjList[u].pb(v);
        adjList[v].pb(u);
    }

    // Calculate path from x to y
    vector<bool> visited(n, false);
    vector<ll> parents(n, UNDEFINED);
    dfs(x, y, adjList, visited, parents);
    vector<bool> belongsToThePath(n, false);
    ll currentVertex = y;

    while (currentVertex != x){
        belongsToThePath[currentVertex] = true;
        currentVertex = parents[currentVertex];
    }
    
    belongsToThePath[x] = true;

    // New graph without edges adjacent to vertexs of the path    
    vector<vector<ll>> newAdjList(n);
    vector<bool> adjacentToX(n, false);
    vector<bool> adjacentToY(n, false);

    forn(i,n){
        for(auto v : adjList[i]){
            if (!belongsToThePath[i] && !belongsToThePath[v]){
                newAdjList[i].pb(v);
                newAdjList[v].pb(i);
            }

            if (i == x){
                adjacentToX[v] = true;
            } else if (i == y){
                adjacentToY[v] = true;
            }
        }
    }

    // Calcuting number of vertexs in each connected component adjacent to X and Y 
    vector<vector<ll>> verticesOfConnectedComponents(2);
    visited.assign(n,false);

    forn(i,n){
        if (!visited[i] && !belongsToThePath[i] && (adjacentToX[i] || adjacentToY[i])){
            int m = numberOfVerticesInConnectedComponent(i, newAdjList, visited);
            if (adjacentToX[i]){
                verticesOfConnectedComponents[0].pb(m);
            } else {
                verticesOfConnectedComponents[1].pb(m);
            }
        }
    }

    // Calculating answer
    ll totalPaths = (ll) n * (n-1); // All the paths without considering constraints
    ll extraPaths = 0; // I know that the path from X to Y will never be available
    verticesOfConnectedComponents[1].pb(1); // All the paths from a vertex of a connected component adjancent to X can't reach Y
    verticesOfConnectedComponents[0].pb(1);

    for (auto v1 : verticesOfConnectedComponents[0]){
        for (auto v2 : verticesOfConnectedComponents[1]){
            extraPaths += (ll) v1*v2;
        }
    }

    totalPaths -= extraPaths;
    cout << totalPaths << "\n";
}