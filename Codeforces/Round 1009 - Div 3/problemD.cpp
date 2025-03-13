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

bool customCompare(pair<ll, ll> p1, pair<ll, ll> p2){
	if (p1.first < p2.first){
		return true;
	} else if (p2.first < p1.first){
		return false;
	}
	
	return p1.second > p2.second;
}

bool isIncluded(pair<ll, ll> p1, pair<ll, ll> p2){
	return p2.first <= p1.first && p1.second <= p2.first;
}

bool areDisjoint(pair<ll, ll> &p1, pair<ll, ll> &p2) {
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    bool option1 = endingTimeP1 < startingTimeP2;
    bool option2 = endingTimeP2 < startingTimeP1;
    return option1 || option2;
}

ll pointsInside(pair<ll, ll> p){
	ll r = (p.second - p.first)/2;
	ll center = p.first + r;
	ll res = 0;
	ll x = p.first - center;
	
	for (int i = 0; i <= r; i++){
		ll y = i;
		ll distance = (ll) pow(x, 2) + pow(y, 2);
		
		while (distance > r){
			distance = (ll) pow(x, 2) + pow(y, 2);
			x--;
		}
		
		if (distance <= r){
			res += x;
		} 
	}
	
	return res;
}

void solve(vector<pair<ll, ll>> &circles){
	sort(all(circles), customCompare);
	
	pair<ll, ll> lastCircle = circles[0];
	ll res = pointsInside(lastCircle);
	
	forsn(i, 1, SIZE(circles)){
		if (!isIncluded(circles[i], lastCircle)){
			// Check if they have intersection
			res += pointsInside(circles[i]);
			
			if (!areDisjoint(circles[i], lastCircle)){
				pair<ll, ll> newCircle = {circles[i].first, lastCircle.second};
				res -= pointsInside(newCircle);
			}
			
			lastCircle = circles[i];
		} 
	}
	
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		ll n, m;
		cin >> n >> m;
		
		vector<pair<ll, ll>> circles(n);
		vector<ll> centers(n);
		vector<ll> radius(n);
		forn(i, n) cin >> centers[i];
		forn(i, n) cin >> radius[i];
		forn(i, n) circles[i] = {centers[i] - radius[i], centers[i] + radius[i]};
		
		solve(circles);
	}
}
