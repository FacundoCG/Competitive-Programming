#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<vector<int>> vector2;
typedef vector<vector2> vector3;
typedef vector<vector3> vector4;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
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
ll n, m, res;

int exploreRectangle(int i, int j, vector<string> &grid, vector<vector<int>> &M, vector<vector<int>> &depth){
	ll c1 = grid[i][j] - 'a';
	ll d1 = depth[i][j];
	if (i + d1 >= n) return 0;
	
	ll c2 = grid[i+d1][j] - 'a';
	ll d2 = depth[i+d1][j];
	if (i + d1 + d2 >= n) return 0;
	
	ll c3 = grid[i+d1+d2][j] - 'a';
	ll d3 = depth[i+d1+d2][j];
	
	if (d1 != d2 || d3 < d2) return 0;
	
	res += 1; // It means that I can make one flag of width 1 and height d2 for each color	
	if (j-1 < 0) return 0;
	
	ll c4 = grid[i][j-1] - 'a';
	ll d4 = depth[i][j-1];
	if (d4 != d1 || c1 != c4) return 0;

	ll c5 = grid[i+d1][j-1] - 'a';
	ll d5 = depth[i+d1][j-1];
	if (d5 != d2 || c5 != c2) return 0;
	
	ll c6 = grid[i+d1+d2][j-1] - 'a';
	ll d6 = depth[i+d1+d2][j-1];
	if (d6 < d5 || c6 != c3) return 0;
	
	// If I have k good tiles to my left, it means that I can make k flags using my current tile i,j to the left
	M[i][j] = M[i][j-1] + 1;
	res += M[i][j];
	return 0;
}

void solve(vector<string> &grid){
	res = 0;
	
	vector<vector<int>> depth(n, vector<int>(m, 1));
	
	for (ll i = n-2; i >= 0; i--){
		forn(j, m){
			if (grid[i][j] == grid[i+1][j]) depth[i][j] = 1 + depth[i+1][j];
		}
	}
	
	vector<vector<int>> M(n, vector<int>(m, 0));
	
	forn(i, n){
		forn(j, m) exploreRectangle(i, j, grid, M, depth);
	}
	
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	cin >> n >> m;
	vector<string> grid(n);
	forn(i, n) cin >> grid[i];
	solve(grid);
}
