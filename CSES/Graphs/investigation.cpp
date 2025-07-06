#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;
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

using peso = ll;
using indice_nodo = ll;
using nodo_pesado = pair<peso, indice_nodo>;
using arista_pesada = pair<peso, pair<indice_nodo, indice_nodo>>; 
 
// ############################################################### //

// Devuelve el vector de distancias desde inicio al i-esimo vertice.
vector<ll> djikstra(indice_nodo inicio, vector<vector<nodo_pesado>> &ady){
    vector<ll> distancia(ady.size(), LINF);
    // vector<ll> parent(ady.size(), UNDEFINED);
    vector<bool> vis(ady.size(), false);

    distancia[inicio] = 0;
    set<nodo_pesado> q;

    q.insert({0, inicio});

    while(!q.empty()){
        ll v = q.begin() -> second;
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

ll addMod(ll a, ll b, ll m = MOD){
    ll res = ((a % m) + (b % m)) % m;
    return res;
}
 
enum Color {WHITE, GREY, BLACK};  // Sin visitar / en proceso / Procesado.

// Devuelve true si encuentra un ciclo.
bool tdfs(ll v, const vector<vector<ll>> &ady, vector<Color> &color, vector<ll> &orden){
    color[v] = GREY;

    for(auto u : ady[v]){
        if(color[u] == GREY){  // Si encuentra un nodo en proceso, hay un ciclo.
            return true;
        }
        else if (color[u] == WHITE){  // Si encuentra un nodo no visitado, realiza DFS.
            if(tdfs(u, ady, color, orden)) return true;
        }
    }

    orden.pb(v);
    color[v] = BLACK;
    return false;
}

// Devuelve true sii existe un ciclo en G.
// Si no existe ciclo, en orden queda almacenado un orden topologico de G.
bool toposort(vector<vector<ll>> &ady, vector<ll> &orden){
    vector<Color> color(SIZE(ady), WHITE);
    orden.clear();

    forn(v, SIZE(ady)){
        if (color[v] == WHITE && tdfs(v, ady, color, orden)) return true;
    }

    reverse(orden.begin(), orden.end());
    return false;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	vector<vector<nodo_pesado>> adjList(n), adjListT(n);
	vector<arista_pesada> edges(m);
	
	forn(i, m){
		ll a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		adjList[a].pb({c, b});
		adjListT[b].pb({c, a});
		edges[i] = {c, {a, b}};
	}
	
	// Distancia minima de 1 a n
	vector<ll> distancesFrom1 = djikstra(0, adjList);
	vector<ll> distancesFromN = djikstra(n-1, adjListT);
	cout << distancesFrom1[n-1] << " ";
	
	// Tengo que generar el DAG de caminos minimos
	vector<vector<ll>> dagMinPaths(n);
	for (auto p : edges){
		ll weight = p.fst;
		ll u = p.snd.fst;
		ll v = p.snd.snd;
		if (distancesFrom1[n-1] == (distancesFrom1[u] + weight + distancesFromN[v])) dagMinPaths[u].pb(v);
	}
	
	// Tengo un orden topologico
	vector<ll> orden;
	toposort(dagMinPaths, orden);
	
	// Ahora contar la cantidad de formas de llegar a n-1 desde 1 en este DAG
	vector<ll> numberOfPaths(n, 0);
	numberOfPaths[0] = 1;
		
	forn(i, SIZE(orden)){
		ll u = orden[i];
		for (ll w : dagMinPaths[u]) numberOfPaths[w] = addMod(numberOfPaths[u], numberOfPaths[w], MOD);
	}
 
	cout << numberOfPaths[n-1] << " ";
	
	// Camino más corto desde 1 a n-1 en el DAG
	vector<ll> minPathDag(n, INF);
	minPathDag[0] = 0;
	forn(i, SIZE(orden)){
		ll u = orden[i];
		for (ll w : dagMinPaths[u]) minPathDag[w] = min(minPathDag[w], minPathDag[u] + 1);
	}
	
	// Camino más largo 1 a n-1 en el DAG
	vector<ll> maxPathDag(n, 0);
	forn(i, SIZE(orden)){
		ll u = orden[i];
		for (ll w : dagMinPaths[u]) maxPathDag[w] = max(maxPathDag[w], maxPathDag[u] + 1);
	}
	
	cout << minPathDag[n-1] << " " << maxPathDag[n-1] << "\n";

    return 0;
}
