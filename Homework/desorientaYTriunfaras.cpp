
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using vvl = vector<vl>;
using ii = pair<int,int>;
using vii = vector<ii>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
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

struct Elem{
	int id;
	ll interesados;
	Elem(int _id = -1, ll _interesados = -1) : id(_id), interesados(_interesados){}
	
	bool operator<(const Elem &other) const{
		return make_pair(id, interesados) < make_pair(other.id, other.interesados);
	}
};

ostream & operator<<(ostream &os, const Elem e){
	os << "{id: " << e.id << ", interesados: " << e.interesados;
	return os << "}";
}

const int MAX_N = 300;
ll memo[MAX_N+1][MAX_N+1];
ii intervaloIzq[MAX_N+1][MAX_N+1];
ii intervaloDer[MAX_N+1][MAX_N+1];
int raiz[MAX_N+1][MAX_N+1];

int n;
vector<Elem> A;
vl prefixSumA;

ll query(int l, int r){
	assert(0 <= l && l <= r && r < n);
	if (l == 0) return prefixSumA[r];
	return prefixSumA[r] - prefixSumA[l-1];
}

ll dp(int l, int r){
	if (l > r || l < 0 || r >= n) return 0;
	
	if (memo[l][r] == -1){
		memo[l][r] = LINF;
		forsn(x, l, r+1){
			ll currentOption = query(l, r) + dp(l, x-1) + dp(x+1, r);
			memo[l][r] = min(memo[l][r], currentOption);
		}
		
		forsn(x, l, r+1){
			ll currentOption = query(l, r) + dp(l, x-1) + dp(x+1, r);
			if (memo[l][r] == currentOption){
				intervaloIzq[l][r] = {l, x-1};
				intervaloDer[l][r] = {x+1, r};
				raiz[l][r] = x;
			}
		}
	}
	
	return memo[l][r];
}

string dfs(int l, int r){
	if (l > r) return "";
	string res = "(";
	auto [l1, r1] = intervaloIzq[l][r];
	auto [l2, r2] = intervaloDer[l][r];
	int root = raiz[l][r];
	//~ DBG(l); DBG(r); DBG(root);
	res += dfs(l1, r1);
	res += to_string(A[root].id);
	res += dfs(l2, r2);
	res += ")";
	return res;
}

	
int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	forn(i, MAX_N+1) forn(j, MAX_N+1) memo[i][j] = -1;
	cin >> n;
	
	forn(i, n){
		int id; ll interesados;
		cin >> id >> interesados;
		A.pb(Elem(id, interesados));
	}
	
	sort(all(A));
	
	prefixSumA.resize(n);
	prefixSumA[0] = A[0].interesados;
	forsn(i, 1, n) prefixSumA[i] = prefixSumA[i-1] + A[i].interesados;
	
	//~ DBG(A);
	
	cout << dp(0, n-1) << "\n";
	cout << dfs(0, n-1) << "\n";
	
	return 0;
	
}
