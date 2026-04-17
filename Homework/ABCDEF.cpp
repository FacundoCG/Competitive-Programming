#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using vvl = vector<vl>;
using ii = pair<int,int>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
//~ const int MAX_N = 1e5 + 1;
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

const int MAX_SUM = 60000;
const int MAX_N = 100;

ll A[MAX_N+1];

void solve(){
	ll n; cin >> n;
	forn(i, n) cin >> A[i];
	map<ll, ll> freq;
	
	forn(i1, n) forn(i2, n) forn(i3, n){
		ll e = A[i1], f = A[i2], d = A[i3];
		if (d == 0) continue;
		
		ll sum = (e+f)*d;
		freq[sum]++;
	}
	
	ll res = 0;
	
	forn(i1, n) forn(i2, n) forn(i3, n){
		ll a = A[i1], b = A[i2], c = A[i3];
		ll sum = a*b+c;
		
		//if (abs(sum) > MAX_SUM) continue;
		if (esta(sum, freq)) res += freq[sum];
	}
	
	cout << res << "\n";
}

 
int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t = 1; 
	//~ cin >> t;
	forn(_, t) solve();
	return 0;
}

