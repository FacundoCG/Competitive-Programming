#include <bits/stdc++.h>
using namespace std;

const long long UNDEFINED = -1;
typedef pair<int, int> edge;

pair<bool, edge> hasCycle(int v, vector<vector<int>> &adjList, vector<bool> &visited, vector<int> &parents){
    //cout << "Current v: " << v << endl;
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
            //cout << "Success" << endl;
            //cout << "Backedge: {" << v << "," << w << "}" << endl;
            edge backEdge = {w,v};
            return {true, backEdge};
        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;

    vector<vector<int>> adjList(n);
    vector<bool> visited(n, false);
    vector<int> parents(n, UNDEFINED);

    for (int i = 0; i < m; i++){
        int v, w;
        cin >> v >> w;

        v-=1;
        w-=1;

        adjList[v].push_back(w);
        adjList[w].push_back(v);
    }

    pair<bool, edge> hasCycles;
    edge e;

    for (int i = 0; i < n; i++){
        if (!visited[i]){
            hasCycles = hasCycle(i, adjList, visited, parents);
            if (hasCycles.first){
                e = hasCycles.second;
                break;
            }
        }
    } 

    if (!hasCycles.first){
        cout << "IMPOSSIBLE" << "\n";
        return 0;
    }

    //cout << "The back edge is: {" << e.first << "," << e.second << "}" << endl;

    vector<int> cycle;
    int originalV = e.second;
    int v = e.second;
    int w = e.first;
    
    while (v != w){
        cycle.push_back(v+1);
        v = parents[v];
    }

    cycle.push_back(w+1);
    cycle.push_back(cycle[0]);

    cout << cycle.size() << "\n";
    for (int i = 0; i < cycle.size(); i++){
        if (i == cycle.size() - 1){
            cout << cycle[i] << "\n";
        } else {
            cout << cycle[i] << " ";
        }
    }
}