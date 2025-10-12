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
const int MOD = 998244353;
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

int mod(int a, int m = MOD){
	int res = a % m;
    if (res < 0) res += m;
	return res;
}

int addMod(int a, int b, int m = MOD){
    int res = (mod(a, m) + mod(b, m)) % m;
    return res;
}

string s;
int n;

typedef pair<char, int> elem;

const int MAX_N = 1 << 22;
int memo[MAX_N];

int dp(int i){
	if (i == 0) return 1;
	
	if (memo[i] == UNDEFINED){
		memo[i] = 0;
		
		vector<elem> A;
		forn(j, n){ if (i & (1 << j)) A.pb({s[j], j});}
		
		forn(j, SIZE(A)){
			int index = A[j].snd;
			if (j+1 < SIZE(A)){ if (A[j+1].fst != A[j].fst) memo[i] = addMod(memo[i], dp(i & (~(1 << index))));}
			else memo[i] = addMod(memo[i], dp(i & (~(1 << index))));
		} 
	}
	
	return memo[i];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> n >> s;
	
	int all_elements =  (1 << n)-1;
	forn(i, all_elements+1) memo[i] = UNDEFINED;
	int res = dp(all_elements);
	cout << res << "\n";

    return 0;
}
