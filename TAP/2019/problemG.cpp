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
template <typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    int n;  
    cin >> n;

    min_heap<ll> bandasEnemigas;
    ll galtier = 0;
    string res = "SI";

    forn(i,n){
        ll miembros;
        cin >> miembros;

        if (i == 0){
            galtier = miembros;
        } else {
            bandasEnemigas.push(miembros);
        }
    }

    while (!bandasEnemigas.empty()) {
        ll totalBandasQueQuedan = bandasEnemigas.size();
        ll primeraBandaQueMuere = bandasEnemigas.top();
        ll miembrosMiosQueMueren = (ll) (primeraBandaQueMuere-1)*totalBandasQueQuedan;
        miembrosMiosQueMueren += (ll) totalBandasQueQuedan - 1;

        galtier -= miembrosMiosQueMueren;

        if (galtier <= 0){
            res = "NO";
            break;
        }

        bandasEnemigas.pop();
    }

    cout << res << "\n";
}