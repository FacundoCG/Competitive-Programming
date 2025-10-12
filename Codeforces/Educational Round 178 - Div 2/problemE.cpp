#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
//const int MAX_N = 1e5 + 1;
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

const int MAX_N = pow(10, 6);
int nextMemo[MAX_N];

// Calcular extremo izquierdo que cumple P(X)
int leftBinarySearch(int start, int end, vector<int> &A, int i){
    int l = start - 1; 
    int r = end + 1; 

    while(r - l > 1) { 
        int mid = (l + r) / 2;
        if(!(A[mid] >= i)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (r < start || r > end || !(A[r] >= i)){
		r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return r; // r es el primer elemento que cumple P(X)
}

int leftBinarySearch2(int start, int end, vector<int> &A, int i){
    int l = start - 1; 
    int r = end + 1; 

    while(r - l > 1) { 
        int mid = (l + r) / 2;
        if(!(A[mid] > i)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (r < start || r > end || !(A[r] > i)){
		r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return r; // r es el primer elemento que cumple P(X)
}

void solve(string &s, string &t, vector<vector<int>> &letters, vector<int> &memo){
	int lastIndex = -1;
	forn(i, SIZE(t)){
		int c = t[i] - 'a';
		lastIndex = leftBinarySearch2(0, SIZE(letters[c])-1, letters[c], lastIndex);
		if (lastIndex == -1) break;
		lastIndex = letters[c][lastIndex];
	}
		
	if (lastIndex == -1){
		cout << 0 << "\n";
	} else if (lastIndex + 1 == SIZE(s)){
		cout << 1 << "\n";
	} else {
		cout << memo[lastIndex+1] << "\n";
	}
}

int dp(int i, string &s, vector<vector<int>> &letters, vector<int> &memo){
	if (i >= SIZE(s) || i < 0) return 1;
	
	if (memo[i] == UNDEFINED){
		int k = nextMemo[i];	
		if (k == -1) {
			memo[i] = 1;
		} else {
			memo[i] = 1 + dp(k+1, s, letters, memo);	
		}
	}
	
	return memo[i];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
	int n, k, q;
	cin >> n >> k;
		
	string s;
	cin >> s;

	vector<vector<int>> letters(k);
	vector<int> memo(n, UNDEFINED);
	
	forn(i, n){
		int c = (int) s[i] - 'a';
		letters[c].pb(i);
	}
	
	vector<int> A(k, UNDEFINED);
	forn(i, k) {
		if (SIZE(letters[i]) != 0) A[i] = letters[i][0];	
	}
	
	nextMemo[0] = A[0];
	forsn(i, 1, k) {
		if (A[i] == UNDEFINED){
			nextMemo[0] = UNDEFINED;
		} else if (nextMemo[0] != UNDEFINED){
			nextMemo[0] = max(nextMemo[0], A[i]);
		}		
	}
	
	forsn(i, 1, n){
		int c = s[i-1] - 'a';
		int j = leftBinarySearch(0, SIZE(letters[c])-1, letters[c], i);
		if (j == -1) A[c] = -1;
		else A[c] = letters[c][j];
		
		if (nextMemo[i-1] == -1){
			nextMemo[i] = -1;
		} else if (A[c] == -1){
			nextMemo[i] = -1;
		} else {
			nextMemo[i] = max(nextMemo[i-1], A[c]);
		}		
	}
	
	
	forn(i, n) dp(i, s, letters, memo);
		
	cin >> q;
	forn(_, q){
		string t;
		cin >> t;
		solve(s, t, letters, memo);
	}
}
