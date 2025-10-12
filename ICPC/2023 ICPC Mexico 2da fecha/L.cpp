#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

using vi = vector<int>;
using vvi = vector<vi>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;
const ld EPSILON = 1e-10;

#define pb push_back
#define fst first
#define snd second

#define esta(x, c) ((c).find(x) != (c).end())
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << "=" << (x) << endl;
#define RAYA cerr << "-----------" << endl;

#define forn(i, n) for(int i=0; i<(int)(n); i++)
#define forsn(i, s, n) for(int i=(s); i<(int)(n);i++)

template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v){
	os << "[";
	forn(i, SIZE(v)){
		if (i > 0) os << ",";
		os << v[i];
	}
	return os << "]";
}

// ######################## //

typedef tuple<double, double, double> velocidad;
int n;
double A, B, C;

//~ map<velocidad, int> memo[50];
int memo[50][501][501];
vi problem(50);

int sumProblemas = 0;

int f(int t1, int t2, int t3){
	double c1 = ceil(((double) t1)/ A);
	double c2 = ceil(((double) t2)/ B);
	double c3 = ceil(((double) t3)/ C);
	return (int) max(c1, max(c2, c3));
}

int dp(int i, int t1, int t2){
	if (i >= n) {
		int t3 = sumProblemas - t1 - t2;
		return f(t1, t2, t3);
	}
	
	if (memo[i][t1][t2] == UNDEFINED){
		memo[i][t1][t2] = dp(i+1, t1 + problem[i], t2);
		memo[i][t1][t2] = min(memo[i][t1][t2], dp(i+1, t1, t2 + problem[i]));
		memo[i][t1][t2] = min(memo[i][t1][t2], dp(i+1, t1, t2));
	}
	
	// O(50*500*500)
	
	return memo[i][t1][t2];
}

int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	cin >> n >> A >> B >> C;
	forn(i, n) {
		cin >> problem[i];
		sumProblemas += problem[i];
	}
	
	forn(i, n){
		forn(j, 501){forn(k, 501) memo[i][j][k] = UNDEFINED;}
	}
	
	int res = dp(0, 0, 0);
	cout << res << "\n";
	
	return 0;
}
