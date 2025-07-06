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

struct CountNumbers {
	string b;
	vector<vector<vl>> memo;
	
	CountNumbers(string &number) : b(number){
		memo.resize(SIZE(b), vector<vl>(10, vl(3, UNDEFINED)));
	}
	
	ll dp(int i, int lastDigit, int state){
		if (i >= SIZE(b)) return 1;
		int currentDigit = b[i] - '0';
		
		if (memo[i][lastDigit][state] == UNDEFINED){
			memo[i][lastDigit][state] = 0;

			if (state == 0){		
				forn(j, 10){
					if (j != lastDigit) memo[i][lastDigit][state] += dp(i+1, j, 0);
				}
			} else if (state == 1){
				forn(j, currentDigit+1){
					if (j == currentDigit && j != lastDigit) memo[i][lastDigit][state] += dp(i+1, j, 1);
					if (j != currentDigit && j != lastDigit) memo[i][lastDigit][state] += dp(i+1, j, 0);
				}
			} else {
				memo[i][lastDigit][state] += dp(i+1, 0, 2);
				forsn(j, 1, 10) memo[i][lastDigit][state] += dp(i+1, j, 0);
			}
		}
	
		return memo[i][lastDigit][state];
	}
	
	ll solve(){
		int firstDigit = b[0] - '0';
		ll res = dp(1, 0, 2);
		
		forsn(j, 1, firstDigit+1){
			int state = (j == firstDigit);
			res += dp(1, j, state);
		}
		
		return res;
	}
};

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	ll a, b;
	cin >> a >> b;
		
	string firstNumber = to_string(b);
	CountNumbers B(firstNumber);	
	ll res = B.solve();
	
	if (a != 0){
		string secondNumber = to_string(a-1);
		CountNumbers A(secondNumber);
		res -= A.solve();
	}
	
	cout << res << "\n";
		
    return 0;
}
