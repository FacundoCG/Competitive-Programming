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
int n;

// Calcular extremo derecho que cumple P(X)
int rightBinarySearch(int start, int end, vector<ll> &A, ll v){
    int l = start - 1;
    int r = end + 1;

    while (r - l > 1){
        int mid = (l + r)/2;

        if (A[mid] < v){
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (l < start || l > end || !(A[l] < v)) l = -1; // Si l no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	
    return l; // l es el ultimo elemento que cumple P(X)
}

int leftBinarySearch(int start, int end, vector<ll> &A, ll v){
    int l = start - 1; 
    int r = end + 1; 

    while(r - l > 1) { 
        int mid = (l + r) / 2;
        if(!(A[mid] > v)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (r < start || r > end || !(A[r] > v)) r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1

    return r; // r es el primer elemento que cumple P(X)
}

void solve(vector<ll> &A){
	ll res = 0;
	
	forn(i, n){
		forn(j, n){
			if (i == j) continue;
			
			int maximum, minimum;
			if (A[i] >= A[j]) {maximum = i, minimum = j;}
			else {maximum = j, minimum = i;} 
			
			int lastIndex = rightBinarySearch(0, n-1, A, A[maximum] + A[minimum]);
			// Tengo que elegir entre: [0, lastIndex]
			
			// Quiero que lo elegido entre [0, lastIndex] cumple que: A[i] + A[j] + A[k] > A[n-1]
			// Y que: A[maximum] < A[min1] + A[min2]
			
			
			
			//~ int firstIndex = leftBinarySearch(0, n-1, A, A[maximum] - A[minimum]);

			
			//~ if (firstIndex <= lastIndex){
				//~ DBG(A[i]); DBG(A[j]);
				//~ res += lastIndex - firstIndex + 1;
				//~ if (firstIndex <= i && i <= lastIndex) res--;
				//~ if (firstIndex <= j && j <= lastIndex) res--;
			//~ }
			
			//~ // Yo quiero ver ahora cuántos k hay tal que: (i, j, k) es buena tripla
			//~ // Busco primer k' tq: A[k] >= A[j] + A[i]
			//~ // Sé que los k < k': A[k] < A[j] + A[i]
			//~ // Ahora me pregunto cuánto de estos A[k] + A[minimum] > A[maximum]
			//~ // A[j] + A[i]  > A[k] > A[maximum] - A[minimum] 
			
		}
	}
	res /= 2;
	res /= 3;
	cout << res << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		cin >> n;
		
		vector<ll> A(n);
		forn(i, n) cin >> A[i];
		sort(all(A));
		solve(A);
	}
	
    return 0;
}
