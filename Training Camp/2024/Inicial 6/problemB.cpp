#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 998244353;
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

ll dp(ll i, vector<ll> &A, vector<ll> &memo, ll c, vector<ll> &minimum){
	if (i == -1) return 0; 
	
	if (memo[i] == UNDEFINED){
		memo[i] = dp(i-1, A, memo, c, minimum);
		
		if (i - c >= -1){
			memo[i] = max(memo[i], dp(i-c, A, memo, c, minimum) + minimum[i]);
		}
	}
	
	return memo[i];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    ll n, c;
    cin >> n >> c;
    
    vector<ll> A(n);
    forn(i, n) cin >> A[i];
	
	ll totalSum = 0;
    forn(i, n) totalSum += A[i];
	
	if (c > n){
		cout << totalSum << "\n";
		return 0;
	}
	
    vector<ll> memo(n, UNDEFINED);
    multiset<ll> s;
    vector<ll> minimum(n);
    
    forn(i, c) s.insert(A[i]);
    minimum[c-1] = *s.begin(); 
    
    forsn(i, c, n){
		auto it = s.find(A[i-c]);
		s.erase(it);
		s.insert(A[i]);
		minimum[i] = *s.begin();
	}
	    
    ll optimization = dp(n-1, A, memo, c, minimum);
	//DBG(optimization);
    
    ll res = totalSum - optimization;
    cout << res << "\n";
}
