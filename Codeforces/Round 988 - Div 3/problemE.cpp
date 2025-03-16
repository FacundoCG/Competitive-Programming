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


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //

void makeQuery(ll i, ll j){
	cout << "? " << i << " " << j << endl;
	cout.flush();
}

int solve(ll n){
    string res = "IMPOSSIBLE";
    ll j = n;
    ll resQuery, lastQuery;
    makeQuery(1, j);
    cin >> resQuery;
    
    if (resQuery == 0){
		cout << "! " << res << endl;
		cout.flush();
		return 0;
	} else if (n == 2 && resQuery != 0){
		res = "01";
		cout << "! " << res << endl;
		cout.flush();
		return 0;
	}
    
    j--;
    lastQuery = resQuery;
    res = "";
    
    while (j > 1 && lastQuery > 0){
		makeQuery(1, j);
		cin >> resQuery;
		
		if (resQuery == lastQuery){ // I had a 0 to the final because it didn't change the value
			res += '0';
		} else {
			res += '1';
		}
		
		if (resQuery == 0){
			ll zerosLeft = lastQuery;
			ll onesLeft = j-zerosLeft;
			forn(_, zerosLeft) res += '0';
			forn(_, onesLeft) res += '1';
			break;
		} else {
			lastQuery = resQuery;
			j--;
		}
	}
	
	if (j <= 1){
		res += '1';
		res += '0';
	}
	
	reverse(all(res));
	cout << "! " << res << endl;
	cout.flush();
	return 0;
}


int main() {
    int t;
    cin >> t;
    
    forn(_,t){
		ll n;
		cin >> n;
		solve(n);
    }
}






