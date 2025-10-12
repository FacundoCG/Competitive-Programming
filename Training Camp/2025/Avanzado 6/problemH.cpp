#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;

const ll UNDEFINED = -1;
//~ const int MAX_N = 1e5 + 1;
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


// ############################################################### //

void dfs(int v, int color_actual, vvi &ady, vi &colores){
	assert(colores[v] == UNDEFINED);
	colores[v] = color_actual;  // Marco como visitado.
	
	for(int u : ady[v]){
		if(colores[u] == UNDEFINED){
			dfs(u, color_actual, ady, colores);
		}
	}
	
}


int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	vi valores(n);
	
	forn(i, n){
		cin >> valores[i];
	}
	
	vvi ady(n);
	
	vi colores(n, UNDEFINED);
	
	forn(i, m){
		int a, b;
		cin >> a >> b;
		a--; b--;
		ady[a].pb(b);
		ady[b].pb(a);
	}
	
	int color_actual = 0;
	
	forn(v, n){
		if(colores[v] == UNDEFINED){
			dfs(v, color_actual, ady, colores);
			color_actual++;
		}
	}
	
	//~ DBG(colores);
	
	vvi elementos(color_actual);
	
	forn(v, n){
		elementos[colores[v]].pb(valores[v]);
	}
	
	//~ DBG(elementos);
	
	forn(i, color_actual){
		sort(all(elementos[i]), greater<int>());
	}
	
	vi res(n);
	vi iteradores(color_actual, 0);
	
	forn(i, n){
		int col = colores[i];
		//~ DBG(i);
		
		res[i] = elementos[col][iteradores[col]];
		iteradores[col]++;
	}
	
	//~ DBG(res);
	
	for(int r : res){
		cout << r << " ";
	}
	cout << "\n";
	
	return 0;
}
