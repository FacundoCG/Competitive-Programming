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

int n, m;

bool dfs(int i, int j, vector<string> &grid, vector<vector<bool>> &visited, vector<vector<int>> &sequenceRow, vector<vector<int>> &sequenceColumn){
	if (i <= 0 || j <= 0 || visited[i][j]) return true;
	visited[i][j] = true;
	
	if (grid[i][j] == '1' && sequenceRow[i][j-1] != j && sequenceColumn[i-1][j] != i) return false;
	return dfs(i-1, j, grid, visited, sequenceRow, sequenceColumn) && dfs(i, j-1, grid, visited, sequenceRow, sequenceColumn);
}

void solve(vector<string> &grid){
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	vector<vector<int>> sequenceRow(n, vector<int>(m, 0));
	vector<vector<int>> sequenceColumn(n, vector<int>(m, 0));
	
	forn(i, n) sequenceRow[i][0] = (grid[i][0] == '1');
	forn(i, n){
		forsn(j, 1, m) sequenceRow[i][j] = sequenceRow[i][j-1] + (grid[i][j] == '1');
	}
	
	forn(i, m) sequenceColumn[0][i] = (grid[0][i] == '1');
	forn(i, m){
		forsn(j, 1, n) sequenceColumn[j][i] = sequenceColumn[j-1][i] + (grid[j][i] == '1');
	}
	
	//~ DBG(sequenceRow);
	//~ DBG(sequenceColumn);
	
	bool res = dfs(n-1, m-1, grid, visited, sequenceRow, sequenceColumn);
	
	if (res){
		cout << "YES" << "\n";
	} else {
		cout << "NO" << "\n";
	}
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		cin >> n >> m;
		vector<string> grid(n);
		forn(i, n) cin >> grid[i];
		solve(grid);
	}
}
