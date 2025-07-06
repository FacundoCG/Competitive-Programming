#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
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
 
 
// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18
 
// ############################################################### //

struct Graph {
    int m;
    vector<vector<int>> adjList;
    vector<int> longestBranchFrom;
    vector<int> longestPathThrough;
	int lengthDiameter;
	
    Graph(int size): m(size){
        adjList.resize(m);
        longestBranchFrom.resize(m, 0);
        longestPathThrough.resize(m, 0);
		lengthDiameter = 0;
    }

    void addEdge(int u, int v){
        adjList[u].pb(v);
        adjList[v].pb(u);
    }
    
    void dfs(int v, int currentParentOfV){
		vector<int> branchsLength;
		
		for (int u : adjList[v]){
			if (u == currentParentOfV) continue;
			dfs(u, v);
			branchsLength.pb(longestBranchFrom[u]);
		}

		longestBranchFrom[v] = 0;
		sort(all(branchsLength)); // Esto se puede hacer en O(n) buscando los dos máximos 
		if (SIZE(branchsLength) > 0) longestBranchFrom[v] = 1 + branchsLength[SIZE(branchsLength)-1];
		if (SIZE(branchsLength) > 1) longestPathThrough[v] = branchsLength[SIZE(branchsLength)-1] + 2 + branchsLength[SIZE(branchsLength)-2];
		lengthDiameter = max(lengthDiameter, max(longestBranchFrom[v], longestPathThrough[v]));
	}
};

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
 
    Graph G(n);
 
    forn(i,n-1){
        int w, v;
        cin >> w >> v;
        w--; v--;
        G.addEdge(v, w);
    }
 
    G.dfs(0, UNDEFINED);
    cout << G.lengthDiameter << "\n";
}
