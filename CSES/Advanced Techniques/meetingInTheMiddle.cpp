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
 
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
unordered_map<ll, ll, custom_hash> calculateSumsOf(ll *C, ll m){
	ll limit = (ll) pow(2, m);
	
	unordered_map<ll, ll, custom_hash> sumsOfC;
	
	for(ll i = 0; i < limit; i++){
		ll currentSum = 0;
		ll currentIndex = 0;
		ll currentSubset = i;
		
		while (currentSubset > 0){
			if (currentSubset & 1) {
				currentSum += C[currentIndex];
			}
				
			currentSubset = currentSubset >> 1; 
			currentIndex++;
		}
				
		sumsOfC[currentSum]++;
	}
	
	return sumsOfC;
}
 
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	ll n, x;
    cin >> n >> x;
    
    ll A[n/2], B[(n+1)/2];
    forn(i, n/2) cin >> A[i];
    forn(i, (n+1)/2) cin >> B[i];
    
    unordered_map<ll, ll, custom_hash> sumsOfA;
    
    ll res = 0;
    ll limit = (ll) pow(2, n/2);
		
	for(ll i = 0; i < limit; i++){
		ll currentSum = 0;
		ll currentIndex = 0;
		ll currentSubset = i;
		
		while (currentSubset > 0){
			if (currentSubset & 1) currentSum += A[currentIndex];
			currentSubset = currentSubset >> 1; 
			currentIndex++;
		}
				
		sumsOfA[currentSum]++;
	}
    
        
    limit = (ll) pow(2, (n+1)/2);
		
	for(ll i = 0; i < limit; i++){
		ll currentSum = 0;
		ll currentIndex = 0;
		ll currentSubset = i;
		
		while (currentSubset > 0){
			if (currentSubset & 1) currentSum += B[currentIndex];
			currentSubset = currentSubset >> 1; 
			currentIndex++;
		}
			
		ll r = x - currentSum;
		if (sumsOfA.count(r)) res += sumsOfA[r];
	}
	
	cout << res << "\n";
}
