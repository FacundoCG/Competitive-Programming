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

// This function checks if the intervals p1 and p2 are disjoint
bool areDisjoint(pair<ll, ll> &p1, pair<ll, ll> &p2) {
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    // This option checks supposing that p1 starts before than p2
    bool option1 = endingTimeP1 < startingTimeP2;
    // This option checks supposing that p2 starts before than p1
    bool option2 = endingTimeP2 < startingTimeP1;

    return option1 || option2;
}

// This order helps me to sort the intervals to have first those which finish earlier. In case of a tie, I choose first the interval which starts earlier.
bool customCompare(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll endingTimeP1 = p1.second;
    ll endingTimeP2 = p2.second;

    if (endingTimeP1 < endingTimeP2){
        return true;
    } else if (endingTimeP1 > endingTimeP2){
        return false;
    }

    ll startingTimeP1 = p1.first;
    ll startingTimeP2 = p2.first;

    return startingTimeP1 < startingTimeP2;
}

ll maximumNumberOfDisjointIntervals(vector<pair<ll, ll>> &intervals){
    int n = intervals.size();
    if (n == 0) return 0;
    sort(all(intervals), customCompare);

    pair<ll, ll> lastInterval = intervals[0];
    int res = 1;

    forsn(i,1,n){
        pair<ll, ll> currentInterval = intervals[i];

        if (areDisjoint(currentInterval,lastInterval)){
            lastInterval = currentInterval;
            res++;
        }
    }

    return res;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    ll n;
    cin >> n;
 
    vector<pair<ll,ll>> movies(n);
 
    for (int i = 0; i < n; i++) {
        ll startingTime, endingTime;
        cin >> startingTime >> endingTime;
        movies[i] = {startingTime, endingTime-1};
    }
 
    ll res = maximumNumberOfDisjointIntervals(movies);
 
    cout << res << "\n";
}