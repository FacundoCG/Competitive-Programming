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

int n;

bool isGood(vi &P, string &s){
	vi maxPrefix(SIZE(P), 0), minSuffix(SIZE(P), INF);
	bool res = true;
	
	maxPrefix[1] = P[1];
	forsn(i, 2, SIZE(P)) maxPrefix[i] = max(maxPrefix[i-1], P[i]);
	
	minSuffix[n] = P[n];
	dforsn(i, 1, n) minSuffix[i] = min(minSuffix[i+1], P[i]);
	
	forn(i, SIZE(s)){
		if (s[i] == '1') continue;
		int currentIndex = i+1;
		
		if (currentIndex == 1){
			res &= (P[currentIndex] > minSuffix[currentIndex]);
		} else if (currentIndex == SIZE(P)-1){
			res &= (P[currentIndex] < maxPrefix[currentIndex]);
		} else {
			res &= (P[currentIndex] < maxPrefix[currentIndex] || P[currentIndex] > minSuffix[currentIndex]);
		}
	}
	
	return res;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		cin >> n;
		string s;
		cin >> s;
		
		vi P(n+1), onePositions;
		forn(i, n){
			if (s[i] == '1') {
				P[i+1] = i+1;
				onePositions.pb(i+1);
			}
		}
		
		int lastIndex = 1;
		
		forn(i, SIZE(onePositions)){
			int currentIndex = onePositions[i];
			int currentElement = currentIndex-1;
			
			forsn(j, lastIndex, currentIndex){
				P[j] = currentElement;
				currentElement--;
			} 
			
			lastIndex = currentIndex+1;
		}
		
		int currentElement = n;
		forsn(i, lastIndex, n+1){
			P[i] = currentElement;
			currentElement--;
		}
		
		//~ forsn(i, 1, n+1) cout << P[i] << " ";
		
		if (isGood(P, s)){
			cout << "YES\n";
			forsn(i, 1, n+1) cout << P[i] << " ";
			cout << "\n";
		} else {
			cout << "NO\n";
		}
	}
	
    return 0;
}
