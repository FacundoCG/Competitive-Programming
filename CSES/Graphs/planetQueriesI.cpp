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

struct BinaryJumping{
	// Estructura para grafos de sucesores.
	vector<vector<int>> binaryJumping;
	int logk;
	
	// Inicializacion en tiempo O(n*log(max_k))
	BinaryJumping(vector<int> &succ, int max_k){
		logk = log2(max_k);  // Piso.
		binaryJumping.assign(SIZE(succ), vector<int>(logk+1, UNDEFINED));
		
		for(int i=0; i<SIZE(succ); i++){
			binaryJumping[i][0] = succ[i];
		}
		
		for(int it=1; it<=logk; it++){
			for(int i=0; i<SIZE(succ); i++){
				if (binaryJumping[i][it-1] != UNDEFINED) binaryJumping[i][it] = binaryJumping[binaryJumping[i][it-1]][it-1];
			}
		}
	}
	
	// O(log(k)). Donde x es el nodo, k es la distancia de salto.
	int succ_k(int x, int k){
		// Suponemos que k >= 0

		int it = 0;
		while(k != 0){
			if ((k & 1) == 1){
				if (x != UNDEFINED) x = binaryJumping[x][it];
			}
			k = k >> 1;
			it++;
		}
		
		return x; // x = UNDEFINED significa que te excediste con los saltos
	}
	
};

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, q;
	cin >> n >> q;
	
	vector<int> succ(n);
	forn(i, n) cin >> succ[i];
	forn(i, n) succ[i]--;
	
	vector<pair<int, int>> queries(q);
	int maxJump = n;
	forn(i, q){
		int v, jumps;
		cin >> v >> jumps;
		v--;
		queries[i] = {v, jumps};
		maxJump = max(maxJump, jumps);
	}
	
	BinaryJumping G(succ, maxJump);
	forn(i, q) cout << G.succ_k(queries[i].fst, queries[i].snd) + 1 << "\n";
	
    return 0;
}
