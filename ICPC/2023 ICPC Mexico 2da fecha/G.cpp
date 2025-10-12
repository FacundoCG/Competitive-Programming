#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

using vi = vector<int>;
using vl = vector<ll>;
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

ll res = 0;
set<pair<ll, int>> max_in, max_out, best_loop;
vl in, out;

void deleteOld(int u, int v){
	res -= in[u]*out[u];
	if (u != v) res -= in[v]*out[v];
}

void addEdge(int u, int v){
	auto it = max_in.find({in[v], v});
	ll sumV = in[v] + out[v], sumU = in[u] + out[u];
	best_loop.erase({sumV, v});
	best_loop.erase({sumU, u});
	max_in.erase(it);
	
	auto it1 = max_out.find({out[u], u});
	max_out.erase(it1);
	
	in[v]++; out[u]++;
	sumV = in[v] + out[v], sumU = in[u] + out[u];
	max_in.insert({in[v], v});
	max_out.insert({out[u], u});
	best_loop.insert({sumV, v});
	best_loop.insert({sumU, u});
	
	res += in[u]*out[u];
	if (u != v) res += in[v]*out[v];
}

int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	int n, t;
	cin >> n >> t;
	
	in.resize(n, 0); out.resize(n, 0);
	forn(i, n){
		max_in.insert({0, i});
		max_out.insert({0, i});
		best_loop.insert({0, i});
	}
	
	forn(_, t){
		int u, v;
		cin >> u >> v;
		u--; v--; // u->v
		
		deleteOld(u, v);
		addEdge(u, v);
		
		auto h = *max_out.rbegin(), w = *max_in.rbegin();
		//~ DBG(h); DBG(w);
		
		auto it = *best_loop.rbegin();
		ll sumBestLoop = it.fst;
		
		if (sumBestLoop >= h.fst + w.fst){
			cout << res << " " << sumBestLoop + 1 << "\n";
		} else {
			cout << res << " " << h.fst + w.fst << "\n";
		}
	}
	
	return 0;
}
