#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> edge;
const ll UNDEFINED = -1;
 
pair<bool, edge> hasCycle(int v, vector<vector<int>> &adjList, vector<bool> &visited, vector<bool> &recStack, vector<int> &parents){
    edge e = {UNDEFINED, UNDEFINED};
    pair<bool, edge> res = {false, e}; 

    if (!visited[v]){
        visited[v] = true;
        recStack[v] = true;

        for (int i = 0; i < adjList[v].size(); i++){
            int w = adjList[v][i];

            if (!visited[w]){
                parents[w] = v;
                res = hasCycle(w, adjList, visited, recStack, parents);

                if (res.first){
                    return res;
                }
            } else if (recStack[w]){
                e = {v, w};
                res = {true, e};
                return res;
            }
        }
    }

    recStack[v] = false;
    return res;
}
 
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adjList(n);
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<int> parents(n, UNDEFINED);

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
            pair<bool, edge> p = hasCycle(i, adjList, visited, recStack, parents);
            existsCycle = existsCycle || p.first;

            if (existsCycle){

            }
        }
    }
 
    if (!existsCycle) {
        cout << "NO" << "\n";
        return 0;
    }
 
    
}