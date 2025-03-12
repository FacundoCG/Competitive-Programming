#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 998244353;
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

int leftOne(vector<ll> &A){
	int res = SIZE(A);
	forn(i, SIZE(A)){
		if(A[i] == 1){
			res = i;
			break;
		}
	}
	
	return res;
}

int rightThree(vector<ll> &A){
	int res = -1;
	dforn(i, SIZE(A)){
		if(A[i] == 3){
			res = i;
			break;
		}
	}
	
	return res;
}

ll subMod(ll a, ll b, ll m){
	ll res = ((a - b) % m + m) % m;
	return res;
}

ll addMod(ll a, ll b, ll m){
	ll res = ((a % m) + (b % m)) % m;
	return res;
}

ll mulMod(ll a, ll b, ll m){
	ll res = ((a % m) * (b % m)) % m;
	return res;
}

ll binPowMod(ll base, ll exp, ll m){
	if (exp == 0) return 1;
	
	ll a = binPowMod(base, exp/2, m);
	ll res = mulMod(a, a, m);
	
	if (exp % 2 == 1) res = mulMod(res, base, m);
	return res;
}

ll divideMod(ll a, ll b, ll m){
	// Remember that b = 2^suf[i]
	// The b^-1 is b^{m-2} % m;
	// This is because the m that we are using is prime and we can apply fermat's little theorem
	// (a/b) % m = (a % m * b^-1 % m) % m
	ll res = mulMod(a % m, binPowMod(b, m-2, m) % m, m) % m; 
	return res;
}

void solve(vector<ll> &B){
	ll res = 0;
	ll numberOfOnes = 0;
	vector<ll> onesForEachThree(SIZE(B), 0);
	ll emptySetsCounted = 0;
	
	forn(i, SIZE(B)){
		if (B[i] == 1) numberOfOnes++;
		else if (B[i] == 3){
			onesForEachThree[i] = numberOfOnes;
			emptySetsCounted += onesForEachThree[i];
		}
	}
	
	vector<ll> suf(SIZE(B)+1, 0);
	dforn(i, SIZE(B)) suf[i] = suf[i+1] + (B[i] == 2);
	
	ll d = 0;
	
	forn(i, SIZE(B)){
		if (B[i] == 1){
			d = addMod(d, binPowMod(2, suf[i], MOD), MOD); // I count all the twos that I have between [i+1, ..., n]
		} else if (B[i] == 3){
			res = addMod(res, divideMod(d, binPowMod(2, suf[i], MOD), MOD), MOD); // I add the pairs (1,3) that sum subsequences
			// The second term divides the acumulative sum, taking off the 2s that shouldn't have been taken. My idea was divide by 2^suf[i]. The thing is that we are taking % MOD, so we have to multiply by the inverse of that number
		}
	}
	
	res = subMod(res, emptySetsCounted, MOD);
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
        
    forn(_, t){
		ll n;
		cin >> n;
		
		vector<ll> A(n);
		forn(i, n) cin >> A[i];
		
		int l = leftOne(A);
		int r = rightThree(A);
		
		vector<ll> B;
		forsn(i, l, r+1) B.pb(A[i]);
		solve(B);
	}
}
