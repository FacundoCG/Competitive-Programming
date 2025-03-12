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


// ############################################################### //

void floydWarshall(vector<vector<ll>> &distances){
    int n = distances.size();

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (distances[i][k] != LINF && distances[k][j] != LINF){
                    ll newDistance = (ll) distances[i][k] + distances[k][j];
                    distances[i][j] = min(distances[i][j], newDistance);
                }
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    string s,t;
    cin >> s >> t;

    int n;
    cin >> n;

    vector<vector<ll>> distances(26, vector<ll>(26, LINF));

    forn(i,n){
        char a, b;
        ll w;
        cin >> a >> b >> w;

        ll index1 = a - 'a';
        ll index2 = b - 'a';
        distances[index1][index2] = min(distances[index1][index2], w);
    }

    forn(i, 26){
        distances[i][i] = 0;
    }

    floydWarshall(distances);

    int m = s.size();
    ll res = 0;

    if (s.size() != t.size()){
        cout << -1 << "\n";
        return 0;
    }

    forn(i,m){
        if (s[i] != t[i]){
            ll index1 = s[i] - 'a';
            ll index2 = t[i] - 'a';
            ll minCostTransformation = LINF;

            forn(j,26){
                if (distances[index1][j] != LINF && distances[index2][j] != LINF){
                    if (distances[index1][j] + distances[index2][j] < minCostTransformation){
                        int newIndex = 'a' + j;
                        char c = static_cast<char>(newIndex);
                        minCostTransformation = distances[index1][j] + distances[index2][j];
                        s[i] = c;
                        t[i] = c;
                    }
                }
            }

            if (minCostTransformation != LINF){
                res += minCostTransformation;
            }
            
        }
    }

    if (s != t){
        cout << -1 << "\n";
        return 0;
    }

    cout << res << "\n";
    cout << s << "\n";
}