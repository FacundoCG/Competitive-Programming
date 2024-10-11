#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> interval;

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
#define all(c) (c).begin(),(c).end()

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl

#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)

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
// This function checks if p1 is included in p2
bool isIncluded(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    bool res = startingTimeP2 <= startingTimeP1 && endingTimeP1 <= endingTimeP2;
    return res;
}

ll intervalSize(pair<ll, ll> &p1){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;

    if (endingTimeP1 < startingTimeP1){
        return 0;
    }

    ll res = (ll) endingTimeP1 - startingTimeP1 + 1;
    //cout << "The interval size is: " << res << endl;
    return res;
}

pair<ll,ll> interseccion(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    ll newStartingTime = max(startingTimeP1, startingTimeP2);
    ll newEndingTime = min(endingTimeP1, endingTimeP2);

    return {newStartingTime, newEndingTime};
}

bool estaALaIzquierda(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;
    bool res1 = startingTimeP2 <= endingTimeP1 && endingTimeP1 <= endingTimeP2;
    bool res2 = endingTimeP1 <= startingTimeP2;

    return res1 || res2;
}

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

bool customCompare2(pair<interval, ll> &a1, pair<interval, ll> &a2){
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

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<pair<interval, ll>> friendships;

    forn(i,m){
        int a, b, k;
        cin >> a >> b >> k;

        interval p1 = {a, a+k-1};
        friendships.pb({p1,b});
    }

    sort(all(friendships), customCompare2);

    vector<pair<interval, ll>> amigosQueQuedan;
    pair<interval, ll> intervaloAComparar = friendships[0];

    forsn(i, 1, m){
        pair<interval, ll> elementoActual = friendships[i];
        interval p1 = intervaloAComparar.first;
        interval p2 = elementoActual.first;

        if (areDisjoint(p1, p2)){
            amigosQueQuedan.pb(elementoActual);
            intervaloAComparar = elementoActual;
        } else {
            
        }
    }


}