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

int n;

int dfs(int v, vb &visited, vector<set<int>> &adjList){
	visited[v] = true;
	int res = (v >= n);
	
	for (int u : adjList[v]){
		if (!visited[u]) res += dfs(u, visited, adjList);
	}
	
	return res;
}

void dfsBuild(int v, vi &res, vb &visited, vector<set<int>> &adjList){
	visited[v] = true;
	if (v >= n) res.pb(v-n);
	
	for (int u : adjList[v]){
		if (!visited[u]) dfsBuild(u, res, visited, adjList);
	}
}

void solve(vi &row1, vi &row2, vector<vector<pair<int, int>>> &elements){	
	vector<set<int>> adjList(2*n);
	vb visited(2*n, false);
	
	// Construyo el grafo
	forn(i, n){
		if (row1[i] == row2[i]) continue;
		int a = row1[i], b = row2[i];
		
		auto p = elements[a][0];
		if (p.fst == 0 && p.snd == i) p = elements[a][1]; // Si está en mi misma fila y columna, entonces busco a la otra posición
		
		if (p.fst == 0){ // Si está en mi misma fila
			adjList[i+n].insert(p.snd); // La otra no puedo hacer swap
			adjList[i].insert(p.snd + n);
		} else {
			adjList[i+n].insert(p.snd + n);
			adjList[i].insert(p.snd);
		}
		
		p = elements[b][0];
		if (p.fst == 1 && p.snd == i) p = elements[b][1];
		
		if (p.fst == 1){ // Si está en mi misma fila
			adjList[i+n].insert(p.snd);
			adjList[i].insert(p.snd + n);
		} else {
			adjList[i+n].insert(p.snd + n);
			adjList[i].insert(p.snd);
		}
	}
	
	vi goodVertexs;
	
	forn(i, n){
		if (!visited[i]){
			int res1 = dfs(i, visited, adjList), res2 = dfs(i+n, visited, adjList);
			if (res1 <= res2) goodVertexs.pb(i);
			else goodVertexs.pb(i+n);
		}
	}
	
	visited.assign(2*n, false);
	vi res;
	for (int v : goodVertexs) dfsBuild(v, res, visited, adjList);
	cout << SIZE(res) << "\n";
	for (int v : res) cout << v+1 << " ";
	cout << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		cin >> n;
		
		vi row1(n), row2(n);
		vector<vector<pair<int, int>>> elements(n+1);
		
		forn(i, n){
			cin >> row1[i];
			elements[row1[i]].pb({0, i});			
		}
		
		forn(i, n){
			cin >> row2[i];
			elements[row2[i]].pb({1, i});			
		}
		
		bool flag = false;
		forsn(i, 1, n+1) flag |= (SIZE(elements[i]) != 2);
		
		if (flag){
			cout << -1 << "\n";
			continue;
		}
		
		solve(row1, row2, elements);
	}
	
	
    return 0;
}
