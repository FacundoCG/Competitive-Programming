#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

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

int dp(int i, int j, vi &A, vi &B, vector<vi> &memo, vector<vi> &path){
	if (i == -1 || j == -1) return 0;
	
	if (memo[i][j] == UNDEFINED){
		if (A[i] == B[j]) {
			path[i][j] = 2;
			memo[i][j] = 1 + dp(i-1, j-1, A, B, memo, path);
		} else {
			int opt1 = dp(i-1, j, A, B, memo, path);
			int opt2 = dp(i, j-1, A, B, memo, path);
			if (opt1 < opt2){
				memo[i][j] = opt2;
				path[i][j] = 0;
			} else {
				path[i][j] = 1;
				memo[i][j] = opt1;
			}
		}
	}
	
	return memo[i][j];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	vi A(n), B(m);
	forn(i, n) cin >> A[i];
	forn(i, m) cin >> B[i];
	
	vector<vi> memo(n, vi(m, UNDEFINED));
	vector<vi> path(n, vi(m, UNDEFINED));
	int res = dp(n-1, m-1, A, B, memo, path);
	cout << res << "\n";
	
	int i = n-1;
	int j = m-1;
	
	vi lcsPath;
	
	while (i >= 0 && j >= 0){
		if (path[i][j] == 2){
			lcsPath.pb(A[i]);
			i--; j--;
		} else if (path[i][j] == 1){
			i--;
		} else {
			j--;
		}
	}
	
	reverse(all(lcsPath));
	forn(k, SIZE(lcsPath)) cout << lcsPath[k] << " ";
	cout << "\n";
	
    return 0;
}
