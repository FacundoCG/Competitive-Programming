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
using vvvvl = vector<vvvl>;
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

const int N_OF_POWERS = 26;
int powersOfTwo[N_OF_POWERS+1];

const int MAX_SIZE = (1 << 26);
int indexsFor[MAX_SIZE];

void solve(){
	int n; cin >> n;
	string s; cin >> s;
	s = "." + s;
	
	memset(indexsFor, -1, sizeof(indexsFor));
	indexsFor[0] = 0;
	int currentBitMask = 0, res = 0;
	
	forsn(i, 1, n+1){
		int indexLetter = (int)(s[i] - 'a');
		currentBitMask = currentBitMask ^ powersOfTwo[indexLetter];
		if (indexsFor[currentBitMask] != -1) res = max(res, i-indexsFor[currentBitMask]);
		
		forn(j, 26){
			int usefulBitMask = currentBitMask ^ powersOfTwo[j]; // Me sobra un solo elemento
			if (indexsFor[usefulBitMask] != -1) res = max(res, i-indexsFor[usefulBitMask]);
		}
		
		if (indexsFor[currentBitMask] == -1) indexsFor[currentBitMask] = i;
	}
	
	cout << res << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	powersOfTwo[0] = 1;
	forsn(i, 1, N_OF_POWERS) powersOfTwo[i] = powersOfTwo[i-1]*2;
	
	int t = 1;
	//~ cin >> t;
	forn(_, t) solve();
	
    return 0;
}
