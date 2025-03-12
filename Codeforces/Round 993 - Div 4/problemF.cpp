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
ll sumOf(vector<ll> &C){
	ll res = 0;
	forn(i, SIZE(C)) res += C[i];
	
	return res;
}

ll maximumAbsoluteValueOf(vector<ll> &C){
	ll res = 0;
	forn(i, SIZE(C)){
		res = max(res, abs(C[i]));
	}
	
	return res;
}

void solveQuery (int x, vector<bool> &memo){
	string res = "NO";
	
	if (memo[x]){
		res = "YES";
	} 
	
	cout << res << "\n";
}

void solve(vector<ll> &A, vector<ll> &B, vector<ll> &queries){
	ll sumA = sumOf(A);
	ll sumB = sumOf(B);
	ll maximumX = maximumAbsoluteValueOf(queries);
	
	// Estos son los posibles productos que voy a poder hacer con: (sumA - A[i])*(sumB - B[j])
	// Los divido según si son positivos o negativos y solo me interesa registrar aquellos que son menores o iguales al máximo valor absoluto de la X más grande de las queries
	vector<bool> positiveProducts(maximumX + 1);
	vector<bool> negativeProducts(maximumX + 1);
	
	// Estos son los posibles valores de (sumA - A[i]) y de (sumB - B[j]). Los vuelvo a dividir en positivos y negativos.
	// Además, solo registro a aquellos que son <= al valor absoluto de la máxima X ya que no tiene sentido registrar a factores con mayor valor absoluto que este ya que me quedaría: |(A-A[i])|*|(B-B[i])| > |X| lo cual no me sirve
	vector<bool> positiveFactorsOfA(maximumX + 1);
	vector<bool> negativeFactorsOfA(maximumX + 1);
	vector<bool> positiveFactorsOfB(maximumX + 1);
	vector<bool> negativeFactorsOfB(maximumX + 1);
	
	// Registro los posibles factores de A
	forn(i, SIZE(A)){
		ll currentSum = sumA - A[i];
		ll absoluteValueOfCurrentSum = abs(currentSum);
		if (absoluteValueOfCurrentSum <= maximumX){ 
			if (currentSum >= 0) positiveFactorsOfA[absoluteValueOfCurrentSum] = true;
			else negativeFactorsOfA[absoluteValueOfCurrentSum] = true;
		}
	}
	
	// Registro los posibles factores de B
	forn(i, SIZE(B)){
		ll currentSum = sumB - B[i];
		ll absoluteValueOfCurrentSum = abs(currentSum);
		if (absoluteValueOfCurrentSum <= maximumX){ 
			if (currentSum >= 0) positiveFactorsOfB[absoluteValueOfCurrentSum] = true;
			else negativeFactorsOfB[absoluteValueOfCurrentSum] = true;
		}
	}
	
	// Ahora tengo que registrar los posibles productos de hacer un factor de A*B
	// Acá voy a aprovechar que |A*B| <= |MaximumX|
	forsn(i, 1, maximumX+1){
		forsn(j, 1, maximumX+1){
			ll currentProduct = i*j;
			if (currentProduct > maximumX) break; // Si el producto actual se pasa, entonces no me sirve el j actual
			
			// Registro las 4 posibles combinaciones: i*j, i*(-j), (-i)*j, (-i)*(-j)
			if (positiveFactorsOfA[i] && positiveFactorsOfB[j]) positiveProducts[i*j] = true;
			if (positiveFactorsOfA[i] && negativeFactorsOfB[j]) negativeProducts[i*j] = true;
			if (negativeFactorsOfA[i] && positiveFactorsOfB[j]) negativeProducts[i*j] = true;
			if (negativeFactorsOfA[i] && negativeFactorsOfB[j]) positiveProducts[i*j] = true;
		}
	}
	
	// Proceso las queries
	forn(i, SIZE(queries)){
		int currentX = (int) queries[i];
		
		if (currentX >= 0){
			solveQuery(currentX, positiveProducts);
		} else {
			solveQuery(abs(currentX), negativeProducts);
		}
	}
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
	ll n, m, q;
	cin >> n >> m >> q;
		
	vector<ll> A(n);
	vector<ll> B(m);
	vector<ll> queries(q);
		
	forn(i, n) cin >> A[i];
	forn(i, m) cin >> B[i];
	forn(i, q) cin >> queries[i];
				
	solve(A, B, queries);
}
