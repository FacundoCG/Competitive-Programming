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

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_, t){
        ll n, k;
        cin >> n >> k;

        vector<ll> cards(n);

        forn(i, n) cin >> cards[i];

        sort(all(cards));

        ll res = 1;
        
        vector<ll> numberOfDecksOfSize(n);
        numberOfDecksOfSize[1] = cards[n-1];

        dforn(i, n-1){
            numberOfDecksOfSize[1] -= cards[i];
            numberOfDecksOfSize[2] = cards[i]; 
        }        

    }
}