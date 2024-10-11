#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> interval;

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
#define forall(i,c) for(auto i=(c).begin(), i != (c).end(); i++)
#define dforall(i,c) for(auto i=(c).rbegin(), i != (c).rend(); i--)
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

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

bool customCompare2(pair<interval, ll> a1, pair<interval,ll> &a2){
    interval p1 = a1.first;
    interval p2 = a2.first;
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

// This function checks if p1 is included in p2
bool isIncluded(interval &p1, interval &p2){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    bool res = startingTimeP2 <= startingTimeP1 && endingTimeP1 <= endingTimeP2;
    return res;
}

void updatePossibleIntervals(vector<pair<interval, ll>> &intervals, interval currentInterval, vector<bool> &isContainedByOtherInterval, int start){
    while (start < intervals.size() && !isContainedByOtherInterval[intervals[start].second] && isIncluded(intervals[start].first, currentInterval)){
        isContainedByOtherInterval[intervals[start].second] = true;
        start++;
    }
}


// El problema que tengo es que quizas un intervalo está contenido por otros dos intervalos y con mi chequeo solo se lo doy a uno.

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;

    vector<pair<interval, ll>> intervals(n);

    forn(i,n){
        ll x,y;
        cin >> x >> y;
        interval p = {x,y};
        intervals[i] = {p,i};
    }

    DBG(intervals);

    sort(all(intervals), customCompare2);

    DBG(intervals);

    vector<bool> containsOtherInterval(n);
    vector<bool> isContainedByOtherInterval(n);

    forn(i,n-1){
        interval currentInterval = intervals[i].first;
        interval nextInterval = intervals[i+1].first;

        if (isIncluded(nextInterval, currentInterval)){
            int j1 = intervals[i].second;
            int j2 = intervals[i+1].second;

            containsOtherInterval[j1] = true;
            isContainedByOtherInterval[j2] = true;
            updatePossibleIntervals(intervals, currentInterval, isContainedByOtherInterval, i+2);
        }
    }

    forn(i,n){
        if (containsOtherInterval[i]){
            cout << "1 "; 
        } else {
            cout << "0 ";
        }
    }

    cout << "\n";
    RAYA;
    forn(i,n){
        if (isContainedByOtherInterval[i]){
            cout << "1 ";
        } else {
            cout << "0 ";
        }
    }

    cout << "\n";
}