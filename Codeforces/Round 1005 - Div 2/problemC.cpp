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

vector<ll> compress(vector<ll> &A){
	vector<ll> res;
	res.pb(A[0]);
	int lastIndex = 0;
	
	forsn(i, 1, SIZE(A)){
		if ((res[lastIndex] < 0 && A[i] < 0) || (res[lastIndex] >= 0 && A[i] >= 0)){
			res[lastIndex] += A[i];
		} else {
			res.pb(A[i]);
			lastIndex = SIZE(res)-1;
		}
	}
	
	return res;
}

void solve(vector<ll> &A){
	vector<ll> B = compress(A);
	vector<ll> prefixPositive;
	vector<ll> suffixNegative;
	ll res = 0;
	
	forn(i, SIZE(B)){
		if (B[i] >= 0) prefixPositive.pb(B[i]);
		else suffixNegative.pb(abs(B[i]));
	}
	
	forsn(i, 1, SIZE(prefixPositive)) prefixPositive[i] += prefixPositive[i-1];
	dforn(i, SIZE(suffixNegative)-1) suffixNegative[i] += suffixNegative[i+1];
	
	ll extra = 0;
	
	if (B[0] < 0) extra++;
	
	if (!suffixNegative.empty()) res = suffixNegative[0]; // I pick all the negatives and zero positives
		
	forn(i, SIZE(prefixPositive)){ // I pick the first i positives and the last m-i negatives
		ll currentSum = prefixPositive[i];
		if (i+extra < SIZE(suffixNegative)) currentSum += suffixNegative[i+extra];
		res = max(res, currentSum);
	}
	
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_,t){
		int n;
		cin >> n;
		vector<ll>A(n);
		forn(i, n) cin >> A[i];
		solve(A);
    }
}
