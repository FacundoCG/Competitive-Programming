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

int main()
{
    ll n;

    cin >> n;

    vector<ll> xs(n);
    vector<ll> ys(n);
    vector<ll> rs(n);
    bool flag = false;

    for(ll i=0; i<n; i++){
        cin >> xs[i];
        cin >> ys[i];
        cin >> rs[i];
    }

    // Compraro las distancias todos con todos.
    for(ll i=0; i<n; i++){
        for(ll j=i+1; j<n; j++){
            cout << "Iteration i: " << i << ", j:" << j << endl;
            ll a = (ll) 2*(xs[j] - xs[i]);
            ll b = (ll) 2*(ys[j] - ys[i]);
            ll c = (ll) pow(rs[i],2) - pow(rs[j],2) + pow(xs[j],2) + pow(ys[j],2) - pow(xs[i],2) - pow(ys[i],2);
            ll d = gcd(a,b);

            if (a != 0 && b != 0 && c % d == 0){
                cout << "NO" << "\n";
                return 0;
            }
        }
    }

    cout << "SI";

    return 0;
}