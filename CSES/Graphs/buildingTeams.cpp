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
    vector<int> team;

    Graph(int size): m(size){
        adjList.resize(m);
        visited.resize(m, false);
        team.resize(m, UNDEFINED);
    }

    void addEdge(int u, int v){
        adjList[u].pb(v);
        adjList[v].pb(u);
    }
    
    bool isBipartite(int v){
		visited[v] = true;
		team[v] = 1;
		queue<int> q;
		q.push(v);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for (int w : adjList[u]){
				if (visited[w] && team[w] == team[u]) return false;
				if (visited[w]) continue;
				visited[w] = true;
				team[w] = team[u] ^ 1;
				q.push(w);
			}	
		}

		return true;
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
	
	bool isPossible = true;
	
	forn(i, G.m){
		if (!G.visited[i]){
			isPossible &= G.isBipartite(i);
		}
	}
	
	if (!isPossible){
		cout << "IMPOSSIBLE\n";
		return 0;
	}
	
	forn(i, G.m) cout << G.team[i] + 1 << " ";
	cout << "\n";
}
