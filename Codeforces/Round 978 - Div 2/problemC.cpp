#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const ll NEG_INF = -1e15;
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
int n;

// ############################################################### //
ll calculateVotesFor(ll i, ll j, ll shape, vector<string> &grid){
	ll res = 0;
	
	if (shape == 0 && i+2 >= n) return NEG_INF;
	if (i+1 >= n) return NEG_INF;
	
	if (shape == 0){
		if (j == 0 || j == 1 || j == 3){
			if (grid[1][i] == 'A' && grid[1][i+1] == 'A'){
				res++;
			} else if (grid[1][i+1] == 'A' && grid[1][i+2] == 'A'){
				res++;
			} else if (grid[1][i] == 'A' && grid[1][i+2] == 'A'){
				res++;
			}
		}
		
		if (j == 0 || j == 2 || j == 4){
			if (grid[0][i] == 'A' && grid[0][i+1] == 'A'){
				res++;
			} else if (grid[0][i+1] == 'A' && grid[0][i+2] == 'A'){
				res++;
			} else if (grid[0][i] == 'A' && grid[0][i+2] == 'A'){
				res++;
			}
		}		
	} else if (shape == 1){
		if (grid[0][i] == 'A' && grid[1][i] == 'A'){
			res++;
		} else if (grid[1][i] == 'A' && grid[1][i+1] == 'A'){
			res++;
		} else if (grid[0][i] == 'A' && grid[1][i+1] == 'A'){ 
			res++;
		}
	} else if (shape == 2){
		if (grid[0][i] == 'A' && grid[1][i] == 'A'){
			res++;
		} else if (grid[0][i] == 'A' && grid[0][i+1] == 'A'){
			res++;
		} else if (grid[1][i] == 'A' && grid[0][i+1] == 'A'){ 
			res++;
		}
	} else if (shape == 3){
		if (grid[0][i] == 'A' && grid[0][i+1] == 'A'){
			res++;
		} else if (grid[0][i] == 'A' && grid[1][i+1] == 'A'){
			res++;
		} else if (grid[0][i+1] == 'A' && grid[1][i+1] == 'A'){ 
			res++;
		}
	} else if (shape == 4){
		if (grid[1][i] == 'A' && grid[1][i+1] == 'A'){
			res++;
		} else if (grid[1][i+1] == 'A' && grid[0][i+1] == 'A'){
			res++;
		} else if (grid[1][i] == 'A' && grid[0][i+1] == 'A'){ 
			res++;
		}
	}
	
	return res;
}

ll dp(ll i, ll j, vector<string> &grid, vector<vector<ll>> &memo){
	if (i == n && j == 0){ // If I reach the next column to the last with a zero, it means that the configuration was valid because I didn't put anything that goes outside the n columns
		return 0;
	}
	
	if (i > n || (i == n && j != 0)){ // I reach to a column >= n+1, or to column n with an state != 0, the configuration isn't valid
		return NEG_INF;
	}
		
	if (memo[i][j] == UNDEFINED){
		ll option1 = 0;
		ll option2 = 0;
		ll option3 = 0;
		
		// For each state, I analyze what shapes I can put and what column and state they give me for the next call
		if (j == 0){ 
			option1 = dp(i+3, 0, grid, memo) + calculateVotesFor(i, j, 0, grid);
			option2 = dp (i+1, 2, grid, memo) + calculateVotesFor(i, j, 1, grid);
			option3 = dp(i+1, 1, grid, memo) + calculateVotesFor(i, j, 2, grid);
		} else if (j == 1){
			option1 = dp(i+1, 4, grid, memo) + calculateVotesFor(i, j, 0, grid);
			option2 = dp(i+2, 0, grid, memo) + calculateVotesFor(i, j, 4, grid);
		} else if (j == 2){
			option1 = dp(i+1, 3, grid, memo) + calculateVotesFor(i, j, 0, grid);
			option2 = dp(i+2, 0, grid, memo) + calculateVotesFor(i, j, 3, grid);
		} else if (j == 3){
			option1 = dp(i+2, 2, grid, memo) + calculateVotesFor(i, j, 0, grid);
		} else if (j == 4){
			option1 = dp(i+2, 1, grid, memo) + calculateVotesFor(i, j, 0, grid);
		}
		
		memo[i][j] = max(option1, max(option2, option3));
	}
	
	return memo[i][j];
}

void solve(vector<string> &grid){
	// When I select a district I have 5 possible states to the next column that I move:
	// - State 0:   [_, _] - State 1: [*, _]  - State 2: [_, _]  - State 3: [*, *]  - State 4: [_, _]
	//			    [_, _] 			  [_, _]			 [*, _]				[_, _]			   [*, *]
	
	// _ = means that the house wasn't selected
	// * = means that the house was selected
	
	// Initially, I start at the first column with a state 0 because I didn't select anything from the first and the second column yet
	vector<vector<ll>> memo(n, vector<ll>(5, UNDEFINED));
	ll res = dp(0, 0, grid, memo);
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_,t){
        cin >> n;
		
		string s1, s2;
		cin >> s1 >> s2;
        vector<string> grid = {s1, s2};
        solve(grid);
    }
};
