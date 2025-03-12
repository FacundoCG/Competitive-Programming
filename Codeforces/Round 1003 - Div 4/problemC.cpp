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

// Calcular extremo derecho que cumple P(X)
ll rightBinarySearch(int start, int end, vector<ll> &B, ll c, ll currentValue){
    int l = start - 1;
    int r = end + 1;

    while (r - l > 1){
        int mid = (l + r)/2;

        if (B[mid] - currentValue <= c){
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (l < start || l > end){
		l = 0; // Si l no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return B[l] - currentValue; // l es el ultimo elemento que cumple P(X)
}


void solve(vector<ll> &A, vector<ll> &B){
	sort(all(B));
	
	string res = "YES";
	
	A[SIZE(A)-1] = max(A[SIZE(A)-1], B[SIZE(B)-1] - A[SIZE(A)-1]);
	
	dforn(i, SIZE(A)-1){
		ll possibleNewValue = rightBinarySearch(0, SIZE(B)-1, B, A[i+1], A[i]);
		if (possibleNewValue >= A[i] && possibleNewValue <= A[i+1]){
			A[i] = possibleNewValue;
		} else if (possibleNewValue <= A[i] && A[i] > A[i+1]){
			A[i] = possibleNewValue;
		}
	}
	
	forsn(i, 1, SIZE(A)){
		if (A[i] < A[i-1]) res = "NO";
	}
		
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		ll n, m;
		cin >> n >> m;
		
		vector<ll> A(n), B(m);
		
		forn(i,n) cin >> A[i];
		forn(i, m) cin >> B[i];
		
		solve(A, B);
	}
}
