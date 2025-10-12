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

void printBitSet(bitset<64> &C){
	forn(i, 64) cout << C[i];
	cout << "\n";
}

int countOnes(bitset<64> &C){
	int res = 0;
	
	forn(i, 64){
		if (C[i] == 1) res++;
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
		ll n, k;
		cin >> n >> k;
		vector<ll> A(n);
		forn(i, n) cin >> A[i];
		
		vector<bitset<64>> B(n);
		forn(i, n) B[i] = bitset<64>(A[i]);
		
		ll maxValue = 0;
		
		forn(i, 63){
			forn(j, n){
				if (B[j][i] == 0){
					ll neccesary = 1LL << i;
					if (neccesary <= k){
						B[j][i] = 1;
						k -= neccesary;
					}
				}
			}
		}
		
		forn(i, n) maxValue += countOnes(B[i]);
		cout << maxValue << "\n";
	}
	
    return 0;
}
