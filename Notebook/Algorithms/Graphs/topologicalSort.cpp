#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX;
typedef long long ll;
typedef pair<ll, ll> edge;

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

void topologicalSort(vector<vector<int>> &adjList){
    int n = adjList.size();
    stack<int> stack;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++){
        if (!visited[i]){
            topologicalSortUtil(i, adjList, visited, stack);
        }
    }
}