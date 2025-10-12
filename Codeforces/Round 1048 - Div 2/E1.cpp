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

struct Solve{
	vector<vi> adjList;
	int minDeepestBranch = INF;
	vi depthOf, subtreeSize, levelSize, subtreeLevelSize;
	vector<vl> memo;
	int k;
	
	Solve(vector<vi> &adj, int K) : adjList(adj), k(K){
		depthOf.resize(SIZE(adjList), 1);
		subtreeSize.resize(SIZE(adjList));
		levelSize.resize(SIZE(adjList)+2, 0);
		subtreeLevelSize.resize(SIZE(adjList)+2, 0);
		memo.resize(SIZE(adjList)+2, vl(SIZE(adjList)+2, UNDEFINED));
	}
	
	void dfs(int v){
		subtreeSize[v] = 1;
		
		for (int u : adjList[v]){
			depthOf[u] = depthOf[v] + 1;
			dfs(u);
			subtreeSize[v] += subtreeSize[u];
		}
		
		if (SIZE(adjList[v]) == 0) minDeepestBranch = min(minDeepestBranch, depthOf[v]);
	}
	
	void calculate(){
		forn(i, SIZE(adjList)){
			int level = depthOf[i];
			levelSize[level]++;
			subtreeLevelSize[level] += subtreeSize[i];
		}
	}
	
	ll dp(int i, int currentK){
		if (currentK < 0) return 0;
		if (i == minDeepestBranch+1 && k == 0) return i;
		if (i == minDeepestBranch+1 && k != 0) return 0;
		
		if (memo[i][currentK] == UNDEFINED){
			memo[i][currentK] = max(dp(i+1, currentK - levelSize[i]), dp(i+1, currentK));
		}
		
		return memo[i][currentK];
	}
	
	void ans(){
		int vertexsUnused = subtreeLevelSize[minDeepestBranch+1];
		int currentK = k - vertexsUnused;
		
		int res = 1;
		
		if (currentK <= 0){
			res = minDeepestBranch;
		} else {
			forsn(i, 1, vertexsUnused+1){
				for (int j = minDeepestBranch; j >= 1; j--){
					if (dp(j, currentK-i) == 1) res = max(res, j);
				}
			}
		}
	
		cout << res << "\n";
	}
	
};



int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		int n, k;
		cin >> n >> k;
		
		vector<vi> adjList(n);
		
		k = min(k, n-k);
		
		forsn(i, 1, n){
			int v;
			cin >> v;
			v--;
			adjList[v].pb(i);
		}
		
		Solve G(adjList, k);
		G.dfs(0);
		G.calculate();
		G.ans();
	} 
	
    return 0;
}
