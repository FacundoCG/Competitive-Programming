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

const ll COTA_SUP_N = 1e5*4;
int lp[COTA_SUP_N+1];
vi factorizationOf[COTA_SUP_N+1];
vi primes;

void linear_sieve(){
	forsn(i, 1, COTA_SUP_N+1) lp[i] = 0;
	
	forsn(i, 2, COTA_SUP_N+1){
        if (lp[i] == 0){
			lp[i] = i;
            primes.pb(i);
        }

        for(int j = 0; i*primes[j] <= COTA_SUP_N; j++) {
			lp[i*primes[j]] = primes[j];
			if (primes[j] == lp[i]) break;
		}
    }
}

void factorizar(int x){
    set<int> res;
    int oldX = x;
    while (x > 1){
       res.insert(lp[x]);
       x /= lp[x];
    }
    
    for (int p : res) factorizationOf[oldX].pb(p);
}



void solve(){
	int n; cin >> n;
	
	vector<pair<ll, int>> A(n);
	forn(i, n) cin >> A[i].snd;
	forn(i, n) cin >> A[i].fst;
	sort(all(A));
	
	ll res = 0;
	set<int> primesPresent;
	
	forn(i, n){
		for (int p : factorizationOf[A[i].snd]){
			if (esta(p, primesPresent)){ cout << res << "\n"; return ;}
			primesPresent.insert(p);
		}
	}
	
	res = A[0].fst + A[1].fst;
	
	if (SIZE(primesPresent) == 0){
		cout << res << "\n";
		return ;
	}
	
	forn(i, n){
		if (A[i].fst >= res) break;
		if (A[i].fst >= A[1].fst){
			int x = A[i].snd + 1;
			for (int p : factorizationOf[x]){
				if (esta(p, primesPresent)) res = min(res, A[i].fst);
			}
		} else {
			int x = A[i].snd;
			for (int p : factorizationOf[x]) primesPresent.erase(p);
			for (int p : primesPresent){
				int k = x % p;
				ll needed = (ll) p-k;
				res = min(res, needed*A[i].fst);
			}
			
			for (int p : factorizationOf[x]) primesPresent.insert(p);
		}
	}
	
	cout << res << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	linear_sieve();
	factorizationOf[1].clear();
	forsn(i, 2, COTA_SUP_N+1) factorizar(i);
	
	int t;
	cin >> t;
	forn(_, t) solve();
	
    return 0;
}
