#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 998244353;
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

// ############################################################### //

ll subMod(ll a, ll b, ll m){
	ll res = (a % m) - (b % m) + m;
	res %= m;
	return res;
}

ll addMod(ll a, ll b, ll m){
	ll res = ((a % m) + (b % m)) % m;
	return res;
}

void calculateDistances(ll v, ll depth, vector<vector<ll>> &adjList, vector<ll> &parents, vector<vector<ll>> &nodesPerLevel, vector<bool> &visited){
	visited[v] = true;
	nodesPerLevel[depth].pb(v);
	
	
	forn(i, SIZE(adjList[v])){
		ll u = adjList[v][i];
		if (!visited[u]){
			parents[u] = v;
			calculateDistances(u, depth + 1, adjList, parents, nodesPerLevel, visited);
		}
	}
}

void solve(vector<vector<ll>> &adjList){
	vector<ll> parents(SIZE(adjList), 0);
	vector<vector<ll>> nodesPerLevel(SIZE(adjList));
	vector<bool> visited(SIZE(adjList), false);
	
	parents[1] = 1;
	
	calculateDistances(1, 0, adjList, parents, nodesPerLevel, visited);
	
	vector<ll> numberOfValidSequencesFinishedAt(SIZE(adjList)); // These are number of valid sequences of the form [..., i] for each vertex i
	vector<ll> numberOfValidSequencesPerLevel(SIZE(adjList));
	numberOfValidSequencesPerLevel[0] = 1; // Just the [1]
	numberOfValidSequencesFinishedAt[1] = 1;
	
	for (ll u : nodesPerLevel[1]){
		numberOfValidSequencesFinishedAt[u] = 1; // I just have one valid sequence that each in a direct son of the root
		numberOfValidSequencesPerLevel[1]++;
	}
	
	forsn(i, 2, SIZE(nodesPerLevel)){
		for (ll u : nodesPerLevel[i]){
			ll p = parents[u];
			numberOfValidSequencesFinishedAt[u] = subMod(numberOfValidSequencesPerLevel[i-1], numberOfValidSequencesFinishedAt[p], MOD);
			numberOfValidSequencesPerLevel[i] = addMod(numberOfValidSequencesPerLevel[i], numberOfValidSequencesFinishedAt[u], MOD);
		}
	}
	
	ll res = 0;
	
	forsn(i, 1, SIZE(adjList)) res = addMod(res, numberOfValidSequencesFinishedAt[i], MOD);
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		ll n;
		cin >> n;
		
		vector<vector<ll>> adjList(n+1);
		
		forsn(i, 2, n+1){
			ll p;
			cin >> p;
			adjList[i].pb(p);
			adjList[p].pb(i);
		}
		
		solve(adjList);
	}
}
