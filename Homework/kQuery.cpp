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
using ii = pair<ll,ll>;
using vii = vector<ii>;
using vvii = vector<vii>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
//~ const int MAX_N = 1e5 + 1;
int MOD = 1e9 + 7;
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

struct Query{ 
	int k, idx, sign; 
	Query(int K, int IDX, int SIGN) : k(K), idx(IDX), sign(SIGN){}
};

struct SegmentTree{
    int n = 1;
    vi A, B;
    int elemNeutro;

    SegmentTree(int N, vi &a, int neutro) : A(a), elemNeutro(neutro){
        while (n < N) n <<= 1;
        B.resize(2*n, elemNeutro);
        build();
    }

    int combine(int x, int y){ return x + y;}
    int make_data(int x){ return x;}

    void build(){ // Vertice actual y rango [tl, tr] que indica este vertice
        forn(i, SIZE(A)) B[n+i] = make_data(A[i]);
        dforsn(i, 1, n) B[i] = combine(B[2*i], B[2*i+1]);
    }

    int query(int l, int r){
        int res_left = elemNeutro, res_right = elemNeutro;
        l += n; r += n;

        while (l <= r){
            if (l & 1) res_left = combine(res_left, B[l++]);
            if (!(r & 1)) res_right = combine(B[r--], res_right);
            l >>= 1;
            r >>= 1;
        }

        return combine(res_left, res_right);
    }

    void update(int pos, int new_val){
		A[pos] = make_data(new_val);
		pos += n;
		B[pos] = make_data(new_val);
		while (pos > 1){
        pos /= 2;
        B[pos] = combine(B[2*pos], B[2*pos+1]);
		}
	}
};

// Voy a calcular #elementos <= k para cada query
vi kquery(vi &A, vector<vector<Query>> &queries, int nOfQueries){
	set<int> s(all(A));
	map<int, int> posOf;
	int curPos = 0;
	for (int x : s) posOf[x] = curPos++;
	
	vi res(nOfQueries), B(SIZE(posOf), 0);
	SegmentTree T(SIZE(B), B, 0);
	forsn(r, 1, SIZE(A)){		
		int pos = posOf[A[r]];
		T.update(pos, T.A[pos]+1);
		for (const auto &q : queries[r]) {
			auto it = s.lower_bound(q.k+1); it--; // Primer elemento <= k, existe siempre ya que k > 0 y s tiene a 0 
			int posOfK = posOf[*it]; 
			res[q.idx] += T.query(0, posOfK)*q.sign;
		} 
	}
	return res;
}

void solve(){
	int n; cin >> n;
	vi A(n+1); forsn(i, 1, n+1) cin >> A[i];
	
	int q; cin >> q;
	vector<vector<Query>> queries(n+1);
	
	forn(i, q){
		int l, r, k; cin >> l >> r >> k;
		queries[r].pb(Query(k, i, 1));
		queries[l-1].pb(Query(k, i, -1));
	}
	
	vi res = kquery(A, queries, q);
	forn(i, SIZE(res)) res[i] *= -1;
	forsn(r, 1, SIZE(A)) for (const auto &qu : queries[r]) res[qu.idx] += r*qu.sign; // Sumo el tamanio del intervalo
	forn(i, SIZE(res)) cout << res[i] << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t = 1;
	//~ cin >> t;
	forn(_, t) solve();
	
	return 0;
}
