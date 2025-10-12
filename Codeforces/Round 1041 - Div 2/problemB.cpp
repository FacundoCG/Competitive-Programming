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

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		int n, x;
		cin >> n >> x;
		
		string s;
		cin >> s;
		
		int walls = 0;
		int leftWall = 0, rightWall = 0;
		
		forn(i, n) walls += (s[i] == '#');
		forn(i, x-1){
			if (s[i] == '#') leftWall = i+1;
		}
		
		forsn(i, x, n){
			if (s[i] == '#'){
				rightWall = i+1;
				break;
			}
		}
		
		if (walls == 0 || x == 1 || x == n) {
			cout << 1 << "\n";
			continue;
		}
		
		if (leftWall == 0) { leftWall = x-1;}
		if (rightWall == 0) {rightWall = x+1;}
		
		if (walls == 1){
			cout << min(leftWall, n+1-rightWall) + 1 << "\n";
		} else {
			int res;
			if (leftWall <= n+1-rightWall) res = min(x, n+1-rightWall+1);
			else res = min(n+1-x, leftWall+1);			
			cout << res << "\n";
		}				
	}
	
    return 0;
}
