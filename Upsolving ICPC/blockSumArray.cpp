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
const int MOD = 998244353;
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

#define forn(i,n) for (ll i=0;i<(ll)(n);i++)
#define forsn(i,s,n) for (ll i=(s);i<(ll)(n);i++)
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

int n, k; 

void defineGroup(vi &group, vl &A, vl &B){
	ll lowerBound = 0, c = 0;
	
	forn(i, SIZE(group)-1){ // B[index+1] - B[index] + A[index] = A[index+k] 
		int index = group[i];
		c += B[index+1]-B[index];
		lowerBound = max(lowerBound, -c);
		A[index+k] += c;
	}
	
	for (int index : group) A[index] += lowerBound;
}

ll mulMod(ll a, ll b, ll m = MOD){
	ll res = (a % m)*(b % m);
	return res % m;
}

ll binPowMod(ll base, ll exp, ll m = MOD){
    if (exp == 0) return 1;
    ll a = binPowMod(base, exp/2, m);
    ll res = mulMod(a, a, m);
    if (exp % 2 == 1) res = mulMod(res, base, m);
    return res;
}

ll divideMod(ll a, ll b, ll m = MOD){
    ll res = mulMod(a, binPowMod(b, m-2, m), m) % m;
    return res;
}

void solve(){
	// B[i+1] - B[i] = A[i+k] - A[i] sii B[i+1] - B[i] + A[i] = A[i+k]
	// B[i+k+1] - B[i+k] = A[i+2k] - A[i+k] sii B[i+k+1] - B[i+k] + A[i+k] = A[i+2k]
		
	// Notemos que A[j] va a pertenecer a un sistema sii: j < n-k ya que va a aparecer en B[j+1] - B[j] = A[j+k] - A[j] o si A[j] - A[j-k] = B[j-k+1] - B[j-k] 
	cin >> n >> k;
	vl B(n-k+1); forn(i, SIZE(B)) cin >> B[i];
	if (k == 1){ cout << "1\n"; return ;}
	
	vvi groups;
	vb visited(n);
	forn(i, SIZE(B)-1) if (!visited[i]){
		int index = i;
		vi group;
		while (index < n && !visited[index]){
			group.pb(index);
			visited[index] = true;
			index += k;
		}
		groups.pb(group);
	}
	
	vl A(n);
	for (auto &group : groups) defineGroup(group, A, B);
	
	// T[i] = A[i] + ... + A[i+k-1] y satisfago el sistema T[i+1] - T[i] = B[i+1] - B[i] para todo i por como defini los A[j]
	// Llegue a que B[i] - T[i] = delta para todo i
	
	forn(i, k) B[0] -= A[i]; // Le resto a B[0] lo que ya defini en los primeros k
	if (B[0] < 0){ cout << "0\n"; return ;} // Si me pase, no hay solucion
	
	// Notemos que hay dos tipos de indices:
	// Los i que pertenecen a algun grupo, cada ventana de k elementos contiene exactamente a 1 de ellos
	// Incrementar a uno del grupo por x, implica incrementar a todos los del grupo y eso implica achicar la diferencia de todas las ventanas de k por x
	
	// Asi que x_group1 + x_group_2 + ... = delta
	
	// Y faltan tambien los i que no fueron a ningun grupo, y esos son los que pertenecen a todas las ventanas de tamanio k (en caso de que existan dichos indices)
	// Luego lo que falta resolver: x_group1 + ... x_group_h + x_j + ... x_k-1 = delta
	
	// Y dicho delta es B[0] porque ya le reste el lowerBound de los x_group_i que defini
	
	// Ahora quiero saber cantidad de formas de sumar B[0] con k elementos no negativos. Esto es nComb(B[0]+k-1, k-1)
	ll num = 1, denom = 1;
	forsn(i, B[0]+1, B[0]+k) num = mulMod(num, i);
	forsn(i, 1, k) denom = mulMod(denom, i);
	cout << divideMod(num, denom) << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t = 1;
	//~ cin >> t;
	forn(_, t) solve();
	
    return 0;
}
