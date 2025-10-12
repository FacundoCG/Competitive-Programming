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

// Segment tree básico para point update y range query de suma

struct objeto{
	ll sum;
	ll maxPrefix, maxSuffix;
	ll ans;
	
	objeto(){
		sum = maxPrefix = maxSuffix = ans = 0;
	}
	
	objeto(ll s, ll mp, ll ms, ll a) : sum(s), maxPrefix(mp), maxSuffix(ms), ans(a){}
};

struct SegmentTree{
    int n;
    vl A;
    vector<objeto> B;
    ll elemNeutro;

    SegmentTree(int N, vl &a) : n(N), A(a){
        B.resize(4*n);
        build(1, 0, n-1);
    }

    objeto combine(objeto x, objeto y){
		objeto res;
		res.sum = x.sum + y.sum;
		res.maxSuffix = max(y.maxSuffix, x.maxSuffix + y.sum);
		res.maxPrefix = max(x.maxPrefix, x.sum + y.maxPrefix);
		res.ans = max(max(x.ans, y.ans), x.maxSuffix + y.maxPrefix);
		return res;
	}
	
    objeto make_data(ll x){
		objeto res;
		res.sum = x;
		res.ans = res.maxPrefix = res.maxSuffix = max(0ll, x);
		return res;
	}

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
        if (l > r) return 0; 
        if (l == tl && r == tr) return B[v].ans;
        int tm = (tl+tr)/2;
        return max(query(2*v, tl, tm, l, min(r, tm)), query(2*v+1, tm+1, tr, max(l, tm+1), r));
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


int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	vl A(n);
	forn(i, n) cin >> A[i];
	
	SegmentTree S(n, A);
	
	forn(_, m){
		ll k, u;
		cin >> k >> u;
		k--;
		S.update(1, 0, n-1, (int) k, u);
		cout << S.B[1].ans << "\n";
	}
	
    return 0;
}
