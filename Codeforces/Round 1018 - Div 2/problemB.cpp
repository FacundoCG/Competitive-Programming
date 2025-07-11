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

ll solve(vector<ll> &A, int k, ll toSum){
	ll res = toSum;
	sort(all(A));
	DBG(A);
	dforn(i, SIZE(A)){
		if (k == 0) break;
		res += A[i];
		DBG(res);
		k--;
	}
	
	return res;
}

int main() { 
	ios :: sync_with_stdio(0);
    cin.tie(0);
	
    int t;
    cin >> t;
    
    forn(_, t){
		int n, k;
		cin >> n >> k;
		
		vector<ll> L(n), R(n);
		vector<ll> A;
		ll res = 0;
		
		forn(i, n) cin >> L[i];
		forn(i, n) cin >> R[i];
		forn(i, n){
			res += max(L[i], R[i]);
			if (L[i] > R[i]){
				A.pb(R[i]);
			} else {
				A.pb(L[i]);
			}
		}
		
		sort(all(A));
		
		dforn(i, SIZE(A)){
			if (k == 1){
				res += 1;
				break;
			}
			
			res += A[i];
			k--;
		}
		
		
		cout << res << "\n";
	}
}
