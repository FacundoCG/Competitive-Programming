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
vector<vector<bool>> visited(5, vector<bool>(4, false));
vector<vector<bool>> visitedWithDFS(5, vector<bool>(4, false));
vector<vector<ll>> memo(5, vector<ll>(4, 0));

bool isNeighbor(ll current_i, ll current_j, ll an_i, ll a_j){
    bool res = false;

    if (current_i + 1 == an_i && current_j == a_j){
        res = true;
    }

    if (current_i + 1 == an_i && current_j - 1 == a_j){
        res = true;
    }

    if (current_i + 1 == an_i && current_j + 1 == a_j){
        res = true;
    }

    if (current_i - 1 == an_i && current_j == a_j){
        res = true;
    }

    if (current_i - 1 == an_i && current_j - 1 == a_j){
        res = true;
    }

    if (current_i - 1 == an_i && current_j + 1 == a_j){
        res = true;
    }

    if (current_i == an_i && current_j - 1 == a_j){
        res = true;
    }

    if (current_i == an_i && current_j + 1 == a_j){
        res = true;
    }
    
    return res;
}

bool existsAvailablePathFrom(ll current_i, ll current_j, ll an_i, ll a_j){
    if (isNeighbor(current_i, current_j, an_i, a_j)){
        return true;
    }

    visitedWithDFS[current_i][current_j] = true;
    bool res = false;

    if (current_i + 1 < 5 && visited[current_i+1][current_j] && !visitedWithDFS[current_i+1][current_j]){
        res = res || existsAvailablePathFrom(current_i+1, current_j, an_i, a_j);
    }

    if (current_i + 1 < 5 && current_j + 1 < 4 && visited[current_i+1][current_j+1] && !visitedWithDFS[current_i+1][current_j+1]){
        res = res || existsAvailablePathFrom(current_i+1, current_j+1, an_i, a_j);
    }

    if (current_i + 1 < 5 && 0 <= current_j - 1 && visited[current_i+1][current_j-1] && !visitedWithDFS[current_i+1][current_j-1]){
        res = res || existsAvailablePathFrom(current_i+1, current_j-1, an_i, a_j);
    }

    if (0 <= current_i - 1 && visited[current_i-1][current_j] && !visitedWithDFS[current_i-1][current_j]){
        res = res || existsAvailablePathFrom(current_i-1, current_j, an_i, a_j);
    }

    if (0 <= current_i - 1 && current_j + 1 < 4 && visited[current_i-1][current_j+1] && !visitedWithDFS[current_i-1][current_j+1]){
        res = res || existsAvailablePathFrom(current_i-1, current_j+1, an_i, a_j);
    }

    if (0 <= current_i - 1 && 0 <= current_j - 1 && visited[current_i-1][current_j-1] && !visitedWithDFS[current_i-1][current_j-1]){
        res = res || existsAvailablePathFrom(current_i-1, current_j-1, an_i, a_j);
    }

    if (0 <= current_j - 1 && visited[current_i][current_j-1] && !visitedWithDFS[current_i][current_j-1]){
        res = res || existsAvailablePathFrom(current_i, current_j-1, an_i, a_j);
    }

    if (current_j + 1 < 4 && visited[current_i][current_j+1] && !visitedWithDFS[current_i][current_j+1]){
        res = res || existsAvailablePathFrom(current_i, current_j+1, an_i, a_j);
    }

    visitedWithDFS[current_i][current_j] = false;

    return res;
}

int calculateCorrectI(ll an_i, ll correct_i){
    if (an_i >= initial_i){
        return an_i - initial_i;
    }

    return correct_i - (initial_i - an_i);
}

int calculateCorrectJ(ll a_j, ll correct_j){
    if (a_j >= initial_i){
        return a_j - initial_i;
    }

    return correct_j - (initial_i - a_j);
}

ll solveFromInitialPoint(ll current_i, ll current_j, int sizePattern, vector<vector<int>> &possibilitiesForPoint, ll help_i, ll help_j){
    if (sizePattern == 0){
        return 1;
    }

    visited[current_i][current_j] = true;
    ll res = 0;

    for(int i = initial_i-n; i < initial_i+n && i < 5; i++){
        for(int j = initial_j-m; j < initial_j+m && j < 4; j++){
            if (i < 0 || j < 0){
                continue;
            }

            int check1 = calculateCorrectI(i, help_i);
            int check2 = calculateCorrectJ(j, help_j);

            if (check1 < 0 || check2 < 0 || check1 > n || check2 > m){
                continue;
            }

            if (!visited[i][j] && existsAvailablePathFrom(current_i, current_j, i, j)){
                res += solveFromInitialPoint(i, j, sizePattern-1, possibilitiesForPoint, help_i, help_j);
                res %= MOD;
            }
        }
    }

    int correct_i = calculateCorrectI(current_i, help_i);
    int correct_j = calculateCorrectJ(current_j, help_j);

    if (correct_i < 0 || correct_i > n || correct_j < 0 || correct_j > m){
        return 0;
    }

    if (possibilitiesForPoint[correct_i][correct_j] == 2){
        res *= 2;
    }

    res %= MOD;

    visited[current_i][current_j] = false; 

    return res;
}

ll solve(vector<vector<int>> &possibilitiesForPoint, int sizePattern){
    ll res = 0;
    
    forn(i,5){
        forn(j,4){
            initial_i = i;
            initial_j = j;

            forn(i_n, n){
                forn(j_m,m){
                    memo[i][j] += solveFromInitialPoint(initial_i, initial_j, sizePattern-1, possibilitiesForPoint, i_n, j_m);
                    memo[i][j] %= MOD;
                    res += memo[i][j];
                    res %= MOD;
                }
            }
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

    forn(i,n){
        forn(j,m){
            cin >> possibilitiesForPoints[i][j];
        }
    }

    cin >> a >> b;

    ll res = 0;

    forsn(i,a,b+1){
        res += solve(possibilitiesForPoints, i) % MOD;
    }   

    DBG(memo);

    cout << res << "\n";
}