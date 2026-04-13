#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vvvvl = vector<vvvl>;
using ii = pair<int,int>;
 
template <typename T>
using vv = vector<vector<T>>;
 
const ll UNDEFINED = 1e9;
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
 
#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
 
// ############################################################### //

using Edge = pair<int, int>;
map<Edge, ll> freq;
int n, s;

vi toposort(vector<set<int>> &adj){
	vi order, in_deg(n);
	
	forn(v, n) for (int u : adj[v]) in_deg[u]++;
	
	queue<int> q;
	forn(v, n) if (in_deg[v] == 0) q.push(v);
	
	while (!q.empty()){
		int v = q.front(); q.pop();
		order.pb(v);
		
		for (int u : adj[v]){
			in_deg[u]--;
			if (in_deg[u] == 0) q.push(u);
		}
	}
	
	return order;
}

void solve(){
	cin >> n >> s; 
	vector<set<int>> adj(n);
	
	forn(_, s){
		int v, u; cin >> v >> u;
		v--; u--;
		adj[v].insert(u);
		freq[make_pair(v, u)]++;
	}
		
	vi toposortOrder = toposort(adj);
	
	vl numberOfPaths(n);
	numberOfPaths[n-1] = 1;
	
	dforn(i, n-1){
		int v = toposortOrder[i];
		for (int u : adj[v]){
			Edge e = make_pair(v, u);
			numberOfPaths[v] += numberOfPaths[u]*freq[e];
		}
	}
	
	vl dp(n);
	dp[n-1] = numberOfPaths[n-1];
	
	dforn(i, n-1){
		int v = toposortOrder[i];
		for (int u : adj[v]) dp[v] = max(dp[v], dp[u] + numberOfPaths[v]);
	}
	
	cout << dp[0] << "\n";
}

 
int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t = 1; 
	//~ cin >> t;
	forn(_, t) solve();
	return 0;
}
