#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> edge;
typedef long long ll;

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

// Time Complexity: O(|E|*log(|E|))
// Obs: I don't need the adjList if I can work with the number of vertices
// Obs: I suppose that the edges are already sorted for all the methods.

// Normal Kruskal
void kruskal(int n, vector<pair<int, edge>> &edges){
    DisjSet trees(n);
    
    for (auto &p: edges){
        edge e = p.second;
        int weight = p.first;
        int v = e.first;
        int u = e.second;

        if (trees.find(u) != trees.find(v)){ 
            trees.Union(v, u);
        }
    }
}

// This algorithm calculates the weight of an AGM.
ll weightOfAGM(int n, vector<pair<ll, edge>> &edges){
    ll res = 0;
    DisjSet trees(n);
    
    for (auto &p: edges){
        edge e = p.second;
        ll weight = p.first;
        int v = e.first;
        int u = e.second;

        if (trees.find(u) != trees.find(v)){
            res += weight; 
            trees.Union(v, u);
        }
    }

    return res;
}