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

struct Graph {
    int m;
    vector<bool> visited;
    vector<vector<int>> adjList;
    vector<int> parent;
	int cycle_start, cycle_end;

    Graph(int size): m(size){
        adjList.resize(m);
        visited.resize(m, false);
        parent.resize(m, UNDEFINED);
    }

    void addEdge(int u, int v){
        adjList[u].pb(v);
        adjList[v].pb(u);
    }
    
    void defineParentFrom(int v){
		visited[v] = true;
		for (int u : adjList[v]){
			if (!visited[u]){
				parent[u] = v;
				defineParentFrom(u);
			}
		}
	}
    
    void defineParents(){
		forn(i, m){
			if (!visited[i]) defineParentFrom(i);
		}
		
		visited.assign(m, false);
	}
    
    
    bool findCycle(int v){
		visited[v] = true;
		for (int u : adjList[v]){
			if (u == parent[v]) continue; 
			if (visited[u]) {
				cycle_end = v;
				cycle_start = u;
				return true;
			}
			
			if (findCycle(u)) return true;
		}

		return false;
	}
};

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, m;
    cin >> n >> m;
    
    Graph G(n);
    forn(_, m){
		int u, v;
		cin >> u >> v;
		u--; v--;
		G.addEdge(u,v);
	}
	
	G.defineParents();
	
	forn(i, G.m){
		if (!G.visited[i] && G.findCycle(i)){			
			int currentVertex = G.cycle_end;
			vector<int> cycle;
			//~ DBG(G.cycle_start); DBG(G.cycle_end);
			
			while (currentVertex != G.cycle_start){
				//~ DBG(currentVertex);
				cycle.pb(currentVertex);
				currentVertex = G.parent[currentVertex];
			}
			
			cycle.pb(G.cycle_start);
			cout << SIZE(cycle)+1 << "\n";
			dforn(j, SIZE(cycle)) cout << cycle[j]+1 << " ";
			cout << G.cycle_start + 1 << "\n";
			
			return 0;
		}
	}
	
	cout << "IMPOSSIBLE\n";
	return 0;
}
