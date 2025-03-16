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

pair<ll, ll> calculateStartingPoint(vector<string> &map){
	ll n = SIZE(map);
	ll m = SIZE(map[0]);
	pair<ll, ll> res = {0, 0};
	
	forn(i, n){
		forn(j, m){
			if (map[i][j] == 'S') res = {i, j};
		}
	}
	
	return res;
}

bool existsTrapAround(vector<string> &map, ll i, ll j){
	ll n = SIZE(map);
	ll m = SIZE(map[0]);
	
	if (i+1 < n && map[i+1][j] == 'T') return true;
	if (0 <= i-1 && map[i-1][j] == 'T') return true;
	if (j+1 < m && map[i][j+1] == 'T') return true;
	if (0 <= j-1 && map[i][j-1] == 'T') return true;
	return false;
}

ll dfs(vector<string> &map, ll i, ll j, vector<vector<bool>> &visited){
	ll n = SIZE(map);
	ll m = SIZE(map[0]);
	
	visited[i][j] = true;
	if (existsTrapAround(map, i, j)) return 0;
	ll res = 0;
	
	if (i+1 < n && !visited[i+1][j]){
		if (isdigit(map[i+1][j])){
			ll digit = map[i+1][j] - '0';
			res += dfs(map, i+1, j, visited) + digit;
		} else if (map[i+1][j] == '.') res += dfs(map, i+1, j, visited);
	}
	
	
	if (0 <= i-1 && !visited[i-1][j]){
		if (isdigit(map[i-1][j])){
			ll digit = map[i-1][j] - '0';
			res += dfs(map, i-1, j, visited) + digit;
		} else if (map[i-1][j] == '.') res += dfs(map, i-1, j, visited);
	}
	
	if (j+1 < m && !visited[i][j+1]){
		if (isdigit(map[i][j+1])){
			ll digit = map[i][j+1] - '0';
			res += dfs(map, i, j+1, visited) + digit;
		} else if (map[i][j+1] == '.') res += dfs(map, i, j+1, visited);
	}
	
	if (0 <= j-1 && !visited[i][j-1]){
		if (isdigit(map[i][j-1])){
			ll digit = map[i][j-1] - '0';
			res += dfs(map, i, j-1, visited) + digit;
		} else if (map[i][j-1] == '.') res += dfs(map, i, j-1, visited);
	}
	
	return res;
}

void solve(vector<string> &map){
	ll n = SIZE(map);
	ll m = map[0].size();
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	pair<ll, ll> p = calculateStartingPoint(map);
	ll res = dfs(map, p.fst, p.snd, visited);
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	ll n, m;
	
	while (cin >> n){
		cin >> m;
		vector<string> map(n);
		forn(i, n) cin >> map[i];
		solve(map);
	}
}
