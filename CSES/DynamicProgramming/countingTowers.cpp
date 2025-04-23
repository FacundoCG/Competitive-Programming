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

typedef vector<vector<ll>> vector2;
typedef vector<vector2> vector3;
typedef vector<vector3> vector4;

ll addMod(ll a, ll b){
	return ((a % MOD) + (b % MOD)) % MOD;
}

ll dp(int i, int j, int a, int b, vector4 &memo){
	if (i < 0 && a == 0 && b == 0) return 1;
	if (i < 0 ) return 0;
	
	if (memo[i][j][a][b] == UNDEFINED){
		memo[i][j][a][b] = 0;
		
		if (a == 0 && b == 0){
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 0, 0, 0, memo));
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 0, 1, 1, memo));
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 1, 0, 0, memo));
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 1, 1, 0, memo));
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 1, 0, 1, memo));
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 1, 1, 1, memo));	
		} else if (j == 0){
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 0, 0, 0, memo));
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 0, 1, 1, memo));
		} else if (j == 1){
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 1, 0, 0, memo));
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 1, 1, 0, memo));
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 1, 0, 1, memo));
			memo[i][j][a][b] = addMod(memo[i][j][a][b], dp(i-1, 1, 1, 1, memo));	
		}
	}
	
	return memo[i][j][a][b];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	int t;
	cin >> t;
	
	vector4 memo(pow(10, 6), vector3(2, vector2(2, vector<ll>(2, UNDEFINED))));
	
	forn(_, t){
		cin >> n;
		cout << dp(n-1, 0, 0, 0, memo) << "\n";
	}
}
