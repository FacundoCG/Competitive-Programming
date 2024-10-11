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

void updateSquare(vector<vector<ll>> &picture, int i, int j, int k){
    if (i+k-1 >= picture.size() || j+k-1 >= picture[0].size()){
        return;
    }

    forsn(current_i, i, i+k){
        forsn(current_j, j, j+k){
            picture[current_i][current_j]++;
        }
    }
}

void countApparitionsOfEachPosition(vector<vector<ll>> &picture, int k){
    int n = picture.size();
    int m = picture[0].size();

    forn(i,n){
        forn(j,m){
            updateSquare(picture, i, j, k);
        }
    }
}

vector<ll> countApparitions(vector<vector<ll>> &picture){
    int n = picture.size();
    int m = picture[0].size();
    vector<ll> res;

    forn(i,n){
        forn(j,m){
            res.pb(picture[i][j]);
        }
    }

    sort(all(res));

    return res;
}

void solve(vector<vector<ll>> &picture, vector<ll> &gorillasHeight, int k){
    countApparitionsOfEachPosition(picture, k);

    vector<ll> orderedApparitionOfEachElement = countApparitions(picture);
    int i = gorillasHeight.size() - 1;
    int j = orderedApparitionOfEachElement.size()-1;
    ll res = 0;

    while (i >= 0 && j >= 0){
        res += (ll) gorillasHeight[i]*orderedApparitionOfEachElement[j];
        i--;
        j--;
    }

    cout << res << "\n";
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_,t){
        int n, m, k, w;
        cin >> n >> m >> k >> w;

        vector<ll> gorillasHeights(w);
        vector<vector<ll>> picture(n, vector<ll>(m));

        forn(j,w) cin >> gorillasHeights[j];

        sort(all(gorillasHeights));

        solve(picture, gorillasHeights, k);
    }
}