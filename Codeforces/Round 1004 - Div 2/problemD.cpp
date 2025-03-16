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

ll findMissingElement(set<ll> &s, ll n){
	ll res = 1;
	
	forsn(i, 1, n+1){
		if (!esta(i, s)) res = i;
	}
	
	return res;
}

ll findIndexOf(vector<ll> &A, ll elem){
	ll res = 0;
	
	forn(i, SIZE(A)){
		if (A[i] == elem) res = i;
	}
	
	return res;
}

void makeQuery(ll i, ll j){
	cout << "? " << i << " " << j << endl; 
	cout.flush();
}

int solve(vector<ll> &A){
	set<ll> s(all(A));
	ll n = SIZE(A);
	ll resQuery;
	
	if (SIZE(s) == SIZE(A)){
		ll i = findIndexOf(A, n)+1;
		ll j = findIndexOf(A, 1)+1;
		makeQuery(i, j);
		cin >> resQuery;
		
		if (resQuery < n-1) cout << "! A" << endl;
		else if (resQuery >= n) cout << "! B" << endl;
		else {
			makeQuery(j, i);
			cin >> resQuery;
			
			if (resQuery != n-1) cout << "! A" << endl;				
			else cout << "! B" << endl;
		}
	} else {
		ll missingElement = findMissingElement(s, n);
		ll i = 1;
		if (missingElement == i) i = 2; 
		makeQuery(missingElement, i);
		cin >> resQuery;
		
		if (resQuery != 0) cout << "! B" << endl;
		else cout << "! A" << endl; // I have repetitions of points so it has to be a graph
	}
	
	cout.flush();
	
	return 0;
}

int main() {
    int t;
    cin >> t;
	
	forn(_, t){
        ll n;
        cin >> n;
        
        vector<ll> A(n);
        forn(i, n) cin >> A[i];
        solve(A);
	}
}
