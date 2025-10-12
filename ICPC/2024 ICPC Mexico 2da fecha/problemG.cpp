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

int n;

void dfs(int v, vector<vi> &adjList, vb &visited, vi &sizeTree){
	sizeTree[v] = 1;
	visited[v] = true;
	
	for (int u : adjList[v]){
		if (visited[u]) continue;
		dfs(u, adjList, visited, sizeTree);
		sizeTree[v] += sizeTree[u];
	}
}

map<ll, ll> memo;

void solve(int v, vector<vi> &adjList, vb &visited, vi &sizeTree){
	visited[v] = true;
	if (v != 0){
		ll subtreeSize = sizeTree[v];
		ll restNodes = n-subtreeSize;
		ll currentRes = subtreeSize*restNodes;
		memo[currentRes]++;
	}
	
	for (int u : adjList[v]){
		if (visited[u]) continue;
		solve(u, adjList, visited, sizeTree);
	}
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> n;
	
	vector<vi> adjList(n);
	vi sizeTree(n, 0);
	vb visited(n);
	
	forn(i, n-1){
		int u, v;
		cin >> u >> v;
		u--; v--;
		adjList[u].pb(v);
		adjList[v].pb(u);
	}
	
	dfs(0, adjList, visited, sizeTree);
	memo[0] = 0;
	
	visited.assign(n, false);
	solve(0, adjList, visited, sizeTree);
	
	ll res = (*memo.rbegin()).fst, usingRes = (*memo.rbegin()).snd;
	cout << res << " " << usingRes << "\n";

    return 0;
}
