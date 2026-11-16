#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for (int i = 0; i < (n); i++)
#define dforn(i, n) for (int i = (n)-1; i >= 0; i--)
#define forsn(i, s, n) for (int i = (s); i < (n); i++)
#define pb push_back
#define SIZE(c) int((c).size())
#define all(c) (c).begin(), (c).end()

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "---------------------" << endl

using ll = long long;
using ii = pair<ll, ll>;
using vii = vector<ii>;
using vvii = vector<vii>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;

const int MAX_N = 1005;
const int MAX_N_OF_CHILDREN = 13;

ll parent[MAX_N], memo[MAX_N][MAX_N];
int nOfChildren[MAX_N], indexAsChild[MAX_N][MAX_N];
int childWithIndex[MAX_N][MAX_N_OF_CHILDREN];

vl adj_tree[MAX_N];
vii adj[MAX_N];

struct Path{
	ll cost;
	vl edgePointsOfPath;
	Path(ll _cost = -1, vl _edgePointsOfPath = vl())
		: cost(_cost), edgePointsOfPath(_edgePointsOfPath){}
};

vector<Path> pathsForLca[MAX_N];

struct LCA{
	int n;
	vvl jump;
	vi distances;
	int LOG_N = 30;
	
	LCA(int _n = 0) : n(_n){
		jump.resize(n, vl(LOG_N, -1));
		distances.resize(n);
		forn(v, n) jump[v][0] = parent[v];
		forsn(j, 1, LOG_N) forn(v, n) if (jump[v][j-1] != -1)
			jump[v][j] = jump[jump[v][j-1]][j-1];
			
		forn(v, n){
			ll currentV = v;
			dforn(j, LOG_N) if (jump[currentV][j] != -1){
				distances[v] += (1 << j);
				currentV = jump[currentV][j];
			}
		}
	}
	
	ll climb(ll v, int k){
		dforn(j, LOG_N) if (k & (1 << j)) v = jump[v][j];
		return v;
	}
	
	int dist(ll v){ return distances[v]; }
	
	ll lca(ll v, ll u){
		if (dist(v) < dist(u)) swap(v, u);
		int d = dist(v)-dist(u);
		v = climb(v, d);
		if (v == u) return v;
		dforn(j, LOG_N) if (jump[v][j] != jump[u][j]){
			v = jump[v][j];
			u = jump[u][j];
		}
		return jump[v][0];
	}
	
	ll distVertexs(ll v, ll u){ return dist(v) + dist(u) - 2*dist(lca(u, v)); }
};

void dfs(ll v, ll p){
	parent[v] = p;
	int id = 0;
	for (ll u : adj_tree[v]) if (u != p) {
		dfs(u, v);
		nOfChildren[v]++;
		childWithIndex[v][id] = (int) u;
		indexAsChild[v][u] = id++;
	}
}

int n, noVertex;
LCA T;

// Quiero saber el hijo de v1 que esta en el camino v1->v2 donde v1 es ancestro de v2
ll findForbiddenChild(ll v1, ll v2){	
	int jump = T.dist(v2)-T.dist(v1)-1;
	return T.climb(v2, jump);
}

bool estanTodosVivos(vl childrenOfV, ll v, ll s){
	for (ll u : childrenOfV) if ((s & (1 << indexAsChild[v][u])) == 0)
		return false;
	return true;
}

ll dp(ll v, ll forbiddenBranch);

ll dp2(ll root, ll s, vl &memo2, map<vl, ll> &bestCostFor){
	if (memo2[s] == -1){
		memo2[s] = 0;
		
		// Proba no usar a ninguno de los hijos restantes (los liberas)
		forn(j, MAX_N_OF_CHILDREN) if ((1 << j) & s){
			ll child = childWithIndex[root][j];
			memo2[s] += dp(child, noVertex);
		}
		
		// Fijate de usar alguna combinacion y movete hacia ese subconjunto
		for (auto [vec, cost] : bestCostFor) if (estanTodosVivos(vec, root, s)){
			ll currentS = s;
			for (ll c : vec) currentS = currentS ^ (1 << indexAsChild[root][c]);
			memo2[s] = max(memo2[s], cost + dp2(root, currentS, memo2, bestCostFor));
		}
	}
	
	return memo2[s];
}

