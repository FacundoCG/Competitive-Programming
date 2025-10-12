#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

using vl = vector<ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vp = vector<pair<int, int>>;

const ll UNDEFINED = -1;
//~ const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
//~ const int INF = 1e9;
const ll LINF = 1e18;
const ll N_LINF = (-1)*1e18;
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

// dp(i, j) te faltan agregan j elementos al conjunto de minions fijos y estás actualmente analizando al minion i
// dp(i, j) = max(A[i] + (k-j)*B[i] + dp(i+1, j-1), (k-1)*B[i] + dp(i+1, j))

int n, k;

struct minion_t{
	int indice;
	ll a, b;
	
	minion_t(ll poder_inicial = 0, ll poder_otorgado = 0, int indice_original = 0) : indice(indice_original), a(poder_inicial), b(poder_otorgado) {}
};

ostream & operator <<(ostream &os, const minion_t &m) {
	os << "{" << m.a << "," << m.b << ", " << m.indice << "}";
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


bool customOrder(minion_t &m1, minion_t &m2){
	return tie(m1.b, m1.a, m1.indice) < tie(m2.b, m2.a, m2.indice);
}

ll dp(int i, int j, vector<vl> &memo, vector<vp> &parents, vector<minion_t> &C){
	if (i == n && j > 0) return N_LINF;
	if (j < 0) return N_LINF;
	if (j == 0 && i == n) return 0;
	
	if (memo[i][j] == UNDEFINED){
		memo[i][j] = max(dp(i+1, j, memo, parents, C) + (C[i].b)*(k-1), dp(i+1, j-1, memo, parents, C) + C[i].a + (C[i].b)*(k-j));
		if (dp(i+1, j, memo, parents, C) + (C[i].b)*(k-1) < dp(i+1, j-1, memo, parents, C) + C[i].a + (C[i].b)*(k-j)){
			parents[i][j] = {i+1, j-1};
		} else {
			parents[i][j] = {i+1, j};
		}
	}
	
	return memo[i][j];
}

void solve(){
	cin >> n >> k;
	
	vector<minion_t> C;
	vb used(n);
	
	forn(i, n) {
		ll a, b;
		cin >> a >> b;
		C.pb(minion_t(a, b, i));
	}
	
	sort(all(C), customOrder);
	
	vector<vl> memo(n, vl(k+1, UNDEFINED));
	vector<vp> parents(n, vp(k+1));
	dp(0, k, memo, parents, C);
	
	int i_delta = 0, j_delta = k;
	vi indexsUsed, indicesNoFijos;
		
	while (j_delta != 0){
		assert(i_delta < n);
		assert(j_delta < k+1);
		
		auto p = parents[i_delta][j_delta];
		if (p.snd < j_delta) {
			indexsUsed.pb(C[i_delta].indice);
			used[C[i_delta].indice] = true;
		}
		
		i_delta = p.fst; j_delta = p.snd;
	}
	
	forn(i, n){
		if (used[C[i].indice]) continue;
		indicesNoFijos.pb(C[i].indice);
	}
		
	int m = (n-k)*2 + k;
	cout << m << "\n";
	
	forn(i, k-1) cout << indexsUsed[i]+1 << " ";
	forn(i, SIZE(indicesNoFijos)) cout << indicesNoFijos[i]+1 << " " << (indicesNoFijos[i]+1)*(-1) << " ";
	cout << indexsUsed[k-1]+1 << "\n";
}


int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	while(t--){
		solve();
	}
	
	
	
	return 0;
}
