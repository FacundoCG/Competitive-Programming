#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
//~ const int MAX_N = 1e5 + 1;
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

const int MAX_MOD = 1000;

vector<int> A;
map<int, int> repes;
vector<vector<vector<int>>> memo;
int m;

int dp(int i, int s, int used){
	//~ DBG(i); DBG(s);
	
	if (s == 0 && used == 1) return 1;
	if (i == -1) return 0;
	
	if (memo[i][s][used] == UNDEFINED){
		memo[i][s][used] = 0;
		forn(j, repes[A[i]]+1) {
			if (j == 0){
				memo[i][s][used] |= dp(i-1, (s + j*A[i]) % m, used);
			} else {
				memo[i][s][used] |= dp(i-1, (s + j*A[i]) % m, 1);
			}
		}
	}
	
	return memo[i][s][used];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n;
	cin >> n >> m;
	
	forn(i, m) repes[i] = 0;
	
	forn(i, n){
		int v;
		cin >> v;
		if (repes[v % m] == 0) A.pb(v % m);
		repes[v % m]++;
	}
	
	memo.resize(SIZE(A), vector<vector<int>>(m, vector<int>(2, UNDEFINED)));
	
	// Tengo que chequear si hay alguna suma de subsecuencias en A tal que % m = 0
	int res = dp(SIZE(A)-1, 0, 0);
	if (res){
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
	
    return 0;
}
