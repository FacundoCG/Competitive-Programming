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

const ll NEG_VAL = (ll) pow(10, 13)*(-1);
ll n, k;

ll dp(int i, vector<ll> &A, vector<ll> &memo){
	if (i == -1) return 0;
	
	if (memo[i] == UNDEFINED){
		memo[i] = max(A[i], A[i] + dp(i-1, A, memo));
	}
	
	return memo[i];
}

void solve(vector<ll> &A, string &s){
	int j = 0;
	
	forn(i, n){
		if (s[i] == '0') j = i;
	}
		
	vector<ll> suffixSum(n), prefixSum(n);
	prefixSum[0] = A[0];	
	suffixSum[n-1] = A[n-1];
	forsn(i, 1, n) prefixSum[i] = (ll) prefixSum[i-1] + A[i];	
	dforn(i, n-1) suffixSum[i] = (ll) suffixSum[i+1] + A[i];	
	
	ll MAX_RIGHT = NEG_VAL;
	ll MAX_LEFT = NEG_VAL;
	forsn(h, j+1, n) MAX_RIGHT = max(MAX_RIGHT, prefixSum[h] - prefixSum[j]);
	forn(h, j) MAX_LEFT = max(MAX_LEFT, suffixSum[h] - suffixSum[j]);
			
	ll maximum = max(MAX_LEFT, MAX_RIGHT);
	if (MAX_RIGHT <= 0 && MAX_LEFT <= 0){
	   A[j] = k;
	} else if (MAX_RIGHT >= 0 && MAX_LEFT >= 0){
	    A[j] = k - MAX_RIGHT - MAX_LEFT;
	} else {
	    A[j] = k - max(MAX_RIGHT, MAX_LEFT);
	}
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_ ,t){
		cin >> n >> k;
		
		string s;
		cin >> s;
		vector<ll> A(n);
		bool elementsToChange = false;
		forn(i, n) {
			cin >> A[i];
			if (s[i] == '0') {
				A[i] = NEG_VAL; 
				elementsToChange = true;
			}
		}
		
		vector<ll> memo(n, UNDEFINED);
		dp((int) n-1, A, memo);
		ll res = 0;
		forn(i, n) res = max(res, memo[i]);
		
		if (res > k || (res != k && !elementsToChange)){
			cout << "No\n";
		} else {
			cout << "Yes\n";
			if (res != k && elementsToChange) solve(A, s);
			forn(i, n) cout << A[i] << " ";
			cout << "\n";
		}
	}
}
