#include <bits/stdc++.h>
using namespace std;

class DisjSet {
    int *rank, *parent, n;

public:
    DisjSet(int n){
        rank = new int[n];
        parent = new int[n];
        this->n = n;
        makeSet();
    }

    void makeSet(){
        for (int i = 0; i < n; i++){
            parent[i] = i;
        }
    }

    // Find set (representative) of a given x
    int find(int x){
        if (parent[x] != x){ // If the element isn't the representative of the set (the root), I do recursion over its father to find it. In addition, I put this element as a child of the root.
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void Union(int x, int y){
        // Find the representatives of each element
        int xset = find(x);
        int yset = find(y); 

        // If they have the same representative, they belong to the same set. Then, I don't do anything

        if (xset == yset){
            return;
        } 

        if (rank[xset] < rank[yset]){ // If the height of the tree of the first element is less than the height of the tree of the second element, then I put the first element as a child of the root of the other tree. Therefore, the resulting tree won't have a higher height than the older one.
            parent[xset] = yset;
        } else if (rank[xset] > rank[yset]){ // Idem 
            parent[yset] = xset;
        } else { // If they have the same height, the resulting tree will have a height incremented in one
             parent[xset] = yset;
             rank[yset]++;
        }    
    }
};

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;

    DisjSet connectedComponents(n);
    set<int> representativesOfComponents;
    vector<int> representatives; 

    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        v -= 1;
        u -= 1;

        if (connectedComponents.find(v) != connectedComponents.find(u)){
            connectedComponents.Union(v, u);
        }
    }

    for (int i = 0; i < n; i++){
        int v = connectedComponents.find(i)+1;
        representativesOfComponents.insert(v);
    }

    cout << representativesOfComponents.size() - 1 << "\n";

    for (int v : representativesOfComponents){
        representatives.push_back(v);
    }

    for (int i = 1; i < representatives.size(); i++){
        int v = representatives[i];
        int w = representatives[i-1];
        cout << v << " " << w << "\n";
    }
}