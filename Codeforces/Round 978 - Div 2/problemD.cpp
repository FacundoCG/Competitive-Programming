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

void makeQuery(ll i, ll j){
	cout << "? " << i << " " << j << endl;
	cout.flush();
}

ll determineImpostor(ll c1, ll c2, bool case1){
	ll k = 1;
	if (c1 == k) k = 3;
	ll res = 0;
	ll resQuery1, resQuery2;
	makeQuery(k, c1);
	cin >> resQuery1;
	makeQuery(k, c2);
	cin >> resQuery2;
	
	if (case1){
		if (resQuery1 == resQuery2) res = c2;
		else res = c1;	
	} else {
		if (resQuery1 == resQuery2) res = c1;
		else res = c2;
	}
	
	return res;
}

void solve(ll n){
	ll res;
	ll i = 1;
	ll resQuery1, resQuery2;
	ll c1 = UNDEFINED;
	ll c2 = UNDEFINED;
	bool case1 = true;
	
	while (i <= n-1 && c1 == UNDEFINED){ // I allways pick the pair (i, i+1)
		makeQuery(i, i+1);
		cin >> resQuery1;
		makeQuery(i+1, i);
		cin >> resQuery2;
		
		if (resQuery1 == 1 && resQuery2 == 0){
			// This case is: (i is knight and j is impostor) or (i is impostor and j is knave)
			c1 = i;
			c2 = i+1;
		} else if (resQuery1 == 0 && resQuery2 == 1) {
			// This case is: (i is knave and j is impostor) or (i is impostor and j is knight)
			c1 = i;
			c2 = i+1;
			case1 = false;
		}
		
		i += 2;
	}
	
	if (c1 == UNDEFINED){
		res = n;
	} else { // Given the candidates c1 and c2 I determine who is the impostor between them
		res = determineImpostor(c1, c2, case1);
	}
	
	cout << "! " << res << endl;
	cout.flush();
}

int main() {
    int t;
    cin >> t;
    
    forn(_, t){
		ll n;
		cin >> n;
		solve(n);
	}
}
