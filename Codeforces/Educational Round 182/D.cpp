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
const int MOD = 998244353;
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

vl A;
int n;
ll y;

ll ceilDiv(ll x, ll d){
	if (x % d == 0) return x/d;
	return x/d + 1;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		cin >> n >> y;
		A.clear();
		A.resize(n);
		
		ll maxElement = 0;
		unordered_map<ll, ll> M;
		forn(i, n) { 
			cin >> A[i]; 
			maxElement = max(maxElement, A[i]);
			M[A[i]]++;
		}
		
		DBG(A); DBG(y);
		
		ll res = -LINF;
		DBG(res);
		
		forsn(i, 2, maxElement+1){
			ll currentRes = 0;
			unordered_map<ll, ll> used;
			for(ll x : A){ currentRes += ceilDiv(x, i); used[ceilDiv(x, i)]++;}
			if (currentRes <= res) break; 
			for (auto &[x, reps] : used){
				if (esta(x, M)){
					currentRes -= y*min(reps, M[x]);
					ll falta = max(reps-M[x], 0ll);
					currentRes -= y*falta;
				}
			}
			
			DBG(currentRes);
			RAYA; 
			res = max(res, currentRes);
		}
		
		cout << res << "\n";
	}
	
    return 0;
}
