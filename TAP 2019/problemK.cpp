#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

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

bool customCompare2(pair<ll,ll> &p1, pair<ll,ll> &p2){
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
    int n;
    cin >> n;

    vector<pair<ll,ll>> danielistas;
    vector<pair<ll,ll>> javieristas;

    forn(i,n){
        char c;
        ll s,e;
        
        cin >> c >> s >> e;

        e -= 1;

        if (c == 'D'){
            danielistas.pb({s,e});
        } else {
            javieristas.pb({s,e});
        }
    }

    ll res = 0;

    sort(all(danielistas), customCompare2);
    sort(all(javieristas), customCompare2);

    vector<pair<ll,ll>> javieristasWithoutRedundant;
    vector<pair<ll,ll>> danielistasWithoutRedundant;
    javieristasWithoutRedundant.pb(javieristas[0]);
    danielistasWithoutRedundant.pb(danielistas[0]);

    int i = 1;
    int j = 0;
    int m = javieristas.size();

    while (i < m){
        if (!isIncluded(javieristas[i], javieristasWithoutRedundant[j])){
            javieristasWithoutRedundant.pb(javieristas[i]);
            j++;
        }
        i++;
    }

    i = 1;
    j = 0;
    int k = danielistas.size();

    while(i < k){
        if (!isIncluded(danielistas[i], danielistasWithoutRedundant[j])){
            danielistasWithoutRedundant.pb(danielistas[i]);
            j++;
        }
        i++;
    }

    j = 0;
    i = 0;
    m = javieristasWithoutRedundant.size();
    k = danielistasWithoutRedundant.size();

    while (i < m && j < k){
        pair<ll,ll> p1 = javieristasWithoutRedundant[i];
        pair<ll,ll> p2 = danielistasWithoutRedundant[j];

        if (isIncluded(p1, p2)){
            ll candidate = intervalSize(p1);
            res = max(res, candidate);
            i++;
        } else if (isIncluded(p2, p1)){
            ll candidate = intervalSize(p2);
            res = max(res, candidate);
            j++;
        } else {
            pair<ll, ll> interval = interseccion(p1, p2);
            ll candidate = intervalSize(interval);
            res = max(res, candidate);

            if (estaALaIzquierda(p1, p2)){
                i++;
            } else {
                j++;
            }
        }
    }

    cout << res << "\n"; 

    return 0;
}
