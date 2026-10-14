
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using vvl = vector<vl>;
using ii = pair<int,int>;
using vii = vector<ii>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
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

const int MAX_N = 1001;
bool adj[MAX_N+1][MAX_N+1];
int memo[MAX_N+1][MAX_N+1][2];

int nextV[MAX_N+1][MAX_N+1][2];
int nextJ[MAX_N+1][MAX_N+1][2];
int inserted[MAX_N+1][MAX_N+1][2];

int n, m;

struct Elem{ 
	int next_v, next_j, next_elem; 
	Elem (int _next_v = -1, int _next_j = -1, int _next_elem = -1)
		: next_v(_next_v), next_j(_next_j), next_elem(_next_elem){}
};

// Me queda por procesar el intervalo: [v % n, (v+1) % n, ..., (v+length-1) % n] 
// Si j = 0, estoy parado en v % n
// Si j = 1, estoy parado en (v+length-1)%n

int dp(int v, int length, int j){
	if (length == 1) return 1;
	
	if (memo[v][length][j] == -1){
		memo[v][length][j] = 0;
		if (j == 0){
			int u1 = (v+1) % n, u2 = (v+length-1) % n;
			vector<Elem> nextMovement;
			if (adj[v][u1]) {
				memo[v][length][j] = memo[v][length][j] | dp(u1, length-1, 0);
				nextMovement.pb(Elem(u1, 0, u1));
			}
			
			if (adj[v][u2]) {
				memo[v][length][j] = memo[v][length][j] | dp(u1, length-1, 1);
				nextMovement.pb(Elem(u1, 1, u2));
			}
			
			for (auto [next_v, next_j, next_elem] : nextMovement) if (dp(next_v, length-1, next_j)) {
				nextV[v][length][j] = next_v;
				nextJ[v][length][j] = next_j;
				inserted[v][length][j] = next_elem;
			}
		} else {
			int u = (v+length-1) % n;
			int u1 = (v+length-2) % n, u2 = v % n; 
			
			vector<Elem> nextMovement;
			if (adj[u][u1]) {
				memo[v][length][j] = memo[v][length][j] | dp(v, length-1, 1);
				nextMovement.pb(Elem(v, 1, u1));
			}
			
			if (adj[u][u2]) {
				memo[v][length][j] = memo[v][length][j] | dp(u2, length-1, 0);
				nextMovement.pb(Elem(u2, 0, u2));
			}
			
			for (auto [next_v, next_j, next_elem] : nextMovement) if (dp(next_v, length-1, next_j)) {
				nextV[v][length][j] = next_v;
				nextJ[v][length][j] = next_j;
				inserted[v][length][j] = next_elem;
			}
		}
	}
	
	return memo[v][length][j];
}
	
int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	memset(adj, false, sizeof(adj));
	memset(memo, -1, sizeof(memo));
		
	cin >> n >> m;
	forn(_, m){
		int v, u; cin >> v >> u;
		v--; u--;
		adj[v][u] = true;
		adj[u][v] = true;
	}
	
	forn(v, n) if (dp(v, n, 0) == 1){
		int currentV = v, currentLength = n, currentJ = 0;
		vi res = { currentV };
		set<int> s = { currentV };
		
		while (currentLength > 1){
			res.pb(inserted[currentV][currentLength][currentJ]);
			s.insert(inserted[currentV][currentLength][currentJ]);
			int oldV = currentV, oldJ = currentJ;
			currentV = nextV[oldV][currentLength][oldJ];
			currentJ = nextJ[oldV][currentLength][oldJ];
			currentLength--;			
		}
		
		assert(SIZE(s) == n);
		for (int x : res) cout << x+1 << "\n";
		
		return 0;
	}
	
	cout << "-1\n";
	return 0;
	
}
