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
vector<vector<vector<ll>>> memoRectangles(101, vector<vector<ll>>(101, vector<ll>(101)));
vector<vector<ll>> memoMaxPoints(101, vector<ll>(101));

int maximumPointsFromRectangle(pair<ll, ll> aRectangle){
    ll width = aRectangle.first;
    ll height = aRectangle.second;
    ll maxPoints = 0;

    while (width != 0 && height != 0){
        if (width == 1 && height == 1){
            maxPoints ++;
            width--;
            height--;
        } else if (width > height){
            width--;
        } else {
            height--;
        }

        maxPoints++;
    }

    return maxPoints;
}

bool isImpossibleToSum(vector<pair<ll,ll>> &rectangles, int k){
    ll res = 0;

    forn(i, rectangles.size()){
        res += maximumPointsFromRectangle(rectangles[i]); 
    }

    return res < k;
}

int calculateEffortForKPoints(pair<ll, ll> aRectangle, int k){
    ll effort = 0;
    ll width = aRectangle.first;
    ll height = aRectangle.second;

    while (k > 0){
        if (width == 1 && height == 1){
            k--;
            width--;
            height--;
            effort++;
        } else if (width > height){
            effort += height;
            width--;
        } else {
            effort += width;
            height--;
        }

        k--;
    }

    return effort;
}

ll dp(vector<pair<ll,ll>> &rectangles, vector<vector<ll>> &memo, int i, int j){
    if (j <= 0){
        return 0;
    } else if (i == -1 && j > 0){
        return INF;
    }

    if (memo[i][j] == INF){
        int w = rectangles[i].first;
        int h = rectangles[i].second;
        int maxPoints = min(memoMaxPoints[w][h], (ll) j);

        forn(k, maxPoints+1){
            int effort = memoRectangles[w][h][k];
            memo[i][j] = min(memo[i][j], effort + dp(rectangles, memo, i-1, j-k));
        }
    }

    return memo[i][j];
}

ll dp_BU(vector<pair<ll,ll>> &rectangles, int k){
    int n = rectangles.size();
    vector<vector<ll>> memo(n, vector<ll>(k+1, INF));

    forn(i,n){
        memo[i][0] = 0;
    }

    forn(i,k+1){
        int width = rectangles[0].first;
        int height = rectangles[0].second;
        int limitPoints = memoMaxPoints[width][height];
        
        if (i <= limitPoints){
            memo[0][i] = memoRectangles[width][height][i];
        } else {
            break;
        }
    }

    forsn(i, 1, n){
        int width = rectangles[i].first;
        int height = rectangles[i].second;
        int limitPoints = memoMaxPoints[width][height];

        forsn(j, 1, k+1){
            forn(z, k+1){
                if (z <= limitPoints && j - z >= 0){
                    int effort = memoRectangles[width][height][z];
                    memo[i][j] = min(memo[i][j], memo[i-1][j-z] + effort);
                } else {
                    break;
                }
            }
        }
    }

    return memo[n-1][k];
}

void memorizeRectangles(vector<vector<vector<ll>>> &A){
    forsn(i, 1, 101){
        forsn(j, 1, 101){
            forsn(k, 1, 101){
                A[i][j][k] = min(A[i-1][j][k-1] + j, A[i][j-1][k-1] + i);
            }
        }
    }
}

void memorizeMaxPointsForAllRectangles(vector<vector<ll>> &B){
    forsn(i, 1, 101){
        forsn(j, 1, 101){
            B[i][j] = maximumPointsFromRectangle({i, j});
        }
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    memorizeMaxPointsForAllRectangles(memoMaxPoints);
    memorizeRectangles(memoRectangles);

    forn(_,t){
        int n, k;
        cin >> n >> k;

        vector<pair<ll,ll>> rectangles(n);
        forn(i,n){
            ll w, h;
            cin >> w >> h;
            rectangles[i] = {w,h};
        }

        if (isImpossibleToSum(rectangles,k)){
            cout << -1 << "\n";
            continue;
        }


        ll res = dp_BU(rectangles, k);

        cout << res << "\n";
    }
}