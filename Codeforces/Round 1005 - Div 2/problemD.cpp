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

ll calculatePosition(ll x){
	bitset<32> binaryDigitsOfX(x);
	for (int i = 31; i >= 0; i--){
		if (binaryDigitsOfX[i]) return i;
	}
	
	return UNDEFINED;
}

ll leftBinarySearch(ll start, ll end, vector<ll> &B, ll x){
	ll l = start - 1; 
	ll r = end + 1; 

	while(r - l > 1) { 
		ll mid = (l + r) / 2;
		if(!(x < B[mid])) {
			l = mid;
		} else {
			r = mid;
		}
	}

	if (r < start || r > end || !(x < B[r])) return UNDEFINED;

	return r; // r es el primer elemento que cumple P(X)
}

vector<ll> calculatePrefixXor(vector<ll> &A){
	vector<ll> res(SIZE(A));
	res[0] = A[0];
	forsn(i, 1, SIZE(A)) res[i] = res[i-1] ^ A[i];
	return res;
}

void solveQuery(vector<ll> &A, ll x, vector<ll> &prefixXorOfA, vector<vector<ll>> &B){
	ll res = 0;
	ll currentIndex = -1; // I start outside the array A
	ll lastIndex = -1;
	bool p = true;
		
   while (p){
	   if (x == 0){
		res = currentIndex+1;
		break;
	   }
	   
		ll j = calculatePosition(x);
		ll newIndex = INF;
		ll isBit = UNDEFINED;
		
		forsn(i, j, 32){
			ll possibleIndex = leftBinarySearch(0, SIZE(B[i])-1, B[i], currentIndex);
			if (possibleIndex != UNDEFINED && B[i][possibleIndex] < newIndex) {
				newIndex = B[i][possibleIndex];
				isBit = i;
			}
		}
		
		lastIndex = currentIndex;
		currentIndex = newIndex;

		if (isBit == UNDEFINED){
			res = SIZE(A);
			p = false;
		} else if (isBit == j) {
			if (currentIndex > 0) x ^= prefixXorOfA[currentIndex-1];
			if (lastIndex >= 0) x = x ^ prefixXorOfA[lastIndex];
			
			if (x >= A[currentIndex]){
				x ^= A[currentIndex];
			} else {
				res = currentIndex;
				p = false;
			}
		} else { 
			res = currentIndex;
			p = false;
		}
	}
	
	cout << res << " ";
}

void solve(vector<ll> &A, vector<ll> &queries){
	vector<ll> prefixXorOfA = calculatePrefixXor(A);
	vector<vector<ll>> B(32); // B[i] will give you all the indexs j of array A where mostSignificantOne(A[j]) is at position i
	
	forn(i, SIZE(A)){
		ll positionOfMostSignificantOne = calculatePosition(A[i]);
		B[positionOfMostSignificantOne].pb(i);
	}
	   
	forn(i, SIZE(queries)){
		ll x = queries[i];
		solveQuery(A, x, prefixXorOfA, B);
	}
	
	cout << "\n";
}

int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
 
	ll t;
	cin >> t;
	
	forn(_, t){
		ll n, q;
		cin >> n >> q;
		
		vector<ll> A(n);
		forn(i, n) cin >> A[i];
		reverse(all(A));
		
		vector<ll> queries(q);
		forn(i, q) cin >> queries[i];
		solve(A, queries);
	}
}
