#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

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

template <typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

bool toposort(vector<vi> &ady, vi &orden){
	orden.clear();
	vector<int> in_deg(SIZE(ady), 0);
	
	forn(v, SIZE(ady)){
		for(auto u : ady[v]) in_deg[u]++;
	}
	
	min_heap<int> q; // Si usamos min priority_queue podemos obtener el orden lexicografico más chico
	forn(v, SIZE(ady)){
		if(in_deg[v] == 0) q.push(v);
	}
	
	while(!q.empty()){
		int v = q.top();
		q.pop();
		orden.pb(v);
		
		for(auto u : ady[v]){
			in_deg[u]--;
			if(in_deg[u] == 0){
				q.push(u);
			}
		}
	}
	
	return SIZE(orden) != SIZE(ady);  // Retorna true sii hay un ciclo.
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	vector<vi> adjList(n);
	forn(i, m){
		int a, b;
		cin >> a >> b;
		a--; b--;
		adjList[a].pb(b);
	}
	
	vi orden;
	toposort(adjList, orden);
	
	forn(i, n) cout << orden[i] + 1 << " ";
	cout << "\n";
	
    return 0;
}
