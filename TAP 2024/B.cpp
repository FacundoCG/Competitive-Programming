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
const ld EPSILON = 1e-10;

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()
#define pb push_back

#define DBG(x) cerr << #x << " = " << (x) << endl

# define forn(i,n) for (int i=0; i<(int)(n);i++)
# define forsn(i,s,n) for (int i=(s); i <(int)(n); i++)

template <typename T>
ostream & operator << (ostream &os, const vector<T> &v) {
    os << "[";
    forn(i, v.size()) {
        if (i > 0) os << ",";
        os << v[i];
    }
    return os << "]";
}

int main()
{
    ll n;

    cin >> n;

    ll res = 0; // cantidad divisores.
    vector<ll> divisores;

    for(ll i=2; i<n; i++){
        if (n % i == 0){
            divisores.pb(i);
            //res++;
        }
    }

    //DBG(res);
    //DBG(divisores);

    //cout << res << "\n";
    //for(ll i=0; i<divisores.size(); i++){
    //    cout  << "1 " << divisores[i] << "\n";
    //}

    vector<bool> estaEnDivisores(divisores.size(), true);

    for(ll i=divisores.size()-1; 0<=i; i--){
        for(ll j=0; j<i; j++){
            if(divisores[i] % divisores[j] == 0){
                estaEnDivisores[j] = false;
            }
        }
    }

    // DBG(divisores);
    // DBG(estaEnDivisores);

    for(ll i=0; i<divisores.size(); i++){
        if(estaEnDivisores[i]){
            res++;
        }
    }

    if(res == 0){
        cout << 1 << "\n";
        cout << "1 1";
        return 0;
    }

    cout << res << "\n";
    for(ll i=0; i<divisores.size(); i++){
        if(estaEnDivisores[i]){
            cout << "1 " << divisores[i] << "\n";
        }
    }

}
