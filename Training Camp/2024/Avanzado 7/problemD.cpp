#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
  

using namespace std;

typedef long long ll;
typedef long double ld;

#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update> 

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

// Calcular extremo derecho que cumple P(X)
ll rightBinarySearch(ll start, ll end, vector<ll> &yearOfStability, ll year){
    ll l = start - 1;
    ll r = end + 1;

    while (r - l > 1){
        ll mid = (l + r)/2;

        if (yearOfStability[mid] < year){
            l = mid;
        } else {
            r = mid;
        }
    }

    return l; // l es el ultimo elemento que cumple P(X)
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    ll n, m, q;
    cin >> n >> m >> q;
    
    vector<ll> cityHostedInYear(n);
    forn(i, n) cin >> cityHostedInYear[i];
    
    vector<ll> queries(q);
    forn(i, q) cin >> queries[i];

	vector<ll> cities(m+1);
	forn(i, n) cities[cityHostedInYear[i]]++;
	
	vector<pair<ll, ll>> citiesWithTimesHosted;
	forsn(i, 1, m+1) citiesWithTimesHosted.pb({cities[i], i});
	sort(all(citiesWithTimesHosted));
	
	vector<ll> prefixSum(m+1, 0);
	forsn(i, 1, m+1) prefixSum[i] = prefixSum[i-1] + citiesWithTimesHosted[i-1].first;
	
	vector<ll> yearOfStabilityForCity(m+1);
	forsn(i, 1, m+1) yearOfStabilityForCity[i] = (i-1)*citiesWithTimesHosted[i-1].first - prefixSum[i-1];
	forsn(i, 1, m+1) yearOfStabilityForCity[i] += n; 
	
	vector<vector<ll>> queriesForYearOfStability(m+1); 
	vector<pair<ll,ll>> pairsOfQueries;

	forn(i, q){
		ll year = queries[i];
		ll c = rightBinarySearch(1, m, yearOfStabilityForCity, year);
		ll stabilityYearPreviousTo = yearOfStabilityForCity[c];	
		ll yearsLeft = year - stabilityYearPreviousTo;
		ll kthNumberOfCity;
		
		if (yearsLeft % c != 0) kthNumberOfCity = yearsLeft % c;
		else kthNumberOfCity = c; 
		
		pairsOfQueries.pb({c, kthNumberOfCity});
		queriesForYearOfStability[c].pb(kthNumberOfCity);
	}
	
	map<ll, map<ll, ll>> resQueries;
	ordered_set v;
	v.insert(0);
	
	forsn(i, 1, m+1){
		ll numberOfCity = citiesWithTimesHosted[i-1].second;
		v.insert(numberOfCity);
		for (auto k : queriesForYearOfStability[i]){
			ll desiredCity = *v.find_by_order(k);
			resQueries[i][k] = desiredCity;
		}
	}
	
	forn(i, q){
		ll yearOfStability = pairsOfQueries[i].first;
		ll k = pairsOfQueries[i].second;
		cout << resQueries[yearOfStability][k] << "\n";
	}
}
