#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

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

struct SCC {
	int n, comps = 0;
	vb vis;
	vi order, id_scc;
	vector<vi> ady, ady_t;
	vi representante;  // (Opcional) Dada un *id_scc*, te dice algun nodo de esa scc.
	
	SCC(vector<vi> &_ady, vector<vi> &_ady_t){
		ady = _ady;
		ady_t = _ady_t;
		n = SIZE(ady);
		vis.assign(n, false);
		id_scc.resize(n);
		
		forn(i, n){
			if(!vis[i]) { dfs1(i); }
		}
		vis.assign(n, false);
		reverse(all(order));
		for(int v : order){
			if(!vis[v]){
				dfs2(v, comps);
				representante.pb(v);
				comps++;  // Aumento el contador de SCC.
			}
		}
	}
	
	vector<vi> sccToDAG(){  // (Opcional)
		vector<set<int>> ady_dag_with_set(comps);
		forn(v, n){
			for(int u : ady[v]){
				if(id_scc[v] == id_scc[u]) {continue;}  // Evita self-loops.
				ady_dag_with_set[id_scc[v]].insert(id_scc[u]);
			}
		}
		// Convertir a vector de vector de int.
		vector<vi> ady_dag(comps);
		forn(i, comps){
			ady_dag[i] = vi(all(ady_dag_with_set[i]));
		}
		return ady_dag;
	}

private:
	void dfs1(int v) {
		vis[v] = true;
		for(int u : ady[v]) {
			if (!vis[u]) { dfs1(u); }
		}
		order.pb(v);
	}
    
	void dfs2(int x, int comp) {
		vis[x] = true;
		for (int u : ady_t[x]) {
			if (!vis[u]) { dfs2(u, comp); }
		}
		id_scc[x] = comp;
	}
};

void dfs(int v, vector<vi> &adjList, vector<bool> &visited){
	visited[v] = true;
	
	for (int u : adjList[v]){
		if (visited[u]) continue;
		dfs(u, adjList, visited);
	}
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	vector<vector<int>> adjList(n), adjListT(n);
		
	forn(i, m){
		int a, b;
		cin >> a >> b;
		a--; b--;
		adjList[a].pb(b);
		adjListT[b].pb(a);
	}
	
	SCC G(adjList, adjListT);
	
	if (G.comps == 1){
		cout << "YES\n";
		return 0;
	}
	
	cout << "NO\n";
	int v = G.representante[0];
	int w = G.representante[1];
	
	vector<bool> visited(n, false);
	dfs(v, adjList, visited);
	
	if (!visited[w]){
		cout << v+1 << " " << w+1 << "\n";
	} else {
		cout << w+1 << " " << v+1 << "\n";
	}
		
    return 0;
}
