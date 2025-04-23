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
int n;
string s;
vector<int> prefixSum;
int memo[10000][10000];

int addMod(int a, int b, int m){
    int res = ((a % m) + (b % m)) % m;
    return res;
}

int eaten(int start, int end){
	if (start < 0 || end > n || start > end) return 0;
	
	int res = prefixSum[end];
	if (start != 0) res -= prefixSum[start-1];
	return res;
}

int dp(int i, int j){
	if (i > j){
		return 0;
	}
	
	if (memo[i][j] == UNDEFINED){
		memo[i][j] = 0;
		// Chequeo de [0, ..., i-1] y [j+1, ..., n-1] cuantas deer cokies comí (b)
		// m = i + [n-1 - (j+1) + 1] eran las cookies comidas
		// humanCookies = m - b
				
		int cookiesEaten = i + (n-j-1);
		int deerCookiesEaten = eaten(0, i-1) + eaten(j+1, n-1);
		int humanCookiesEaten = cookiesEaten - deerCookiesEaten;
		
		if (s[i] == '0' && humanCookiesEaten + 1 <= deerCookiesEaten){
			if (i == j){
				memo[i][j] = 1;
			} else {
				memo[i][j] = addMod(memo[i][j], dp(i+1, j), MOD);
			}
		}
		
		if (s[j] == '0' && humanCookiesEaten + 1 <= deerCookiesEaten){
			if (i == j){
				memo[i][j] = 1;
			} else {
				memo[i][j] = addMod(memo[i][j], dp(i, j-1), MOD);
			}
		}
		
		if (s[i] == '1'){
			if (i == j){
				memo[i][j] = 1;
			} else {
				memo[i][j] = addMod(memo[i][j], dp(i+1, j), MOD);
			}
		}
		
		if (s[j] == '1'){
			if (i == j){
				memo[i][j] = 1;
			} else {
				memo[i][j] = addMod(memo[i][j], dp(i, j-1), MOD);
			}
		}
	}
	
	return memo[i][j] % MOD;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    cin >> n;
    cin >> s;
    prefixSum.resize(n, 0);
    prefixSum[0] = (s[0] == '1');
    forsn(i, 1, n) prefixSum[i] = prefixSum[i-1] + (s[i] == '1');
    
    forn(i, 10000){
		forn(j, 10000) memo[i][j] = UNDEFINED;
	}
    
    int res = dp(0, n-1);
    if (res != 0) res = addMod(res,1, MOD);
  
    cout << res << "\n";
}
