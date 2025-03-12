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

ll mulMod(ll a, ll b, ll m){
	ll res = ((a % m) * (b % m)) % m;
	return res; 
}

ll binPowMod(ll base, ll firstExp, ll secondExp, ll m){
	if (secondExp == 0) return base;
	if (firstExp == 0 && secondExp != 0) return 1;
	
	ll res = 1;
	
	if (secondExp > 1){
		ll a = binPowMod(base, firstExp, secondExp/2, m);
		res = binPowMod(a, firstExp, secondExp/2, m);
		if (secondExp % 2 == 1) res = binPowMod(res, firstExp, 1, m);
		return res;
	} else if (firstExp > 0){
		ll a = binPowMod(base, firstExp/2, secondExp, m);
		res = mulMod(a, a, m);
		if (firstExp % 2 == 1) res = mulMod(res, base, m);
		return res;
	}
	
	return res;
}

void solve(ll a, ll b, ll c){
	ll res = binPowMod(a, b, c, MOD);
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
        
    forn(_, t){
		ll a, b, c;
		cin >> a >> b >> c;
		solve(a, b, c);
	}
}
