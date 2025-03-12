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
bool lessPenaltyThan(vector<ll> &penalties, string &s, ll k, ll x){
	// We want to know if we can get a penalty <= x
	ll lastBlue = -2;
	ll segmentsPainted = 0;
	
	forn(i, SIZE(s)){
		if (penalties[i] > x && s[i] == 'B'){ // We need to paint this cell
			if (lastBlue + 1 != i){ // It means that the cell before it wasn't blue, so I need to paint a new segment of blue
				segmentsPainted++;
			}
			
			lastBlue = i;
		}
		
		if (penalties[i] <= x && lastBlue + 1 == i){ // It doesn't matter the color of this cell. I will paint it by blue just to extend the segment painted for the future (in case that the previous cell was blue)
			lastBlue = i;
		}
	}
	
	return segmentsPainted <= k; // If I paint less than k segments
}

ll rightBinarySearch(ll start, ll end, vector<ll> &penalties, string &s, ll k){
	// Note that if we satisfy penalty x, we also satisfy penalties in range [x+1, ... 1e9 + 1]
	// For that reason, we are doing binary search in reverse. In this start > end, so we need to + and - properly
	
    ll l = start + 1; 
    ll r = end - 1;

    while (l - r > 1){
        ll mid = (l + r)/2;

        if (lessPenaltyThan(penalties, s, k, mid)){
            l = mid;
        } else {
            r = mid;
        }
    }

    return l;
}

void solve(vector<ll> &penalties, string &s, ll k){
	// We will iterate over all the penalties and check if we are able to satisfy one
	// We want the minimum penalty in the range [0, ..., 1e9 + 1]
	ll minimumPenalty = rightBinarySearch(1e9 + 1, 0, penalties, s, k);
	cout << minimumPenalty << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		ll n, k;
		cin >> n >> k;
		
		string s;
		cin >> s;
		vector<ll> penalties(n);
		forn(i, n) cin >> penalties[i];
		solve(penalties, s, k);
	}
}
