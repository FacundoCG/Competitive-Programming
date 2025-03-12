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
void concatenateTimes(char c, int times, string &s){
	forn(i, times) s += c;
}

int solve(int n, int m, int k){
	string res = "";
	
	if (k > n && k > m){
		cout << -1 << "\n";
		return 0;
	}
	
	if ((n != k && m == 0) || (m != k && n == 0)){
		cout << -1 << "\n";
		return 0;
	}
	
	bool lastOne;
	bool firstOne;
	
	if (n > m){
		concatenateTimes('0', k, res);
		lastOne = false;
		firstOne = false;
		n -= k;
	} else {
		lastOne = true;
		firstOne = true;
		concatenateTimes('1', k, res);
		m -= k;
	}
	
	
	while (n > 0 && m > 0){
		if (lastOne){
			res += '0';
			lastOne = false;
			n--;
		} else {
			res += '1';
			lastOne = true;
			m--;
		}
	}
	
	if (n > 0){
		if (n > k || (!firstOne && n > 1)){
			cout << -1 << "\n";
			return 0;
		} else {
			concatenateTimes('0', n, res);
		}
	} else if (m > 0){
		if (m > k || (firstOne && m > 1)){
			cout << -1 << "\n";
			return 0;
		} else {
			concatenateTimes('1', m, res);
		}
	}
	
	cout << res << "\n";
	return 0;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		int n, m, k;
		cin >> n >> m >> k;
		solve(n, m, k);
	}
}
