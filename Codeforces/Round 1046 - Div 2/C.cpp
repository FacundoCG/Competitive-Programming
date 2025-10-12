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

int binarySearch(int start, int end, vi &A, int v){
    if (start > end) return -1;

    int mid = start + (end-start)/2;
    if (A[mid] == v) return mid;
    else if (A[mid] < v) return binarySearch(mid+1, end, A, v);
    else return binarySearch(start, mid-1, A, v);
}

int dp(int i, vi &A, vector<vi> &B, vi &memo){
	if (i >= SIZE(A)) return 0;
	
	if (memo[i] == UNDEFINED){
		memo[i] = dp(i+1, A, B, memo);
		int lengthBlock = A[i];
		// Si [i, i+lengthBlock-1] son todos iguales
		
		int j = binarySearch(0, SIZE(B[A[i]])-1, B[A[i]], i);
		if (j+lengthBlock-1 < SIZE(B[A[i]])){
			int k = B[A[i]][j+lengthBlock-1];
			memo[i] = max(memo[i], lengthBlock + dp(k+1, A, B, memo));
		}
	}
	
	return memo[i];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		int n;
		cin >> n;
		
		vi A(n);
		vector<vi> B(n+1);
		
		forn(i, n) {
			cin >> A[i];
			B[A[i]].pb(i);
		}
		
		vi memo(n, UNDEFINED);
		
		int res = dp(0, A, B, memo);
		cout << res << "\n";
		
	}
	
    return 0;
}
