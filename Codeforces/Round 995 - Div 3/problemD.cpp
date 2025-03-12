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

// Calcular extremo izquierdo que cumple P(X)
int leftBinarySearch(vector<ll> &A, int start, int end, ll value, ll z){
    int l = start - 1; 
    int r = end + 1; 

    while(r - l > 1) { 
        int mid = (l + r) / 2;
        if(!(value - A[mid] < z)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (r < start || r > end || !(value - A[r] < z)){
		r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return r; // r es el primer elemento que cumple P(X)
}

bool P(ll x, ll v, ll y){
	return x <= v && v <= y;
}

ll sumArray(vector<ll> &A){
	ll res = 0;
	forn(i, SIZE(A)) res += A[i];
	return res;
}

ll lessThan(vector<ll> &A, ll z){
	ll res = 0;
	ll s = sumArray(A);
		
	vector<ll> sortedA(A);
	sort(all(sortedA));
	
	forn(i, SIZE(A)){
		ll currentSum = s - A[i];
		ll firstIndexToRemove = leftBinarySearch(sortedA, 0, SIZE(A) - 1, currentSum, z); // Me da el indice del primer elemento que hace que: currentSum-A[j] < z. Como está ordenado, esto implica que todo indice mayor a j también va a cumplir dicha condición
		
		if (firstIndexToRemove != UNDEFINED){ // Si existe dicho indice
			res += SIZE(A) - firstIndexToRemove;
		}
	}
	
	return res;
}

void solve(vector<ll> &A, ll x, ll y){
	// Encontremos la cantidad de pares (i,j) que cumplen: x <= S - A[i] - A[j] <= y
	// Contamos la cantidad de pares que cumplen S-A[i]-A[j] <= y, y le descontamos los pares que cumplen S-A[i]-A[j] < x
	ll res = lessThan(A, y+1) - lessThan(A, x);
	ll s = sumArray(A);
	
	// Descontemos uno a res, por cada par (i,i) que cumpla la condición
	forn(i, SIZE(A)){
		if (P(x, s - A[i]*2, y)){
			res--;
		}
	}
	
	// Divido ahora a la mitad res, ya que por cada (i,j) con i != j que haya cumplido, también conté a (j,i)
	res /= 2;
	
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		ll n, x, y;
		cin >> n >> x >> y;
		
		vector<ll> A(n);
		forn(i, n) cin >> A[i];
		solve(A, x, y);
	}
}
