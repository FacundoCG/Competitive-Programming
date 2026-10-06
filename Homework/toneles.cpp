#include <bits/stdc++.h>
using namespace std;
#define for1(i, n) for(int i = 1; i <= (n); ++i)
#define repeat(n) for1(_, n)
#define forn(i, n) for(int i = 0; i < (n); ++i)
#define forsn(i, s, n) for(int i = (s); i < (n); ++i)
#define dbg(x) cout << #x << " = " << (x) << endl;
#define SIZE(c) int((c).size())
using ll = long long;
using lll = __int128;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvi = vector<vi>;
using ii = pair<ll, int>;
using vii = vector<ii>;
using vvii = vector<vii>;
using vb = vector<bool>;

const ll MOD = 1e9 + 7;
const ll LINF = 1e18;
const short INF = 1e3;

#define pb push_back
#define fst first
#define snd second
#define esta(x, c) (c.find(x) != c.end())
#define all(c) (c).begin(), (c).end()

int L, n;
vi A;

ll ceilOf(ll a, ll b){ return (a+b-1)/b; }

void solve(){
	cin >> L >> n; 
	
	A.resize(n); forn(i, n) cin >> A[i];	
		
	vl prefixSum(n);
	prefixSum[0] = A[0];
	forsn(i, 1, n) prefixSum[i] = prefixSum[i-1] + A[i];
	
	ll res = 0;
	forn(i, n) res += ceilOf(prefixSum[i], L);
	
	int optimalPlay = -1;
	forn(i, n){
		
		// Quiero ver si el movimiento de lo que habia en i mejoro las cosas
		ll oldTerm = ceilOf(prefixSum[i], L);
		ll newTerm = ceilOf(prefixSum[i] - A[i], L);
		ll currentRes = res - oldTerm + newTerm;
		if (currentRes < res) optimalPlay = i+1;
	}
	
	cout << res << "\n";
	cout << optimalPlay << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
		
	int t = 1;
	forn(_, t) solve();
}
