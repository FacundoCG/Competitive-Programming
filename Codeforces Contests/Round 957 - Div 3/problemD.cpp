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

int lastAvailableSegment(vector<char> &segments, int initialPosition, int m){
    // This function tells me the index of the best available segment to jump
    int res = -1; // Supose that there isn't water neither log

    // First I look for the best segment of water to jump
    dforsn(i, initialPosition+1, initialPosition+m+1){
        if (segments[i] == 'W'){
            res = i;
            break;
        }
    }

    // Then I look for the best log to jump
    dforsn(i, initialPosition+1, initialPosition+m+1){
        if (segments[i] == 'L'){
            res = i;
            break;
        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;

    forn(_,t){
        int n, m, k;
        cin >> n >> m >> k;

        vector<char> segments(n);
        forn(i,n) cin >> segments[i];

        string res = "NO";
        vector<int> jumpTo(n);

        forn(i,n){
            if (segments[i] == 'C'){
                jumpTo[i] = -1;
            } else if (segments[i] == 'W'){
                jumpTo[i] = i+1;
            } else {
                if (n <= i+m){
                    jumpTo[i] = n;
                } else {
                    jumpTo[i] = lastAvailableSegment(segments, i, m);
                }
            }
        }

        forn(i, m){
            int currentPosition = i;
            int iSwam = 0;
            
            while(currentPosition != n && currentPosition != -1){
                if (segments[currentPosition] == 'W'){
                    iSwam++;
                }

                currentPosition = jumpTo[currentPosition];
            }

            if (currentPosition == n && iSwam <= k){
                res = "YES";
                break;
            }
        }

        cout << res << "\n";
    }
    
}