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
using vvvl = vector<vvl>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvii = vector<vii>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
const int MOD = 1e9+7;
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

// Segment tree basico para point update y range query de suma

struct LazySegmentTree{
	int n;
	vl A, B, lazy;
	ll elemNeutro;

	LazySegmentTree(int N, vl &a, ll neutro) : n(N), A(a), elemNeutro(neutro){
		B.resize(4*n, elemNeutro);
		lazy.resize(4*n);
		build(1, 0, n-1);
	}

	ll combine(ll x, ll y){ return min(x, y);}
	ll make_data(ll x){ return x;}

	void build(int v, int tl, int tr){ // Vertice actual y rango [tl, tr] que indica este vertice
		if (tl == tr) B[v] = make_data(A[tl]); // Cuando llego a una hoja, el valor es el mismo elemento
		else {
			int tm = (tl + tr)/2;
			build(2*v, tl, tm);
			build(2*v+1, tm+1, tr); 
			B[v] = combine(B[2*v], B[2*v+1]);
		}
	}
	
	void applyUpdate(int v, int tl, int tr){
		if (lazy[v]){
			B[v] += lazy[v];
			if (tl != tr){
				lazy[2*v] += lazy[v];
				lazy[2*v+1] += lazy[v];
			}
			lazy[v] = 0;
		}
	}
	
	// query(1, 0, n-1, l, r)
	ll query(int v, int tl, int tr, int l, int r){
		applyUpdate(v, tl, tr);
		if (tr < l || tl > r) return elemNeutro; // Intervalos disjuntos
		if (l <= tl && tr <= r) return B[v];
		
		int tm = (tl+tr)/2;
		ll q1 = query(2*v, tl, tm, l, r);
		ll q2 = query(2*v+1, tm+1, tr, l, r);
		return combine(q1, q2);		
	}

	void update(int v, int tl, int tr, int l, int r, ll new_val){
		if (l <= tl && tr <= r) lazy[v] += new_val;
		applyUpdate(v, tl, tr);
		
		if (tr < l || tl > r) return ; // Intervalos disjuntos no hay update
		if (l <= tl && tr <= r) return ;
		
		
		int tm = (tl+tr)/2;
		update(2*v, tl, tm, l, r, new_val);
		update(2*v+1, tm+1, tr, l, r, new_val);
		B[v] = combine(B[2*v], B[2*v+1]);		
	}
	
	ll makeQuery(int l, int r){
		if (l > r) return elemNeutro;
		return query(1, 0, n-1, l, r);
	}
	
	void makeUpdate(int l, int r, ll x){
		if (l > r) return ;
		return update(1, 0, n-1, l, r, x);
	}
};

void solve(){
	int n; cin >> n;
	string s; cin >> s;
	
	vl A(n), B(n); 
	forn(i, n) {
		A[i] = (s[i] == '(') ? 1 : -1;
		B[i] = A[i];
		if (i > 0) B[i] += B[i-1];
	}
	
	LazySegmentTree T(n, B, INF);
	
	//~ DBG(n);
	//~ DBG(s);
	//~ DBG(A);
	//~ DBG(B);
	
	int q; cin >> q;
	forn(_, q){
		int op; cin >> op;
		op--;
		//~ DBG(op);
		
		if (op == -1){ // Chequear que prefixSumA[n-1] = 0 y min(prefixSumA) >= 0
			ll lastValue = T.makeQuery(n-1, n-1), minValue = T.makeQuery(0, n-1);
			//~ DBG(lastValue); DBG(minValue);
			//~ ll lastValue = B[n-1], minValue = *min_element(all(B));
			if (minValue >= 0 && lastValue == 0) cout << "YES\n";
			else cout << "NO\n";
		} else {
			ll newValue = (A[op] == -1) ? 1 : -1;
			//~ DBG(newValue);
			T.makeUpdate(op, n-1, 2*newValue); // Sumo 2*newValue en [op, n-1]
			//~ forsn(i, op, n) B[i] += 2*newValue;
			A[op] = newValue;
		}
		
		//~ DBG(A);
		//~ RAYA;
	}	
}

int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
		
	int t1 = 10; 
	//~ int t1 = 1; 
	//~ cin >> t1;
	forn(_, t1) {
		cout << "Test " << _+1 << ": \n";
		solve();
	}
}
