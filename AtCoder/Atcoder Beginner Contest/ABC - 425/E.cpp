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
const int MOD = 998244353;
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

const int MAX_N = 5000;
ll memo[MAX_N+1][MAX_N+1];

ll mod(ll a, ll m){
	ll res = a % m;
    if (res < 0) res += m;
	return res;
}

ll addMod(ll a, ll b, ll m){
    ll res = (mod(a, m) + mod(b, m)) % m;
    return res;
}
 
ll mulMod(ll a, ll b, ll m){
	ll res = (ll) mod(a, m)*mod(b, m);
	res %= m;
    return res;
}

ll combinatorial_func(ll n, ll k, ll m){
	if (k > n) return 0;
	if (k == 0 || n == k) return 1;	
	if (memo[n][k] == UNDEFINED) memo[n][k] = addMod(combinatorial_func(n-1, k, m), combinatorial_func(n-1, k-1, m), m);
	return memo[n][k];
}

int n, M;

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	forn(i, MAX_N+1) forn(j, MAX_N+1) memo[i][j] = UNDEFINED;
	
	int t;
	cin >> t >> M;
	
	forn(i, t){
		cin >> n;
				
		ll res = 1;
		ll current_length = 0;
		
		forn(_, n){
			ll x;
			cin >> x;
			current_length += x;
			res = mulMod(res, combinatorial_func(current_length, x, M), M);
		}
		
		cout << res << "\n";
	}

    return 0;
}
