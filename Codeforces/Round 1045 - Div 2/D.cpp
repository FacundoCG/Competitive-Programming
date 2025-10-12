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

vi distances, parent;
vector<vi> adjList;

void dfs(int v, int p, int depth){
	distances[v] = depth;
	parent[v] = p;
	
	for (int u : adjList[v]){
		if (u == p) continue;
		dfs(u, v, depth+1);
	}
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
		
	forn(_, t){
		int n;
		cin >> n;
		
		adjList.clear();
		adjList.resize(n);
		forn(i, n-1){
			int u, v;
			cin >> u >> v;
			u--; v--;
			adjList[u].pb(v);
			adjList[v].pb(u);
		}
		
		//~ DBG(adjList); DBG(n);
		
		// Busco los dos vértices del diametro
		distances.resize(n, 0);
		parent.resize(n);
		dfs(0, -1, 0);
		
		int v1 = (int) (max_element(all(distances)) - distances.begin());
		dfs(v1, -1, 0);
		
		int v2 = (int) (max_element(all(distances)) - distances.begin());
		
		if (distances[v2] == n-1) cout << "-1\n";
		else {
			// Marco el camino del diametro
			vi isPartOfDiameter(n, false);
			int v = v2;
			while (v != UNDEFINED){
				isPartOfDiameter[v] = true;
				v = parent[v];
			}
			
			int a = -1, b = -1, c = -1;
			
			forn(i, n){
				for(int u : adjList[i]){
					if (isPartOfDiameter[i] && !isPartOfDiameter[u] && parent[i] != UNDEFINED){
						a = parent[i];
						b = i;
						c = u;
					}
				}
			}
			
			cout << a+1 << " " << b+1 << " " << c+1 << "\n";
		}
	}
	
    return 0;
}
