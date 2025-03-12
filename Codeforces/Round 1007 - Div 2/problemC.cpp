#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
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
#define forall(i,c) for(auto i=(c).begin(), i != (c).end(); i++)
#define dforall(i,c) for(auto i=(c).rbegin(), i != (c).rend(); i--)

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

void dfs(ll v, vector<vector<ll>> &adjList, vector<vector<ll>> &distances, vector<ll> &parent, ll currentDistance){
	distances[currentDistance].pb(v);
	
	for (ll u : adjList[v]){
		if (u != parent[v]){
			parent[u] = v;
			dfs(u, adjList, distances, parent, currentDistance+1);
		}
	}
}

vector<ll> pathFrom(ll v, ll u, vector<ll> &parent){
	vector<ll> path;
	
	while (u != v){
		path.pb(u);
		u = parent[u];
	}
	
	path.pb(u);
	reverse(all(path));
	return path;
}

void solve(ll st, ll en, vector<vector<ll>> &adjList){
	ll n = SIZE(adjList);
	vector<ll> parent(n);
	vector<vector<ll>> distances(n); // distances[i] contain all vertexs which are at distance i from the root
	vector<bool> isPartOfThePath(n, false); // isPartOfThePath[i] tells you if vertex is is part of the path: st -> ... -> en
	
	dfs(st, adjList, distances, parent, 0); // Calculate the distances and parents of each vertex
	vector<ll> path = pathFrom(st, en, parent); // path from st to en
	for (ll v : path) isPartOfThePath[v] = true;
	
	// The last vertexs will be the path from st to en: st -> ... -> en
	vector<ll> permutation; 
	
	dforn(i, n){ // I use the property that if we move to a vertex which is at depth i, we have two options: currentDepth <= i or (that we are at a part of the part: st -> ... -> en or en is our ancestor). 
		// For the first case, I will just finish at depth 0 in the root. Then I follow the path st -> ... -> en
		// For the second case, if I am on the path I don't have problem to reach en again. If I have en as ancestor, I can climb up again using the rest vertexs which are at lower levels
		for(ll u : distances[i]){
			if (!isPartOfThePath[u]) permutation.pb(u); 
		}
	}
	
	for (ll u : path) permutation.pb(u);
	
	forn(i, SIZE(permutation)) cout << permutation[i] << " ";
	cout << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		ll n, st, en;
		cin >> n >> st >> en;
		
		vector<vector<ll>> adjList(n+1);
		vector<ll> parent(n+1);
		vector<vector<ll>> distances(n+1);
		
		forn(i, n-1){
			ll u, v;
			cin >> u >> v;
			adjList[u].pb(v);
			adjList[v].pb(u);
		}
		
		solve(st, en, adjList);
	}
}
