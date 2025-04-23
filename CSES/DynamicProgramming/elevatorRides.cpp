#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
//const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;
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

//map<int, map<int, map<int, map<int, int>>>> memo;
map<tuple<int, int, int, int>, int> memo;

int A[20];
int n, x;

int dp(int i, int j, int used, int w){
	if (used == 0) return 0; // If I have used all the people, I finish the iteration
	if (i == -1 && used != 0) return INF; // If I don't have more elevators and I didn't use all the people this is an invalid scenario
	if (j == -1) return dp(i-1, n-1, used, 0); // If I don't have more people for this elevator, I move to the next one with a weight of zero
	
	if (memo.count({i, j, used, w}) == 0){
		int res1 = dp(i, j-1, used, w);
		int res2 = INF;
		
		//~ memo[{i, j, used, w}] = dp(i, j-1, used, w); // I don't use this person for this elevator
		//~ int p = 1 << j;		
		//~ if ((p & used) && w + A[j] <= x){
			//~ memo[{i, j, used, w}] = min(memo[{i, j, used, w}], 1 + dp(i, j-1, used & ~p, w + A[j]));
		//~ }
		
		int p = 1 << j;		
		if ((p & used) && w + A[j] <= x) res2 = 1 + dp(i, j-1, used & ~p, w + A[j]);
		memo[{i, j, used, w}] = min(res1, res2);
	}
	
	return memo[{i, j, used, w}];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	cin >> n >> x;
	forn(i, n) cin >> A[i];
	int allUsed = 1 << n;
	allUsed -= 1;
	DBG(n); DBG(allUsed); DBG(x);
	cout << dp(n-1, n-1, allUsed, 0) << "\n"; // I start in the elevator n-1-th with the person n-1 and a current weight of 0 
}
