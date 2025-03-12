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



int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(i,t){
        int n;
        cin >> n;

        vector<ll> numbers(n);
        vector<ll> prefixSum(n);

        forn(j,n) cin >> numbers[j];

        prefixSum[0] = numbers[0];

        forsn(j,1,n){
            prefixSum[j] = prefixSum[j-1] + numbers[j];
        }

        string s;
        cin >> s;

        vector<ll> positionsOfL;
        vector<ll> positionsOfR;

        forn(j,s.size()){
            if (s[j] == 'L'){
                positionsOfL.pb(j);
            } else {
                positionsOfR.pb(j);
            }
        }

        ll res = 0;

        int j = 0;
        int k = positionsOfR.size() - 1;

        while(j < positionsOfL.size() && k >= 0){
            int posOfCurrentL = positionsOfL[j];
            int posOfCurrentR = positionsOfR[k];

            if (posOfCurrentL < posOfCurrentR){
                res += prefixSum[posOfCurrentR];

                if (posOfCurrentL != 0){
                    res -= prefixSum[posOfCurrentL-1];
                }
            } 

            j++;
            k--;
        }

        cout << res << "\n";
    }
}