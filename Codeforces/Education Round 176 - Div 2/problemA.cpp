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
#define forsn(i,s,n) for (ll i=(s);i<(ll)(n);i++)
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
ll calculateMinOperations(ll m, ll a, ll b, ll n, int c, int d){
	ll res = 0;
	ll k = a;
	ll j = 0;
	
	DBG(n);
	DBG(k);
	
	while (n > k && j < 1000){
		DBG(m);
		ll x = m/2;
		ll y = m/2;
		
		if (m % 2 != 0){
			x += c; y += d;
		} 
		
		ll newN = n - (x*a + b*y);
		if (newN <= k) {
			n = newN;
			DBG(x);
			DBG(y);
			res = x + y;
		}
		m++;
		j++;
	}
	
	DBG(res);
	
	return res;
}

int solve(ll n, ll k){
	ll res = 0;
	
	if (n == k){
		cout << 1 << "\n";
		return 0;
	}
	
	if (n % 2 != 0){
		n -= k;
		res++;
	}
	
	if (n > k){
		ll diff = (n-k)/(k-1);
		if ((n-k) % (k-1) != 0) diff++;
		res += diff;
	}

	res += 1; // Because n <= k, so I choose x as n and then I have 0
	cout << res << "\n";
	return 0;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	ll t;
	cin >> t;
	forn(_, t){
		ll k, n;
		cin >> n >> k;
		solve(n, k);
	}
	
	return 0;
}
