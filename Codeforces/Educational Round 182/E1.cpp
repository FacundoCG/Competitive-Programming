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
const int MOD = 998244353;
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
vl A, T, L, R;
int l;
ll memo[5000][5500];
int goodSubsequences;
vector<vl> subsequencesForRes;

ll mod(ll a, ll m = MOD){
	ll res = a % m;
    if (res < 0) res += m;
	return res;
}

ll addMod(ll a, ll b, ll m = MOD){
    ll res = (mod(a, m) + mod(b, m)) % m;
    return res;
}

int leftBinarySearch(int start, int end, vl &B, ll x){
    int l1 = start - 1; 
    int r = end + 1; 

    while(r - l1 > 1) {
        int mid = l1 + (r-l1)/2;
        if(!(B[mid] >= x)) l1 = mid;
        else r = mid;
    }
    
    return r; // r es el primer elemento que cumple P(X)
}


ll dp(int i, int j){
	if (i >= n) return j == SIZE(T); // Si completé T
	
	if (memo[i][j] == UNDEFINED){
		memo[i][j] = dp(i+1, j); // No agarro el elemento
		ll prevElement = 0;
		if (j > 0) prevElement = T[j-1];
		
		if (j < l){
			if (A[i] == T[j]) memo[i][j] = addMod(memo[i][j], dp(i+1, j+1));
			else if (A[i] <= prevElement) memo[i][j] = addMod(memo[i][j], dp(i+1, j));
		} else if (j == l){
			if (A[i] == T[j]) memo[i][j] = addMod(memo[i][j], dp(i+1, j+2));
			else if (A[i] <= prevElement) memo[i][j] = addMod(memo[i][j], dp(i+1, j));
		} else {
			if (j < SIZE(T) && A[i] < T[j]) memo[i][j] = addMod(memo[i][j], dp(i+1, j));
			else {
				int k = leftBinarySearch(0, SIZE(R)-1, R, A[i]);
				int toJump = SIZE(R)-1 - k; 
				if (A[i] == R[k]) memo[i][j] = addMod(memo[i][j], dp(i+1, l+1+toJump+1));
				else memo[i][j] = addMod(memo[i][j], dp(i+1, l+1+toJump));
			}
		}
	}

	return memo[i][j];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		cin >> n;
		A.clear(); T.clear();
		A.resize(n);
		
		forn(i, n) cin >> A[i];
		forn(i, n){
			forn(j, n+500) memo[i][j] = UNDEFINED;
		}
		
		L.clear(); R.clear();
		L.pb(A[0]); R.pb(A[n-1]);
		forsn(i, 1, n) if (A[i] > L.back()) L.pb(A[i]);
		dforn(i, n) if (A[i] > R.back()) R.pb(A[i]);
				
		l = SIZE(L)-1;
		for (ll x : L) T.pb(x);
		dforn(i, SIZE(R)) T.pb(R[i]);
				
		ll res = dp(0, 0);
		cout << res << "\n";
	}
	
    return 0;
}
