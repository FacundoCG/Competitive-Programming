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

void update(bitset<64> &dx, int i){
	while (dx[i] != 0){
		dx[i] = 0; i++;
	}
	
	dx[i] = 1;
}

void solve(ll x, ll y){
	// Let's be: a = x + k and b = y + k
 	// We want to have: a + b = a XOR b
	// We will start with a = k and b = k. If we need it, we will sum 2^i to a or b
	
	bitset<64> da(x);
	bitset<64> db(y);
	bitset<64> dk(0);
	forn(i, 50){
		if (da[i] == 1 && db[i] == 1) { // We can't have a[i] = 1 and b[i] = 1 to satisfy the equality. So, I sum 2^i to a and b in order to avoid this case
			dk[i] = 1; update(da, i+1); update(db, i+1);
		} else if (da[i] == 1 && db[i] == 0){			
			if (da[i+1] == 0 && db[i+1] == 0){ // I will sum 2^i to a in order to have a better case for the future since da[i] = 0 and db[i] = 0 doesn't allow me to add anything
				dk[i] = 1; da[i+1] = 1;
			} else if (da[i+1] == 1 && db[i+1] == 1){ // This is a bad case, so I avoid it
				dk[i] = 1; update(da, i+1);
			}
		} else if (da[i] == 0 && db[i] == 1){
			if (da[i+1] == 0 && db[i+1] == 0){
				dk[i] = 1; db[i+1] = 1;
			} else if (da[i+1] == 1 && db[i+1] == 1){
				dk[i] = 1; update(db, i+1);
			}
		}
	}
	
	ll k = dk.to_ullong();
	ll c = (x+k) + (y+k);
	ll d = (x+k) ^ (y+k);
	
	if (c == d){
		cout << k << "\n";
	} else {
		cout << -1 << "\n";
	}
}

int main() {
	
	int t;
	cin >> t;
	forn(_, t){
		ll x, y;
		cin >> x >> y;
		solve(x, y);
	}

	return 0;
}
