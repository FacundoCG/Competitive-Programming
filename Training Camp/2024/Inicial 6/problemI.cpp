#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 998244353;
const ll INF = 1e9;
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
#define forall(i,c) for(auto i=(c).begin(), i != (c).end(); i++)
#define dforall(i,c) for(auto i=(c).rbegin(), i != (c).rend(); i--)

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


int main() { 
    ll n, k, m;
    cin >> n >> k >> m;
    
    vector<string> words(n);
    vector<ll> costs(n);
    forn(i, n) cin >> words[i];
    forn(i, n) cin >> costs[i];
    
    map<string, ll> wordsBelongsTo;
    map<ll, ll> minimumCostByGroup;
    forn(i, k) minimumCostByGroup[i] = INF*100;

    
    forn(i, k){
		ll x;
		cin >> x;
		
		forn(_, x){
			ll index;
			cin >> index;
			minimumCostByGroup[i] = min(minimumCostByGroup[i], costs[index-1]);
			wordsBelongsTo[words[index-1]] = i;
		}
	}
    
    vector<string> phrase(m);
    forn(i, m) cin >> phrase[i];
    
    ll res = 0;
    
    forn(i, m){
		ll index = wordsBelongsTo[phrase[i]];
		res += minimumCostByGroup[index];
	}
	
	cout << res << "\n";
}
