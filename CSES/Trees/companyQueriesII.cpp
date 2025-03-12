#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

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

// ############################################################### //

vector<int> levelOfNode;

int rightBinarySearch(int start, int end, int currentNode, int desiredLevel, vector<vector<int>> &memoAncestors){
    int l = start - 1;
    int r = end + 1;
    
    while (r - l > 1){
        int mid = (l + r)/2;
        int nodeToJump = memoAncestors[currentNode][mid];
 
        if (nodeToJump != UNDEFINED && levelOfNode[nodeToJump] >= desiredLevel){
            l = mid;
        } else {
            r = mid;
        }
    }
 
    return l; // l es el ultimo elemento que cumple P(X)
}

int rightBinarySearchForLCA(int start, int end, int v, int w, vector<vector<int>> &memoAncestors){
    int l = start - 1;
    int r = end + 1;
    
    while (r - l > 1){
        int mid = (l + r)/2;
        int nodeToJumpForV = memoAncestors[v][mid];
        int nodeToJumpForW = memoAncestors[w][mid];
 
        if (nodeToJumpForV != UNDEFINED && nodeToJumpForV != nodeToJumpForW){
            l = mid;
        } else {
            r = mid;
        }
    }
 
    return l; // l es el ultimo elemento que cumple P(X)
}

int findTheAncestorFor(int v, int numberOfJumps, vector<vector<int>> &memoAncestors){
    int currentLevel = levelOfNode[v];
    int levelToFind = currentLevel - numberOfJumps;
    int currentNode = v;
    int k = memoAncestors[0].size();
    
    while (currentLevel != levelToFind){
        int bestNewLevel = rightBinarySearch(0, k-1, currentNode, levelToFind, memoAncestors);
        currentNode = memoAncestors[currentNode][bestNewLevel];
        currentLevel = levelOfNode[currentNode];
    }
 
    return currentNode;
}

int findTheLCA(int v, int w, vector<vector<int>> &memoAncestors){
    int jumps = abs(levelOfNode[v] - levelOfNode[w]);

    if (levelOfNode[v] < levelOfNode[w]){
        w = findTheAncestorFor(w, jumps, memoAncestors);
    } else if (levelOfNode[v] > levelOfNode[w]){
        v = findTheAncestorFor(v, jumps, memoAncestors);
    }

    if (v == w){
        return v;
    }

    int k = memoAncestors[0].size();

    while (memoAncestors[v][0] != memoAncestors[w][0]){
        int bestNewLevel = rightBinarySearchForLCA(0, k-1, v, w, memoAncestors);
        v = memoAncestors[v][bestNewLevel];
        w = memoAncestors[w][bestNewLevel];
    }

    int lca = memoAncestors[v][0];

    return lca;
}

void calculateParents(int v, vector<vector<int>> &adjList, vector<bool> &visited, vector<vector<int>> &memoAncestors, int currentDepth){
    visited[v] = true;
    levelOfNode[v] = currentDepth;

    for (int u : adjList[v]){
        if (!visited[u]){
            memoAncestors[u][0] = v;
            calculateParents(u, adjList, visited, memoAncestors, currentDepth+1);
        }
    }
}

void precomputeAncestors(vector<vector<int>> &adjList, vector<vector<int>> &memoAncestors){
    vector<bool> visited(adjList.size(), false);
    calculateParents(0, adjList, visited, memoAncestors, 0);
    int k = log2(adjList.size())+1;

    forn(i, adjList.size()) visited[i] = false;
    visited[0] = true;

    queue<int> toVisit;
    toVisit.push(0);

    while (!toVisit.empty()){
        int v = toVisit.front();
        toVisit.pop();

        for (int u : adjList[v]){
            if (!visited[u]){
                toVisit.push(u);
                visited[u] = true;

                forsn(i, 1, k){
                    if (memoAncestors[u][i-1] != UNDEFINED){
                        memoAncestors[u][i] = memoAncestors[memoAncestors[u][i-1]][i-1];
                    }
                }
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, q;
    cin >> n >> q;

    int k = log2(n) + 1;

    vector<vector<int>> adjList(n);
    vector<vector<int>> memoAncestors(n, vector<int>(k, UNDEFINED));
    levelOfNode.resize(n);

    forn(i, n-1){
        int v;
        cin >> v;
        v--;

        adjList[v].pb(i+1);
        adjList[i+1].pb(v);
    }
    
    precomputeAncestors(adjList, memoAncestors); 

    forn(_, q){
        int v, w;
        cin >> v >> w;
        v--; w--;

        int lca = findTheLCA(v, w, memoAncestors) + 1;
        cout << lca << "\n";
    }
}