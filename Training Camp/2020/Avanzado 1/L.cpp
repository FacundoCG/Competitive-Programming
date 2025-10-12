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

int n;
vector<vl> A;
ll memo[300][300][300];

ll dp(int i, int j, int k){
	int pasosTotales = i+j;
	int bajaste = pasosTotales-k;
	if (i >= n || j >= n || k >= n || bajaste >= n) return 0;
	
	if (memo[i][j][k] == UNDEFINED){
		if (i == bajaste && j == k) memo[i][j][k] = A[i][j];
		else memo[i][j][k] = A[i][j] + A[bajaste][k];
		
		ll res = -LINF;
		if (i+1 < n && bajaste+1 < n) res = dp(i+1, j, k);
		if (i+1 < n && k+1 < n) res = max(res, dp(i+1, j, k+1));
		if (j+1 < n && bajaste+1 < n) res = max(res, dp(i, j+1, k));
		if (j+1 < n && k+1 < n) res = max(res, dp(i, j+1, k+1));
		if (res == -LINF) res = 0;
		memo[i][j][k] += res;
	}
	
	return memo[i][j][k];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> n;
	A.resize(n, vl(n));
	
	forn(i, n){
		forn(j, n) cin >> A[i][j];
	}
	
	forn(i, n){
		forn(j, n){
			forn(k, n) memo[i][j][k] = UNDEFINED;
		}
	}
	
	ll res = dp(0, 0, 0);
	cout << res << "\n";
	
    return 0;
}
