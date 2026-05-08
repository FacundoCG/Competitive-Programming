#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using ii = pair<ll,ll>;
using vii = vector<ii>;
using vvii = vector<vii>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
//~ const int MAX_N = 1e5 + 1;
int MOD = 1e9 + 7;
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

struct Problem{
	ll points, penalty, duration;
	bool operator <(Problem &other){ 
		if (penalty == 0) return false;
		if (other.penalty == 0) return true;
		return penalty*other.duration > duration*other.penalty;
	}
};

int n, T;

ll dp(int i, int j, vector<Problem> &A, vvl &memo){
	if (i == n) return 0;
	
	if (memo[i][j] == UNDEFINED){
		memo[i][j] = dp(i+1, j, A, memo);
		ll newTime = j + A[i].duration;
		if (newTime <= T)
		memo[i][j] = max(memo[i][j], dp(i+1, (int) newTime, A, memo) + max(0ll, A[i].points-newTime*A[i].penalty));
	}
	
	return memo[i][j];
}

void solve(){
	cin >> n >> T;

	vector<Problem> A;
	forn(_, n){
		ll points, penalty, duration; cin >> points >> penalty >> duration;
		A.pb(Problem(points, penalty, duration));
	}
	sort(all(A));
	vvl memo(n, vl(T+1, UNDEFINED));
	cout << dp(0, 0, A, memo) << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t = 1;
	//~ cin >> t;
	forn(_, t) solve();
	
	return 0;
}
