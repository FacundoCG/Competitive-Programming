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
typedef pair<int, int> interval;

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, k;
	cin >> n >> k;
	
	vi A(n), B;
	map<int, int> repeticiones;
	set<interval> s;

	forn(i, n) cin >> A[i];
	forn(i, k) {
		B.pb(A[i]);
		repeticiones[A[i]]++;
	}
	
	sort(all(B));
	int startInterval = B[0], endInterval = B[0];
	forsn(i, 1, k){
		if (B[i] > endInterval+1){ // Nuevo intervalo disjunto
			s.insert({startInterval, endInterval});
			startInterval = B[i], endInterval = B[i];
		} else if (B[i] == endInterval+1){
			endInterval++;
		}
	} 
	
	s.insert({startInterval, endInterval});
	
	forsn(i, k, n){
		repeticiones[A[i-k]]--;
		if (repeticiones[A[i-k]] == 0){
			// Parto el intervalo en el que se encuentra
			interval toDelete = {A[i-k], A[i-k]};
			auto it = s.lower_bound(toDelete);
			if ((*it).fst > A[i-k]) it--;
			
		}
		
		repeticiones[A[i]]++;
		if (repeticiones[A[i]] == 1){
			// Tengo que ver de agregar este nuevo intervalo
		}
		
		interval p = *s.begin();
		if (p.fst != 0){
			cout << "0 ";
		} else {
			cout << p.snd + 1 << " ";
		}
	}
	
	cout << "\n";
	
    return 0;
}
