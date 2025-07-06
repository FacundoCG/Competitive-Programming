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

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

template <typename T>
using ordered_multiset = tree<
    pair<T, int>,
    null_type,
    less<pair<T, int>>, // NOT less_equal
    rb_tree_tag,
    tree_order_statistics_node_update
>;

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, k;
	cin >> n >> k;
	
	vi A(n);
	forn(i, n) cin >> A[i];
	
	ll currentInversions = 0;
	ordered_multiset<int> s;
	
	forn(i, k){
		pair<int, int> p = {A[i], n};
		currentInversions += SIZE(s) - s.order_of_key(p);
		p.snd = i;
		s.insert(p);
	}
	
	cout << currentInversions << " ";
	
	forsn(i, k, n){
		int toDelete = A[i-k];
		pair<int, int> p1 = {toDelete, -1}, p2 = {A[i], n};
		//~ DBG(s.order_of_key(p1));
		currentInversions -= s.order_of_key(p1);
		s.erase({toDelete, i-k});
		//~ DBG(s.order_of_key(p2));
		currentInversions += SIZE(s) - s.order_of_key(p2);
		p2.snd = i;
		s.insert(p2);
		cout << currentInversions << " ";
	}
	
	cout << "\n";
	
    return 0;
}
