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

struct SegmentTreeLazy{
    int n;
    vl A, B;
    ll elemNeutro;

    SegmentTreeLazy(int N, vl &a, ll neutro) : n(N), A(a), elemNeutro(neutro){
        B.resize(4*n, elemNeutro);
        build(1, 0, n-1);
    }

    void build(int v, int tl, int tr){ // Vértice actual y rango [tl, tr] que indica este vértice
        if (tl == tr) B[v] = A[tl]; // Cuando llego a una hoja, el valor es el mismo elemento
        else {
            int tm = (tl + tr)/2;
            build(2*v, tl, tm);
            build(2*v+1, tm+1, tr); 
        }
    }

    ll query(int v, int tl, int tr, int pos){
        if (tl == tr) return B[v];
        int tm = (tl+tr)/2;
        if (pos <= tm) return B[v] + query(2*v, tl, tm, pos);
        return B[v] + query(2*v+1, tm+1, tr, pos);
    }

    void update(int v, int tl, int tr, int l, int r, ll add){
        if (l > r) return ;
        if (l == tl && r == tr) B[v] += add;
        else {
            int tm = (tl + tr)/2;
            update(2*v, tl, tm, l, min(r, tm), add);
            update(2*v+1, tm+1, tr, max(l, tm+1), r , add);
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
	
	SegmentTreeLazy S(n, A, 0);
	
	forn(_, q){
		int k;
		cin >> k;
		
		if (k == 1){
			int a, b, u;
			cin >> a >> b >> u;
			a--; b--;
			S.update(1, 0, n-1, a, b, u);
		} else {
			int pos;
			cin >> pos;
			pos--;
			cout << S.query(1, 0, n-1, pos) << "\n";
		}
	}

    return 0;
}
