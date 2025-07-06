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

enum ESTADO{
	VISITADO,
	VISITANDO,
	NO_VISITADO
};

// Acá devuelve ciclos de longitud 2
int findCycle(int v, vector<vector<int>> &adjList, vector<int> &parent, vector<ESTADO> &visited){
    visited[v] = VISITANDO;
    
    for (int u : adjList[v]){
        if (visited[u] == VISITANDO) {
			parent[u] = UNDEFINED;
			return v;
		}
		
        if (visited[u] == NO_VISITADO){
			parent[u] = v;
            int possibleCycle = findCycle(u, adjList, parent, visited);
            if (possibleCycle != UNDEFINED) return possibleCycle;
        }
    }

    visited[v] = VISITADO;
    return UNDEFINED;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	vector<vector<int>> adjList(n);
	vector<ESTADO> visited(n, NO_VISITADO);
	vector<int> parent(n, UNDEFINED);	
		
	forn(i, m){
		int a, b;
		cin >> a >> b;
		a--; b--;
		adjList[a].pb(b);
	}
	
	forn(i, n){
		if (visited[i] == NO_VISITADO){
			int startCycle = findCycle(i, adjList, parent, visited);
			if (startCycle != UNDEFINED){
				vector<int> path;
				int currentVertex = startCycle;
				while (currentVertex != UNDEFINED){
					path.pb(currentVertex);
					currentVertex = parent[currentVertex];
				}
				
				reverse(all(path));
				cout << SIZE(path) + 1 << "\n";
				forn(j, SIZE(path)) cout << path[j] + 1 << " ";
				cout << path[0] + 1 << "\n";
				
				return 0;
			}
		}
	}
	
	cout << "IMPOSSIBLE\n";
		
    return 0;
}
