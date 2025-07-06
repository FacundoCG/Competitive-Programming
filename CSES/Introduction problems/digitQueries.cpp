#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

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

ll memo[18], A[18];

void solveQuery(ll k){
	ll j, index;
	
	forsn(i, 1, 18){
		if (memo[i] >= k){
			j = i-1;
			break;
		}
	}
	
	ll start = A[j] + 1;
	start += (k - memo[j] - 1)/(j+1);
	index = (k - memo[j] - 1)%(j+1);
	
	string res = to_string(start);
	cout << res[index] << "\n";
}

// k = 10, 1
// k = 11, 0
// k = 12, 1
// k = 13, 1
// 14, 1
// 15, 2
// 16, 1
// 17, 3
// 18, 1
// 19, 4
// 20, 1

// Si i = 1, memo[i] = 9
// if (k - memo[i] == 0) res = suma[i] // 9 + 99

// Si k > 9, busco el mayor i tal que memo[i] <= k
// numeroDeInicio = 9 + 90 + 900;
// meMuevoDesdeNumeroDeInicio = (k - memo[i])/digitosActual;
// numero = numeroInicio + meMuevoDesdeNumeroDeInicio
// index = (k - memo[i]) % cantidadDigitos;
// res = numero[index];

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int q;
	cin >> q;
	
	A[0] = 0, memo[0] = 0;
	forsn(i, 1, 18){
		ll a = (ll) pow(10, i-1);
		A[i] = A[i-1] + 9*a;
		memo[i] = memo[i-1] + 9*i*a;
	}
	
	forn(_, q){
		ll k;
		cin >> k;
		solveQuery(k);
	}
	
    return 0;
}
