#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using vvl = vector<vl>;
using ii = pair<ll,ll>;
using vii = vector<ii>;
using vvii = vector<vii>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e8;
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

int n; 

ll mod(ll a, ll m = MOD){
	ll res = a % m;
	if (res < 0) res += m;
	return res;
}

ll addMod(ll a, ll b, ll m = MOD){
	ll res = mod(a, m) + mod(b, m);
	return mod(res, m);
}

int findIndexFor(ll x, vector<ii> &A){
	auto it = lower_bound(all(A), make_pair(x+1, x+1));
	if (it == A.end()) return n;
	return (int) (it - A.begin());
}

ll dp(int i, vii &A, vl &memo){
	if (i == n) return 1;
	
	if (memo[i] == UNDEFINED){
		memo[i] = dp(i+1, A, memo); // Ignoro al i-th
		int j = findIndexFor(A[i].snd, A);
		memo[i] = addMod(memo[i], dp(j, A, memo)); // Tomo al i-th y me muevo al primero valido
	}
	
	return memo[i];
}

void solve(){	
	vii A(n);
	forn(i, n) cin >> A[i].fst >> A[i].snd;
	forn(i, n) A[i].snd--;
	
	sort(all(A));
	vl memo(n, UNDEFINED);
	ll res = addMod(dp(0, A, memo), -1);
	
	string formatted_res = to_string(res);
	while (SIZE(formatted_res) < 8) formatted_res = "0" + formatted_res;
	cout << formatted_res << "\n";
}

int main()
{
	while (cin >> n){
		if (n == -1) break;
		solve();
	}
	return 0;
}
