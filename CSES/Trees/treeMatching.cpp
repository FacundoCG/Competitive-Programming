#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl
#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define all(c) (c).begin(),(c).end()

// Show vector
template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v) {
    os << "[";
    forn(i, v.size()) {
        if (i > 0) os << ",";
        os << v[i];
    }
    return os << "]";
}

// Show pair
template <typename T1, typename T2>
ostream & operator <<(ostream &os, const pair<T1, T2> &p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

// Show set
template <typename T>
ostream & operator <<(ostream &os, const set<T> &s) {
    os << "{";
    for(auto it = s.begin(); it != s.end(); it++){
        if(it != s.begin()) os << ",";
        os << *it;
    }
    return os << "}";
}


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //
vector<vector<int>> adjList;
vector<bool> visited;
vector<vector<int>> nodesPerLevel;
int lastLevel;

void calculateLevelFrom(int v, int currentHeight){
    nodesPerLevel[currentHeight].pb(v);
    visited[v] = true;

    for (int u : adjList[v]){
        if (!visited[u]){
            calculateLevelFrom(u, currentHeight+1);
        }
    }
}

int solve(vector<vector<int>> &memo){
    // The complexity time is O(|E|) because I iterate over all the neighborhoods of all the vertices

    dforn(i, lastLevel+1){
        for (auto v : nodesPerLevel[i]){
            for (auto u : adjList[v]){
                if (visited[u]){
                    // I just can sum the nodes that I have already precalculated
                    memo[v][1] += memo[u][0]; // It means that I can't use v so u is free
                }
            }

            for (auto u : adjList[v]){
                if (visited[u]){
                    // I choose the best possible edge (u, v). All the rest vertices will be free except for u
                    memo[v][0] = max(memo[v][0], 1 + memo[v][1] - memo[u][0] + memo[u][1]);
                }
            }

            visited[v] = true;
        }
    }

    return memo[0][0]; // Return the max amount of matching for a rooted tree in 0
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;

    adjList.resize(n);
    visited.resize(n);
    nodesPerLevel.resize(n);

    forn(i,n-1){
        int w, v;
        cin >> w >> v;
        w-=1;
        v-=1;

        adjList[w].pb(v);
        adjList[v].pb(w);
    }

    calculateLevelFrom(0, 0);
    vector<vector<int>> memo(n, vector<int>(2, 0));
    // memo[i][0] means that the vertex i is free, so I can decide if I want to use it
    // memo[i][1] means that the vertex i is already used by its father, so I can't use any edge of and all its children will be free

    forn(i, n){
        visited[i] = false;
    }

    dforn(i, n){
        if (!nodesPerLevel[i].empty()){
            lastLevel = i;
            break;
        }
    }

    int res = solve(memo);
    cout << res << "\n";
}