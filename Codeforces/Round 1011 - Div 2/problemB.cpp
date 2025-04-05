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

int solve(vector<int> &A){
	vector<int> P;
	vector<pair<int, int>> res;
	
	int n = SIZE(A);
	forn(i, SIZE(A)){
		if (A[i] == 0) P.pb(i);
	}
	
	if (SIZE(P) == 0){
		cout << 1 << "\n";
		cout << 1 << " " << n << "\n";
		return 0;
	}
	
	if (P[0] == 0){
		res.pb({1, 2});
		if (SIZE(P) > 2 || (SIZE(P) == 2 && P[1] != 1)){
			res.pb({2, n-1}); res.pb({1, 2});
		} else {
			res.pb({1, n-1});
		}
	} else if (P[0] == n-1){
		res.pb({n-1, n}); res.pb({1, n-1});
	} else if (P[0] == n-2){
		res.pb({n-1, n});
		
		if (SIZE(P) > 2 || (SIZE(P) == 2 && P[1] != n-1)){
			res.pb({1, n-2}); res.pb({1, 2});
		} else {
			res.pb({1, n-1});
		}
	} else {
		int sizeLost = P[0];
		res.pb({1, P[0]+1});
		if (SIZE(P) == 1){
			res.pb({1, n-sizeLost});
		} else {
			res.pb({2, n-sizeLost}); res.pb({1, 2});
		}		
	}
	
	cout << SIZE(res) << "\n";
	forn(i, SIZE(res)) cout << res[i].fst << " " << res[i].snd << "\n";
	return 0;
}

int main() {
	
	int t;
	cin >> t;
	forn(_, t){
		int n;
		cin >> n;
		vector<int> A(n);
		forn(i, n) cin >> A[i];
		solve(A);
	}

	return 0;
}
