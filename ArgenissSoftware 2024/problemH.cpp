#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
const ld EPSILON = 1e-10;
const double PI = acos(-1.0);

#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl

#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define forall(i,c) for(auto i=(c).begin(), i != (c).end(); i++)
#define dforall(i,c) for(auto i=(c).rbegin(), i != (c).rend(); i--)

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

int n,m,t;
vector<vector<int>> smallNeighborhood, bigNeighborhood;
set<pair<int,int>> hotPoints;

int sizeSmallNeighboorhood(vector<vector<int>> &map, int i, int j){
    int neighbors = 0;

    if (i+1 < n && map[i+1][j] == 0){
        neighbors++;
    }

    if (0 <= i-1 && map[i-1][j] == 0){
        neighbors++;
    }

    if (j+1 < m && map[i][j+1] == 0){
        neighbors++;
    }

    if (0 <= j-1 && map[i][j-1] == 0){
        neighbors++;
    }

    return neighbors;
}

int sizeBigNeighboorhood(vector<vector<int>> &map, int i, int j){
    int neighbors = sizeSmallNeighboorhood(map, i, j); 

    if (0 <= i-1 && 0 <= j-1 && map[i-1][j-1] == 0){
        neighbors++;
    }

    if (0 <= i-1 && j+1 < m && map[i-1][j+1] == 0){
        neighbors++;
    }

    if (i+1 < n && 0 <= j-1 && map[i+1][j-1] == 0){
        neighbors++;
    }

    if (i+1 < n && j+1 < m && map[i+1][j+1] == 0){
        neighbors++;
    }

    return neighbors;
}

void updateNeighborhood(vector<vector<int>> &map, int i, int j){
    if (i+1 < n){
        smallNeighborhood[i+1][j] = sizeSmallNeighboorhood(map, i+1, j);
        bigNeighborhood[i+1][j] = sizeBigNeighboorhood(map, i+1, j);
    }

    if (0 <= i-1){
        smallNeighborhood[i-1][j] = sizeSmallNeighboorhood(map, i-1, j);
        bigNeighborhood[i-1][j] = sizeBigNeighboorhood(map, i-1, j);
    }

    if (j+1 < m){
        smallNeighborhood[i][j+1] = sizeSmallNeighboorhood(map, i, j+1);
        bigNeighborhood[i][j+1] = sizeBigNeighboorhood(map, i, j+1);
    }

    if (0 <= j-1){
        smallNeighborhood[i][j-1] = sizeSmallNeighboorhood(map, i, j-1);
        bigNeighborhood[i][j-1] = sizeBigNeighboorhood(map, i, j-1);
    }

    if (0 <= i-1 && 0 <= j-1 && map[i-1][j-1] == 1){
        bigNeighborhood[i-1][j-1] = sizeBigNeighboorhood(map, i-1, j-1);
    }

    if (0 <= i-1 && j+1 < m && map[i-1][j+1] == 1){
        bigNeighborhood[i-1][j+1] = sizeBigNeighboorhood(map, i-1, j+1);
    }

    if (i+1 < n && 0 <= j-1 && map[i+1][j-1] == 1){
        bigNeighborhood[i+1][j-1] = sizeBigNeighboorhood(map, i+1, j-1);
    }

    if (i+1 < n && j+1 < m && map[i+1][j+1] == 1){
        bigNeighborhood[i+1][j+1] = sizeBigNeighboorhood(map, i+1, j+1);
    }
}

void putPointIsHot(vector<vector<int>> &map, int i, int j){
    map[i][j] = 0;
}

void updatePoint(vector<vector<int>> &map, int i, int j, set<pair<int,int>> &newHotPoints){
    if (map[i][j] == 1 && bigNeighborhood[i][j] >= 1){
        newHotPoints.insert({i,j});
    } else if (map[i][j] == 2 && smallNeighborhood[i][j] >= 1){
        newHotPoints.insert({i,j});
    } else if (map[i][j] == 3 && smallNeighborhood[i][j] >= 2){
        newHotPoints.insert({i,j});
    } else if (map[i][j] == 4 && smallNeighborhood[i][j] >= 3){
        newHotPoints.insert({i,j});
    }
}

void updateNewHotPoints(vector<vector<int>> &map, int i, int j, set<pair<int,int>> &newHotPoints){
    
    if (i+1 < n){
        updatePoint(map, i+1, j, newHotPoints);
    }

    if (0 <= i-1){
        updatePoint(map, i-1, j, newHotPoints);
    }

    if (j+1 < m){
        updatePoint(map, i, j+1, newHotPoints);
    }

    if (0 <= j-1){
        updatePoint(map, i, j-1, newHotPoints);
    }

    if (0 <= i-1 && 0 <= j-1 && map[i-1][j-1] == 1){
        updatePoint(map, i-1, j-1, newHotPoints);
    }

    if (0 <= i-1 && j+1 < m && map[i-1][j+1] == 1){
        updatePoint(map, i-1, j+1, newHotPoints);
    }

    if (i+1 < n && 0 <= j-1 && map[i+1][j-1] == 1){
        updatePoint(map, i+1, j-1, newHotPoints);
    }

    if (i+1 < n && j+1 < m && map[i+1][j+1] == 1){
        updatePoint(map, i+1, j+1, newHotPoints);   
    }
}

void printGrid(vector<vector<int>> &grid){
    forn(i, grid.size()){
        forn(j, grid[0].size()){
            cout << grid[i][j] << " ";
        }

        cout << "\n";
    }
}

void updateBothNeighborhoods(vector<vector<int>> &map){
    forn(i,n){
        forn(j,m){
            if (map[i][j] == 0){
                updateNeighborhood(map, i, j); 
            }
        }
    }
}

void solve(vector<vector<int>> &map){
    ll res = 0;
    
    while(!hotPoints.empty() && t >= 0){
        res += hotPoints.size();
        set<pair<int,int>> newHotPoints;

        for (auto p : hotPoints){
            int i = p.first;
            int j = p.second;
            updateNeighborhood(map, i, j);
        }

        for (auto p : hotPoints){
            int i = p.first;
            int j = p.second;
            updateNewHotPoints(map, i, j, newHotPoints); 
        }

        for (auto p : newHotPoints){
            int i = p.first;
            int j = p.second;
            putPointIsHot(map, i, j);
        }

        hotPoints = newHotPoints;
        t--;
    }

    cout << res << "\n";
}



int main() {
    cin >> n >> m >> t;

    vector<vector<int>> map(n, vector<int>(m));
    smallNeighborhood.resize(n, vector<int>(m, 0));
    bigNeighborhood.resize(n, vector<int>(m, 0));

    forn(i,n){
        forn(j,m){
            cin >> map[i][j];    
            if (map[i][j] == 0){
                hotPoints.insert({i,j});
            }
        }
    }

    solve(map);
}