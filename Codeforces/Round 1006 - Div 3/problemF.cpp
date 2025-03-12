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

ll biggestRowOfZeroesLessThan(ll n){
	ll zeroes = 1;
    ll currentLevel = 3; // Currentlevel is a level of the form: k000...000k with #(0) = zeroes
    
    while (n >= currentLevel + zeroes + 1){ // If I can move to the next level of the form k000...000k
        currentLevel += zeroes + 1;
        zeroes = currentLevel - 2;
    }
    
    return currentLevel; 
}

vector<ll> calculateRow(ll n, ll k){
    vector<ll> res;
    
    if (n == 1){
		res = {k};
		return res;
	} else if (n == 2){
		res = {k, k};
		return res;
	} 
	
    ll i = biggestRowOfZeroesLessThan(n); // It gives you the biggest i such that the row at level i is [k, 0, 0, ..., 0, 0, k] and i <= n
    ll levelToCalculate = n-i+1; // levelToCalculate will be in the interval [0, ..., n/2] because the i found satisfies with n that n is in [i, i + (i-2)+1). Then, the worst case is if n = 2*i - 2. The difference in this case will the biggest possible which is i-2 which would be around n/2
    
	// res is: desiredRow + [0 ... 0] + desiredRow
	vector<ll> desiredRow = calculateRow(levelToCalculate, k);
	ll zeroes = n - 2*SIZE(desiredRow);
		
	forn(j, SIZE(desiredRow)) res.pb(desiredRow[j]); // res = desiredRow
	forn(_, zeroes) res.pb(0); // res = desiredRow + [0 ... 0]
	forn(j, SIZE(desiredRow)) res.pb(desiredRow[j]); // // res = desiredRow + [0 ... 0] + desiredRow
    
    return res;
}

void solve(ll n, ll k){
	vector<ll> row = calculateRow(n, k);
	forn(i, SIZE(row)) cout << row[i] << " ";
	cout << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		ll n, k;
		cin >> n >> k;
		solve(n, k);
	}
}
