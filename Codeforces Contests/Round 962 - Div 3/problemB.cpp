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

vector<vector<int>> calculatePrefixSumGrid(vector<vector<int>> &grid){
    // The grid is size n x n
    int n = grid.size();
    vector<vector<int>> prefixSumGrid(n, vector<int>(n));

    forn(j,n){
        prefixSumGrid[j][0] = grid[j][0];
    }

    forn(i,n){
        forsn(j,1,n){
            prefixSumGrid[i][j] = prefixSumGrid[i][j-1] + grid[i][j];
        }
    }

    return prefixSumGrid;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(i,t){
        int n, k;
        cin >> n >> k;

        vector<vector<int>> grid(n, vector<int>(n));
        forn(j,n){
            string s;
            cin >> s;

            forn(h, s.size()){
                grid[j][h] = s[h] - '0';
            }
        }

        vector<vector<int>> gridReducedByK; 
        vector<vector<int>> prefixSumGrid = calculatePrefixSumGrid(grid);
        int firstRow = 0;
        int lastRow = k-1;
        int firstCol = 0;
        int lastCol = k-1;

        //DBG(grid);
        //DBG(prefixSumGrid);

        while (firstRow < n && lastRow < n){
            vector<int> rowForRes;
            while(firstCol < n && lastCol < n){
                int number = 0;
                //DBG(firstCol);
                //DBG(firstRow);
                if (grid[firstRow][firstCol] != 0){
                    number++;
                }

                rowForRes.pb(number);
                firstCol = lastCol + 1;
                lastCol += k;
            }

            //DBG(rowForRes);
            gridReducedByK.pb(rowForRes);
            firstCol = 0;
            lastCol = k-1;
            firstRow = lastRow + 1;
            lastRow += k;
        }

        forn(j, gridReducedByK.size()){
            forn(h, gridReducedByK[0].size()){
                cout << gridReducedByK[j][h];
            }

            cout << "\n";
        }
    }
}