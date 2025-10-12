#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using ii = pair<int,int>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
const ld EPSILON = 1e-10;
const double PI = acos(-1.0);

#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl

#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)

// Show pair
template <typename T1, typename T2>
ostream & operator <<(ostream &os, const pair<T1, T2> &p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

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

struct InclusionExclusion{
    ll k, n;
    vl A;

    InclusionExclusion(ll K, ll N, vl &a) : k(K), n(N), A(a) {}

    // Quiero ver la # elementos que cumplen P(x) en la unión de los conjuntos: A[0], A[1], ..., A[k-1]
    int amountOfSets(ll mask){
        int res = 0;
        while (mask > 0){
            res += (mask & 1);
            mask = mask >> 1;
        }
        return res;
    }

    ll sizeIntersection(ll mask){
        ll res = 0;
        ll divisor = 1;
        int j = 0;

        while (mask > 0){
            if (mask & 1){
				if (divisor > n/A[j]){
					divisor = 0;
					break;
				} else { divisor *= A[j];}
            }
            j++;
            mask = mask >> 1;
        }

        if (divisor > 0) res += n/divisor;
        return res;
    }
    
    ll solve(){
        ll res = 0;
        ll cota = 1ll << k;
        forsn(mask, 1, cota){
            ll sizeSet = amountOfSets(mask);
            if (sizeSet % 2 == 0) res -= sizeIntersection(mask);
            else res += sizeIntersection(mask);
        }
        return res;
    }
};

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	ll n, k;
	cin >> n >> k;
	
	vl A(k);
	forn(i, k) cin >> A[i];
	
	InclusionExclusion P(k, n, A);
	ll res = P.solve();
	cout << res << "\n";
	
    return 0;
}
