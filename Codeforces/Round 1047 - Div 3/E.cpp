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

ll n, k;

ll f(vl &A, vl &freq){
	ll res = 0;
	ll mex = 0;
	
	forn(i, n+2){
		if (freq[i] == 0) {mex = i; break;}
	}
	
	forn(i, n){
		if (A[i] >= mex) res += mex;
		else if (freq[A[i]] == 1) res += A[i];
		else res += mex;
	}
		
	return res;
}

ll solve(vl &A, vl &freq, ll x, ll elementsLeft){
	if (elementsLeft == 0) return 0;
	ll res = 0;
	
	if (freq[x] == 0) {
		res = x*elementsLeft;
		if (elementsLeft > 1 && k % 2 == 0) res = (x+1)*elementsLeft;
		// Después de la primera todos los elementsLeft son x
		// Si elementsLeft > 1: entran en el ciclo x -> x+1 -> x
		// Si elementsLeft = 1: mueren en x
	} else if (freq[x] == 1){
		res = x + solve(A, freq, x+1, elementsLeft - 1);
	} else {
		// Los elementsLeft van a irse a >= x+1 después de la primera iteración
		// En la segunda no va a haber ningún x y van a volver
		// Todos se fueron a un número >= x+1 -> x -> x+1
		if ((k-1) % 2 == 1) res = x*elementsLeft;
		else res = (x+1)*elementsLeft;
	}

	return res;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		cin >> n >> k;
		
		vl A(n), B(n+2, 0);
		forn(i, n) {cin >> A[i]; B[A[i]]++;}
		sort(all(A));
		
		ll res = 0;
		if (k == 1) res = f(A, B);
		else res = solve(A, B, 0, n);
		cout << res << "\n";
	}
	
    return 0;
}
