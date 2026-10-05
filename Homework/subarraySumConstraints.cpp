#include <bits/stdc++.h>
using namespace std;
#define for1(i, n) for(int i = 1; i <= (n); ++i)
#define repeat(n) for1(_, n)
#define forn(i, n) for(int i = 0; i < (n); ++i)
#define forsn(i, s, n) for(int i = (s); i < (n); ++i)
#define dbg(x) cout << #x << " = " << (x) << endl;
using ll = long long;
using lll = __int128;
using vi = vector<short>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvi = vector<vi>;
using ii = pair<int, ll>;
using vii = vector<ii>;
using vvii = vector<vii>;
using vb = vector<bool>;

const ll MOD = 1e9 + 7;
const ll LINF = 1e18;
const short INF = 1e3;

#define pb push_back
#define fst first
#define snd second
#define esta(x, c) (c.find(x) != c.end())
#define all(c) (c).begin(), (c).end()

bool dfs(int v, vvii &adj, vb &visited, vl &prefixSum){
	visited[v] = true;
	for (auto [u, weight] : adj[v]){
		ll desiredWeightForU = prefixSum[v] + weight;
		if (!visited[u]){
			prefixSum[u] = desiredWeightForU;
			bool res = dfs(u, adj, visited, prefixSum);
			if (!res) return res;
		}
		if (prefixSum[u] != desiredWeightForU) return false;
	}
	
	return true;
}

void solve(){
	int n, m; cin >> n >> m;
	vvii adj(n+1);
	
	forn(_, m){
		int l, r; cin >> l >> r;
		ll s; cin >> s; // prefixSum[r] - prefixSum[l-1] = s
		adj[l-1].pb(make_pair(r, s));
		adj[r].pb(make_pair(l-1, -s));
	}
	
	vb visited(n+1);
	vl prefixSum(n+1);
	
	forn(i, n+1) if (!visited[i]){
		bool validAssignment = dfs(i, adj, visited, prefixSum);
		if (!validAssignment){ cout << "NO\n"; return ;}
	}
		
	cout << "YES\n";
	forsn(i, 1, n+1) cout << prefixSum[i] - prefixSum[i-1] << " ";
	cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
		
	int t = 1;
	forn(_, t) solve();
}
