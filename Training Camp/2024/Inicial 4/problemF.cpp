#include <bits/stdc++.h>
using namespace std;

int connectedComponentEdges(int vertex, vector<vector<int>>& adjList, vector<bool>& visited, vector<int>& edgesPerVertex){
    int res = 0;

    queue<int> q;
    q.push(vertex);
    visited[vertex] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int &w : adjList[v]){
            if (!visited[w]){
                visited[w] = true;
                q.push(w);
            }

            edgesPerVertex[w]--;
        }

        res += edgesPerVertex[v];
    }

    return res;
}

pair<int, bool> connectedComponentSize(int vertex, vector<vector<int>>& adjList, vector<bool>& visited, vector<bool>& specialVertex){
    bool isComponentHome = specialVertex[vertex];
    int sizeComponent = 0;

    queue<int> q;
    q.push(vertex);
    visited[vertex] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int &w : adjList[v]){
            if (!visited[w]){
                visited[w] = true;
                q.push(w);

                if (specialVertex[w]){
                    isComponentHome = true;
                }
            }
        }

        sizeComponent++;
    }

    return {sizeComponent, isComponentHome};
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> adjList(n+1);
    vector<bool> visited(n+1, false);
    vector<bool> isHomeGoverment(n+1, false);
    vector<int> edgesPerVertex(n+1, 0);
    vector<int> edgesPerComponent;
    vector<int> sizeNoSpecials;

    for (int i = 0; i < k; i++) {
        int v;
        cin >> v;
        isHomeGoverment[v] = true;
    }

    for (int i = 0; i < m; i++) {
        int v, w;
        cin >> v >> w;

        adjList[v].push_back(w);
        adjList[w].push_back(v);
        edgesPerVertex[v]++;
        edgesPerVertex[w]++;
    }

    int res = 0;
    int biggestSpecialComponent = 0;

    vector<int> componentsSize;
    for (int i = 1; i <= n; i++){
        if (!visited[i]){
            pair<int, bool> p = connectedComponentSize(i, adjList, visited, isHomeGoverment);
            int size = p.first;
            bool isHome = p.second;

            componentsSize.push_back(size);

            if (isHome){
                biggestSpecialComponent = max(biggestSpecialComponent, size);
            } else {
                sizeNoSpecials.push_back(size);
            }
        }
    }

    visited.assign(n+1, false);

    for (int i = 1; i <= n; i++){
        if (!visited[i]){
            int edges = connectedComponentEdges(i, adjList, visited, edgesPerVertex);
            edgesPerComponent.push_back(edges);
        }
    }

    for (int i = 0; i < edgesPerComponent.size(); i++){
        int numberOfVertexs = componentsSize[i];
        res +=  numberOfVertexs * (numberOfVertexs - 1)/2 - edgesPerComponent[i];
    }

    for (int &c : sizeNoSpecials){
        res += c*biggestSpecialComponent;
        biggestSpecialComponent += c;
    }

    cout << res << "\n";
}
