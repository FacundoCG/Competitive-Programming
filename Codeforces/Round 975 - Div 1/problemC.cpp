#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl
#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define all(c) (c).begin(),(c).end()

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


// ############################################################### //

int heightDfs(vector<vector<int>> &adjList, int v, int parent){
    int res = 1;

    for (int u : adjList[v]){
        if (u != parent){
            res = max(res, heightDfs(adjList, u, v) + 1);
        }
    }

    return res;
}

void calculateNodesPerLevel(vector<vector<int>> &adjList, int v, int currentLevel, int parent, vector<int> &nodesPerLevel){
    nodesPerLevel[currentLevel]++;

    for (int u : adjList[v]){
        if (u != parent){
            calculateNodesPerLevel(adjList, u, currentLevel+1, v, nodesPerLevel);
        }
    }
}

void calculateMaxDepthOfNode(vector<vector<int>> &adjList, int v, int currentLevel, int parent, vector<int> &maxDepthOfNode){
    maxDepthOfNode[v] = currentLevel;

    for (int u : adjList[v]){
        if (u != parent){
            calculateMaxDepthOfNode(adjList, u, currentLevel+1, v, maxDepthOfNode);
            maxDepthOfNode[v] = max(maxDepthOfNode[v], maxDepthOfNode[u]);
        }
    }
}

void solve(vector<vector<int>> &adjList, int heightTree){
    int n = adjList.size(); // Number of vertices
    int res = n-1;  

    vector<int> nodesPerLevel(heightTree+1);
    vector<int> nodesMaxDepthLessThan(heightTree+1);
    vector<int> maxDepthOfNode(n);

    // I will calculate the amount of nodes at depth i
    calculateNodesPerLevel(adjList, 0, 1, 0, nodesPerLevel);

    // I will calculate the maxDepth for a given node.
    calculateMaxDepthOfNode(adjList, 0, 1, 0, maxDepthOfNode); //

    // I will have a prefix for: the amount of nodes between level 1 and level i
    vector<int> prefixNodesPerLevel(heightTree+1);

    forsn(i,1,heightTree+1){
        prefixNodesPerLevel[i] = prefixNodesPerLevel[i-1] + nodesPerLevel[i];
    }

    // I calculate the number of nodes which depth is less or equal than i
    forn(i, n){
        nodesMaxDepthLessThan[maxDepthOfNode[i]]++;
    }

    // Now I calculate the prefix sum of the last one
    forsn(i,1,heightTree+1){
        nodesMaxDepthLessThan[i] += nodesMaxDepthLessThan[i-1];
    }

    forsn(i, 1, heightTree+1){
        int nodesToEliminate = n - prefixNodesPerLevel[i]; // I calculate how many nodes are above depth i
        nodesToEliminate += nodesMaxDepthLessThan[i-1]; // I calculate how many nodes belong to branchs whose max depth is less than i
        res = min(res, nodesToEliminate);
    }

    cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_, t){
        int n;
        cin >> n;

        vector<vector<int>> adjList(n);

        forn(_, n-1){
            int u, v;
            cin >> u >> v;
            adjList[u-1].pb(v-1);
            adjList[v-1].pb(u-1);
        }

        int heightTree = heightDfs(adjList, 0, 0);
        solve(adjList, heightTree);
    }
}