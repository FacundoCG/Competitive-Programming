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
using ii = pair<ll,ll>;
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

const ll MAX_N = 200;
ll A[MAX_N+3];

int n;

ll dp(int i, int j_max, int j_min, vvvl &memo){
	if (i == n) return 0;
	
	if (memo[i][j_max][j_min] == UNDEFINED){
		memo[i][j_max][j_min] = 1 + dp(i+1, j_max, j_min, memo);
		if (A[i] > A[j_max]) memo[i][j_max][j_min] = min(memo[i][j_max][j_min], dp(i+1, i, j_min, memo));
		if (A[i] < A[j_min]) memo[i][j_max][j_min] = min(memo[i][j_max][j_min], dp(i+1, j_max, i, memo));
	}
	
	return memo[i][j_max][j_min];
}

void solve(){
	A[n] = 0;
	A[n+1] = 1e7;
	forn(i, n) cin >> A[i];
	
	vvvl memo(n+3, vvl(n+3, vl(n+3, UNDEFINED)));
	ll res = dp(0, n, n+1, memo);
	cout << res << "\n";
}

 
int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
		
	//~ int t = 1; 
	//~ cin >> t;
	//~ forn(_, t) solve();
	
	while (cin >> n) if (n != -1) solve();

	return 0;
}
