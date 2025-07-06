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
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;
    vector<int> A(n);
    forn(i, n) cin >> A[i];
    map<int, int> positionSeen;
    set<int> s;
    
    int res = 0;
    forn(i, n){
		if (!esta(A[i], s)){ // If this element isn't in the sequence, I add it and update its position
			s.insert(A[i]);
			positionSeen[A[i]] = i;
		} else { // If the element is in the sequence it means that I can't expand it anymore, I will add it to the sequence but I will delete all from: [startSequence, positionSeen[A[i]]]
			// I know that the old sequence finished at i-1. And It started at (i-1) - start + 1 = SIZE(s) // i - SIZE(s)
			int start = i - SIZE(s);
			forsn(j, start, positionSeen[A[i]]) s.erase(A[j]);
			positionSeen[A[i]] = i;
		}
		
		res = max(res, SIZE(s));
	}
	
	cout << res << "\n";
}
