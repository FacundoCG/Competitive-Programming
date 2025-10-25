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

int query(int i, int x){
	cout << "? " << i << " " << x << "\n";
	cout.flush();
	
	int res;
	cin >> res;
	return res;
}

bool isSubMask(int x, int mask, int j){
	// It tells you if the mask is a subset of x until position j
	forn(k, j+1) if (((1 << k) & x) != ((1 << k) & mask)) return false;
	return true;
}

int numberOfSubMasks(int mask, int j){
	int res = 0;
	forsn(i, 1, n+1) res += (int) isSubMask(i, mask, j);
	return res;
}

void eliminarDe(set<int> &res, int mask, int j){
	forsn(i, 1, n+1) if (isSubMask(i, mask, j)) res.erase(i);
}

void solve(){
	cin >> n;
	vi A;
	set<int> res;
	forsn(i, 1, n) A.pb(i);
	forsn(i, 1, n+1) res.insert(i);
	
	int j = 0;
	int currentBitmask = 0;
	
	while (!A.empty()){		
		vi A1, A2;
		for (int x : A){
			if (query(x, (1 << j))) A1.pb(x);
			else A2.pb(x);
		}
		
		if (SIZE(A1) == numberOfSubMasks(currentBitmask | (1 << j), j)) { A = A2; eliminarDe(res, currentBitmask | (1 << j), j); }
		else {A = A1; eliminarDe(res, currentBitmask, j); currentBitmask |= (1 << j);}
		j++;
	}
	
	cout << "! " << *res.begin() << "\n";	
	cout.flush();
}

int main()
{
	
	int t; cin >> t;
	forn(_, t) solve();
	
    return 0;
}
