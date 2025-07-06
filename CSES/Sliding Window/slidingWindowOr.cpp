#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

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

// Show pair
template <typename T1, typename T2>
ostream & operator <<(ostream &os, const pair<T1, T2> &p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

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

int addMod(int a, int b, int m = MOD){
    int res = ((a % m) + (b % m)) % m;
    return res;
}
 
int mulMod(int a, int b, int m = MOD){
	ll resLL = (ll) (a % m) * (b % m);
	resLL %= m;
	int res = (int) resLL;
    return res;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, k;
	cin >> n >> k;
	
	vector<int> A(n);
	//~ vector<vector<int>> B(n, vector<int>(32, 0));
	vector<int> currentRes(32, 0);

	int x, a, b, c;
	cin >> x >> a >> b >> c;
	
	int j, v;
	//~ ll asd = (ll) 1 << 31;
	//~ DBG(asd);
	
	//~ forn(i, n){
		//~ if (i == 0) A[0] = x;
		//~ else A[i] = addMod(mulMod(a, A[i-1], c), b, c);
		
		//~ v = A[i], j = 0;
		//~ while (v > 0){
			//~ if (v & 1) B[i][j] = 1;
			//~ if (i < k) currentRes[j] += B[i][j];
			//~ v /= 2; j++;
		//~ }
	//~ }
		
	//~ ll currentOr = 0;
	//~ forn(i, 32) {
		//~ if (currentRes[i]) {
			//~ ll toAdd = (ll) 1 << i;
			//~ currentOr = currentOr | toAdd;
		//~ }
	//~ }
	
	//~ ll res = currentOr;
	
	//~ forsn(i, k, n){
		//~ currentOr = 0;
		//~ forn(h, 32) {
			//~ currentRes[h] = currentRes[h] - B[i-k][h] + B[i][h];
			//~ ll toAdd = (ll) 1 << h;
			//~ if (currentRes[h]) currentOr = currentOr | toAdd;
		//~ }

		//~ res ^= currentOr;
	//~ }
	
	//~ cout << res << "\n";
	cout << n << "\n";
    return 0;
}
