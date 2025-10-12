#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using ii = pair<int,int>;

template <typename T>
using vv = vector<vector<T>>;

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

ll solve(int l, int r, vl &B, vl &prefixSum){
	if (l > r) return 0;
	if (l == r) return B[l];
	
	int opt = l;
	
	for (int j = r-1; j >= l; j--){
		
	}
	
	return solve(l, opt-1, B, prefixSum) + solve(opt+1, r, B, prefixSum);
}

int main()
{	
	int t;
	cin >> t;
	
	forn(_, t){
		int n;
		cin >> n;
		
		vl A(n);
		forn(i, n) cin >> A[i];
		
		vl B;
		vl elements;
		
		int j = 0;
		
		while (j < n){
			B.pb(A[j]);
			bool flag = (A[j] == 1);
			int k = 1; j++;
			while (flag && j < n && A[j] == 1){k++; j++;}
			elements.pb(k);
		}
		
		vl prefixSum(SIZE(elements));
		prefixSum[0] = elements[0];
		forsn(i, 1, SIZE(elements)) prefixSum[i] = prefixSum[i-1] + elements[i];
		ll res = solve(0, SIZE(B)-1, B, prefixSum);
		cout << res << "\n";
	}
	
    return 0;
}
