#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;
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
 
ll addMod(ll a, ll b, ll m){
	ll res = ((a % m) + (b % m)) % m;
	return res;
}
 
ll mulMod(ll a, ll b, ll m){
	ll res = ((a % m) * (b % m)) % m;
	return res;
}

ll lcm(ll a, ll b){
	ll res = mulMod(a/__gcd(a,b), b, MOD);
	return res;
}

vector<ll> calculateDivisors(ll n){
	vector<ll> res;
	
	for (int i = 1; i*i <= n; i++){
		if (n % i == 0) {
			res.pb(i); 
			if (n / i != i) res.pb(n/i);
		} 
	}
	
	sort(all(res));
	return res;
}

vector<vector<ll>> calculateMultiplesOfEachDivisor(vector<ll> &divisors){
	vector<vector<ll>> res(SIZE(divisors));
	
	forn(i, SIZE(divisors)){
		ll currentDivisor = divisors[i];
		forsn(j, i+1, SIZE(divisors)){
			if (divisors[j] % currentDivisor == 0) res[i].pb(j);
		}
	}
	
	return res;
}

int main() { 
    ll n;
    cin >> n;
    
    ll res = 0;
    
    // We want to identify all the pairs which satisfies a+b+c = n
    for(int c = 1; c <= n-2; c++){ // I fix the c in the range [1, ..., n-2]
		ll k = n-c; // Now we want to count the pairs which a+b = k. I know that gcd(a,b) | k. Then it has to be one of its divisors
		vector<ll> divisorsOfK = calculateDivisors(k); 
		vector<vector<ll>> multiplesOfEachDivisor = calculateMultiplesOfEachDivisor(divisorsOfK); // For the divisor at position i, I calculate which divisors in the range [i+1, ..., SIZE(divisors)-1] are its multiples
		vector<ll> pairsThatIDivide(SIZE(divisorsOfK)); // For the divisor j, pairsThatIDivide[j] tells you for how many pairs (a,b), j is the gcd(a,b)
		
		for (int i = SIZE(divisorsOfK)-1; i >= 0; i--){
			ll d = divisorsOfK[i]; // This is my current gcd(a,b)
			pairsThatIDivide[i] = (k-1)/d; // How many pairs in the range (1, k-1), (2, k-2), ..., (k-2, 2), (k-1, 1) I divide
			for (ll j : multiplesOfEachDivisor[i]) pairsThatIDivide[i] -= pairsThatIDivide[j]; // I substract the pairs that my multiples already used because they are the gcd
			ll toSum = mulMod(pairsThatIDivide[i], lcm(c, d), MOD); // Then I know how many pairs (a,b) have d as the gcd. I multiply this by the term of the sum
			res = addMod(res, toSum, MOD); 
		}
	}
	
	cout << res << "\n";
}
