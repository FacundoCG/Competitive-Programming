#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

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
int n;
ll S;

const ll MAX_SUM = 500*(501)/2;
ll memo[501][MAX_SUM+1];

ll addMod(ll a, ll b, ll m){
    ll res = ((a % m) + (b % m)) % m;
    return res;
}
 
ll mulMod(ll a, ll b, ll m){
    ll res = ((a % m) * (b % m)) % m;
    return res;
}
 
ll binPowMod(ll base, ll exp, ll m){
    if (exp == 0) return 1;
    
    ll a = binPowMod(base, exp/2, m);
    ll res = mulMod(a, a, m);
    
    if (exp % 2 == 1) res = mulMod(res, base, m);
    return res;
}
 
ll divideMod(ll a, ll b, ll m){
    ll res = mulMod(a % m, binPowMod(b, m-2, m) % m, m) % m;
    return res;
}

ll dp(int i, int t){
	if (t == S/2) return 1;
	if (i == 0 || t > S/2) return 0;
	
	if (memo[i][t] == UNDEFINED){
		memo[i][t] = dp(i-1, t);
		memo[i][t] = addMod(memo[i][t], dp(i-1, t + i), MOD);
	}
	
	return memo[i][t];
}

// Sea A la cantidad de conjuntos que suman S/2
// Vos queres calcular (A/2) % MOD
// Ahora mismo vos estas calculando: A % MOD / 2 que no es equivalente
// Tenes que hacer : (A % MOD) * (Inverso Multiplicativo de 2 % MOD);

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	cin >> n;
	S = (n+1)*n/2;
	
	if (S % 2 != 0){
		cout << 0 << "\n";
		return 0;
	}
	
	forn(i, n+1){
		forn(j, S+1) memo[i][j] = UNDEFINED;
	}
	
	ll m = dp(n, 0);
	ll res = divideMod(m, 2, MOD);
	
	cout << res << "\n";
}
