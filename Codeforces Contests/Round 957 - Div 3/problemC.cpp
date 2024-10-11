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

vector<ll> mergeVectors(vector<ll> &A, vector<ll> &B){
    vector<ll> res;

    forn(i, A.size()){
        res.pb(A[i]);
    }

    forn(i, B.size()){
        res.pb(B[i]);
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;

    forn(_,t){
        int n,m,k;
        cin >> n >> m >> k;
        
        vector<ll> prefixSum(n);
        // My permutation has length n and contains all elements from 1 to n

        prefixSum[0] = n;

        forsn(i,1,n){
            prefixSum[i] = prefixSum[i-1] + (n-i);
        }

        ll res = 0;

        vector<ll> goodNumbers;
        vector<ll> badNumbers;
        vector<ll> neutralNumbers;

        dforsn(i,k,n+1){
            goodNumbers.pb(i);
        }

        forsn(i,1,m+1){
            badNumbers.pb(i);
        }

        forsn(i,m+1,k){
            neutralNumbers.pb(i);
        }

        vector<ll> permutation = mergeVectors(goodNumbers,neutralNumbers);
        permutation = mergeVectors(permutation, badNumbers);

        forn(i, permutation.size()){
            cout << permutation[i] << " ";
        }

        cout << "\n";
    }
    
}