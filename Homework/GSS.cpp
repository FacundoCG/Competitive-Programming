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

struct Info{
	ll maxSubArray, maxElem, minElem;	
	Info (ll _x = -LINF, ll _maxElem = -LINF, ll _minElem = LINF) : 
		maxSubArray(_x), maxElem(_maxElem), minElem(_minElem){}
};

struct SegmentTree{
	int n;
	vector<Info> B;
	Info elemNeutro = Info();
	vl lazy;
		
	SegmentTree(int _n, vl &A) : n(_n){
		B.resize(4*n, elemNeutro);
		lazy.resize(4*n);
		build(1, 0, n-1, A);
	}
	
	Info combine(Info leftChild, Info rightChild){
		Info res;
		res.maxSubArray = max(leftChild.maxSubArray, rightChild.maxSubArray);
		res.maxSubArray = max(res.maxSubArray, rightChild.maxElem-leftChild.minElem);
		res.maxElem = max(leftChild.maxElem, rightChild.maxElem);
		res.minElem = min(leftChild.minElem, rightChild.minElem);
		return res;
	}
	
	Info make_data(ll x){ return Info(-LINF, x, x); }
	
	void build(int v, int l, int r, vl &A){
		if (l == r){ B[v] = make_data(A[l]); return ;}
		int m = (l+r)/2;
		build(2*v, l, m, A);
		build(2*v+1, m+1, r, A);		
		B[v] = combine(B[2*v], B[2*v+1]);
	}
	
	void apply(int v, int l, int r){
		if (lazy[v] != 0){
			B[v].minElem += lazy[v]; 
			B[v].maxElem += lazy[v]; 			
			if (l != r){
				lazy[2*v] += lazy[v];
				lazy[2*v+1] += lazy[v];
			}
			lazy[v] = 0;
		}
	}
	
	Info query(int v, int tl, int tr, int l, int r){
		if (tr < l || r < tl) return elemNeutro;
		apply(v, tl, tr);
		if (l <= tl && tr <= r) return B[v];
		int tm = (tl+tr)/2;
		return combine(query(2*v, tl, tm, l, r), query(2*v+1, tm+1, tr, l, r));
	}
	
	void update(int v, int tl, int tr, int l, int r, ll x){
		apply(v, tl, tr);
		if (tr < l || r < tl) return ;
		if (l <= tl && tr <= r) {
			lazy[v] = x; 
			apply(v, tl, tr);
			return ;
		}
		
		int tm = (tl+tr)/2;
		update(2*v, tl, tm, l, r, x);
		update(2*v+1, tm+1, tr, l, r, x);
		B[v] = combine(B[2*v], B[2*v+1]);
	}
	
	Info makeQuery(int l, int r){ return query(1, 0, n-1, l, r); }
	void makeUpdate(int l, int r, ll x){ return update(1, 0, n-1, l, r, x); }
};

void solve(){
	int n; cin >> n;
	
	vl prefixSum(n+1), A(n+1);
	forsn(i, 1, n+1) { 
		cin >> A[i]; 
		prefixSum[i] = prefixSum[i-1] + A[i];
	}
	
	//~ DBG(n);
	//~ DBG(A);
	//~ DBG(prefixSum);
	
	int m = SIZE(prefixSum);
	SegmentTree T(m, prefixSum);
	
	int q; cin >> q;
	//~ DBG(q);
	forn(_, q){
		int c; cin >> c;
		//~ DBG(c);
		//~ vl currentB(n+1);
		//~ forsn(i, 1, n+1) currentB[i] = T.makeQuery(i-1, i).maxSubArray;
		//~ DBG(currentB);
		
		if (c == 0){
			int pos; cin >> pos; 
			ll x; cin >> x;
			//~ DBG(pos); DBG(x);
			ll newValue = x - A[pos]; // Saco el valor viejo y agrego el nuevo
			//~ DBG(newValue);
			T.makeUpdate(pos, n, newValue);
			A[pos] = x;
		} else {
			int l, r; cin >> l >> r;
			//~ DBG(l); DBG(r);
			l--; // prefixSum[r] - prefixSum[l] es lo maximo que puedo sumar
			cout << T.makeQuery(l, r).maxSubArray << "\n";
		}
		//~ RAYA;
	}
}

int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
		
	int t = 1;
	//~ cin >> t; 
	forn(_, t) solve();
}
