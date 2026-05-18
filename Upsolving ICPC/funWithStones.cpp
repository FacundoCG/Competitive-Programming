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
using vvvvl = vector<vvvl>;
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

ll mod(ll a, ll m = MOD){
	ll res = a % m;
	if (res < 0) res += m;
	return res;
}

ll addMod(ll a, ll b, ll m = MOD){
	ll res = mod(a, m) + mod(b, m);
	return mod(res, m);
}

ll mulMod(ll a, ll b, ll m = MOD){
	ll res = mod(a, m)*mod(b, m);
	return mod(res, m);
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

vl L, R;

int f(ll l, ll r, int j, int bit, int decision){
	int res = 0;
	ll x = (1ll << bit);
	
	if (j & 1){ // Si soy = l
		if (l & x){
			if (decision == 0) return -1;
			else res = res | 1;
		} else if (decision == 0) res = res | 1;
		// Si lo tiene prendido l a bit y yo no lo prendi, return -1 porque seria <
		// Si lo tiene prendido l a bit y yo lo prendi, res = res | 1 ya que seguimos siendo iguales
		// Si no lo tiene prendido y no lo prendi, res = res | 1 ya que seguimos siendo iguales
		// Si no lo tiene prendido y lo prendi, res = res | 0 ya que ahora soy >
	}
	
	if (j & 2){ // Si soy = r
		if (r & x){
			if (decision == 1) res = res | 2;
		} else {
			if (decision == 0) res = res | 2;
			else return -1;
		}
		// Si lo tiene prendido r a bit y yo no lo prendi, res = res | 0 ya que ahora son < r
		// Si lo tiene prendido r a bit y yo lo prendi, res = res | 2 ya que seguimos siendo iguales
		// Si no lo tiene prendido y no lo prendi, res = res | 2 ya que seguimos siendo iguales
		// Si no lo tiene prendido y lo prendi, return -1 ya que ahora soy >
	}
	
	return res;
}

ll dp(int i, int j1, int j2, int j3, vvvvl &memo){
	if (i == -1) return 1;
	
	if (memo[i][j1][j2][j3] == UNDEFINED){
		memo[i][j1][j2][j3] = 0;
		vi J = {j1, j2, j3};
		
		forn(k1, 2) forn(k2, 2) forn(k3, 2) if ((k1^k2^k3) == 0){
			vi newJ(3);
			vi K = {k1, k2, k3};
			
			bool p = true;
			forn(j, SIZE(newJ)) newJ[j] = f(L[j], R[j], J[j], i, K[j]), p = p && (newJ[j] != -1);
			if (p) memo[i][j1][j2][j3] = addMod(memo[i][j1][j2][j3], dp(i-1, newJ[0], newJ[1], newJ[2], memo));
		}
	}
	
	return memo[i][j1][j2][j3];
}

void solve(){
	ll L_1, R_1, L_2, R_2, L_3, R_3; 
	cin >> L_1 >> R_1 >> L_2 >> R_2 >> L_3 >> R_3;
	
	L = {L_1, L_2, L_3};
	R = {R_1, R_2, R_3};
	
	vvvvl memo(31, vvvl(4, vvl(4, vl(4, UNDEFINED))));
	ll numberOfTriplesWithZeroXor = dp(30, 3, 3, 3, memo);
	ll numberOfTotalTriples = mulMod(R_1 - L_1+1ll, mulMod(R_2-L_2+1ll, R_3-L_3+1ll));
	
	ll num = addMod(numberOfTotalTriples, -numberOfTriplesWithZeroXor);
	cout << divideMod(num, numberOfTotalTriples) << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t = 1;
	//~ cin >> t;
	forn(_, t) solve();
	
    return 0;
}
