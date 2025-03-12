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
bool isSubTree;
int x;

void calculateSubtreeXors(vector<vector<int>> &adjList, vector<int> &subtreeXOR, vector<int> &values, int v, int parent){
    subtreeXOR[v] = values[v];

    for (int u : adjList[v]){
        if (u != parent){
            calculateSubtreeXors(adjList, subtreeXOR, values, u, v);
            subtreeXOR[v] ^= subtreeXOR[u];
        }
    }
}

bool existsWayOfRemovingTwoEdges(vector<vector<int>> &adjList, vector<int> &subtreeXOR, int v, int parent, bool existsAncestor){
    bool res = false;

    if (existsAncestor && subtreeXOR[v] == x){ // If I have already checked that 
        res = true;
    } else if (isSubTree && subtreeXOR[v] == x){
        res = true;
    }

    if (subtreeXOR[v] == 0){ // If exists a node which subtree has value 0, I update that exists an ancestor
        existsAncestor = true;
    }

    for (int u : adjList[v]){
        if (u != parent){
            res |= existsWayOfRemovingTwoEdges(adjList, subtreeXOR, u, v, existsAncestor);
        }
    }

    if (subtreeXOR[v] == x){
        isSubTree = true;
    }

    return res;
}

void solve(vector<vector<int>> &adjList, vector<int> &values, vector<int> &subtreeXOR, int k){
    int xorSum = 0;
    int n = adjList.size();

    forn(i, n) xorSum ^= values[i];

    if (xorSum == 0){ // If the XOR of all the values is 0, it means that I can remove any edge and satisfy the condition
        cout << "YES" << "\n";
        return;
    } else if (k == 2){
        cout << "NO" << "\n"; // I can remove just one edge but it won't satisfy the condition
        return;
    } 

    isSubTree = false;
    x = xorSum;

    // I calculate the subtree of XORs for all the vertices
    calculateSubtreeXors(adjList, subtreeXOR, values, 0, 0);

    // Now I need to check if exists a way to remove two edges and satisfy the condition
    bool existsSolution = existsWayOfRemovingTwoEdges(adjList, subtreeXOR, 0, 0, false); 
    string res = "NO";

    if (existsSolution){
        res = "YES";
    }

    cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_, t){
        int n, k;
        cin >> n >> k;

        vector<int> values(n);
        vector<vector<int>> adjList(n);
        vector<int> subtreeXOR(n);

        forn(i, n) cin >> values[i];

        forn(i, n-1){
            int u, v;
            cin >> u >> v;
            
            u--;
            v--;

            adjList[u].pb(v);
            adjList[v].pb(u);
        }

        solve(adjList, values, subtreeXOR, k);
    }
}