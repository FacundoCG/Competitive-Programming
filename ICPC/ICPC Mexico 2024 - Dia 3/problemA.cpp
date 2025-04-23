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

#define forn(i,n) for (int i=0;i<(int)(n);++i)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);++i)
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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

// Template definition
template<typename T>
using ordered_set = tree<
    T,                      // Key type
    null_type,              // Mapped type (use null_type for set)
    less<T>,                // Comparator
    rb_tree_tag,            // Underlying tree type
    tree_order_statistics_node_update>; // Node update


const int MAX_N = pow(10, 4);
int memo[MAX_N][MAX_N];
int A[MAX_N];

int main() { 
	ios :: sync_with_stdio(0);
    cin.tie(0);
	
    int n;
    scanf("%d", &n);
    forn(i, n) scanf("%d", &A[i]);
    
    forn(i, n){
		multiset<int> s;
		s.insert(A[i]);
		
		forsn(j, i+1, n){
			if (j == i+1) memo[i][j-1] = INF;
			memo[i][j] = memo[i][j-1];
			auto it = s.insert(A[j]);
			auto prev = it, next = it;
			
			if (it != s.begin()){
				prev--;
				memo[i][j] = min(memo[i][j], abs(A[j] - *prev));
			}
			
			next++;
			if (next != s.end()){
				memo[i][j] = min(memo[i][j], abs(A[j] - *next));
			}
		}
	}
	
	int q;
	scanf("%d", &q);
	
	forn(_, q){
		int l, r;
		scanf("%d %d", &l, &r);		
		l--; r--;
		printf("%d\n", memo[l][r]);
	}
}