void normalizar(vl &A1){ sort(all(A1)); }

bool isUsingForbiddenChild(vl &children, ll forbiddenChild){
	for (ll c : children) if (c == forbiddenChild) return true;
	return false;
}

// Maximo costo que podes mantener el subarbol de v con aristas extra y sin ciclos pares
ll dp(ll v, ll forbiddenBranch){
	if (forbiddenBranch == v) forbiddenBranch = noVertex; // Ya cuando llegas al edgepoint te desbloqueas
	if (memo[v][forbiddenBranch] == -1){
		ll forbiddenChild = noVertex;
		if (forbiddenBranch != noVertex) forbiddenChild = findForbiddenChild(v, forbiddenBranch);
		
		map<vl, ll> bestCombinationFor;		
		for (auto [cost, edgePoints] : pathsForLca[v]){ // Chequea que nunca uses el hijo de la rama prohibida
			vl currentCombination;
			ll profit = cost;
			for (ll edgePoint : edgePoints){
				ll child = T.climb(edgePoint, T.dist(edgePoint)-T.dist(v)-1);
				currentCombination.pb(child);
				profit += dp(child, edgePoint);
			}
			
			normalizar(currentCombination);
			if (isUsingForbiddenChild(currentCombination, forbiddenChild)) continue;
			bestCombinationFor[currentCombination] = max(bestCombinationFor[currentCombination], profit);			
		}
		
		ll allChildren = (1 << nOfChildren[v]) - 1;
		if (forbiddenChild != noVertex) allChildren = allChildren ^ (1 << indexAsChild[v][forbiddenChild]); // Apaga al hijo prohibido, los otros no tienen restriccion
		
		// Quedate con el mejor subconjunto de combination de children que tenga maximo costo y combine de la mejor forma
		vl memo2(allChildren+1, -1);
		memo[v][forbiddenBranch] = dp2(v, allChildren, memo2, bestCombinationFor);
		if (forbiddenChild != noVertex) memo[v][forbiddenBranch] += dp(forbiddenChild, forbiddenBranch); // Ese subarbol sigue con la restriccion y continua con ella independientemente de las otras elecciones
	}
	
	return memo[v][forbiddenBranch];
}

int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	int m; cin >> n >> m;
	ll totalCost = 0;
	
	forn(_, m){
		ll v, u, cost; cin >> v >> u >> cost;
		v--; u--;
		if (cost == 0){
			adj_tree[v].pb(u);
			adj_tree[u].pb(v);
		} else {
			adj[v].pb(make_pair(u, cost));
			adj[u].pb(make_pair(v, cost));
		}
		totalCost += cost;
	}
	
	dfs(0, -1);
	T = LCA(n);
	
	//~ forn(i, n){
		//~ DBG(i); DBG(parent[i]);
		//~ RAYA;
	//~ }
	
	// Para intentar mantener la arista no debe formar ciclo par 
	forn(v, n) for (auto [u, cost] : adj[v]) if (v < u && T.distVertexs(v, u) % 2 == 0){
		ll lca = T.lca(u, v);
		vl edgePointsOfPath;		
		if (v == lca) edgePointsOfPath = {u};
		else if (u == lca) edgePointsOfPath = {v};
		else edgePointsOfPath = {u, v};
		pathsForLca[lca].pb(Path(cost, edgePointsOfPath));
	}
	
	forn(i, MAX_N) forn(j, MAX_N) memo[i][j] = -1;
	
	noVertex = n;	
	cout << totalCost - dp(0, noVertex) << "\n";
	
	return 0;
}
