#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int N_INF = (-1)*1e9;
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

int n;
vector<int> A, cap;

int dp(int c, int k, int i, vector<vector<vi>> &memo){
	if (c < 0 || k < 0) return N_INF;
	if (k == 0 && c != 0) return N_INF;
	if (k != 0 && i == n) return N_INF;
	if (k == 0 && c == 0) return 0;
	
	if (memo[c][k][i] == UNDEFINED){
		memo[c][k][i] = max(dp(c, k, i+1, memo), A[i] + dp(c - cap[i], k-1, i+1, memo));
	}
	
	return memo[c][k][i];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> n;
	
	A.resize(n);
	cap.resize(n);

	forn(i, n){
		cin >> cap[i];
		cin >> A[i];
	}
	
	int capacidadMax = 0, aguaTotal = 0;
	forn(i, n) capacidadMax += cap[i];
	forn(i, n) aguaTotal += A[i];
		
	vector<vector<vi>> memo(capacidadMax+1, vector<vi>(n+1, vi(n, UNDEFINED)));

	forsn(k, 1, n+1){
		ld res = 0;
		
		forsn(c, 1, capacidadMax+1){
			int aguaUsada = dp(c, k, 0, memo);
			ld currentRes = (ld) ((ld) aguaTotal + (ld) aguaUsada)/2.0;
			currentRes = min(currentRes, (ld) c);
			res = max(res, currentRes);
		}
				
		cout << setprecision(numeric_limits<ld>::digits10 + 1); // Muestra con full precision para ld
		cout << res << " ";
	}
	
	cout << "\n";
	
    return 0;
}
