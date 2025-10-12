#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

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
#define forsn(i,s,n) for (ll i=(s);i<(ll)(n);i++)
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

int calculatePotencia(ll &a, ll b){
	int res = 0;
	
	while (a % b == 0){
		a /= b;
		res++;
	}
	
	return res;
}

vector<ll> divisoresOf(ll a){
    vector<ll> res;
    int until = sqrt(a) + 1;
    forsn(i, 1, until){
        if (a % i == 0) res.pb(i);
        if (a % i == 0 && i != a/i) res.pb(a/i);
    }
    
    sort(all(res));

    return res;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		ll p, q;
		cin >> p >> q;
		
		if (p % q != 0){
			cout << p << "\n";
		} else {
			vl divisorsOfQ = divisoresOf(q);
			ll res = 1;
			ll currentQ = q;
				
			for (ll d : divisorsOfQ){
				if (d == 1) continue;
				int potenciaQ = calculatePotencia(currentQ, d);
				if (potenciaQ == 0) continue; 
				
				ll currentRes = p;
				while (currentRes % d == 0) currentRes /= d;
				forn(i, potenciaQ-1) currentRes *= d;
				res = max(res, currentRes);
			}
				
			cout << res << "\n";
		}	
	}
	
    return 0;
}
