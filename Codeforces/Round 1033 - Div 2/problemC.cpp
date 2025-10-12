#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

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

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		ll n, m;
		cin >> n >> m;
		
		ll cota_sup = (ll) n*(n+1)/2;
		
		if (m < n || m > cota_sup){
			cout << "-1\n";
			continue;
		}
		
		vector<ll> res;
		
		ll toSum = m;
		ll nodesLeft = n;
		
		while (toSum != 0){
			if (toSum - nodesLeft == 0){
				forsn(i, 1, nodesLeft+1) res.pb(i);
				break;
			} else if (toSum < 2*nodesLeft){ // toSum en (nodesLeft, nodesLeft*2]
				ll a = toSum - (nodesLeft - 1);
				res.pb(a);
				
				forsn(i, 1, nodesLeft+1){
					if (i != a) res.pb(i);
				}
				
				break;
			} else {
				toSum -= nodesLeft;
				res.pb(nodesLeft);
				nodesLeft--;
			}
		}
		
		cout << res[0] << "\n";
		
		forsn(i, 1, n) cout << res[i] << " " << res[i-1] << "\n";
		
		
		
	}
	
    return 0;
}
