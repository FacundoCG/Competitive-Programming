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

void solve(vector<ll> &A, map<ll, ll> &repetitions){	
	ll l = UNDEFINED;
	ll r = UNDEFINED;
	ll newL = 0;
	ll newR = 0;
	ll flag = true;
	
	forn(i, SIZE(A)){
		if (repetitions[A[i]] == 1){
			if (flag){ // I need to set a new segment
				newL = i;
				newR = i;
				flag = false;
			} else {
				newR++; // I have already set a segment so I just need to expand the previous one
			}
			
			if (newR - newL >= r - l){ // If the current segment is betten than the [l,r] previous selected, we update those vlaues
				r = newR;
				l = newL;
			}
		} else {
			flag = true; // I need to set a new segment because I can't delete this element
		}
	}
	
	if (l != UNDEFINED){
		cout << l+1 << " " << r+1 << "\n";
	} else {
		cout << 0 << "\n";
	}
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		int n;
		cin >> n;
		
		vector<ll> A(n);
		map<ll, ll> repetitions;
		
		forn(i, n){
			cin >> A[i];
			repetitions[A[i]]++;
		}
		
		solve(A, repetitions);
	}
}
