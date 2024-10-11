#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> edge;
const ll INF = LLONG_MAX;
const int NEG_INF = INT_MIN;
const ll UNDEFINED = -1;
 
bool hasCycle(int v, vector<vector<int>> &adjList, vector<bool> &visited, vector<bool> &recStack){ 
    if (!visited[v]){
        visited[v] = true;
        recStack[v] = true;

        for (int i = 0; i < adjList[v].size(); i++){
            int w = adjList[v][i];

            if (!visited[w] && hasCycle(w, adjList, visited, recStack)){
                return true;
            } else if (recStack[w]){
                return true;
            }
        }
    }

    recStack[v] = false;
    return false;
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
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);

    for (int i = 0; i < m; i++) {
        int v,w;
        cin >> v >> w;
        v-=1;
        w-=1;
        adjList[v].push_back(w);
    }
    bool existsCycle = false;
 
    for (int i = 0; i < n; i++){
        if (!visited[i]){
            existsCycle = existsCycle || hasCycle(i, adjList, visited, recStack);
        }
    }
 
    if (existsCycle) {
        cout << "IMPOSSIBLE" << "\n";
        return 0;
    }
 
    stack<int> s = topologicalSort(adjList);
    
    while (!s.empty()){
        cout << s.top()+1 << " ";
        s.pop();
    }
 
    cout << "\n";
}