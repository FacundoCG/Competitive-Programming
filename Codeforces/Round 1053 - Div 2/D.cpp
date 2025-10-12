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

ll mod(ll a, ll m = MOD){
	ll res = a % m;
    if (res < 0) res += m;
	return res;
}

ll addMod(ll a, ll b, ll m = MOD){
    ll res = (mod(a, m) + mod(b, m)) % m;
    return res;
}
 
ll mulMod(ll a, ll b, ll m = MOD){
	ll res = (ll) mod(a, m)*mod(b, m);
	res %= m;
    return res;
}
 
ll binPowMod(ll base, ll exp, ll m = MOD){
    if (exp == 0) return 1;
    ll a = binPowMod(base, exp/2, m);
    ll res = mulMod(a, a, m);
    if (exp % 2 == 1) res = mulMod(res, base, m);
    return res;
}
 
ll divideMod(ll a, ll b, ll m = MOD){
    ll res = mulMod(a, binPowMod(b, m-2, m), m) % m;
    return res;
}

const int MAX_N = 2*1e5;
ll fact[MAX_N+1];

ll combinatorial_func(ll n, ll k, ll m = MOD){
	return divideMod(fact[n], mulMod(fact[k], fact[n-k], m), m);
}

int n;

void solve(){
	cin >> n;
	
	vl A(n+1);
	forsn(i, 1, n+1) cin >> A[i];
	
	ll res = 1;
	ll columnsAvailable = 0;
	
	dforsn(i, 1, n+1){
		if (2*i <= n) columnsAvailable += 2; // Dos nuevas columnas libres
		else if (2*i == n+1) columnsAvailable++; // Solo para la fila del medio en el caso que n es impar
		
		if (columnsAvailable < A[i]){ // No hay columnas libres suficientes para esta fila
 			cout << "0\n";
			return ;
		}
		
		res = mulMod(res, combinatorial_func(columnsAvailable, A[i]));
		columnsAvailable -= A[i];		
	}
	
	if (columnsAvailable != 0) res = 0;
	cout << res << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	fact[0] = 1;
	forsn(i, 1, MAX_N+1) fact[i] = mulMod(fact[i-1], i);
	forn(_, t) solve();
	
    return 0;
}
