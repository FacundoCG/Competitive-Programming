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

int n, m;

ll solve(vl &C, ll S){
	ll res = S;
	
	forn(i, SIZE(C)-1){ // Cada elemento de A tiene dos opciones: se va a A[n-1] y cumple el requisito || se trae las cosas de A[n-1]
		if (C[i] > S) res += S;
		else res += C[i];
	}
	
	return res;
}

ll sumOf(vl &A){
	ll res = 0;
	forn(i, SIZE(A)) res += A[i];
	return res;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> n >> m;
	ll res = 0;
	vl A(n), B(m);
	forn(i, n) cin >> A[i];
	forn(i, m) cin >> B[i];
	sort(all(A));
	sort(all(B));
	
	ll S1 = sumOf(A), S2 = sumOf(B);
	
	if (B[m-1] < A[n-1]){ // Muevo todo lo de B a A[n-1]
		res = solve(A, S2);
	} else if (A[n-1] < B[m-1]){
		res = solve(B, S1);
	} else if (S1 < S2){
		res = solve(B, S1);
		// Mando todo a B
	} else {
		// Mando todo a A
		res = solve(A, S2);
	}

	cout << res << "\n";
	
    return 0;
}
