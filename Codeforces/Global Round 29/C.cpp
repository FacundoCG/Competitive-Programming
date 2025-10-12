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

int n;
string s;

//~ int dp(int i, vi &memo){
	//~ if (i >= n) return 1;
	
	//~ if (memo[i] == UNDEFINED){
	
	//~ }
	
	//~ return memo[i];
//~ }

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		cin >> n;		
		cin >> s;
		
		vi jump(n, UNDEFINED);
		bool res = true;
		
		forn(i, n){
			if (s[i] == '1') continue;
			if (jump[i] != UNDEFINED) continue;
						
			// 1 Derecha/2 Izquierda
			if (i+1 < n && s[i+1] == '0') jump[i] = UNDEFINED;
			else if (i-1 >= 0 && s[i-1] == '0') jump[i] = UNDEFINED;
			else if (i-1 == -1 || i+1 == n) jump[i] = UNDEFINED;
			else {
				if (i-2 >= 0 && s[i-2] == '0' && jump[i-2] == UNDEFINED) jump[i] = UNDEFINED;
				else if (i+2 < n && s[i+2] == '0'){
					jump[i] = 1;
					jump[i+2] = 2;
				} else {
					res = false;
					break;
				}
			}
		}
		
		if (res) cout << "YES\n";
		else cout << "NO\n";
	}
	
    return 0;
}
