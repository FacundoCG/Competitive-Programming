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
#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.
#define SIZE(c) int((c).size())
 
#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl
#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define all(c) (c).begin(),(c).end()
 
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


// ############################################################### //

using peso = ll;
using indice_nodo = int;
using nodo_pesado = pair<peso, indice_nodo>;


// Devuelve el vector de distancias desde inicio al i-esimo vertice.
vector<ll> dijkstra(const indice_nodo inicio, const vector<vector<nodo_pesado>> &ady){
    vector<ll> distancia(ady.size(), LINF);
    // vector<ll> parent(ady.size(), UNDEFINED);
    vector<bool> vis(ady.size(), false);

    distancia[inicio] = 0;
    set<nodo_pesado> q;

    q.insert({0, inicio});

    while(!q.empty()){
        indice_nodo v = q.begin() -> second;
        q.erase(q.begin());

        if (vis[v]) {continue;}
        vis[v] = true;
        for(auto p : ady[v]){
			ll longitud = p.fst;
			ll u = p.snd;
            // Longitud del camino de v hacia u.
            // Relax:
            if(distancia[v] + longitud < distancia[u]){
                q.erase({distancia[u], u});
                distancia[u] = distancia[v] + longitud;
                // parent[u] = v;
                q.insert({distancia[u], u});
            }
        }
    }
    return distancia;
}

// ############################################################### //
 
int addMod(int a, int b, int m){
    int res = ((a % m) + (b % m)) % m;
    return res;
}
 
int mulMod(int a, int b, int m){
	ll resLL = (ll) a*b;
	resLL %= m;
	int res = (int) resLL;
    return res;
}
 
int binPowMod(int base, int exp, int m){
    if (exp == 0) return 1;
    
    int a = binPowMod(base, exp/2, m);
    int res = mulMod(a, a, m);
    
    if (exp % 2 == 1) res = mulMod(res, base, m);
    return res;
}
 
int divideMod(int a, int b, int m){
    int res = mulMod(a % m, binPowMod(b, m-2, m) % m, m) % m;
    return res;
}

// ############################################################### //

int fact[100001];
int memo[100001];
int newDistances[100001];

int combinatorial_func(int n, int k){
	return divideMod(fact[n], mulMod(fact[k], fact[n-k], MOD), MOD);
}

int comb(int n, int k){
	return divideMod(fact[n], fact[n-k], MOD);
}

void calcularFactorial(int n){
	fact[0] = 1;
	for(int i=1; i<=n; i++){
		fact[i] = mulMod(fact[i-1], i, MOD);
	}
}

// ############################################################### //

int main()
{	
	ios :: sync_with_stdio(0);
    cin.tie(0);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<vector<pair<peso, indice_nodo>>> ady(n);
	
	for(int i=0; i<m; i++){
		indice_nodo a, b;
		peso w;
		
		cin >> a >> b >> w;
		
		ady[a].pb({w, b});
		ady[b].pb({w, a});
	}
	
	// Por enunciado, G es conexo.
	
	vector<ll> dist = dijkstra(0, ady);	
	sort(all(dist));	
	
	forn(i, n){
		int newD = (int) dist[i];
		newDistances[i] = newD;
	}
	
	int res = 0;
	
	calcularFactorial(n); 
	
	for (int i = n-k; i >= 1; i--) memo[i] = comb(n-i-1, k-1);
	
	for(int i = n-k; i >= 1; i--){
		int delta = mulMod(newDistances[i], memo[i], MOD);
		res = addMod(res, delta, MOD);
	}
	
	res = divideMod(res, fact[k-1], MOD);
	int div = combinatorial_func(n-1, k) % MOD;
	cout << divideMod(res, div, MOD);
	
    return 0;
}
