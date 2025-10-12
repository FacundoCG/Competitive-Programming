#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using ii = pair<int,int>;

template <typename T>
using vv = vector<vector<T>>;

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

using edge = pair<int, int>;

struct DisjointSet{
    vector<ll> parent, rnk;
    ll numOfComponents;

    DisjointSet(ll n){
        rnk.assign(n, 0);
        forn(i, n) {parent.pb(i);}
        numOfComponents = n;
    }

    ll findSet(ll x){
        if(parent[x]!=x) {parent[x] = findSet(parent[x]);}
        return parent[x];
    }

    void unionSet(ll x, ll y){
        // Encontrar los representantes del conjunto.
        x = findSet(x); y = findSet(y);

        // Si los conjuntos son disjuntos:
        if (x != y){
            // Pongo al que tiene menos rango por debajo del de mayor rango.
            if (rnk[x] < rnk[y]){
                parent[x] = y;
            } else if (rnk[x] > rnk[y]){
                parent[y] = x;
            } else {  // Si tienen el mismo rango, incremento del rango.  (rnk[x] == rnk[y])
                parent[y] = x;
                rnk[x]++;
            }
            numOfComponents--;
        }
    }

    bool same(ll x, ll y){
        return findSet(x) == findSet(y);
    }
};


int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<vi> adjList(n);
	vector<edge> edges(m);
	forn(i, m){
		cin >> edges[i].fst >> edges[i].snd;
		edges[i].fst--; edges[i].snd--;
	}
	
	set<edge> badEdges;
	vector<edge> forbiddenEdges(k);
	forn(i, k){
		cin >> forbiddenEdges[i].fst >> forbiddenEdges[i].snd;
		forbiddenEdges[i].fst--; forbiddenEdges[i].snd--;
		badEdges.insert(forbiddenEdges[i]);
	}
	
	DisjointSet DSU(n);
	
	forn(i, m){
		int v = edges[i].fst, u = edges[i].snd;
		edge e1 = {u, v}, e2 = {v, u};
		if (!esta(e1, badEdges) && !esta(e2, badEdges)) DSU.unionSet(v, u);
	}
	
	vi res(k);
	
	dforn(i, k){
		res[i] = (int) DSU.numOfComponents;
		int u = forbiddenEdges[i].fst, v = forbiddenEdges[i].snd;
		DSU.unionSet(v, u);	
	}
	
	forn(i, k) cout << res[i] << " ";
	cout << "\n";
	
    return 0;
}
