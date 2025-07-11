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
ll memo[5000][5000];
ll prefixSum[5001];
ll A[5000];

ll sumRange(int i, int j){
	if (i > j) return 0;
	ll res = prefixSum[j+1] - prefixSum[i];
	return res;
}

ll dp(int i, int j){
	if (i > j) return 0;
	
	if (memo[i][j] == LINF){
		ll option1 = A[i] + sumRange(i+1, j) - dp(i+1, j);
		ll option2 = A[j] + sumRange(i, j-1) - dp(i, j-1);
		memo[i][j] = max(option1, option2);
	}
	
	return memo[i][j];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	cin >> n;
	forn(i, n) cin >> A[i];
	prefixSum[0] = 0;
	
	forn(i, n){
		if (i > 0) prefixSum[i] = prefixSum[i-1] + A[i-1];
		forn(j, n) memo[i][j] = LINF;
	}
	
	prefixSum[n] = prefixSum[n-1] + A[n-1];
	cout << dp(0, n-1) << "\n";
}
