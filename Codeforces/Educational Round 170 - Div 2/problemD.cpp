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


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //

vector<int> calculatePrefixSum(vector<int> &A){
	vector<int> prefixSum(SIZE(A));
	prefixSum[0] = A[0];
	forsn(i, 1, SIZE(A)) prefixSum[i] = prefixSum[i-1] + A[i];
	return prefixSum;
}

void calculateThePrefixSumForMatrix(vector<vector<int>> &prefixMatrix, vector<vector<int>> &A){	
	forn(i, SIZE(prefixMatrix)){
		prefixMatrix[i] = calculatePrefixSum(A[i]);
	}
}

int dp(int i, int j, vector<vector<int>> &memo, vector<vector<int>> &intelligenceChecksLessThan, vector<vector<int>> &strengthChecksLessThan){
	if (i == SIZE(memo)){ // It means that I have already collected all the points of attribute
		return 0;
	} 
	
	if (memo[i][j] == UNDEFINED){ // If I have j strength points, I want to know how many checks I can pass from the i-th update of points
		// I have two options: add one point to strength (j+1) or add one point to intelligence (i-j)1
		int option1 = strengthChecksLessThan[i][j+1] + intelligenceChecksLessThan[i][i-j] + dp(i+1, j+1, memo, intelligenceChecksLessThan, strengthChecksLessThan);
		int option2 = strengthChecksLessThan[i][j] + intelligenceChecksLessThan[i][i-j+1] + dp(i+1, j, memo, intelligenceChecksLessThan, strengthChecksLessThan);
		memo[i][j] = max(option1, option2);
	}
	
	return memo[i][j];
}

void solve(int m, vector<vector<int>> &intelligenceChecksLessThan, vector<vector<int>> &strengthChecksLessThan){
	vector<vector<int>> memo(m, vector<int>(m+1, UNDEFINED));
	int res = dp(0, 0, memo, intelligenceChecksLessThan, strengthChecksLessThan);
	cout << res << "\n";
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
	int n, m;
	cin >> n >> m;
	
	// From the attribute points i before the attribute points i+1, it tells you how many attributes check of intelligence j are
	// attributesIntelligenceFrom[i][j]
	vector<vector<int>> attributesIntelligenceFrom(m, vector<int>(m+1,0));
	vector<vector<int>> attributesStrengthFrom(m, vector<int>(m+1,0));
	
	int j = -1;
	
	forn(i, n){
		int r;
		cin >> r;
		
		if (r == 0){
			j++;
		} else if (r > 0 && j != UNDEFINED){
			attributesIntelligenceFrom[j][r]++;
		} else if (j != UNDEFINED){
			attributesStrengthFrom[j][abs(r)]++;
		}
	}
	
	// Now, I will calculate the prefixSum of each vector, which basically tells you for the attribute point i, how many attribute check of intelligence <= j are
	vector<vector<int>> intelligenceChecksLessThan(m, vector<int>(m+1,0));
	vector<vector<int>> strengthChecksLessThan(m, vector<int>(m+1,0));
	calculateThePrefixSumForMatrix(intelligenceChecksLessThan, attributesIntelligenceFrom);
	calculateThePrefixSumForMatrix(strengthChecksLessThan, attributesStrengthFrom);
	
	solve(m, intelligenceChecksLessThan, strengthChecksLessThan);
};
