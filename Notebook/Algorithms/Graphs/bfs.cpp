#include <bits/stdc++.h>
using namespace std;

const long long UNDEFINED = -1;

// Time complexity of all algorithms: O(|E| + |V|)

// This BFS calculates the parents of each node in the BFS tree.
void calculatingParents(int v, vector<vector<int>> &adjList, vector<int> &parents){
    int n = adjList.size();
    vector<bool> visited(n, false);

    visited[v] = true;
    parents[v] = v;

    queue<int> q;
    q.push(v);

    while (!q.empty()){
        int u = q.front();
        q.pop();

        for (int i = 0; i < adjList[u].size(); i++){
            int w = adjList[u][i];
            if (!visited[w]){
                parents[w] = u;
                visited[w] = true;
                q.push(w);
            }
        }
    }
}

// This BFS checks if the graph is bipartite. It also calculates the colors of each node.
bool isBipartite(int v, vector<vector<int>> &adjList, vector<int> &teams){
    bool res = true;
    int n = adjList.size();
    teams[v] = 1;

    queue<int> q;
    q.push(v);

    while (!q.empty()){
        int u = q.front();
        q.pop();

        for (int i = 0; i < adjList[u].size(); i++){
            int w = adjList[u][i];
            if (teams[w] == 0){ // If the node isn't painted, paint it.
                if (teams[u] == 1){
                    teams[w] = 2;
                } else {
                    teams[w] = 1;
                }
                q.push(w);
            } else {
                if (teams[w] == teams[u]){ // If the node is painted, I check that its color is different from the v.
                    res = false;
                    break;
                }
            }
        }
    }

    return res;
}

// Normal BFS
void bfs(int v, vector<vector<int>> &adjList, vector<bool> &visited){
    int n = adjList.size();
    visited[v] = true;

    queue<int> q;
    q.push(v);

    while (!q.empty()){
        int u = q.front();
        q.pop();

        for (int i = 0; i < adjList[u].size(); i++){
            int w = adjList[u][i];
            if (!visited[w]){
                visited[w] = true;
                q.push(w);
            }
        }
    }
}

// Calcuting number of connected components in a graph.
int numberOfConnectedComponents(vector<vector<int>> &adjList){
    int n = adjList.size();
    vector<bool> visited(n, false);
    int res = 0;

    for (int i = 0; i < n; i++){
        if (!visited[i]){
            bfs(i, adjList, visited);
        }
    }

    return res;
}

// Calculating the number of vertices in a connected component.
int numberOfVerticesInConnectedComponent(int v, vector<vector<int>> &adjList){
    int n = adjList.size();
    vector<bool> visited(n, false);
    visited[v] = true;
    int res = 1;

    queue<int> q;
    q.push(v);

    while (!q.empty()){
        int w = q.front();
        q.pop();

        for (int i = 0; i < adjList[w].size(); i++){
            int u = adjList[w][i];

            if (!visited[u]){
                q.push(u);
                visited[u] = true;
                res++;
            }
        }
    }

    return res;
}