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
ll n;

ll dp1(int i, int j, vector<vl> &memo){
	if (i == -1) return 1;
	
	if (memo[i][j] == UNDEFINED){
		memo[i][j] = 0;
		
		if (j == 0){
			if (i == 1 || i == 2) memo[i][j] = dp1(i-1, j, memo);
			else memo[i][j] = 2ll * dp1(i-1, j, memo);
		} else { 
			if (i == 1 || i == 2){
				if ((1ll << i) & n) memo[i][j] = dp1(i-1, 1, memo);
			} else {
				if ((1ll << i) & n) memo[i][j] = dp1(i-1, 0, memo) + dp1(i-1, 1, memo);
				else memo[i][j] = dp1(i-1, j, memo);
			}
		}
	}
	
	return memo[i][j];
}


int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	// [1, n] i & 2 = 0 o i & 4 = 0
	

	forn(_, t){
		cin >> n;
		
		int index = 0;
		dforn(i, 63){
			if (n & (1ll << i)){
				index = i;
				break;
			}
		}
		
		vector<vl> memo(63, vl(2, UNDEFINED));
		ll complement = 0; // #x tal que x&1 = 1 y x&2 = 1
 		ll res = n;
		if (index == 2) complement = dp1(index-1, 1, memo);
		else if (index > 2) complement = dp1(index-1, 1, memo) + dp1(index-1, 0, memo);
		res -= complement;
		cout << res << "\n";
	}
	
    return 0;
}
