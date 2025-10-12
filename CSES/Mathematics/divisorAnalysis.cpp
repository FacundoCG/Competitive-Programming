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

typedef pair<ll, ll> factor;

ll mod(ll a, ll m = MOD){
	ll res = ((a % m) + m) % m;
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

int n;
vl powersOf2;

ll sumaPotencias(ll p, ll e){
	// p^0 + p^1 + ... + p^e = p^(e+1)-1/p-1
	ll res = binPowMod(p, e+1) - 1;
	res = mod(res);
	res = divideMod(res, mod(p-1));	
	return res;
}

ll sumaDeGauss(ll a, ll b){
	ll res = (ll) b*(b+1)/2; // [1, b]
	res -= (ll) (a-1)*a/2; // [1, a-1]
	return res;
}

ll numberOfDivisors(vector<factor> &A){
	ll res = 1;
	forn(i, SIZE(A)) res = mulMod(res, A[i].snd+1);
	return res;
}

ll sumOfDivisors(vector<factor> &A){
	vl memo(SIZE(A));
	memo[n-1] = sumaPotencias(A[n-1].fst, A[n-1].snd);
	dforn(i, n-1) memo[i] = mulMod(memo[i+1], sumaPotencias(A[i].fst, A[i].snd));
	return memo[0];
}

ll prodOfDivisors(vector<factor> &A){
	vl memo(SIZE(A));
	ll sumExponentes = sumaDeGauss(1, A[n-1].snd);
	memo[n-1] = binPowMod(A[n-1].fst, sumExponentes);
	int j = 1;
	
	dforn(i, n-1) {
		//~ sumExponentes = sumaDeGauss(1, A[i].snd)*2;
		sumExponentes = sumaDeGauss(1, A[i].snd);
		ll prodNext = binPowMod(memo[i+1], sumExponentes);
		ll expPrime = binPowMod(A[i].fst, powersOf2[j]*sumExponentes); // *2
		//~ expPrime = mulMod(expPrime, expPrime);
		//~ memo[i] = mulMod(expPrime, prodNext);
		memo[i] = expPrime*prodNext;
		j++;
	}
	
	DBG(memo);
	
	return memo[0];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> n;
	
	powersOf2.resize(n+1);
	powersOf2[0] = 1;
	forsn(i, 1, n+1) powersOf2[i] = mulMod(powersOf2[i-1], 2);
	
	vector<factor> A(n);
	forn(i, n) cin >> A[i].fst >> A[i].snd;
	
	//~ ll k = (1e9)*(1e9+1)*2;
	//~ DBG(k);
	
	cout << numberOfDivisors(A) << " "; 
	cout << sumOfDivisors(A) << " "; 
	cout << prodOfDivisors(A) << "\n"; 
	
    return 0;
}
