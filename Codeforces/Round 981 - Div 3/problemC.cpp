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


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //

int g(int i, int j, vector<int> &A){
	return (0 <= i && i < SIZE(A)) && (0 <= j && j < SIZE(A)) && (A[i] == A[j]);
}

int dp(vector<int> &students, vector<vector<int>> &memo, int i, int c){
	int n = SIZE(students);
	
	if (n % 2 == 0 && i == n/2 - 1){
		if (c == 0){
			return g(i, i+1, students) + min(g(i-1, i, students) + g(i+1, i+2, students), g(i-1, i+1, students) + g(i+2, i, students));
		} else {
			return g(i, i+1, students) + min(g(i+2, i, students) + g(i-1, i+1, students), g(i+2, i+1, students) + g(i-1, i, students));
		}
	}
	
	if (n % 2 == 1 && i == n/2){
		return g(i, i-1, students) + g(i, i+1, students);
	}
	
	
	if (memo[i][c] == UNDEFINED){
		memo[i][c] = 0;
		
		if (c == 0){
			memo[i][c] = min(g(i-1, i, students) + g(n-1-i, n-i, students) + dp(students, memo, i+1, 0), g(i-1, n-1-i, students) + g(i, n-i, students) + dp(students, memo, i+1, 1));
		} else {
			memo[i][c] = min(g(n-i, i, students) + g(n-1-i, i-1, students) + dp(students, memo, i+1, 0), g(n-i, n-1-i, students) + g(i, i-1, students) + dp(students, memo, i+1, 1));
		}
	}
	
	return memo[i][c];
}

void solve(vector<int> &students){
    vector<vector<int>> memo(SIZE(students), vector<int>(2, UNDEFINED));
    
    int res = dp(students, memo, 0, 0);
    cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_, t){
		int n;
        cin >> n;

        vector<int> students(n);
        forn(i, n) cin >> students[i];

        solve(students);
    }
}
