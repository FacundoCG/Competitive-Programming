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
ll memo[3000][3010][3];
vi A;
ll powersOfTwo[3001];

ll mod(ll a, ll m = MOD){
	ll res = a % m;
    if (res < 0) res += m;
	return res;
}

ll addMod(ll a, ll b, ll m = MOD){
    ll res = (mod(a, m) + mod(b, m)) % m;
    return res;
}

ll dp(int i, int k, int j){
	if (i < 0) return 0;
	
	if (memo[i][k][j] == UNDEFINED){
		memo[i][k][j] = dp(i-1, k, j); // No agarro el elemento
		
		if (A[i] > k){ // Si A[i] > MAX(red, blue)
			assert(j != 0);
			if (j == 2) memo[i][k][j] = addMod(memo[i][k][j], powersOfTwo[i]); // Ninguna subsecuencia es buena a partir de agarrar A[i]. Luego, res = pow(2, i);
			else if (j == 1) memo[i][k][j] = addMod(memo[i][k][j], dp(i-1, A[i], 2)); // Tengo dos máximos ahoras
		} else { // A[i] <= MAX(red, blue)
			if (j == 0) memo[i][k][j] = addMod(memo[i][k][j], dp(i-1, A[i], 1));
			if (j == 1) memo[i][k][j] = addMod(memo[i][k][j], dp(i-1, k, 2)); // Tengo dos máximos ahora
			if (j == 2) {
				// Si MIN(blue, red) <= A[i] <= MAX(red, blue)
				memo[i][k][j] = addMod(memo[i][k][j], dp(i-1, A[i], j));
				// Si A[i] < MIN(blue, red)
				memo[i][k][j] = addMod(memo[i][k][j], dp(i-1, k, 2)); // Tengo que mantener el máximo
			} 
		}
	}
	
	return memo[i][k][j];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	powersOfTwo[0] = 1;
	forsn(i, 1, 3001) powersOfTwo[i] = (powersOfTwo[i-1]*2) % MOD;
	
	forn(_, t){
		cin >> n;		
		A.resize(n);
		forn(i, n) cin >> A[i];
				
		forn(i, n){
			forn(j, n+10) {
				memo[i][j][0] = UNDEFINED;
				memo[i][j][1] = UNDEFINED;
				memo[i][j][2] = UNDEFINED;
			}
		}
		
		ll totalSubsequences = powersOfTwo[n];
		ll badSubsequences = dp(n-1, n+1, 0);
		DBG(totalSubsequences); DBG(badSubsequences);
		
		ll res = totalSubsequences - badSubsequences;
		cout << res << "\n";
	}
	
    return 0;
}
