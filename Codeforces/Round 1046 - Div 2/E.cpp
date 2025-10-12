#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using ii = pair<int,int>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 998244353;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
const ld EPSILON = 1e-10;
const double PI = acos(-1.0);

#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl

#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)

// Show pair
template <typename T1, typename T2>
ostream & operator <<(ostream &os, const pair<T1, T2> &p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

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

ll mod(ll a, ll m = MOD){
	ll res = a % m;
    if (res < 0) res += m;
	return res;
}
 
ll mulMod(ll a, ll b, ll m = MOD){
	ll res = (ll) mod(a, m)*mod(b, m);
	res %= m;
    return res;
}

using Edge = pair<int, int>;
struct Tarjan{
	vector<vi> adjList;
	vb visited;
	vi foundAt, minTimeFound;
	set<Edge> bridges;
	
	Tarjan(vector<vi> &adj) : adjList(adj){
		visited.resize(SIZE(adjList), false);
		foundAt.resize(SIZE(adjList));
		minTimeFound.resize(SIZE(adjList));
	}
    
    // Llamarlo con parent = UNDEFINED
	void dfs(int v, int currentTime, int parent){
		visited[v] = true;
		foundAt[v] = minTimeFound[v] = currentTime;
		
		for (int w : adjList[v]){
			if (w == parent) continue;
			
			if (!visited[w]) {
				dfs(w, currentTime+1, v);
                // Quiere decir que w no llego a v ni a ninguno de sus ancestros
				if (foundAt[v] < minTimeFound[w]) bridges.insert({v, w});
			}
            
            minTimeFound[v] = min(minTimeFound[v], minTimeFound[w]);
		}
	}
};

int n, m;
ll V;
vl weights;

struct Graph{
	vector<vi> adjList;
	vi team;
	vb visited;
	
	Graph(vector<vi> &adj) : adjList(adj){
		visited.resize(SIZE(adjList), false);
		team.resize(SIZE(adjList));
	}
	
	bool isBipartite(int v, set<ll> &distinctWeights){
		visited[v] = true;
		team[v] = 1;
		queue<int> q; q.push(v);
		bool res = true;
		
		while(!q.empty()){
			int u = q.front(); q.pop();
			distinctWeights.insert(weights[u]);
			
			for (int w : adjList[u]){
				if (visited[w] && team[w] == team[u]) res = false;
				else if (visited[w]) continue;
				else {
					visited[w] = true;
					team[w] = team[u] ^ 1;
					q.push(w);
				}
			}
		}

		return res;
	} 
};

void solve(){
	cin >> n >> m >> V;
	vector<vi> adj(n);
	weights.clear(); weights.resize(n);
	forn(i, n) cin >> weights[i];
 	
 	vector<ii> edges;
	forn(_, m){
		int v, u;
		cin >> v >> u;
		v--; u--;
		adj[v].pb(u); adj[u].pb(v);
		edges.pb({v, u});
	}
	
	Tarjan T(adj);
	T.dfs(0, 0, UNDEFINED);
	
	adj.clear(); adj.resize(n);
	for (auto [v, u] : edges){
		Edge p1 = {v, u}, p2 = {u, v};
		if (esta(p1, T.bridges) || esta(p2, T.bridges)) continue;
		adj[v].pb(u); adj[u].pb(v);
	}
	
	// Ahora en adj tengo las 2-edge connected components (eliminé los puentes)
	ll res = 1;
	Graph G(adj);
	
	forn(i, n){
		if (G.visited[i]) continue;
		set<ll> weightsOfComponents;
		bool flag = G.isBipartite(i, weightsOfComponents);
		
		if (!flag){ // Hay ciclo de longitud impar (tienen que ser todos 0)
			for (ll w : weightsOfComponents) {if (w != -1 && w != 0) res = 0;}	
		} else { // Solo ciclos de longitud par
			if (esta(-1, weightsOfComponents)){
				if (SIZE(weightsOfComponents) > 2) res = 0;
				else if (SIZE(weightsOfComponents) == 1) res = mulMod(res, V);
			} else if (!esta(-1, weightsOfComponents) && SIZE(weightsOfComponents) > 1) res = 0;
		}
	}
	
	//~ ll res1 = 1;
	//~ forn(_, 3) res1 = mulMod(res1, V);
	//~ DBG(res1);
	cout << res << "\n";
	//~ RAYA;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
	int t;
    cin >> t;
	forn(_, t) solve();
}
