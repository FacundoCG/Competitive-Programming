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

// This function checks if p1 is included in p2
bool isIncluded(pair<ll, ll> p1, pair<ll, ll> p2){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    bool res = startingTimeP2 <= startingTimeP1 && endingTimeP1 <= endingTimeP2;
    return res;
}

bool belongsToTheInterval(pair<ll, ll> p1, ll x){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;

    return startingTimeP1 <= x && x <= endingTimeP1;
}

// This function helps me to sort the intervals to have first those which start earlier. In case of a tie, I choose first the pair<ll,ll> which ends later.
bool customCompare2(pair<ll,ll> p1, pair<ll,ll> p2){
    ll startingTimeP1 = p1.first;
    ll startingTimeP2 = p2.first;

    if (startingTimeP1 < startingTimeP2){
        return true;
    } else if (startingTimeP1 > startingTimeP2){
        return false;
    }

    ll endingTimeP1 = p1.second;
    ll endingTimeP2 = p2.second;

    return endingTimeP1 > endingTimeP2;
}

pair<ll, ll> redundantInterval(vector<pair<ll, ll>> intervals){
    int n = intervals.size();
    pair<ll, ll> res = {UNDEFINED, UNDEFINED};

    sort(all(intervals), customCompare2);

    forn(i, n-1){
        pair<ll, ll> currentInterval = intervals[i];
        pair<ll, ll> nextInterval = intervals[i+1];

        if (isIncluded(nextInterval, currentInterval)){
            res = nextInterval;
            break;
        } else if (i+2 <= n-1){
            pair<ll, ll> laterInterval = intervals[i+2];

            if (belongsToTheInterval(currentInterval, nextInterval.first)){
                pair<ll,ll> newInterval = {currentInterval.second + 1, nextInterval.second};

                if (isIncluded(newInterval, laterInterval)){
                    res = nextInterval;
                    break;
                }
            }

        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<ll,ll>> tvs(n);
    forn(i, n){
        ll s,e;
        cin >> s >> e;
        tvs[i] = {s,e};
    }

    ll res = -1;
    pair<ll, ll> extraInterval = redundantInterval(tvs);

    forn(i,n){
        if (tvs[i] == extraInterval){
            res = i+1;
        }
    }

    cout << res << "\n";
};
