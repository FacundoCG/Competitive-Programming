#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
//const int MAX_N = 1e5 + 1;
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

string s;
ll memo[500][500][501];

ll dp(int i, int j, int k){
	if (i > j && k > 0) return INF;
	if (k <= 0) return 0;
	if (i == j) return dp(i+1, j, k-1);
	
	if (memo[i][j][k] == UNDEFINED){
		if (s[i] == s[j]){
			memo[i][j][k] = dp(i+1, j-1, k-2);
		} else {
			memo[i][j][k] = dp(i+1, j, k);
			memo[i][j][k] = min(memo[i][j][k], dp(i, j-1, k));
			memo[i][j][k] = min(memo[i][j][k], 1 + dp(i+1, j-1, k-2));
		}
	}
	
	return memo[i][j][k];  
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, k;
    cin >> n >> k;
    
    cin >> s;
    
    forn(i, n){
		forn(j, n){
			forn(h, k+1) memo[i][j][h] = UNDEFINED;
		}
	}
    
    ll res = dp(0, n-1, k);
    cout << res << "\n";
}
