#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const ll INF = 1e16;
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


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //

int rightBinarySearch(int start, int end, vector<ll> &A, ll value){
    int l = start - 1;
    int r = end + 1;

    while (r - l > 1){
        int mid = (l + r)/2;

        if (A[mid] <= value){
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (l > end || l < start || A[l] > value) l = UNDEFINED;

    return l; // l es el ultimo elemento que cumple P(X)
}

ll dp(int i, int k, vector<vector<ll>> &memo, vector<ll> &prefixSum, vector<ll> &B){
	int n = SIZE(prefixSum) - 1; 
	int m = SIZE(B) - 1;
	
	if (i == n+1 && k <= m){ // Si terminé de hacer a A vacío y el k usado es <= m, entonces hice una secuencia válida
		return 0;
	}
	
	if (k > m){ // Si k > m, quiere decir que estoy ante una secuencia inválida
		return INF;
	}
	
	// Acá ya estoy con un i < n y un j <= m
	if (memo[i][k] == UNDEFINED){
		memo[i][k] = 0; // Defino el costo para hacer vacío el sufijo [A[i], ..., A[n]] usando como B al array [B[j], ..., B[m]]
		
		ll eliminatedAlready = 0; // El valor de la suma del prefijo que eliminé de momento
		if (i > 0) eliminatedAlready = prefixSum[i-1]; // Yo eliminé de momento el prefijo [A[1], ..., A[i-1]] del A 
		
		int buyUntil = rightBinarySearch(i, n, prefixSum, B[k] + eliminatedAlready); // Hasta donde pueda eliminar del sufijo usando el k actual con una sola operación
		
		if (buyUntil == UNDEFINED){ // Si no puedo eliminar nada, entonces significa que ya no puedo hacer vacío A
			memo[i][k] = INF;
		} else {
			ll cost = m - k; // El costo de hacer la operación de borrar parte del sufijo
			// Tengo dos opciones ahora: incremento k o elimino lo más que puedo con el k actual y continuo con el nuevo sufijo
			// Me quedo con el mínimo de estas dos operaciones
			memo[i][k] = min(dp(i, k+1, memo, prefixSum, B), cost + dp(buyUntil+1, k, memo, prefixSum, B));
		}
	}
	
	return memo[i][k];
}

void solve(vector<ll> &A, vector<ll> &B){
	vector<vector<ll>> memo(SIZE(A), vector<ll>(SIZE(B), UNDEFINED));
	vector<ll> prefixSum(SIZE(A));
	forsn(i, 1, SIZE(A)) prefixSum[i] = prefixSum[i-1] + A[i];
	
	// Empiezo con k = 1, y el array que tengo que vaciar es [A[1], ..., A[n]]
	// Notemos que k <= m
	
	ll res = dp(1, 1, memo, prefixSum, B);
	if (res >= INF) res = -1;
	
	cout << res << "\n";
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_, t){
        int n, m;
        cin >> n >> m;

        vector<ll> A(n+1);
        vector<ll> B(m+1);
        
        forsn(i, 1, n+1) cin >> A[i];
        forsn(i, 1, m+1) cin >> B[i];
        
        solve(A, B);
    }
}
