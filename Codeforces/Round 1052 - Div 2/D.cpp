#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using ii = pair<int,int>;

template <typename T>
using vv = vector<vector<T>>;

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

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		int l, r;
		cin >> l >> r;
		
		// Elementos entre: [l, r]
		vl A(r+1, UNDEFINED);
		ll res = 0;
		
		dforsn(i, l, r+1){
			if (A[i] != UNDEFINED) continue;
						
			// Busco cuál es el j entre [l, r] que lo maximiza
			int current = i;
			int j = 0;
			int powerOfTwo = 0;
			
			while (current > 0){
				if (!(current & 1)) j |= (1 << powerOfTwo);
				powerOfTwo++;
				current = current >> 1;
			}
			
			if (current < l){ // No está en [l, r] el mejor valor ya que es < l
				int powerOfTwo = 0; // Tengo que hacerlo más grande. Así que necesito prender bits
				while (current > 0){
					if (current & 1) j |= (1 << powerOfTwo);
					if (j >=l && j <= r) break; // Valor ideal
					// if (j < l) // Necesito seguir prendiendo bits
					// if (j > r) Necesito apagar bits de los prendidos originalmente
							
					powerOfTwo++;
					current = current >> 1;
				}
			}
						
			A[i] = j;
			A[j] = i;
		}
		
		forn(i, r+1) res += (A[i] | i);
		cout << res << "\n";
		forn(i, r+1) cout << A[i] << " ";
		cout << "\n";
	}
	
    return 0;
}
