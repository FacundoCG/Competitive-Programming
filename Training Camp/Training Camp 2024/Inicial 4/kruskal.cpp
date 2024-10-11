#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> edge;

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

vector<pair<int,edge>> merge(vector<pair<int,edge>> &arr1, vector<pair<int,edge>> &arr2)
{
    int n = arr1.size();
    int m = arr2.size();
    int t = n + m;
    vector<pair<int,edge>> res(t);

    int j = 0;
    int h = 0;

    for (int i = 0; i < t; i++)
    {
        if (j < n && h < m)
        {
            if (arr1[j].first <= arr2[h].first)
            {
                res[i] = arr1[j];
                j++;
            }
            else
            {
                res[i] = arr2[h];
                h++;
            }
        }

        else if (j < n)
        {
            res[i] = arr1[j];
            j++;
        }
        else
        {
            res[i] = arr2[h];
            h++;
        }
    }

    return res;
}

vector<pair<int, edge>> mergeSort(vector<pair<int, edge>> &arr)
{   
    // Worst and best case: O(n * log n)
    // The algorithm is stable but not in place

    int n = arr.size();

    if (n <= 1)
    {
        return arr;
    }

    int mid = n / 2;

    vector<pair<int,edge>> leftHalf, rightHalf;

    for (int i = 0; i < mid; i++)
    {
        leftHalf.push_back(arr[i]);
    }

    for (int i = mid; i < n; i++)
    {
        rightHalf.push_back(arr[i]);
    }

    vector<pair<int,edge>> res1 = mergeSort(leftHalf);
    vector<pair<int,edge>> res2 = mergeSort(rightHalf);

    return merge(res1, res2);
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    DisjSet trees(n+1);
    vector<pair<int, edge>> edges; // The weight and the edge of a vertex;
    vector<int> bestWeightForTheIthEdge;

    for (int i = 0; i < m; i++){
        int v, u, w;
        cin >> v >> u >> w;
        edge e = {v, u};
        edges.push_back({w, e});
    }

    vector<pair<int, edge>> sortedEdges = mergeSort(edges);

    for (auto &p: sortedEdges){
        edge e = p.second;
        int weight = p.first;
        int v = e.first;
        int u = e.second;

        if (trees.find(u) != trees.find(v)){ // Si los vértices no están en el mismo arbol, los uno y sumo el peso de la arista.
            trees.Union(v, u);
            bestWeightForTheIthEdge.push_back(weight);
        }
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; i++){
        
    }
}