#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
const int MAX_N = 1e6 + 1;
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

int fact[MAX_N];

int mulMod(int a, int b, int m = MOD){
	ll resLL = (ll) a*b;
	resLL %= m;
	int res = (int) resLL;
    return res;
}

int binPowMod(int base, int exp, int m = MOD){
    if (exp == 0) return 1;
    
    int a = binPowMod(base, exp/2, m);
    int res = mulMod(a, a, m);
    
    if (exp % 2 == 1) res = mulMod(res, base, m);
    return res;
}
 
int divideMod(int a, int b, int m = MOD){
    int res = mulMod(a % m, binPowMod(b, m-2, m) % m, m) % m;
    return res;
}

void calcularFactorial(int n){
	fact[0] = 1;
	forsn(i, 1, n+1) fact[i] = mulMod(fact[i-1], i, MOD);
}

int combinatorial_func(int n, int k){
	return divideMod(fact[n], mulMod(fact[k], fact[n-k], MOD), MOD);
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n;
	cin >> n;
	
	calcularFactorial(MAX_N-1);
	
	forn(_, n){
		int a, b;
		cin >> a >> b;
		cout << combinatorial_func(a, b) << "\n";
	}
	
    return 0;
}
