#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long ld;

using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()
#define SIZE(c) int((c).size())


#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "------------------" << endl

#define forn(i, n) for (int i=0;i<(int)(n); i++)
#define forsn(i, s, n) for (int i=(s);i<(int)(n); i++)

// Show vector

template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v){
    os << "[";
    forn(i, v.size()){
        if(i>0) os << ",";
        os << v[i];
    }
    return os << "]";
}

ll addMod(ll a, ll b, ll m = MOD){
	ll res = (a % m) + (b % m);
	res %= m;
	return res;
}

ll mulMod(ll a, ll b, ll m = MOD){
	ll res = (ll) (a % m) * (b % m);
	res %= m;
	return res;
}

vi pairsWithSum, pairsWithoutZero;

const int MAX_N = 800;
const int MAX_SUM = 2*800*9;
ll memo[MAX_N+1][MAX_SUM+1];

int getDifference(int x){
	if (x >= 0) return x;
	return abs(x) + 7200;
}

ll dp(int i, int difference){
	if (i == -1 && difference == 0) return 1;
	if (i == -1) return 0;
	
	int j = getDifference(difference);
	
	if (memo[i][j] == UNDEFINED){
		memo[i][j] = 0;
		
		forsn(d, 1, 10){
			int nPairs = pairsWithSum[d];
			if (i == 0) nPairs = pairsWithoutZero[d];
			ll toAdd = mulMod(dp(i-1, difference+d), nPairs);
			memo[i][j] = addMod(memo[i][j], toAdd);
			toAdd = mulMod(dp(i-1, difference-d), nPairs);
			memo[i][j] = addMod(memo[i][j], toAdd);
		}
	}
	
	return memo[i][j];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int q;
	cin >> q;
	
	//~ vector<vl> memo(800, vl(800*9*2+1, UNDEFINED));
	
	forn(i, MAX_N+1){
		forn(j, MAX_SUM+1) memo[i][j] = UNDEFINED;
	}
	
	pairsWithSum.resize(10, 0);
	pairsWithoutZero.resize(10, 0);
	
	forn(i, 10){
		forn(j, 10){
			if (i == j || i < j) continue;
			pairsWithSum[i-j]++;
			if (i != 0 && j != 0) pairsWithoutZero[i-j]++;
		}
	}
	
	forn(_, q){
		int n;
		cin >> n;
		cout << dp(n-1, 0) << "\n";
	}
	
	
    return 0;
}
