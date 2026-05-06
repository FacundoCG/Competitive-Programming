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
using vvvl = vector<vvl>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvii = vector<vii>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
//~ const int MAX_N = 1e5 + 1;
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

struct DisjointSet{
    vl parent, rnk;
    vb availablePosition;
    
    ll numOfComponents;

    DisjointSet(ll n){
        rnk.assign(n, 0);
        availablePosition.assign(n, false);
        forn(i, n) parent.pb(i);
        numOfComponents = 0;
    }
    
    void markPosition(ll x){
		if (availablePosition[x]) return ;
		availablePosition[x] = true;
		numOfComponents++;
	}

    ll findSet(ll x){
        if(parent[x]!=x) parent[x] = findSet(parent[x]);
        return parent[x];
    }

    void unionSet(ll x, ll y){
		if (!availablePosition[x] || !availablePosition[y]) return ;
		
        x = findSet(x); y = findSet(y);
        if (x != y){
            if (rnk[x] < rnk[y]) parent[x] = y;
            else if (rnk[x] > rnk[y]) parent[y] = x;
            else { parent[y] = x; rnk[x]++;}
            numOfComponents--;
        }
    }

    bool same(ll x, ll y){ return findSet(x) == findSet(y);}
};

vvi A;
int n, m, T;

vii directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool isValidPosition(int row, int col, int x){
	if (row >= n || row < 0 || col >= m || col < 0) return false;
	return A[row][col] > x;
}

int getIndex(int row, int col){ return row*m + col; }

void solve(){
	cin >> n >> m;
	A.assign(n, vi(m));
	forn(i, n) forn(j, m) cin >> A[i][j];
	
	cin >> T;
	vi queries(T+1); forsn(i, 1, T+1) cin >> queries[i];
	
	vvii unlockedAt(T+1);
	forn(i, n) forn(j, m){ // Busca cual es el T[x] mas grande tq A[i][j] > T[i]
		auto it = lower_bound(all(queries), A[i][j]); it--;
		int indexUnlocked = (int) (it - queries.begin());
		unlockedAt[indexUnlocked].pb(make_pair(i, j));
	}
	
	vi res(T+1);
	DisjointSet G(n*m);
	dforn(i, T+1){ // Recorrer las que se desbloquearon en el anio queries[i] y actualizar unfloodedAreas
		int x = queries[i];
		for (pair<int, int> p : unlockedAt[i]) G.markPosition(getIndex(p.fst, p.snd));
		for (pair<int, int> p : unlockedAt[i]) for (pair<int, int> q : directions){
			if (isValidPosition(p.fst+q.fst, p.snd+q.snd, x)) G.unionSet(getIndex(p.fst, p.snd), getIndex(p.fst+q.fst, p.snd+q.snd));
		}
		
		res[i] = (int) G.numOfComponents;
	}
	
	forsn(i, 1, T+1){
		if (queries[i] == queries[i-1]) res[i] = res[i-1];
		cout << res[i] << " "; 
	}
	
	cout << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
		
	int t = 1; 
	cin >> t;
	forn(_, t) solve();
	return 0;
}
