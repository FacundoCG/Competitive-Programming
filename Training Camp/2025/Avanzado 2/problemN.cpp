#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 998244353;
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
#define forsn(i,s,n) for (ll i=(s);i<(ll)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)

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

ll addMod(ll a, ll b, ll m = MOD){
    ll res = (((a + m) % m) + ((b + m) % m)) % m;
    return res;
}
 
ll mulMod(ll a, ll b, ll m = MOD){
	ll res = (ll) ((a + m) % m) * ((b + m) % m);
	res %= m;
    return res;
}
 
ll binPowMod(ll base, ll exp, ll m = MOD){
    if (exp == 0) return 1;
    
    ll a = binPowMod(base, exp/2, m);
    ll res = mulMod(a, a, m);
    
    if (exp % 2 == 1) res = mulMod(res, base, m);
    return res;
}
 
struct Peso{
	ll trasposiciones, pasos;
	
	Peso(){
		trasposiciones = INF;
		pasos = INF;
	} 
	
	Peso(int t, int p) : trasposiciones(t), pasos(p){}
	
	bool operator<(const Peso &otroPeso) const { // True sii peso < otherPeso
		if (otroPeso.trasposiciones == trasposiciones) return pasos < otroPeso.pasos;
		return trasposiciones < otroPeso.trasposiciones;
	}
	
	ll calcular(){
		// res = pasos + 2^{trasposiciones}-1
		ll res = addMod(pasos-1, binPowMod(2, trasposiciones, MOD), MOD); // 2^0 + ... + 2^{trasposiciones-1} = 2^trasposiciones-1
		//~ res = addMod(res, MOD-1);
		return res;
	}
};
 
struct Peso1{
	ll trasposiciones, pasos;
	
	Peso1(){
		trasposiciones = INF;
		pasos = INF;
	} 
	
	Peso1(int t, int p) : trasposiciones(t), pasos(p){}
	
	ll calcular() const {
		// res = pasos + 2^{trasposiciones}-1
		ll res = (ll) pasos + (1 << trasposiciones) -1;
		return res;
	}
	
	bool operator<(const Peso1 &otroPeso) const { // True sii peso < otherPeso
		bool selfInf = (trasposiciones >= INF);
		bool otherInf = (otroPeso.trasposiciones >= INF);
		if (selfInf || otherInf) {
			if (selfInf != otherInf) return !selfInf; // el que NO es INF es menor
			// ambos INF: compara pasos para romper empates, o simplemente devuelve false:
			return pasos < otroPeso.pasos; // o: return false;
		}
		
		ll v1 = calcular(), v2 = otroPeso.calcular();
		if (v1 != v2) return v1 < v2;
		if (trasposiciones != otroPeso.trasposiciones) return trasposiciones < otroPeso.trasposiciones;
		return pasos < otroPeso.pasos;
	}
};
 
struct DirectedGraph{
	int n, m, limit;
	vector<vi> adjList, adjListT;
	vector<Peso> distancia;
	vector<vector<Peso1>> distanciaComponente;
	vector<vb> visitedComponente;
	vb visited;
	
	DirectedGraph(int vertexs, int limiteTrasposiciones) : n(vertexs), limit(limiteTrasposiciones){
		adjList.resize(n);
		adjListT.resize(n);
		visited.resize(n);
		distanciaComponente.resize(limit, vector<Peso1>(n));
		visitedComponente.resize(limit, vb(n));
		m = n/2;
	}
	
	void addEdge(int v, int u){ adjList[v].pb(u);}
	void addEdgeT(int v, int u){ adjListT[v].pb(u);}
	
	void dijkstra(int inicio){
		visited.assign(n, false);
		distancia.resize(n);
 
		distancia[inicio] = Peso(0, 0);
		set<pair<Peso, int>> q;
 
		q.insert({distancia[inicio], inicio});
 
		while(!q.empty()){
			int v = q.begin() -> second;
			q.erase(q.begin());
 
			if (visited[v]) continue;
			visited[v] = true;
			
			for(int u : adjList[v]){
				Peso peso = distancia[v];
				peso.pasos += 1;
				
				if(peso < distancia[u]){
					q.erase({distancia[u], u});
					distancia[u] = peso;
					q.insert({distancia[u], u});
				}
			}
			
			int k = v;			
			if (v >= m) k -= m;
			else k += m;
			
			for (int u : adjList[k]){
				Peso peso = distancia[v];
				peso.pasos += 1;
				peso.trasposiciones += 1;
				
				if(peso < distancia[u]){
					q.erase({distancia[u], u});
					distancia[u] = peso;
					q.insert({distancia[u], u});
				}
			}
		}
	}
	
	void relaxEdges(int v, ll t, set<pair<Peso1, int>> &q, vector<vi> &adj, vector<vi> &adjT){
		for (int u : adj[v]){
			Peso1 peso = distanciaComponente[t][v];
			peso.pasos++;
			
			if (peso < distanciaComponente[t][u]){
				q.erase({distanciaComponente[t][u], u});
				distanciaComponente[t][u] = peso;
				q.insert({distanciaComponente[t][u], u});
			}
		}
		
		if (t >= limit-1) return ;
		
		for (int u : adjT[v]){
			Peso1 peso = distanciaComponente[t][v];
			peso.pasos++; peso.trasposiciones++;
			
			if (peso < distanciaComponente[t+1][u]){
				q.erase({distanciaComponente[t+1][u], u});
				distanciaComponente[t+1][u] = peso;
				q.insert({distanciaComponente[t+1][u], u});
			}
		}
	}
	
	void djikstraComponente(int inicio){
		distanciaComponente[0][inicio] = Peso1(0, 0);
		set<pair<Peso1, int>> q;
 
		q.insert({distanciaComponente[0][inicio], inicio});
		
		while(!q.empty()){
			int v = q.begin() -> second;
			ll t = (q.begin()->fst).trasposiciones;
			
			q.erase(q.begin());
			if (visitedComponente[t][v]) continue;
			visitedComponente[t][v] = true;
			
			if (t % 2 == 0) relaxEdges(v, t, q, adjList, adjListT);
			else relaxEdges(v, t, q, adjListT, adjList);
		}
	}
	
};
 
int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	int limiteTrasposiciones = 19;
	DirectedGraph G(2*n, limiteTrasposiciones);
	
	forn(_, m){
		int v, u;
		cin >> v >> u;
		v--; u--;
		G.addEdge(v, u);
		G.addEdgeT(u, v);
		G.addEdge(u+n, v+n);
	}
	
	G.dijkstra(0);
	
	Peso peso = min(G.distancia[n-1], G.distancia[2*n-1]);
	
	if (peso.trasposiciones >= limiteTrasposiciones){
		cout << peso.calcular() << "\n";
	} else { // Vamos a ver 
		G.djikstraComponente(0);
		Peso1 bestPath = G.distanciaComponente[0][n-1];
		forsn(k, 1, limiteTrasposiciones) bestPath = min(bestPath, G.distanciaComponente[k][n-1]);
		
		ll res = bestPath.calcular();
		res %= MOD;
		cout << res << "\n";
	}
		
    return 0;
}
