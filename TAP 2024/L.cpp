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

bool esPotenciaDe2(ll n){
    if (n == 1) return true;

    if (n % 2 == 1){
        return false;
    }

    return esPotenciaDe2(n/2);
}


int main()
{
    int n,q;
    cin >> n >> q;

    vector<ll> arr(n);

    forn(i,n) cin >> arr[i];

    vector<ll> prefixPotenciasDe2(n);
    vector<ll> prefixImpares(n);
    vector<ll> prefixUnos(n);

    if (arr[0] % 2 == 1){
        if (arr[0] == 1){
            prefixUnos[0] = 1;
        } else {
            prefixImpares[0] = arr[0];
        }
    } else if (esPotenciaDe2(arr[0])){
        prefixPotenciasDe2[0] = arr[0];
    }

    forsn(i,1, n){
        prefixImpares[i] = prefixImpares[i-1];
        prefixPotenciasDe2[i] = prefixPotenciasDe2[i-1];
        prefixUnos[i] = prefixUnos[i-1];

        if (arr[i] == 1){
            prefixUnos[i]++;
        } else if (arr[i] % 2 == 1){
            prefixImpares[i] += arr[i];
        } else if (esPotenciaDe2(arr[i])){
            prefixPotenciasDe2[i] += arr[i];
        }
    }

    forn(i,q){
        ll l,r;
        cin >> l >> r;

        ll brian = prefixImpares[r-1];
        ll agustin = prefixPotenciasDe2[r-1];
        ll cantidadUnos = prefixUnos[r-1];


        if (l > 1){
            brian -= prefixImpares[l-2];
            agustin -= prefixPotenciasDe2[l-2];
            cantidadUnos -= prefixUnos[l-2];
        }

        if (cantidadUnos % 2 == 1){
            agustin++;
        }

        if (brian > agustin){
            cout << "B" << "\n";
        } else if (brian < agustin){
            cout << "A" << "\n";
        } else {
            cout << "E" << "\n";
        }
    }
}
