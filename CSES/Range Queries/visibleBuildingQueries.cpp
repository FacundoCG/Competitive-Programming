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

int leftBinarySearch(int start, int end, vi &A, int x){
    int l = start - 1; 
    int r = end + 1; 

    while(r - l > 1) { 
        //int mid = (l + r) / 2;
        int mid = l + (r-l)/2;

        if(!(A[mid] > x)) l = mid;
        else r = mid;
    }
    
    if (r < start || r > end || !(A[r] > x)) r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
    return r; // r es el primer elemento que cumple P(X)
}

struct SegmentTree{
    int n;
    vi A;
    pair<int, int> elemNeutro;
    vector<vi> B;

    SegmentTree(int N, vi &a, pair<int, int> neutro) : n(N), A(a), elemNeutro(neutro){
        B.resize(4*n);
        build(1, 0, n-1);
    }

    pair<int, int> f(int v, int x){
		pair<int, int> res = {0, B[v].back()};
		int j = leftBinarySearch(0, SIZE(B[v])-1, B[v], x);
		if (j != UNDEFINED) res.fst += SIZE(B[v]) - j; // Quiero ver cuál es el primer elemento de B[v] que es > x		
		return res;
    }
    
    pair<int, int> combine(pair<int, int> p1, pair<int, int> p2){
		return {p1.fst + p2.fst, max(p1.snd, p2.snd)};
	}

    void build(int v, int tl, int tr){ // Vértice actual y rango [tl, tr] que indica este vértice
		B[v].pb(A[tl]);
        forsn(i, tl+1, tr+1) {
			if (A[i] > B[v].back()) B[v].pb(A[i]);
        }
        
        if (tl < tr) {
            int tm = (tl + tr)/2;
            build(2*v, tl, tm);
            build(2*v+1, tm+1, tr); 
        }
    }

    // query(1, 0, n-1, l, r)
    pair<int, int> query(int v, int tl, int tr, int l, int r, int x){
        if (l > r) return elemNeutro; 
        if (l == tl && r == tr) return f(v, x); // Respondo la query en este rango
        int tm = (tl+tr)/2;
        
        pair<int, int> res = query(2*v, tl, tm, l, min(r, tm), x);
        res = combine(res, query(2*v+1, tm+1, tr, max(l, tm+1), r, max(res.snd, x)));
        return res;
    }
};


int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, q;
	cin >> n >> q;
	
	vi A(n);
	forn(i, n) cin >> A[i];
	
	SegmentTree T(n, A, {0, 0});
	
	forn(_, q){
		int l, r;
		cin >> l >> r;
		l--; r--;
		cout << T.query(1, 0, n-1, l, r, 0).fst << "\n";
	}
	
    return 0;
}
