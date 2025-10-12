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

const ll COTA_SUP_N = 1000;
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

ll lookForPrime(ll k){
	for (ll p : primes){
		if (k % p != 0) return p;
	}
	
	return 0;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	sieveOfEratosthenes();
	
	forn(_, t){
		ll n, k;
		cin >> n >> k;
		
		vl A(n);
		forn(i, n) cin >> A[i];
		//~ DBG(A); DBG(k);
		
		if (k % 2 == 1){
			forn(i, n){
				if (A[i] % 2 != 0) A[i] += k;
			}
		} else {
			ll p = lookForPrime(k);	
			//~ DBG(p);	
			forn(i, n){
				ll r = A[i] % p;
				forn(j, k){
					if (r == 0) break;
					A[i] += k;
					r = A[i] % p;
				}
			}
		}
		
		forn(i, n) cout << A[i] << " "; 
		cout << "\n";
	}
	
    return 0;
}
