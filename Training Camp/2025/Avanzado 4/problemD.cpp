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

int makeQuery(int a, int b, int c){
	cout << "? " << a << " " << b << " " << c << "\n";
	cout.flush();
	
	int res;
	cin >> res;
	return res;
}

void solve(){
	int n;
	cin >> n;
	
	int k = UNDEFINED;
	mt19937 rng(time(0));
	uniform_int_distribution<int> random_point(1, 3);	
	int a = 1, b = 2, c = 3;
	
	while (k != 0){
		k = makeQuery(a, b, c);
		if (k == 0) break;
		int p = random_point(rng);
		
		if (p == 1) a = k;
		else if (p == 2) b = k;
		else c = k;
	}
	
	cout << "! " << a << " " << b << " " << c << "\n";
	cout.flush();
}

int main()
{	
	int t;
	cin >> t;

	forn(_, t) solve();
	
    return 0;
}
