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
 
 
// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18
 
// ############################################################### //
vector<vector<int>> adjList;
vector<bool> visited;
vector<vector<int>> nodesPerLevel;
vector<int> maxDepthFromNode;
int lastLevel;
 
void calculateLevelFrom(int v, int currentHeight){
    nodesPerLevel[currentHeight].pb(v);
    visited[v] = true;
 
    for (int u : adjList[v]){
        if (!visited[u]){
            calculateLevelFrom(u, currentHeight+1);
        }
    }
}
 
void calculateMaxDepth(int v, int currentDepth, vector<priority_queue<int>> &bestDepthsPerNode){
    maxDepthFromNode[v] = 0;
    visited[v] = true;
 
    for (int u : adjList[v]){
        if (!visited[u]){
            calculateMaxDepth(u, currentDepth+1, bestDepthsPerNode);
            maxDepthFromNode[v] = max(maxDepthFromNode[v], maxDepthFromNode[u]+1);
            bestDepthsPerNode[v].push(maxDepthFromNode[u]);
        }
    }
}
 
int solve(vector<int> &memo, vector<priority_queue<int>> &bestDepthsPerNode){
    // The complexity time is O(|E|) because I iterate over all the neighborhoods of all the vertices
 
    dforn(i, lastLevel+1){
       for (int u : nodesPerLevel[i]){
            visited[u] = true;
            memo[u] = maxDepthFromNode[u]; // Originally I think that the best result is choose the longest branch
 
            for (int v : adjList[u]){
                if (visited[v]){
                    memo[u] = max(memo[u], memo[v]); // I try one of the old results
                }
            }
 
            if (bestDepthsPerNode[u].size() > 1){ // I choose my two longest branches and try connecting them
                int a = bestDepthsPerNode[u].top();
                bestDepthsPerNode[u].pop();
                int b = bestDepthsPerNode[u].top();
                memo[u] = max(memo[u], a + b + 2);
            }
 
       } 
    }
 
    return memo[0]; // Return the max amount of matching for a rooted tree in 0
}
 
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
 
    adjList.resize(n);
    visited.resize(n);
    nodesPerLevel.resize(n);
    maxDepthFromNode.resize(n);
    vector<priority_queue<int>> bestDepthsPerNode(n);
 
    forn(i,n-1){
        int w, v;
        cin >> w >> v;
        w-=1;
        v-=1;
 
        adjList[w].pb(v);
        adjList[v].pb(w);
    }
 
    calculateLevelFrom(0, 0);
    vector<int> memo(n);
 
    forn(i, n){
        visited[i] = false;
    }
 
    dforn(i, n){
        if (!nodesPerLevel[i].empty()){
            lastLevel = i;
            break;
        }
    }
 
    calculateMaxDepth(0, 0, bestDepthsPerNode);
 
    int res = solve(memo, bestDepthsPerNode);
    cout << res << "\n";
}