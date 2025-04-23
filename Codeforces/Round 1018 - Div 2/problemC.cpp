#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
//const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e17;
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

#define forn(i,n) for (int i=0;i<(int)(n);++i)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);++i)
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
ll memo[1000][2];
ll memo1[1000][2];

bool goodRow(vector<vector<ll>> &A, int r1, int r2, int j1, int j2){
	if (r2 < 0) return true;
	
	forn(i, n){
		if (A[r1][i] + j2 == A[r2][i] + j1) return false;
	}
	
	return true;
}

bool goodColumn(vector<vector<ll>> &A, int c1, int c2, int j1, int j2){
	if (c2 < 0) return true;
	
	forn(i, n){
		if (A[i][c2] + j1 == A[i][c1] + j2) return false;
	}
	
	return true;
}

ll dp(int i, int j, vector<vector<ll>> &A, vector<ll> &B){
	if (i == n) return 0;
	
	if (memo[i][j] == UNDEFINED){
		memo[i][j] = LINF;
		
		if (goodColumn(A, i, i-1, j, 0)){
			memo[i][j] = min(memo[i][j], dp(i+1, 0, A, B));
		}
		
		if (goodColumn(A, i, i-1, j, 1)){
			memo[i][j] = min(memo[i][j], B[i] + dp(i+1, 1, A, B));
		}
	}
	
	return memo[i][j];
}

ll dp1(int i, int j, vector<vector<ll>> &A, vector<ll> &B){
	if (i == n) return 0;
	
	if (memo1[i][j] == UNDEFINED){
		memo1[i][j] = LINF;
		
		if (goodRow(A, i, i-1, j, 0)){
			memo1[i][j] = min(memo1[i][j], dp1(i+1, 0, A, B));
		}
		
		if (goodRow(A, i, i-1, j, 1)){
			memo1[i][j] = min(memo1[i][j], B[i] + dp1(i+1, 1, A, B));
		}
	}
	
	return memo1[i][j];
}

int main() { 
	ios :: sync_with_stdio(0);
    cin.tie(0);
	
    int t;
    cin >> t;
    
    forn(_, t){
		cin >> n;
		
		vector<vector<ll>> A(n, vector<ll>(n));
		
		forn(i, n){
			forn(j, n) cin >> A[i][j];
		}
		
		forn(i, n){
			memo[i][0] = UNDEFINED;
			memo[i][1] = UNDEFINED;
			memo1[i][0] = UNDEFINED;
			memo1[i][1] = UNDEFINED;
		}
		
		vector<ll> B(n);
		vector<ll> C(n);
		
		forn(i, n) cin >> B[i];
		forn(i, n) cin >> C[i];
		
		ll res = dp(0, 0, A, C);
		ll res1 = dp1(0, 0, A, B);
		
		if (res < LINF && res1 < LINF){
			res += res1;
		} else {
			res = -1;
		}

		cout << res << "\n";
	}
}
