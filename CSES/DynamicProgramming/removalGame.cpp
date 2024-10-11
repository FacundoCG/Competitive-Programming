#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll NEG_INF = LLONG_MIN;
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

vector<ll> prefixSum;

ll dp(vector<ll> &A, vector<vector<vector<ll>>> &memo, int start, int end, int player){
    int n = A.size();

    if (start > end){
        return 0;
    }

    if (memo[start][end][player] == UNDEFINED){
        memo[start][end][player] = 0;

        ll player2;

        if (player == 0){
            player2 = 1;
        } else {
            player2 = 0;
        }

        ll rest1 = (ll) prefixSum[end] - prefixSum[start];
        memo[start][end][player] = (ll) A[start] + rest1 - dp(A, memo, start+1, end, player2);

        ll rest2 = 0;

        if (end - 1 >= 0){
            rest2 = (ll) prefixSum[end-1];

            if (start - 1 >= 0){
                rest2 -= (ll) prefixSum[start-1];
            }
        }

        ll option2 = (ll) A[end] + rest2 - dp(A, memo, start, end-1, player2);
        memo[start][end][player] = max(memo[start][end][player], option2);
    }

    return memo[start][end][player];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;

    vector<ll> values(n);
    vector<vector<vector<ll>>> memo(n, vector<vector<ll>>(n, vector<ll>(2, UNDEFINED)));
    prefixSum.assign(n, 0);

    forn(i,n) cin >> values[i];

    prefixSum[0] = values[0];

    forsn(i,1,n){
        prefixSum[i] = (ll) prefixSum[i-1] + values[i];
    }

    ll res = dp(values, memo, 0, n-1, 0);

    cout << res << "\n";
}