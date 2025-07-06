#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

const ll UNDEFINED = -1;
const int MAX_N = 3000;
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

string A[3000];
char path[6000];
map<int, int> memo[6000];

// int memo[3000][3000];
int n;

int dp(int i, int j, int currentDepth){
	if (i == n-1 && j == n-1) return 0;
	int index = i*n + j;
	
	if (!esta(index, memo[currentDepth])){
		if (i+1 < n && j+1 < n){
			char c = min(A[i][j+1], A[i+1][j]);
			if (c > path[currentDepth]) return 0;
			path[currentDepth] = c;
			
			if (A[i][j+1] < A[i+1][j]){
				memo[currentDepth][index] = dp(i, j+1, currentDepth+1);
			} else if (A[i+1][j] < A[i][j+1]){
				memo[currentDepth][index] = dp(i+1, j, currentDepth+1);
			} else {
				memo[currentDepth][index] = min(dp(i+1, j, currentDepth+1), dp(i, j+1, currentDepth+1));
			}
		} else if (i+1 < n){
			char c = A[i+1][j];
			if (c > path[currentDepth]) return 0;
			path[currentDepth] = c;
			memo[currentDepth][index] = dp(i+1, j, currentDepth+1);
		} else {
			char c = A[i][j+1];
			if (c > path[currentDepth]) return 0;
			path[currentDepth] = c;
			memo[currentDepth][index] = dp(i, j+1, currentDepth+1);
		}
	}
	
	return memo[currentDepth][index];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	// Camino de longitud 2*(n-1)
	cin >> n;
	forn(i, 2*(n-1)) path[i] = 'Z';
	forn(i, n) cin >> A[i];
	
	path[0] = A[0][0];
	dp(0, 0, 1);
	
	forn(i, 2*(n-1)) cout << path[i];
	cout << "\n";
	
    return 0;
}
