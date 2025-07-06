#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;
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

ll addMod(ll a, ll b, ll m = MOD){
    ll res = ((a % m) + (b % m)) % m;
    return res;
}
 
ll mulMod(ll a, ll b, ll m = MOD){
	ll res = (ll) a*b;
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

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	ll n;
	cin >> n;
	
	vector<ll> A;
	map<ll, ll> repeticiones;
	forn(i, n) {
		ll v;
		cin >> v;
		if (repeticiones[v] == 0) A.pb(v);
		repeticiones[v]++;
	}
	
	ll res = repeticiones[A[0]] + 1;
	forsn(i, 1, SIZE(A)) res = mulMod(repeticiones[A[i]] + 1, res, MOD);
	res -= 1;
	
	cout << res << "\n";
	
    return 0;
}
