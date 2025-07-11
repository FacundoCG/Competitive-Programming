#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

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

// O(MAX_N log(log(MAX_N)))

const ll COTA_SUP_N = pow(10, 7);
vector<bool> is_prime(COTA_SUP_N+1, true);
vector<ll> primes;

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

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	sieveOfEratosthenes();
	
    int n;
    cin >> n;
    vector<ll> A(n);
    forn(i, n) cin >> A[i];
    
    ll g = 0;
    forn(i, n) g = __gcd(g, A[i]);
    forn(i, n) A[i] = A[i]/g;
    
    vector<ll> repeticiones(COTA_SUP_N+1, 0);
    vector<bool> isInB(COTA_SUP_N+1, false);
    
	set<ll> B;
	
	forn(i, n){
		B.insert(A[i]);
		repeticiones[A[i]]++;
		isInB[A[i]] = true;
	}	
	
	string res = "YES";
	ll maxB = *B.rbegin();
	
	for (ll p : primes){
		if (p > maxB) break;
		
		ll r = 0;
		for (ll j = p; j <= maxB; j += p){
			if (isInB[j]) r += repeticiones[j];
			if (r > 1) {
				res = "NO";
				break;
			}
		}
			
		if (r > 1) {
			res = "NO";
			break;
		}
	}
	
	cout << res << "\n";
}
