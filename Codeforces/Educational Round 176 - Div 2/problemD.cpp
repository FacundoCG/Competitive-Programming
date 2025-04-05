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
#define forsn(i,s,n) for (ll i=(s);i<(ll)(n);i++)
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

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	vector<vector<ll>> M(60, vector<ll>(60, INF));
	M[0][0] = 0; // The cost to have both sums = 0 is zero
	
	forsn(x, 1, 60){
		dforn(i, 60){
			dforn(j, 60){
				if (M[i][j] == INF) continue; // If I can't have firstGroupSum = i and secondGroupSum = j using the powers [1, ..., x] I can't do anything
				//ll t = pow(2, x); // If I am at a valid configuration (both sums are reachable), I try adding the power x to each group and update the result
				//~ if (i + x < 60) M[i+x][j] = min(M[i+x][j], M[i][j] + t); 
				//~ if (j + x < 60) M[i][j+x] = min(M[i][j+x], M[i][j] + t);
				if (i + x < 60) M[i+x][j] = min(M[i+x][j], M[i][j] + (1LL << x)); 
				if (j + x < 60) M[i][j+x] = min(M[i][j+x], M[i][j] + (1LL << x));
			}
		}
	}
	
	ll t;
	cin >> t;
	forn(_, t){
		ll x, y;
		cin >> x >> y;
		
		ll res = LINF;
		
		forn(i, 60){
			forn(j, 60){
				// I divide x by 2^i and y by 2^j
				if ((x >> i) == (y >> j)) res = min(res, M[i][j]);
			}
		}
		
		cout << res << "\n";
	}
	
	return 0;
}
