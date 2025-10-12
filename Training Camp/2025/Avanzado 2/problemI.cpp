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

int n;
vi parent;

vi bfs_dist(vvi &ady){
	parent.resize(n);
	vi dist(n, UNDEFINED);
	queue<int> q({0});
	
	parent[0] = UNDEFINED;
	dist[0] = 0;
	
	while(!q.empty()){
		int v = q.front(); q.pop();
		
		for(int u : ady[v]){
			if(dist[u] == UNDEFINED){
				dist[u] = dist[v] + 1;
				parent[u] = v;
				q.push(u);
			}
		}
	}
	
	return dist;
}

bool bfs_checkear_congruencia(vvi &ady, vi &orden_juez){
	
	vi inv_orden_juez(n);  // Dado un nodo, te dice su indice.
	
	forn(i, n){
		inv_orden_juez[orden_juez[i]] = i;
	}
	
	vb padres_exahustados(n, false);
	int padre_actual = 0; 
	
	for(int i=1; i<n; i++){
		//~ DBG(padre_actual);
		//~ DBG(padres_exahustados);
		//~ RAYA;
		int nodo_actual = orden_juez[i];
		if(padre_actual != parent[nodo_actual]){
			if(padres_exahustados[parent[nodo_actual]]){
				return false;
			} else {
				padres_exahustados[padre_actual] = true;
				
				// Retrocedio.
				if(inv_orden_juez[padre_actual] >= inv_orden_juez[parent[nodo_actual]]){
					return false;
				}
				
				padre_actual = parent[nodo_actual];
			}
		}
	}
	
	return true;
}


int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	vvi ady(n);
	
	forn(i, n-1){
		int a, b;
		cin >> a >> b;
		a--; b--;
		
		ady[a].pb(b);
		ady[b].pb(a);
	}
	
	vi orden_juez(n);
	
	forn(i, n){
		cin >> orden_juez[i];
		orden_juez[i]--;
	}
	
	vi dist = bfs_dist(ady);
	
	// Checkear que inicie en el vértice 1.
	if(orden_juez[0] != 0){
		cout << "No\n";
		return 0;
	}
	
	// Checkeo que no tenga repetidos.
	
	vb aparecio(n, false);
	
	for(int v : orden_juez){
		if(aparecio[v]){
			cout << "No\n";
			return 0;
		}
		aparecio[v] = true;
	}
	

	// Checkear que sea v-geodesico
	for(int i=1; i<n; i++){
		if(dist[orden_juez[i-1]] > dist[orden_juez[i]]){  // if not <=
			cout << "No\n";
			return 0;
		}
	}
	
	// Checkeo que se visiten los hijos de los padres en orden bien.
	if(!bfs_checkear_congruencia(ady, orden_juez)){
		cout << "No\n";
		return 0;
	} 
	
	cout << "Yes\n";
	
	
	return 0;
}
