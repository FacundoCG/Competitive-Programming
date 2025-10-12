#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vl = vector<ll>;
using vb = vector<bool>;

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

struct SegmentTree{
    int n;
    vl A, B;
    ll elemNeutro;

    SegmentTree(int N, vl &a, ll neutro) : n(N), A(a), elemNeutro(neutro){
        B.resize(4*n, elemNeutro);
        build(1, 0, n-1);
    }

    ll combine(ll x, ll y){ return x + y;}
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

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, q;
	cin >> n >> q;
	
	vl A(n);
	forn(i, n) cin >> A[i];
	SegmentTree S(n, A, 0);
	
	forn(_, q){
		int k, l, r;
		cin >> k >> l >> r;
		l--;
		
		if (k == 1) S.update(1, 0, n-1, l, r);
		else {
			r--; 
			cout << S.query(1, 0, n-1, l, r) << "\n";
		}
	}
	
    return 0;
}
