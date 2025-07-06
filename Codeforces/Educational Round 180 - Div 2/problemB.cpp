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

typedef pair<int, int> interval;
int n;

bool belongsToTheInterval(interval &p1, int x){
    int startingTimeP1 = p1.first, endingTimeP1 = p1.second;
    return startingTimeP1 <= x && x <= endingTimeP1;
}

bool areDisjoint(interval &p1, interval &p2) {
    int startingTimeP1 = p1.first, endingTimeP1 = p1.second;
    int startingTimeP2 = p2.first, endingTimeP2 = p2.second;
    return endingTimeP1 < startingTimeP2 || endingTimeP2 < startingTimeP1;
}

void solve(vector<int> &A){
	int res = INF;
	
	forn(i, n-1){
		if (abs(A[i] - A[i+1]) <= 1){
			cout << 0 << "\n";
			return ;
		}
	}
	
	forn(i, n-1){
		interval p = {min(A[i], A[i+1]) - 1, max(A[i], A[i+1])+1};
		if (i - 1 >= 0 && belongsToTheInterval(p, A[i-1])){
			cout << 1 << "\n";
			return ;
		}
		
		if (i + 2 < n && belongsToTheInterval(p, A[i+2])){
			cout << 1 << "\n";
			return ;
		}
		
		// Ahora tengo que ver desde [0, i-1] cuantas operaciones tengo que hacer para obtener un elemento en p
		forsn(j, i+2, n-1){
			interval currentInterval = {min(A[j], A[j+1]), max(A[j], A[j+1])};
			if (!areDisjoint(p, currentInterval)){
				res = min(res, j-i+1);
				break;
			}
		}
		
		dforn(j, i-1){
			interval currentInterval = {min(A[j], A[j+1]), max(A[j], A[j+1])};
			if (!areDisjoint(p, currentInterval)){
				res = min(res, i-j-1);
				break;
			}
		}
	}
	
	if (res == INF) res = -1;
	cout << res << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);

	int t;
	cin >> t;
	
	forn(_, t){
		cin >> n;
		vector<int> A(n);
		forn(i, n) cin >> A[i];
		solve(A);
	}

    return 0;
}
