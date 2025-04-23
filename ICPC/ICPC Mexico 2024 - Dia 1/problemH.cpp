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

ll memo[100000][101][2];
int A[100000];

// The biggest consecutive sum which finish at element i, have j times to change the sign and the current sign of elements is k
ll dp(int i, int j, int k){
	if (i < 0) return 0;
	
	if (memo[i][j][k] == UNDEFINED){
		// Si k = 0, entonces voy a sumar A[i]
		// Si k = 1, entonces voy a sumar -A[i]
		ll toSum = (ll) A[i];
		if (k == 1) toSum *= -1;
		memo[i][j][k] = toSum; // Si el intervalo solo es [A[i]]
		
		// Si k = 1, quiere decir que vengo de un cambio de signo. Tengo dos opciones: lo mantengo o lo termino
		if (k == 1) {
			memo[i][j][k] = max(memo[i][j][k], toSum + dp(i-1, j, 1));
			memo[i][j][k] = max(memo[i][j][k], toSum + dp(i-1, j, 0));
		} else {
			memo[i][j][k] = max(memo[i][j][k], toSum + dp(i-1, j, 0));
			// Si j > 0, puedo cambiar el signo
			if (j > 0) memo[i][j][k] = max(memo[i][j][k], toSum + dp(i-1, j-1, 1));
		}
	}
	
	return memo[i][j][k];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, k;
    cin >> n >> k;
    
    //vector<int> A(n);
    forn(i, n) cin >> A[i];
    forn(i, n){
		forn(j, k+1){
			memo[i][j][0] = UNDEFINED;
			memo[i][j][1] = UNDEFINED;
		}
	}
    
    //vector<vector<vector<ll>>> memo(n, vector<vector<ll>>(k+1, vector<ll>(2, UNDEFINED)));
    
    
    dp(n-1, k, 0); // Don't Change the sign to the last element
    dp(n-1, k-1, 1); // Change the sign to the last element
    
    ll res = 0;
    
    forn(i, n){
		res = max(res, memo[i][k][0]);
		res = max(res, memo[i][k-1][1]);
	}
    
    cout << res << "\n";
}
