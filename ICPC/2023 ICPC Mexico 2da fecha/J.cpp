#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;
const ld EPSILON = 1e-10;

#define pb push_back
#define fst first
#define snd second

#define esta(x, c) ((c).find(x) != (c).end())
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << "=" << (x) << endl;
#define RAYA cerr << "-----------" << endl;

#define forn(i, n) for(int i=0; i<(int)(n); i++)
#define forsn(i, s, n) for(int i=(s); i<(int)(n);i++)

template <typename T1, typename T2>
ostream & operator <<(ostream &os, const pair<T1, T2> &p){
	os << "{" << p.fst << ", " << p.snd;
	return os << "}";
}

template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v){
	os << "[";
	forn(i, SIZE(v)){
		if (i > 0) os << ",";
		os << v[i];
	}
	return os << "]";
}

// ######################## //

using Edge = pair<int, int>;
vi componente;

struct Tarjan{
	vector<vi> adjList;
	vb visited;
	vi foundAt, minTimeFound;
	vector<Edge> bridges;
	
	Tarjan(vector<vi> &adj) : adjList(adj){
		visited.resize(SIZE(adjList), false);
		foundAt.resize(SIZE(adjList));
		minTimeFound.resize(SIZE(adjList));
	}
	
	void dfs(int v, int currentTime, int parent){
		visited[v] = true;
		foundAt[v] = minTimeFound[v] = currentTime;
		
		for (int w : adjList[v]){
			if (w == parent) continue;
			if (!visited[w]){
				dfs(w, currentTime+1, v);
				if (foundAt[v] < minTimeFound[w]) bridges.pb({v, w});
			}
			
			minTimeFound[v] = min(minTimeFound[v], minTimeFound[w]);
		}
	}
};

void dfs(int v, int color, vector<vi> &adjList, vb &visited){
	visited[v] = true;
	componente[v] = color;
		
	for (int w : adjList[v]){
		if (!visited[w]) dfs(w, color, adjList, visited);
	}
}

int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	int n, m, q;
	cin >> n >> m >> q;
	
	vvi ady(n);
	map<Edge, int> M;
	
	forn(i, m){
		int a, b;
		cin >> a >> b;
		a--; b--;
		assert(a != b);
		
		if(!esta(make_pair(a, b), M)){
			ady[a].pb(b);
			ady[b].pb(a);
		}
		
		M[{a,b}]++;
		M[{b,a}]++;
	}
	
	Tarjan T(ady);
	T.dfs(0, 0, UNDEFINED);  // Era conexo.
	
	componente.resize(n, UNDEFINED);	
	vector<vi> adjList(n);
	vb visited(n, false);
	int color = 1;
	
	for (auto [u, v] : T.bridges){
		if (M[{u, v}] == 1){					
			adjList[u].pb(v);
			adjList[v].pb(u);
		}
	}
	
	forn(i, n){
		if (!visited[i]) dfs(i, color++, adjList, visited);
	}
	
	forn(i, n){
		assert(visited[i]);
		assert(componente[i] != UNDEFINED);
	}
	
	// Respondo queries.
	forn(i, q){
		int s, e;
		cin >> s >> e;
		s--; e--;
		assert(s != e);
		if(componente[s] != componente[e]){
			cout << "NO\n";
		} else {
			cout << "YES\n";
		}
	}
	
	return 0;
}
