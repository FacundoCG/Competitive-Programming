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

struct intervalo{
	int l, r;
	ll p, q;
	
	intervalo(int L, int R, ll P, ll Q) : l(L), r(R), p(P), q(Q){}

	bool operator<(const intervalo& other) const {
		if (l != other.l) return l < other.l;
		return r < other.r;
    }
};

ll mod(ll a, ll m = MOD){
	ll res = ((a % m) + m) % m;
	return res;
}

ll addMod(ll a, ll b, ll m = MOD){
    ll res = ((a % m) + (b % m)) % m;
    return res;
}
 
ll mulMod(ll a, ll b, ll m = MOD){
	ll res = (ll) a*b;
	res %= m;
    return res;
}
 
ll binPowMod(ll base, ll exp, ll m = MOD){
    if (exp == 0) return 1;
    
    ll a = binPowMod(base, exp/2, m);
    ll res = mulMod(a, a, m);
    
    if (exp % 2 == 1) res = mulMod(res, base, m);
    return res;
}
 
ll divideMod(ll a, ll b, ll m = MOD){
    ll res = mulMod(a % m, binPowMod(b, m-2, m) % m, m) % m;
    return res;
}

struct SegmentTree{
    int n;
    vl A, B;
    ll elemNeutro;

    SegmentTree(int N, vl &a, ll neutro) : n(N), A(a), elemNeutro(neutro){
        B.resize(4*n, elemNeutro);
        build(1, 0, n-1);
    }

    ll combine(ll x, ll y){ return mulMod(x, y);}
    ll make_data(ll x){ return x;}

    void build(int v, int tl, int tr){ // Vértice actual y rango [tl, tr] que indica este vértice
        if (tl == tr) B[v] = make_data(A[tl]); // Cuando llego a una hoja, el valor es el mismo elemento
        else {
            int tm = (tl + tr)/2;
            build(2*v, tl, tm);
            build(2*v+1, tm+1, tr); 
            B[v] = combine(B[2*v], B[2*v+1]);
        }
    }

    // query(1, 0, n-1, l, r)
    ll query(int v, int tl, int tr, int l, int r){
        if (l > r) return elemNeutro; 
        if (l == tl && r == tr) return B[v];
        int tm = (tl+tr)/2;
        return combine(query(2*v, tl, tm, l, min(r, tm)), query(2*v+1, tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, ll new_val){
        if (tl == tr) B[v] = make_data(new_val);
        else {
            int tm = (tl + tr)/2;
            if (pos <= tm) update(2*v, tl, tm, pos, new_val);
            else update(2*v+1, tm+1, tr, pos, new_val);
            B[v] = combine(B[2*v], B[2*v+1]);
        }
    }
};


vector<intervalo> A;
vl P, NotP;

int N, M;

int leftBinarySearch(int start, int end, int k){
    int l = start - 1; 
    int r = end + 1; 

    while(r - l > 1) { 
        int mid = l + (r-l)/2;
        //~ int mid = (r+l)/2;
        if(!(A[mid].l >= k)) l = mid;
        else r = mid;
    }
    
    if (r < start || r > end || !(A[r].l == k)) r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
    return r; // r es el primer elemento que cumple P(X)
}

ll rangeQuery(int i, int j, SegmentTree &T){
	if (i > j) return 1ll;
	
	// Quiero saber cuál es la probabilidad de que se cumpla: NotP[i] && ... && NotP[j]
	// Es decir, NotP[i] * ... * NotP[j]
	return T.query(1, 0, N-1, i, j);
}

// Puedo usar el intervalo i o no
// M[i] = P(i)*dp(j)*~P(i+1, ..., j-1) donde j es el primer intervalo tal que A[j].l = A[i].r + 1
// Si j = -1, hacemos M[i] = 0 si A[i].r != m
// Si j = -1, hacemos M[i] = P(i)*~P(i+1, ..., n-1) si A[i].r = m
// M[i] += ~P(i)*dp(i+1)*k donde k es (A[i+1].l == A[i].l && i != n-1)

ll dp(int i, vl &memo, SegmentTree &T){	
	if (memo[i] == UNDEFINED){
		memo[i] = 0;
		int j = leftBinarySearch(i+1, N-1, A[i].r+1);
		
		if (j != UNDEFINED){
			memo[i] = mulMod(P[i], dp(j, memo, T));
			memo[i] = mulMod(memo[i], rangeQuery(i+1, j-1, T));
		} else if (A[i].r == M) memo[i] = mulMod(P[i], rangeQuery(i+1, N-1, T));
		
		if (i < N-1){ // Puedo skipear el intervalo
			ll skipear = mulMod(NotP[i], dp(i+1, memo, T));
			ll nextIntervalValid = (ll) (A[i].l == A[i+1].l);
			skipear = mulMod(skipear, nextIntervalValid);
			memo[i] = addMod(memo[i], skipear);
		}
	}
	
	return memo[i];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> N >> M;
	
	forn(_, N){
		int l, r;
		ll p, q;
		cin >> l >> r >> p >> q;
		A.pb(intervalo(l, r, p, q));
	}
	
	sort(all(A));
	
	P.resize(N); NotP.resize(N);
	forn(i, N) P[i] = divideMod(A[i].p, A[i].q);
	forn(i, N) NotP[i] = divideMod(A[i].q - A[i].p, A[i].q);
	
	SegmentTree T(N, NotP, 1ll);
	
	vl memo(N, UNDEFINED);
	ll res = 0;
	if (A[0].l == 1) res = dp(0, memo, T);
	cout << res << "\n";	
	
    return 0;
}
