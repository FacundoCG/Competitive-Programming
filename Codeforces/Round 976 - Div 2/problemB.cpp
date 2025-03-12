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

void solve(ll n, vector<ll> &powersOfK){
	ll res = 0;
	ll i = SIZE(powersOfK)-1;
	
	while (n > 0){
		if (n >= powersOfK[i]){
			ll operations = n/powersOfK[i];
			n -= powersOfK[i]*operations;
			res += operations;
		}
		
		i--;
	}
	
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
	
	forn(_, t){
		ll k;
		cin >> k;
		ll numberOfPerfectSquaresUntilK = sqrtl(k); // This is the biggest j such that: j^2 <= k. It means that I have the numbers [1, ..., j] which will be turned off
		// Now, I choose n = k + j
		// If the interval [k+1, ..., k+j] doesn't have any perfect square I am okey with this n
		// If I have a perfect square in the interval, it means that I will need to add 1 to n because j+1 didn't sum
		ll res = (ll) k + numberOfPerfectSquaresUntilK;
		
		ll nextPerfectSquare = (ll) (numberOfPerfectSquaresUntilK+1)*(numberOfPerfectSquaresUntilK+1);
		
		if (nextPerfectSquare <= res){
		   res++;
		}
		
		cout << res << "\n";
	}
}
