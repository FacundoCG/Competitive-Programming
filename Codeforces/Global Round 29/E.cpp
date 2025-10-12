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

ll calculateOR(vl &A){
	ll res = 0;
	forn(i, SIZE(A)) res |= A[i];
	return res;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		int n, q;
		cin >> n >> q;
		
		vl A(n);
		forn(i, n) cin >> A[i];		
		ll orA = calculateOR(A);
		int bitsTurnedOn = __builtin_popcountll(orA);
		vector<pair<ll, int>> B = {{0, bitsTurnedOn}};
		//~ DBG(A); DBG(bitsTurnedOn);

		// Voy a prender los bits apagados y los bits prendidos los voy a mantener siempre
		forn(i, 60){
			if (!((orA >> i) & 1ll)){ // Si el bit i-esimo está apagado, lo prendo
				ll currentCost = 0; // Costo de prender el bit i, y mantener/prender los bits [0, i-1] en el preceso
				vl A1(A);
				
				dforn(j, i+1){
					if (!((calculateOR(A1) >> j) & 1ll)){ // Si este bit no está prendido hay que prenderlo
						int bestIndex = 0; // Elemento que me sale más barato prender el bit j
						ll toSum = (1ll << j); // Bit objetivo
						
						forn(k, SIZE(A1)){
							if ((A1[k] & (toSum-1)) > (A1[bestIndex] & (toSum-1))) bestIndex = k;
						}
						
						ll toAdd = toSum - (A1[bestIndex] & (toSum-1)); // Costo de prender bit j
						A1[bestIndex] += toAdd;
						currentCost += toAdd;
					}
				}
				
				//~ DBG(A1);
				bitsTurnedOn++; 
				B.pb({currentCost, bitsTurnedOn});
			}
		}
		
		//~ DBG(B);
		
		forn(i, q){
			ll b;
			cin >> b;
			
			//~ DBG(b);
			
			int res = 0;
			forn(j, SIZE(B)){ if (B[j].fst <= b) res = B[j].snd;}
			cout << res << "\n";
		}
		
		//~ RAYA;
	}
	
    return 0;
}

