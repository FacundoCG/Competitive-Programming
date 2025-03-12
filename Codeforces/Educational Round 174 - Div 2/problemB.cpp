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

void defineSetOf(ll i, ll j, vector<vector<ll>> &A, vector<vector<ll>> &setOf){
	set<ll> setsUsedByTheNeighbors; // I check what sets are using the neighbors which are already defined and have the same color than A[i][j]
	
	if (i+1 < SIZE(A) && setOf[i+1][j] != UNDEFINED && A[i+1][j] == A[i][j]) setsUsedByTheNeighbors.insert(setOf[i+1][j]);
	if (0 <= i-1  && setOf[i-1][j] != UNDEFINED && A[i-1][j] == A[i][j]) setsUsedByTheNeighbors.insert(setOf[i-1][j]);
	if (j+1 < SIZE(A[i]) && setOf[i][j+1] != UNDEFINED && A[i][j+1] == A[i][j]) setsUsedByTheNeighbors.insert(setOf[i][j+1]);
	if (0 <= j-1 && setOf[i][j-1] != UNDEFINED && A[i][j-1] == A[i][j]) setsUsedByTheNeighbors.insert(setOf[i][j-1]);
	
	if (esta(1, setsUsedByTheNeighbors)) setOf[i][j] = 2;
	else if (esta(2, setsUsedByTheNeighbors) || setsUsedByTheNeighbors.empty()) setOf[i][j] = 1;
}

void solve(vector<vector<ll>> &A, ll n, ll m){
	vector<vector<ll>> setOf(n, vector<ll>(m, UNDEFINED));
	ll maxCapacity = n*m;
	vector<set<ll>> setsForEachColor(maxCapacity + 1);
	
	forn(i, n){
		forn(j, m){
			defineSetOf(i, j, A, setOf);
		}
	}
		
	// I update the sets of each color
	forn(i, n){
		forn(j, m) setsForEachColor[A[i][j]].insert(setOf[i][j]);
	}
	
	// Now I look for the color who has more sets. This is the color that I will choose to paint the matrix
	ll numberOfTotalSets = 0;
	int bestColor = 0;
	
	forn(i, maxCapacity+1){
		numberOfTotalSets +=  SIZE(setsForEachColor[i]);
		bestColor = max(bestColor, SIZE(setsForEachColor[i]));
	}
		
	ll res = numberOfTotalSets - bestColor;
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
		
		vector<vector<ll>> A(n, vector<ll>(m));
		
		forn(i, n){
			forn(j, m) cin >> A[i][j];
 		}
 		
 		solve(A, n, m);
	}
}
