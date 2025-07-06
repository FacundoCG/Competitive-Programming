#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
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

    reverse(all(orden));
    return false;
}


int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	vector<vector<ll>> adjList(n);
	forn(_, m){
		ll a, b;
		cin >> a >> b;
		a--; b--;
		adjList[a].pb(b);
	}
	
	vector<ll> orden;
	toposort(adjList, orden);
	
	vector<ll> res(n, 1);
	dforn(i, n){
		ll v = orden[i];
		for (ll u : adjList[v]) res[v] += res[u];
	}
	
	
	
    return 0;
}
