#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using ii = pair<int,int>;

template <typename T>
using vv = vector<vector<T>>;

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

int n, k; 
int mod(int a, int m = MOD){ return ((a % m) + m) % m;}

void solve(){
	cin >> n >> k;
	vi G(n); forn(i, n) cin >> G[i];
	
	ll d = gcd(n, k);
	ll sumFirstWindow = 0, elemsOfGroupPerWindow = k/d;
	
	forn(i, d){ // Fijo un grupo
		ll lowerBound = 0, currentValue = 0;
		forn(j, n/d){ // Itero por cada elemento del mismo grupo
			ll index = (i + j*k) % n; 
			if (index < k) sumFirstWindow += currentValue; // Recordemos que cada E[index-k+1] = lowerBound + currentValue, aca sumo el currentValue de los elementos de firstWindow nada mas
			currentValue -= G[index] - G[(index+1) % n]; // Equivalente a hacer currentValue += G[(index) % n] - G[(index+1) % n]. Actualizo el valor para el siguiente index
			lowerBound = max(lowerBound, -currentValue); 
		}
		
		if (currentValue != 0){ cout << "N\n"; return ;}
		sumFirstWindow += elemsOfGroupPerWindow*lowerBound; // Sumo el E[i] de los elementos de la primera ventana
	}
	
	if (sumFirstWindow <= G[0] && (G[0] - sumFirstWindow) % elemsOfGroupPerWindow == 0) cout << "S\n";
	else cout << "N\n";
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
