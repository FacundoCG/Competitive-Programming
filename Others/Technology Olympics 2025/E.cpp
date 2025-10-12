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

const ll COTA_SUP_N = 1e4;
vector<bool> is_prime(COTA_SUP_N+1, true);
vl primes; 
 
void sieveOfEratosthenes(){
	is_prime[0] = false;
	is_prime[1] = false;
	for (ll i = 2; i <= COTA_SUP_N; i++) {
		if (is_prime[i]) {
			primes.pb(i);
			for (ll j = i*i; j <= COTA_SUP_N; j += i)
				is_prime[j] = false;
		}
	}
}

map<ll, vl> factorizacionDe;

vl generateA(vl &A, map<ll, int> &freq, int cota){
	vl res;
	vb noUsar(SIZE(A), false);
	
	forn(i, SIZE(A)){
		for (ll p : factorizacionDe[A[i]]){
			if (freq[p] < cota) noUsar[i] = true;
		}	
	}
	
	forn(i, SIZE(A)) {
		if (!noUsar[i]) res.pb(A[i]);
		else { for (ll p : factorizacionDe[A[i]]) freq[p]--; }
	}
	
	return res;
}

void solve(){
	int n;
	cin >> n;
		
	vl A(n);		
	map<ll, int> freq;
	map<ll, vi> primoAsociado;

	forn(i, n) cin >> A[i]; //~ factorizar(A[i], freq);
	
	ll res = 1;
	
	forn(_, 3){
		A = generateA(A, freq, n-2);
		if (SIZE(A) < n-2){ cout << res << "\n"; return ;}
	}
	
	vl prefixGCD(SIZE(A), 0), suffixGCD(SIZE(A), 0);
	prefixGCD[0] = A[0];
	forsn(i, 1, n) prefixGCD[i] = __gcd(prefixGCD[i-1], A[i]);
	
	suffixGCD[SIZE(A)-1] = A[SIZE(A)-1];
	dforn(i, SIZE(A)-1) suffixGCD[i] = __gcd(suffixGCD[i+1], A[i]);
	
	int eliminaste = n - SIZE(A);
	
	if (eliminaste == 2){
		res = 0;
		for (ll x : A) res = __gcd(res, x);
		cout << res << "\n";
		return ;
	} else if (eliminaste == 1){
		forn(i, SIZE(A)){
			ll leftGCD = 0, rightGCD = 0;
			if (i+1 < SIZE(A)) rightGCD = suffixGCD[i+1];
			if (i-1 >= 0) leftGCD = prefixGCD[i-1];
			res = max(res, __gcd(leftGCD, rightGCD));
		}
		
		cout << res << "\n";
		return ;
	}
	
	
	
	
	
	cout << res << "\n";
	//~ RAYA;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;	
	
	sieveOfEratosthenes();
	//~ DBG(SIZE(primes));
	
	forn(_, t) solve();
	
    return 0;
}
