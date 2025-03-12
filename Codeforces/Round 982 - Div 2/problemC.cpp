#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

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
#define forall(i,c) for(auto i=(c).begin(), i != (c).end(); i++)
#define dforall(i,c) for(auto i=(c).rbegin(), i != (c).rend(); i--)

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

void dfs(map<ll,vector<ll>> &graph, set<ll> &visited, ll v){	
	if (!esta(v, visited)){
		visited.insert(v);
		
		for (ll u : graph[v]){
			dfs(graph, visited, u);
		}
	}
}

void solve(vector<ll> &A){
	// We choose one i such that: 0 <= i < |A| and A[i] = |A| - i
	// Then, I append i zeros onto the end of A
	// Let's n = |A| (original A)
	// The first thing that we can conclude is that, we will just can choose indexs between: 0 <= i < n and we can't pick two times the same index

	// We can pass the relation to: 0 <= i < n and A[i] + i = |A|
	// A = [n, n-1, n-2, ..., n-]
	
	map<ll, vector<ll>> graph;
	
	forsn(i, 1, SIZE(A)){
		ll v = A[i] + i; // The vertex where I am currently
		ll u = v + i; // The vertex where I can jump from my position. Because the current node will be equal to |A|, and the next node should be |A| + i
		graph[v].pb(u);
	}
	
	set<ll> visited; // The vertexs that I visited with the dfs
	dfs(graph, visited, SIZE(A)); // The node where I am start is |A|
	
	// Now I choose the bigger number in visited because it means the maximum size of the array achieved
	
	ll res = *visited.rbegin();
	
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_, t){
        int n;
        cin >> n;

        vector<ll> A(n);
        forn(i, n) cin >> A[i];
        
        solve(A);
    }
}
