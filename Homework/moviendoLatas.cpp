
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
using vii = vector<ii>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
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

vvl trasponer(vvl A){
	int nOfRows = SIZE(A), nOfCols = SIZE(A[0]);
	vvl res(nOfCols, vl(nOfRows));
	forn(row, nOfRows) forn(col, nOfCols) res[col][row] = A[row][col];
	return res;
}

vvl generatePrefixSum(vvl A){
	int nOfRows = SIZE(A), nOfCols = SIZE(A[0]);
	vvl res(nOfRows, vl(nOfCols));
	forn(row, nOfRows) res[row][0] = A[row][0];
	forn(row, nOfRows) forsn(col, 1, nOfCols) res[row][col] = res[row][col-1] + A[row][col];
	return res;
}

ll query(int l, int r, vl &prefixSum){
	assert(0 <= l && l <= r && r < SIZE(prefixSum));
	if (l == 0) return prefixSum[r];
	return prefixSum[r] - prefixSum[l-1];
}
	
int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	int n; cin >> n;
	
	int n_prime = 3*n+10;
	vvl A(n_prime, vl(n_prime)), M(n_prime, vl(n_prime));
	
	ll sumA = 0, bestTriangle = -LINF;
	int nOfCols = 1;
	forsn(row, n, 2*n){
		forsn(col, n, n+nOfCols) { 
			cin >> A[row][col];
			sumA += A[row][col];
		}
		nOfCols++;
	}
	
	vvl sumFilas = generatePrefixSum(A);
	vvl sumColumnas = generatePrefixSum(trasponer(A));
	
	// Construyo las diagonales en bajada: (i, j) -> (i+1, j-1)
	vvl sumDiagonal(20*n_prime);
	vvi posInDiagonal(n_prime, vi(n_prime));

	forn(row, n_prime) forn(col, n_prime){
		int diagonal = row+col;
		posInDiagonal[row][col] = SIZE(sumDiagonal[diagonal]);
		ll x = (!sumDiagonal[diagonal].empty()) ? A[row][col] + sumDiagonal[diagonal].back() : A[row][col];
		sumDiagonal[diagonal].pb(x);
	}
	
	// Primero defino M[n][n]
	nOfCols = n;
	forsn(row, n, 2*n) {
		forsn(col, n, n+nOfCols) M[n][n] += A[row][col];
		nOfCols--;
	}
		
	// Luego defino M[n][n+1] ... M[n][2*n-1]
	forsn(col, n+1, 2*n){
		M[n][col] = M[n][col-1] - query(n, 2*n-1, sumColumnas[col-1]);
		int diagonal = n+col+n-1;
		int start = posInDiagonal[n][col+n-1];
		M[n][col] += query(start, start+n-1, sumDiagonal[diagonal]);
	}
	
	// Luego  voy a empezar a iterar desde M[n+1][n], hasta M[2*n-1][2*n-1]
	forsn(row, n+1, 2*n) forsn(col, n, 2*n){
		M[row][col] = M[row-1][col] - query(col, col+n-1, sumFilas[row-1]);
		int diagonal = row+col+n-1;
		int start = posInDiagonal[row][col+n-1];
		M[row][col] += query(start, start+n-1, sumDiagonal[diagonal]);
	}
	
	forn(row, n_prime) forn(col, n_prime) bestTriangle = max(bestTriangle, M[row][col]);
	
	assert(sumA-bestTriangle >= 0);
	cout << sumA-bestTriangle << "\n";
	
	return 0;
	
}
