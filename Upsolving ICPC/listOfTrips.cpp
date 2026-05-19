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
using vvvvl = vector<vvvl>;
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

struct HLD{
    int n, root, curPos = 0;
    vi parent, depth, head, pos, sz;
    vvi adj;

    HLD(vvi ADJ, int ROOT = 0) : n(SIZE(ADJ)), root(ROOT), adj(ADJ) {
        parent.assign(n, -1);
        depth.assign(n, 0);
        head.assign(n, 0);
        pos.assign(n, 0);
        sz.assign(n, 0);

        parent[root] = root;
        dfs(root);
        decompose(root, root);
    }

    void dfs(int v){
        sz[v] = 1;
        for (int &u : adj[v]){
            parent[u] = v; depth[u] = depth[v] + 1;
            adj[u].erase(find(all(adj[u]), v)); 
            dfs(u); sz[v] += sz[u];
            if (sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
        }
    }

    void decompose(int v, int h){
        head[v] = h; pos[v] = curPos++;
        for (int u : adj[v]) decompose(u, u == adj[v][0] ? h : u);
    }

    pair<int,int> subtree(int v){ return {pos[v], pos[v] + sz[v] - 1}; }
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
 
    int combine(int x, int y){ return max(x, y);}
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
};


// Modificar segun que funcion estes aplicando
int query(int a, int b, HLD &H, SegmentTree &T){
	int res = 0;
    for (; H.head[a] != H.head[b]; b = H.parent[H.head[b]]){
		if (H.depth[H.head[a]] > H.depth[H.head[b]]) swap(a, b);
        int query_heavy_path = T.query(H.pos[H.head[b]], H.pos[b]);
        res = res + query_heavy_path;
    }
    
    if (H.depth[a] > H.depth[b]) swap(a, b);
    int last_query_heavy_path = T.query(H.pos[a], H.pos[b]);
    return res = res + last_query_heavy_path;
}

void dfs(int v, int p, int d, vvi &adj_tree, vvi &adj, vi &minDepth, vi &depth){
	depth[v] = d;
	for (int u : adj[v]) if (u != p){
		if (depth[u] != UNDEFINED) minDepth[v] = min(minDepth[v], depth[u]);
		else {
			adj_tree[v].pb(u); adj_tree[u].pb(v);
			dfs(u, v, d+1, adj_tree, adj, minDepth, depth);
			minDepth[v] = min(minDepth[v], minDepth[u]);
		}
	}
}

void solve(){
	int n, m, q; cin >> n >> m >> q;
	vvi adj(n);
	
	forn(_, m){
		int v, u; cin >> v >> u; v--; u--;
		adj[v].pb(u);
		adj[u].pb(v);
	}
	
	vvi adj_tree(n);
	vi minDepth(n, INF), depth(n, UNDEFINED);
	dfs(0, -1, 0, adj_tree, adj, minDepth, depth);
	HLD H(adj_tree, 0);
	
	vi A(n, 0);
	forn(i, n) A[H.pos[i]] = (depth[i] >= minDepth[i]);
	
	SegmentTree T(n, A, 0);	
	forn(_, q){
		int s, e; cin >> s >> e; s--; e--;
		cout << (query(s, e, H, T) == 0 ? "YES" : "NO") << "\n";
	}
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
