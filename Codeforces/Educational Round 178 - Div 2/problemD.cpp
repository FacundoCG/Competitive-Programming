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

vector<ll> primes;
const ll COTA_SUP_N = 11000000;
vector<bool> is_prime(COTA_SUP_N+1, true);
 
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

bool P(int m, vector<ll> &A){	
	int a = SIZE(A)-m;
	if (a <= 1) return true;
	vector<ll> B(a);
	int i = SIZE(A)-1;
	dforn(j, a){
		B[j] = A[i];
		i--;
	}
	
	ll coins = 0;
	
	forn(j, a){
		coins += B[j] - primes[j];
	}
	
	return coins >= 0;
}

// Calcular extremo izquierdo que cumple P(X)
int leftBinarySearch(int start, int end, vector<ll> &A){
    int l = start - 1; 
    int r = end + 1; 

    while(r - l > 1) { 
        int mid = (l + r) / 2;
        if(!P(mid, A)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (r < start || r > end || !P(r, A)){
		r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return r; // r es el primer elemento que cumple P(X)
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    sieveOfEratosthenes();
    
    forn(_, t){
		int n;
		cin >> n;
		
		vector<ll> A(n);
		forn(i, n) cin >> A[i];
		sort(all(A));
		
		ll res = leftBinarySearch(0, n, A);
		cout << res << "\n";
	}
}
