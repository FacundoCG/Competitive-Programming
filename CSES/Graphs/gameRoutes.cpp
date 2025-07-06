#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> edge;
const ll INF = LLONG_MAX;
const int NEG_INF = INT_MIN;
const int MOD = 1e9 + 7;

ll addMod(ll a, ll b, ll m = MOD){
    int res = ((a % m) + (b % m)) % m;
    return res;
}

void topologicalSortUtil(int v, vector<vector<int>> &adjList, vector<bool> &visited, stack<int> &stack){
    visited[v] = true;
 
    for (int i = 0; i < adjList[v].size(); i++){
        int w = adjList[v][i];
 
        if (!visited[w]){
            topologicalSortUtil(w, adjList, visited, stack);
        }
    }
 
    stack.push(v);
}
 
stack<int> topologicalSort(vector<vector<int>> &adjList){
    int n = adjList.size();
    stack<int> stack;
    vector<bool> visited(n, false);
 
    for (int i = 0; i < n; i++){
        if (!visited[i]){
            topologicalSortUtil(i, adjList, visited, stack);
        }
    }
 
    return stack;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adjList(n);
    vector<ll> numberOfPaths(n, 0);
    vector<int> parents(n);

    for (int i = 0; i < m; i++) {
        int v,w;
        cin >> v >> w;
        v-=1;
        w-=1;
        adjList[v].push_back(w);
    }

    numberOfPaths[0] = 1;

    stack<int> s = topologicalSort(adjList);

    while (!s.empty()){
        int u = s.top();
        s.pop();
        
        for (int w : adjList[u]) numberOfPaths[w] = addMod(numberOfPaths[u], numberOfPaths[w], MOD);
    }

    ll res = numberOfPaths[n-1];
    cout << res << "\n";
}
