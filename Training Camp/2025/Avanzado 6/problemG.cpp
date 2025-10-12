#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

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
#define forsn(i,s,n) for (ll i=(s);i<(ll)(n);i++)
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

const ll COTA_SUP_N = 1e5;
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

vector<pair<ll, int>> factorizar_primos(ll a){
    vector<pair<ll, int>> factorizacion_primos;
    
    for (ll p : primes){
		int potencia = 0;
		
		if (a == 1) break;
		
		while (a % p == 0){
			a /= p;
			potencia++;
		}
		
		if (potencia > 0) factorizacion_primos.pb({p, potencia});
	}
    
    // a = p1*p2 p1, p2 > 1e6
    
    if (a != 1) factorizacion_primos.pb({a, 1}); // Si no es 1 después de haberlo dividido por los primos de hasta 10^6, entonces es un primo > 10^6 de potencia 1
    return factorizacion_primos;;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	sieveOfEratosthenes();
	
	forn(_, t){
		ll n;
		cin >> n;
		
		if (n == 1){
			cout << 1 << "\n";
			continue;
		}
		
		// p <= q, p*q | n, r = p/q
		
		vector<pair<ll, int>> factorizacion_primos = factorizar_primos(n);
		ll paresNumeros = 1;
		ll badNumeros = 1;
		
		// sea n = p1^{a1} * p2^{a2} * ... * pk^{ak}
		// Está claro que p,q tq p|n y q|n van a ser de la forma: p = p1^{b_1} * p2^{b_2} * ... * pk^{b_k} y q = p1^{c_1} * p2^{c_2} * ... * pk^{c_k} con b_i, c_i <= a_i para todo i
		// Y p/q también va a cumplir con ser de la forma: p1^{d_1} * p2^{d_2} * ... * pk^{d_k} -a_i <= d_i <= a_i 
		// p/q, q/p que si p != q 

		forn(i, SIZE(factorizacion_primos)){
			ll x = 2*factorizacion_primos[i].snd + 1;
			paresNumeros *= x;
			//~ badNumeros *= factorizacion_primos[i].snd/2 + 1; // potencia = 3, p^0, p^1, ..., p^potencia -> p^0, ..., p^{potencia/2}
		}
		
		paresNumeros -= badNumeros;
		paresNumeros /= 2;
		
		ll res = badNumeros + paresNumeros;
		cout << res << "\n";
	}
		
    return 0;
}
