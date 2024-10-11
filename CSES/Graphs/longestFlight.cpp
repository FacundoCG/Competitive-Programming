#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> edge;
const ll INF = LLONG_MAX;
const int NEG_INF = INT_MIN;

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
    vector<int> distances(n, NEG_INF);
    vector<int> parents(n);

    for (int i = 0; i < m; i++) {
        int v,w;
        cin >> v >> w;
        v-=1;
        w-=1;
        adjList[v].push_back(w);
    }

    distances[0] = 0;

    stack<int> s = topologicalSort(adjList);

    while (!s.empty()){
        int u = s.top();
        s.pop();

        if (distances[u] != NEG_INF){
            for (int i = 0; i < adjList[u].size(); i++){
                int w = adjList[u][i];

                if (distances[w] < distances[u] + 1){
                    parents[w] = u;
                    distances[w] = distances[u] + 1;
                }
            }
        }
    }

    int res = distances[n-1];
    int lastNode = n-1;

    if (res == NEG_INF){
        cout << "IMPOSSIBLE" << "\n";
        return 0;
    }

    cout << res+1 << "\n";

    vector<int> path;
    while (lastNode != 0){
        path.push_back(lastNode+1);
        lastNode = parents[lastNode];
    }

    path.push_back(1);

    for (int i = path.size() - 1; i >= 0; i--){
        if (i == 0){
            cout << path[i] << "\n";
        } else {
            cout << path[i] << " ";
        }
    }
}
