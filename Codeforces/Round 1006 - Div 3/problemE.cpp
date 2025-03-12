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

ll biggerNSmallerThan(ll k){
	int res = 1;
	forsn(i, 1, 501){
		ll possibleN = i*(i+1)/2;
		if (possibleN <= k){
			res = i;
		}
	}
	
	return res;
}

void generatePointsFor(vector<pair<ll,ll>> &A, ll n, ll keep, ll seed){
	while (n >= 0){
		A.pb({keep, seed});
		seed++;
		n--;
	}
}

void solve(ll k){
	vector<pair<ll,ll>> A;
	ll i = 0;
	ll j = 0;
	
	while (k != 0){
		ll bestN = biggerNSmallerThan(k);
		generatePointsFor(A, bestN, i, j);
		i += bestN+100;
		j += bestN+101;
		k -= bestN*(bestN+1)/2;
	}
	
	if (k == 0){
		A.pb({-1, -1});
	}
	
	cout << SIZE(A) << "\n";
	forn(h, SIZE(A)){
		cout << A[h].first << " " << A[h].second << "\n"; 
	}
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		ll k;
		cin >> k;
		solve(k);
	}
    
}

