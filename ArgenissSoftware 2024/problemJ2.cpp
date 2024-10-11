#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 998244353;
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

int n, m, initial_i, initial_j;
vector<vector<bool>> visited, visitedWithDFS, unblock;


bool mismoPunto(int current_i, int current_j, int an_i, int an_j){
    return current_i == an_i && current_j == an_j;
}

bool esDiagonal(int current_i, int current_j, int an_i, int an_j){
    bool res = false;
    int h = current_j+2;

    for (int i = current_i+2; i < n; i++){
        if (mismoPunto(i,h, an_i, an_j)){
            res = true;
        }

        h++;
    }

    h = current_j+2;

    for (int i = current_i-2; i >= 0; i--){
        if (mismoPunto(i,h, an_i, an_j)){
            res = true;
        }

        h--;
    }

    h = current_j+2;

    for (int i = current_i+2; i < n; i++){
        if (mismoPunto(i,h, an_i, an_j)){
            res = true;
        }

        h--;
    }

    h = current_j+2;

    for (int i = current_i-2; i >= 0; i--){
        if (mismoPunto(i,h, an_i, an_j)){
            res = true;
        }

        h++;
    }

    return res;
}

bool esRecta(int current_i, int current_j, int an_i, int an_j){
    bool res = false;

    for (int i = current_i+2; i < n; i++){
        if (mismoPunto(i,current_j, an_i, an_j)){
            res = true;
        }
    }

    for (int i = current_i-2; i >= 0; i--){
        if (mismoPunto(i,current_j, an_i, an_j)){
            res = true;
        }
    }

    for (int j = current_j-2; j >= 0; j--){
        if (mismoPunto(current_i, j, an_i, an_j)){
            res = true;
        }
    }

    for (int j = current_j+2; j < m; j++){
        if (mismoPunto(current_i, j, an_i, an_j)){
            res = true;
        }
    }

    return res;
}

bool puntoValido(int current_i, int current_j, int an_i, int an_j){
    return !esRecta(current_i, current_j, an_i, an_j) && !esDiagonal(current_i, current_j, an_i, an_j);
}

bool hayPuntoValido(set<pair<int,int>> &puntos, int an_i, int a_j){
    bool res = false;

    forn(i, n){
        forn(j, m){
            if (visited[i][j]){
                res = res || puntoValido(i, j, an_i, a_j);
            }
        }
    }

    return res;
}

ll solveFromInitialPoint(ll current_i, ll current_j, int sizePattern, vector<vector<int>> &possibilitiesForPoint, set<pair<int,int>> &puntos){
    ll res = 0;
    visited[current_i][current_j] = true;

    if (sizePattern == 0){
        res = 1;
    } 

    for (int i = 0; i < n && sizePattern != 0; i++){
        for (int j = 0; j < m; j++){
            if (!visited[i][j] && hayPuntoValido(puntos, i, j)){
                res += (ll) solveFromInitialPoint(i, j, sizePattern-1, possibilitiesForPoint, puntos);
                res %= (ll) MOD;
            }
        }
    } 

    if (possibilitiesForPoint[current_i][current_j] == 2){
        res *= 2;
    }

    visited[current_i][current_j] = false;

    res %= (ll) MOD;

    return res;
}

ll solve(vector<vector<int>> &possibilitiesForPoint, int sizePattern){
    set<pair<int,int>> puntos;
    ll res = 0;
    
    forn(i,n){
        forn(j,m){
            res += (ll) solveFromInitialPoint(i, j, sizePattern-1, possibilitiesForPoint, puntos);
            res %= MOD;
        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int a, b;
    cin >> n >> m;

    vector<vector<int>> possibilitiesForPoints(n, vector<int>(m));
    visited.resize(n, vector<bool>(m, false));

    forn(i,n){
        forn(j,m){
            cin >> possibilitiesForPoints[i][j];
        }
    }

    cin >> a >> b;

    ll res = 0;

    forsn(i,a,b+1){
        res += (ll) solve(possibilitiesForPoints, i) % MOD;
    }   

    cout << (ll) res << "\n";
}