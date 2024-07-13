#include <bits/stdc++.h>
using namespace std;

void findBranches(int root, vector<vector<int>>& adjList, vector<int>& currentPath, vector<vector<int>>& branches){
    if (adjList[root-1].empty()){
        currentPath.push_back(root);
        branches.push_back(currentPath);
    } else {
        if (adjList[root-1].size() == 1){
            currentPath.push_back(root);
            findBranches(adjList[root-1][0], adjList, currentPath, branches);
        } else { // When I have two or more childs
            currentPath.push_back(root);
            findBranches(adjList[root-1][0], adjList, currentPath, branches);

            for (int i = 1; i < adjList[root-1].size(); i++){
                vector<int> newPath;
                findBranches(adjList[root-1][i], adjList, newPath, branches);
            }
        }
    }
}

void buildAdjacentList(vector<vector<int>>& adjList, vector<int>& parents){
    int n = parents.size();

    for (int i = 0; i < n; i++){
        if (parents[i] != i+1){
            int father = parents[i] - 1;
            adjList[father].push_back(i+1);
        }
    }
}

int findRoot(vector<int>& parents){
    int n = parents.size();
    int res;

    for (int i = 0; i < n; i++) {
        if (parents[i] == i+1){
            res = i+1;
        }
    }

    return res;
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n;
        cin >> n;

        vector<int> parents(n);

        for (int j = 0; j < n; j++){
            int k;
            cin >> k;
            parents[j] = k;
        }

        int root = findRoot(parents);
        vector<vector<int>> adjList(n);
        buildAdjacentList(adjList, parents);
        vector<int> path;
        vector<vector<int>> branches;
        findBranches(root, adjList, path, branches);

        cout << branches.size() << "\n";
        for (vector<int>& j : branches){
            cout << j.size() << "\n";

            for (int n : j){
                cout << n << " ";
            }

            cout << "\n";
        }

        if (i != t-1){
            cout << "\n";
        }
    }
}