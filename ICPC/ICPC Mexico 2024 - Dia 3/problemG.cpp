#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
//const int MAX_N = 1e5 + 1;
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

const int MAX_N = pow(10, 6);
int m;

bool dp(int i, int player, vector<int> &A, int toRest, vector<vector<int>> &memo){
	if (i == m-1) return 1;
	
	if (memo[i][player] == UNDEFINED){
		memo[i][player] = dp(i+1, (player+1) % 2, A, A[i], memo);
		
		if (memo[i][player] == 0){
			memo[i][player] = 1;
		} else {
			memo[i][player] = 0;
		}
		
		if (A[i] - toRest != 1) memo[i][player] |= dp(i+1, player, A, A[i], memo);
	}
	
	return memo[i][player];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;
    
    vector<bool> used(MAX_N + 1);
    vector<int> A;
    forn(i, n){
		int v;
		cin >> v;
		if (!used[v]){
			used[v] = true;
			A.pb(v);
		}
	}
	
	sort(all(A));
	m = SIZE(A);
    
    vector<vector<int>> memo(m, vector<int>(2, UNDEFINED));
    
    bool winPlayer1 = dp(0, 0, A, 0, memo);
    if (winPlayer1){
		cout << "Alicius\n";
	} else {
		cout << "Bobius\n";
	}
}
