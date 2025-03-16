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

ll f(ll i, ll j){
	ll a = (ll) pow(2, i);
	ll b = j/a;
	ll res = a + 2*a*b + j % a; // f(i, j) = 2^i + 2^{i+1} * j/2^i + j % 2^i
	return res;
}

ll leftBinarySearch(ll start, ll end, ll i, ll v){
    ll l = start - 1; 
    ll r = end + 1; 

    while(r - l > 1) { 
        ll mid = (l + r) / 2;
        ll g = f(i, mid);
        if(!(g >= v)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return f(i, r); // r es el primer elemento que cumple P(X)
}


void solve(vector<ll> &A){
	reverse(all(A));
	ll res = f(A[0], 0);
	
	forsn(i, 1, SIZE(A)){
		res = leftBinarySearch(0, 1e18, A[i], res);
	}
	
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	int q;
	cin >> q;
	
	forn(_, q){
		ll n;
		cin >> n;
		vector<ll> A(n);
		forn(i, n){
			cin >> A[i];
			A[i]--;
		}
		sort(all(A));
		solve(A);
	}
	
	
}
