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
ll n, m;

// Calcular extremo izquierdo que cumple P(X)
ll leftBinarySearch(ll start, ll end, vector<ll> &A, ll c){
    ll l = start - 1; 
    ll r = end + 1; 

    while(r - l > 1) { 
        ll mid = (l + r) / 2;
        if(!(A[mid] >= c)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (r < start || r > end || !(A[r] >= c)){
		r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return r; // r es el primer elemento que cumple P(X)
}


void solve(vector<ll> &A){
	ll res = 0;
	map<ll,ll> M;
	
	forsn(i, 1, n+1){
		ll j = leftBinarySearch(0, m-1, A, i);
		ll numberOfElements = 0;
		if (j != -1) numberOfElements = m-j;
		M[i] = numberOfElements;
	}
	
	//~ DBG(A);
	
	//~ forsn(i, 1, n+1){
		//~ DBG(i);
		//~ DBG(M[i]);
	//~ }
	
	//~ forsn(a, 1, (n/2) + 1){
		//~ ll b = n-a;
		//~ DBG(a); DBG(b);
		//~ ll toSum = M[a]*M[b] - M[b];
		//~ DBG(toSum);
		
		//~ res += M[a]*M[b] - M[b];
	//~ }
	
	forsn(a, 1, n){
		ll b = n-a;
		ll toSum = M[a]*M[b] - M[max(a,b)];
		//DBG(a); DBG(b); DBG(toSum);
		res += toSum;
	}
	
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	ll t;
	cin >> t;
	forn(_, t){
		cin >> n >> m;
		vector<ll> A(m);
		forn(i, m) cin >> A[i];
		sort(all(A));
		solve(A);
	}
	
	return 0;
}
