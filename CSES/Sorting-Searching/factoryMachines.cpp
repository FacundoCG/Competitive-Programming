#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18 + 10;
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

ll n, t;

bool P(vector<ll> &A, ll time){
	ll produced = 0;
	forn(i, n) {
		produced += (ll) time/A[i];
		if (produced >= t) return true;
	}
	
	return false;
}

// Calcular extremo izquierdo que cumple P(X)
ll leftBinarySearch(ll start, ll end, vector<ll> &A){
    ll l = (ll) start - 1; 
    ll r = (ll) end + 1; 

    while(r - l > 1) { 
        ll mid = (ll) (l + r) / 2;
        if(!P(A, mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    return r; // r es el primer elemento que cumple P(X)
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> n >> t;
	
	vector<ll> A(n);
	forn(i, n) cin >> A[i];
	
	ll res = leftBinarySearch(1, LINF, A);
	cout << res << "\n";
	
    return 0;
}
