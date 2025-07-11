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
#define SIZE(c) int((c).size())

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
vector<int> maxDepthFrom;
vector<priority_queue<int>> bestDepthsFrom;
vector<bool> visited;
vector<int> parent;
 
void calculateMaxDepth(int v, int currentDistanceFromRoot){
    visited[v] = true;
    maxDepthFrom[v] = 0;
 
    for (int u : adjList[v]){
        if (!visited[u]){
            parent[u] = v;
            calculateMaxDepth(u, currentDistanceFromRoot+1);
            maxDepthFrom[v] = max(maxDepthFrom[v], maxDepthFrom[u] + 1);
            bestDepthsFrom[v].push(maxDepthFrom[u]+1);
        }
    }
}
 
 
void solve(int n){
	visited.assign(n, false);
    queue<int> toVisit;
    toVisit.push(0);
 
    while (!toVisit.empty()){
        int v = toVisit.front();
        toVisit.pop();
        int myParent = parent[v];
 
        if (v != 0){
			DBG(v);
            if (SIZE(bestDepthsFrom[myParent]) > 1) { // If I have two branches to choose at least
                int a = bestDepthsFrom[myParent].top();
                bestDepthsFrom[myParent].pop();
                if (a != maxDepthFrom[v] + 1) bestDepthsFrom[v].push(a+1);
                else bestDepthsFrom[v].push(bestDepthsFrom[myParent].top()+1);					
                bestDepthsFrom[myParent].push(a);
            } else {
                bestDepthsFrom[v].push(1);
            }
        }
 
        for (int u : adjList[v]){
            if (!visited[u]){
                visited[u] = true;
                toVisit.push(u);
            }
        }
    }
    
    forn(i, n) cout << bestDepthsFrom[i].top() << " ";
    cout << "\n";
}
 
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
 
    adjList.resize(n);
    maxDepthFrom.resize(n); // This will tell me the longest branch starting from vertex i
    bestDepthsFrom.resize(n); // This will tell me if I have more than one longest branch
    visited.resize(n); 
    parent.resize(n);
    parent[0] = UNDEFINED;
 
    forn(i,n-1){
        int w, v;
        cin >> w >> v;
        w--; v--;
        adjList[w].pb(v);
        adjList[v].pb(w);
    }
 
    forn(i, n) bestDepthsFrom[i].push(0);
    calculateMaxDepth(0, 0);
    solve(n);
}
