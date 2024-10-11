#include <bits/stdc++.h>
using namespace std;

const long long UNDEFINED = -1;
typedef pair<int, int> edge;

// This DFS tells me if there is a cycle in the graph and returns the back-edge.
pair<bool, edge> hasCycle(int v, vector<vector<int>> &adjList, vector<bool> &visited, vector<int> &parents){ 
    visited[v] = true;
    edge e = {UNDEFINED, UNDEFINED};
    pair<bool, edge> res = {false, e};

    for (int i = 0; i < adjList[v].size(); i++){
        int w = adjList[v][i];
        if (!visited[w]){
            parents[w] = v;
            res = hasCycle(w, adjList, visited, parents);
            if (res.first){
                break;
            }
        } else if (visited[w] && parents[v] != w && parents[v] != UNDEFINED){
            edge backEdge = {w,v};
            return {true, backEdge};
        }
    }

    return res;
}

// Normal DFS
void dfs(int v, vector<vector<int>> &adjList, vector<int> &visited){
    visited[v] = true;

    for (int i = 0; i < adjList[v].size(); i++){
        int w = adjList[v][i];

        if (!visited[w]){
            dfs(w, adjList, visited);
        }
    }
}
