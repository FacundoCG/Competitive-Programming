#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> edge;

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
#define forall(i,c) for(auto i=(c).begin(), i != (c).end(); i++)
#define dforall(i,c) for(auto i=(c).rbegin(), i != (c).rend(); i--)

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

// Show pair
template <typename T1, typename T2>
ostream & operator <<(ostream &os, const pair<T1, T2> &p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
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


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

class DisjSet {
    int *rank, *parent, n;

public:
    DisjSet(int n){
        rank = new int[n];
        parent = new int[n];
        this->n = n;
        makeSet();
    }

    void makeSet(){
        for (int i = 0; i < n; i++){
            parent[i] = i;
        }
    }

    // Find set (representative) of a given x
    int find(int x){
        if (parent[x] != x){ // If the element isn't the representative of the set (the root), I do recursion over its father to find it. In addition, I put this element as a child of the root.
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void Union(int x, int y){
        // Find the representatives of each element
        int xset = find(x);
        int yset = find(y); 

        // If they have the same representative, they belong to the same set. Then, I don't do anything

        if (xset == yset){
            return;
        } 

        if (rank[xset] < rank[yset]){ // If the height of the tree of the first element is less than the height of the tree of the second element, then I put the first element as a child of the root of the other tree. Therefore, the resulting tree won't have a higher height than the older one.
            parent[xset] = yset;
        } else if (rank[xset] > rank[yset]){ // Idem 
            parent[yset] = xset;
        } else { // If they have the same height, the resulting tree will have a height incremented in one
             parent[xset] = yset;
             rank[yset]++;
        }    
    }
};

// ############################################################### //



vector<vector<pair<int,int>>> kruskal(int n, vector<pair<int, edge>> &edges){
    vector<vector<pair<int,int>>> agm(n);
    DisjSet trees(n);
    
    for (auto &p: edges){
        edge e = p.second;
        int weight = p.first;
        int v = e.first;
        int u = e.second;

        if (trees.find(u) != trees.find(v)){ 
            trees.Union(v, u);
            agm[u].pb({weight,v});
            agm[v].pb({weight,u});
        }
    }

    return agm;
}

void bfsForMiniMaxPath(vector<vector<pair<int,int>>> &mst, vector<vector<ll>> &miniMaxPath, int currentVertex){
    int n = mst.size();
    vector<bool> visited(n, false);
    vector<int> parents(n);
    queue<int> toProcess;
    toProcess.push(currentVertex);

    miniMaxPath[currentVertex][currentVertex] = 0;
    visited[currentVertex] = true;
    
    while (!toProcess.empty()){
        int v = toProcess.front();
        toProcess.pop();

        forn(i, mst[v].size()){
            int w = mst[v][i].second;
            int weight = mst[v][i].first;

            if (!visited[w]){
                visited[w] = true;
                toProcess.push(w);
                parents[w] = max(weight, parents[v]);
            }
        }
    }

    forn(i, n){
        miniMaxPath[currentVertex][i] = parents[i];
    }
}

void updateLatencies (vector<ll> &currentLatencies, vector<vector<ll>> &miniMaxPath, int newServer){
    forn(i, currentLatencies.size()){
        currentLatencies[i] = min(currentLatencies[i], miniMaxPath[i][newServer]);
    }
}

void solve(set<int> &housesWhichNeedInternet, vector<pair<int, edge>> &edges, int n){
    // The minimum overall latency for each k = 1,...,n
    vector<ll> res(n);

    // Variables
    int p = housesWhichNeedInternet.size(); 
    set<int> bestServers;
    vector<ll> currentLatencies(n,LINF);

    // Firstly, I need to generate the minimum spanning tree. I sort the edges before that
    sort(all(edges));
    vector<vector<pair<int, int>>> mst = kruskal(n, edges); 

    // Now I need to find the mini max path for each node agains the others 
    vector<vector<ll>> miniMaxPath(n, vector<ll>(n));

    forn(i,n){
        // I calculate the mini max path for each node
        bfsForMiniMaxPath(mst, miniMaxPath, i);
    }

    // Calculate the res when it isn't 0
    forn(i,p){
        ll newLatency = LINF;
        int newServer = UNDEFINED;

        forn(j,n){
            // We calcule the overall minimum latency if we add j as server
            ll overAllLatency = 0;

            if (esta(j, bestServers)){
                continue;
            }

            for(auto p : housesWhichNeedInternet){
                overAllLatency += min(miniMaxPath[p][j], currentLatencies[p]);
            }

            if (overAllLatency < newLatency){
                newServer = j;
                newLatency = overAllLatency;
            }
        }

        res[i] = newLatency;
        bestServers.insert(newServer);

        if (esta(newServer, housesWhichNeedInternet)){
            housesWhichNeedInternet.erase(newServer);
        }

        updateLatencies(currentLatencies, miniMaxPath, newServer);
    }

    // Print the res
    forn(i,n){
        cout << res[i] << " ";
    } 

    cout << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_,t){
        int n, m, p;
        cin >> n >> m >> p;

        set<int> housesWhichNeedInternet;
        vector<pair<int, edge>> edges;

        forn(_,p){
            int h;
            cin >> h;
            housesWhichNeedInternet.insert(h-1);
        }

        forn(_,m){
            int v,u, weight;
            cin >> v >> u >> weight;
            edge e = {v-1,u-1};
            edges.pb({weight, e});
        } 

        solve(housesWhichNeedInternet, edges, n);
    }
}