#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long ld;

using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()
#define SIZE(c) int((c).size())


#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "------------------" << endl

#define forn(i, n) for (int i=0;i<(int)(n); i++)
#define forsn(i, s, n) for (int i=(s);i<(int)(n); i++)

// Show vector

template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v){
    os << "[";
    forn(i, v.size()){
        if(i>0) os << ",";
        os << v[i];
    }
    return os << "]";
}

int n, m;
set<pair<int, int>> goodEdges;

int bipartite(int v, vector<vi> &adjList, vb &visited){
	vi team(n, 0);
	visited[v] = true;
	team[v] = 1;
	
	queue<int> q;
	q.push(v);
	
	int res = 0;
	
	while (!q.empty()){
		int u = q.front(); q.pop();
		for (int w : adjList[u]){
			if (visited[w] && team[w] == team[u]){
				res++;
				goodEdges.insert({u, w});
				continue;
			} else if (visited[w]){
				continue;
			}
			
			visited[w] = true;
			team[w] = team[u] ^ 1;
			q.push(w);
		}
	}
	
	return res;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> n >> m;
	
	vector<vi> adjList(n);
	vector<vb> badEdge(n, vb(n, false));
	
	forn(i, m){
		int u, v;
		cin >> u >> v;
		u--; v--;
		badEdge[u][v] = true;
		badEdge[v][u] = true;
	}
	
	forn(i, n){
		forn(j, n){
			if (i == j) continue;
			if (badEdge[i][j]) continue;
			adjList[i].pb(j);
		}
	}

	vb visited(n, false);
	int res = 0;
	
	forn(i, n){
		if (!visited[i]) res += bipartite(i, adjList, visited);
	}
		
	int limite = n*(n-1)/4;
	
	if (res > limite){
		cout << "NO\n";
		return 0;
	}
	
	cout << "YES\n";
	cout << res << "\n";
	for (auto p : goodEdges){
		cout << p.fst+1 << " " << p.snd+1 << "\n";
	}
	
	
    return 0;
}
