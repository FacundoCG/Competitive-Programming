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
	int k, pos, idx, sign; 
	Query(int K, int POS, int IDX, int SIGN) : k(K), pos(POS), idx(IDX), sign(SIGN){}
	
	bool operator < (const Query &other) const { return k < other.k; }
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

vi kquery(vi &A, vector<Query> queries, int nOfQueries){
	vii C(SIZE(A));
	forsn(i, 1, SIZE(A)) C[i] = {A[i], i};
	sort(all(C));
	sort(all(queries));
	
	vi res(nOfQueries), B(SIZE(A), 0);
	SegmentTree T(SIZE(B), B, 0);
	
	int pos = 1;
	for (const auto &q : queries){
		while (pos < SIZE(C) && C[pos].fst <= q.k){
			int index = C[pos].snd; T.update(index, T.A[index]+1);
			pos++;
		}
		res[q.idx] += q.sign*T.query(0, q.pos);
	}
	
	return res;
}

void solve(){
	int n, q; cin >> n >> q;
	vi A(n+1); forsn(i, 1, n+1) cin >> A[i];
	vector<Query> queries;
	
	forn(i, q){
		int l, r, k1, k2; cin >> l >> r >> k1 >> k2;		
		queries.pb(Query(k2, r, i, 1));
		queries.pb(Query(k2, l-1, i, -1));
		queries.pb(Query(k1-1, r, i, -1));
		queries.pb(Query(k1-1, l-1, i, 1));
	}
	
	vi res = kquery(A, queries, q);
	forn(i, q) cout << res[i] << "\n";
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
