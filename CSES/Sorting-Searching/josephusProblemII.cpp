#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

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

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 

int n, k;

int elementToJump(ordered_set &s, int newPosition){
	if (SIZE(s) <= newPosition) newPosition = newPosition - SIZE(s);
	return *s.find_by_order(newPosition);
}

void solve(){
	ordered_set s;
	forsn(i, 1, n+1) s.insert(i);
	
	vi res;
	
	int currentElement = 1;
	
	while (!s.empty()){
		// Estoy parado en la posición i. Quiero borrar la i+k, y mover a i+k+1		
		int salto = k % SIZE(s);
		int i = s.order_of_key(currentElement);
		int aBorrar = elementToJump(s, i+salto);
		currentElement = elementToJump(s, i+salto+1);
		s.erase(aBorrar);
		res.pb(aBorrar);
	} 
	
	for(int v : res) cout << v << " ";
	cout << "\n";
}


int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> n >> k;
	solve();
	
    return 0;
}
