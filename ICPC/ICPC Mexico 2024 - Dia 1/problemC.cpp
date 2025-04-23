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
int n;

bool customCompare(pair<int, int> p1, pair<int, int> p2){
	int minutesp1 = p1.fst*3;
	int minutesp2 = p2.fst*3;
	
	if (minutesp1 < minutesp2){
		return true;
	} else if (minutesp1 > minutesp2){
		return false;
	}
	
	return p1.snd > p2.snd;
}

int dp(int i, int m, vector<vector<int>> &memo, vector<pair<int, int>> &A){
	if (m > 480 || i >= n){
		return 0;
	}
	
	if (memo[i][m] == UNDEFINED){
		memo[i][m] = 0;
		pair<int, int> book = A[i];
		int newTime = m + book.fst*3;
		if (newTime <= 780){
			memo[i][m] = book.snd + dp(i+1, newTime, memo, A);
		}
	}
	
	return memo[i][m];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    cin >> n;
    
    vector<pair<int, int>> booksPerFame(n);
    vector<pair<int, int>> booksPerPleasure(n);
    vector<vector<int>> memoPleasure(n, vector<int>(781, UNDEFINED));
    vector<vector<int>> memoFame(n, vector<int>(781, UNDEFINED));
  
    forn(i, n){
		int p;
		cin >> p;
		booksPerFame[i] = {p, 0};
		booksPerPleasure[i] = {p, 0};
	}
	
	forn(i, n){
		int p;
		cin >> p;
		booksPerPleasure[i].snd = p;
	}
	
	forn(i, n){
		int f;
		cin >> f;
		booksPerFame[i].snd = f;
	}
	
	sort(all(booksPerPleasure), customCompare);
	sort(all(booksPerFame), customCompare);
	
	int maxFame = dp(0, 0, memoFame, booksPerFame);
	int maxPleasure = dp(0, 0, memoPleasure, booksPerPleasure);
	
	if (maxFame == maxPleasure){
		cout << "EITHER" << "\n";
	} else if (maxFame < maxPleasure){
		cout << "PLEASURE" << "\n";
	} else {
		cout << "FAME" << "\n";
	}
}
