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
int n;

void swap(vector<ll> &C, int i, int j){
	ll oldValue = C[i];
	C[i] = C[j];
	C[j] = oldValue;
}

bool badCase(vector<ll> &A, vector<ll> &B, int i, int j){
	return (A[i] == B[j] && B[i] != A[j]) || (A[i] != B[j] && B[i] == A[j]);
}

int countBadIndexs(vector<ll> &A, vector<ll> &B){
	int res = 0;
	forsn(i, 1, n+1){
		if (A[i] == B[i]) res++;
	}
	
	return res;
}

int solve(vector<ll> &A, vector<ll> &B){
	vector<pair<int, int>> res;
	vector<int> indexInB(n+1);
	vector<int> indexInA(n+1);
	
	int badIndexs = countBadIndexs(A, B);
	
	forsn(i, 1, n+1){
		if (A[i] == B[i] && i != (n/2 + 1)){
			int j = n/2 + 1;
			swap(A, i, j);
			swap(B, i, j);
			res.pb({i, j});
		}
		
		indexInA[A[i]] = i;
		indexInB[B[i]] = i;
	}
	
	if (badIndexs >= 2){
		cout << -1 << "\n";
		return 0;
	} else if (badIndexs == 1 && n % 2 == 0){
		cout << -1 << "\n";
		return 0;
	}
	
	forsn(i, 1, n/2+1){
		int j = n-i+1;
		
		if (badCase(A, B, i, j)){
			cout << -1 << "\n";
			return 0;
		} else if (A[i] != B[j] && A[j] != B[i]){
			// Yo quiero que B[j] = A[i]
			// Busco el valor de A[i] en B y lo swapeo
			int k = indexInB[A[i]];
			swap(B, j, k); // Ahora A[i] = B[j]
			swap(A, j, k);
			res.pb({j, k});
			
			indexInA[A[j]] = j;
			indexInA[A[k]] = k;
			indexInB[B[j]] = j;
			indexInB[B[k]] = k;
		}
		
		if (badCase(A, B, i, j)){
			cout << -1 << "\n";
			return 0;
		}
	}
	
	cout << SIZE(res) << "\n";
	
	// Printear secuencia
	for (auto p : res) cout << p.fst << " " << p.snd << "\n"; 
	return 0;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
	int t;
	cin >> t;
	forn(_, t){
		cin >> n;
		
		vector<ll> A(n+1);
		vector<ll> B(n+1);
		forsn(i, 1, n+1) cin >> A[i];
		forsn(i, 1, n+1) cin >> B[i];
		solve(A, B);
	}
}
