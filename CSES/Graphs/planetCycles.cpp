#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
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

enum ESTADO {
	VISITADO_AHORA,
	VISITADO_ANTES,
	NO_VISITADO
};

struct BinaryJumping{
	// Estructura para grafos de sucesores.
	vector<vector<int>> binaryJumping;
	int logk;
	
	// Inicializacion en tiempo O(n*log(max_k))
	BinaryJumping(vector<int> &succ, int max_k){
		logk = (int) log2(max_k);  // Piso.
		binaryJumping.assign(SIZE(succ), vector<int>(logk+1, UNDEFINED));
		
		for(int i=0; i<SIZE(succ); i++){
			binaryJumping[i][0] = succ[i];
		}
		
		for(int it=1; it<=logk; it++){
			for(int i=0; i<SIZE(succ); i++){
				if (binaryJumping[i][it-1] != UNDEFINED) binaryJumping[i][it] = binaryJumping[binaryJumping[i][it-1]][it-1];
			}
		}
	}
	
	// O(log(k)). Donde x es el nodo, k es la distancia de salto.
	int succ_k(int x, int k){
		if (k < 0) return UNDEFINED;

		int it = 0;
		while(k != 0){
			if ((k & 1) == 1){
				if (x != UNDEFINED) x = binaryJumping[x][it];
			}
			k = k >> 1;
			it++;
		}
		
		return x; // x = UNDEFINED significa que te excediste con los saltos
	}	
};

struct SuccesorGraph{
	vi succesors;
	BinaryJumping BJ;
	vector<ESTADO> visited;
	vi representantOfVertex;
	vi rootOfTree;
	vi distanceFromRoot;
	vi distanceFromRepresentant;
	vi lengthOfCycleAt;
	vector<vi> adjList;
	
	
	SuccesorGraph(vi &succ) : succesors(succ), BJ(succ, SIZE(succ)){
		visited.resize(SIZE(succ), NO_VISITADO);
		representantOfVertex.resize(SIZE(succ), UNDEFINED);
		rootOfTree.resize(SIZE(succ), UNDEFINED);
		distanceFromRoot.resize(SIZE(succ), UNDEFINED);
		distanceFromRepresentant.resize(SIZE(succ), UNDEFINED);
		lengthOfCycleAt.resize(SIZE(succ), UNDEFINED);	
		adjList.resize(SIZE(succ));
		forn(i, SIZE(succ)) adjList[succ[i]].pb(i);
		findCycles();
	}
	
	int distanceInTheCycle(int v, int u){
		// Sé que los dos vértices pertenecen al mismo ciclo y quiero calcular cuál es su distancia
		int res = distanceFromRepresentant[u] - distanceFromRepresentant[v]; // v -> ... -> u
		if (distanceFromRepresentant[u] < distanceFromRepresentant[v]){ // v -> ... inicio ciclo -> ... -> u
			int longitudCiclo = lengthOfCycleAt[representantOfVertex[v]];
			res = distanceFromRepresentant[u] + (longitudCiclo - distanceFromRepresentant[v]) + 1; 
		} 
	
		return res;
	}
	
	int distanceBetween(int v, int u){
		int rootOfV = rootOfTree[v], rootOfU = rootOfTree[u];
		int res;
		
		if (representantOfVertex[rootOfV] != representantOfVertex[rootOfU]) res = UNDEFINED; // Si no están en el mismo ciclo
		else if (rootOfV == rootOfU){ // Están en el mismo árbol		
			int jumps = distanceFromRoot[v] - distanceFromRoot[u];
			int vertexJumpt = BJ.succ_k(v, jumps);
			if (vertexJumpt != u) jumps = -1;
			res = jumps;
		} else if (representantOfVertex[u] == UNDEFINED) res = UNDEFINED; // u y v están en arboles distintos
		else res = distanceFromRoot[v] + distanceInTheCycle(rootOfV, rootOfU);
		
		return res;
	}
	
	void dfs(int v, vector<int> &representantsOfCycles){
		visited[v] = VISITADO_AHORA;
		
		if (visited[succesors[v]] == VISITADO_AHORA){
			representantsOfCycles.pb(succesors[v]);
			visited[v] = VISITADO_ANTES;
			return ;
		} else if (visited[succesors[v]] == VISITADO_ANTES){
			visited[v] = VISITADO_ANTES;
			return ;
		}
		
		dfs(succesors[v], representantsOfCycles);
		visited[v] = VISITADO_ANTES;
	}
	
	void markCycle(int v){
		int lengthOfCycle = 0;
		int startCycle = v;
		
		while (representantOfVertex[v] == UNDEFINED){
			representantOfVertex[v] = startCycle;
			distanceFromRepresentant[v] = lengthOfCycle;
			v = succesors[v];
			lengthOfCycle++;
		}
		
		lengthOfCycleAt[startCycle] = lengthOfCycle - 1;
	}
	
	void buildTree(int v, int currentDepth, int root){
		rootOfTree[v] = root;
		distanceFromRoot[v] = currentDepth;
		
		for (int u : adjList[v]){
			if (representantOfVertex[u] != UNDEFINED) continue;
			buildTree(u, currentDepth+1, root);
		}
	}
	
	
	void findCycles(){
		vector<int> representantsOfCycles;
		
		forn(i, SIZE(succesors)){
			if (visited[i] == NO_VISITADO) dfs(i, representantsOfCycles);
		}
		
		for (int v : representantsOfCycles) markCycle(v);
		
		forn(i, SIZE(succesors)){
			if (representantOfVertex[i] != UNDEFINED) buildTree(i, 0, i);
		}
	}
};

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n;
	cin >> n;
	
	vi succ(n);
	forn(i, n) cin >> succ[i];
	forn(i, n) succ[i]--;
	
	SuccesorGraph G(succ);
	
	forn(i, n){
		int root = G.rootOfTree[i];
		int cycle = G.representantOfVertex[root];
		cout << G.distanceFromRoot[i] + G.lengthOfCycleAt[cycle] + 1 << " ";
	}
	
	cout << "\n";
		
    return 0;
}
