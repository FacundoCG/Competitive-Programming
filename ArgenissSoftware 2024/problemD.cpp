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

bool isPossiblePaint(vector<vector<int>> &myPicture, vector<vector<int>> &desiredPicture, int i, int j, int c, int r){
    bool res = true;

    forsn(i_f, i, i+r){
        forsn(j_c, j, j+c){
            if (desiredPicture[i_f][j_c] != 1){
                res = false;
                break;
            }
        }
    }

    return res;
}

void paint(vector<vector<int>> &myPicture, vector<vector<bool>> &alreadyPainted, int i, int j, int c, int r){
    int n = myPicture.size();
    int m = myPicture[0].size();

    if (i + r > n || j + c > m){
        return ;
    }

    forsn(i_f, i, i+r){
        forsn(j_c, j, j+c){
            if (myPicture[i_f][j_c] == 1){
                myPicture[i_f][j_c] = 0;
            } else {
                myPicture[i_f][j_c] = 1;
            }
        }
    }
}

bool areEqual(vector<vector<int>> &myPicture, vector<vector<int>> &desiredPicture){
    bool res = true;
    
    forn(i, desiredPicture.size()){
        forn(j, desiredPicture[0].size()){
            if (desiredPicture[i][j] != myPicture[i][j]){
                res = false;
                break;
            }
        }
    }

    return res;
}

int main() {
    int n, m, c, r;

    while (cin >> n >> m >> r >> c){
        if (n == 0) break;

        int res = 0;

        vector<vector<int>> desiredPicture(n, vector<int>(m));
        vector<vector<int>> myPicture(n, vector<int>(m, 0));
        vector<vector<bool>> alreadyPainted(n, vector<bool>(m, false));

        forn(i,n){
            string s;
            cin >> s;

            forn(j, s.size()){
                desiredPicture[i][j] = s[j] - '0';
            }
        }

        forn(i,n){
            forn(j,m){
                if (desiredPicture[i][j] != myPicture[i][j]){
                    paint(myPicture, alreadyPainted, i, j, c, r);
                    res++;
                }
            }
        }

        if (!areEqual(desiredPicture,myPicture)){
            res = -1;
        }

        cout << res << "\n";
    }
}