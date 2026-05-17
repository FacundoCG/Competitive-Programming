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

int n, k; 
bool inconsistentSystem = false;
int mod(int a, int m = MOD){ return ((a % m) + m) % m;}

void updateGroup(vi &group, vi &G, vi &E){
	// Voy a escribir al E[j] de cada j de group como: E[j] = constante + E[group[0]]
	vi A(SIZE(group)+1);
	int lowerBound = 0; 
	forn(i, SIZE(group)){
		int index = group[i]; 
		A[i+1] = G[mod(index-1, n)] - G[index] + A[i];
		if (A[i+1] <= 0) lowerBound = max(lowerBound, abs(A[i+1]));
		// Si hago G[(index-1) % n] - G[index] = E[(index-k) % n] - E[index] = T[(index-k) % n] - T[index]
		// Si hago G[(index-k-1) % n] - G[(index-k) % n] = E[(index-2k) % n] - E[(index-k) % n]
		// = G[(index-k-1) % n] - G[(index-k) % n] + E[(index-k) % n] = E[(index-2k) % n]
	}
	
	// lowerBound es el valor minimo que necesita E[group[0]] para garantizarme que todos los E[j] de group sean >= 0
	// T[i] es la suma la ventana {i-k+1, ..., i} y G[i] es el valor deseado de dicha ventana
	// Usando este sistema logre llegar a: T[i-1] - T[i] = G[i-1] - G[i] que es equivalente a T[i] - G[i] = T[i-1] - G[i-1]
	// Basicamente todos los T[i] cumplen que: T[i] + delta = G[i]
	
	// Notar que la ultima ecuacion es: G[[lastIndex-1] % n] - G[lastIndex] = E[groups[0]] - E[lastIndex] ya que estoy en un ciclo
	// Esto llega a que: E[groups[0]] = G[[lastIndex-1] % n] - G[lastIndex] + E[lastIndex] = G[[lastIndex-1] % n] - G[lastIndex] + A[SIZE(group)-1] + E[groups[0]]
	// Y esto llega a que: G[[lastIndex-1] % n] - G[lastIndex] + A[i] = 0 es necesario chequear entonces que A[SIZE(group)] = 0 para que el sistema tenga solución
	forn(i, SIZE(group)) E[group[i]] = lowerBound + A[i];
	if (A.back() != 0) inconsistentSystem = true;
}

void solve(){
	cin >> n >> k;
	vi G(n); forn(i, n) cin >> G[i];
	
	bool P = (k == 1);
	if (k == n) P = (*max_element(all(G)) == *min_element(all(G)));
	if (k == 1 || k == n) { cout << (P ? "S" : "N") << "\n"; return ;}
	
	vi E(n);
	vb visited(n);
	vvi groups;
	forn(i, n) if (!visited[i]){
		int index = i;
		vi currentGroup;
		while (!visited[index]){
			currentGroup.pb(index);
			visited[index] = true;
			index = mod(index-k, n);
		}
		groups.pb(currentGroup);
	}
	
	for (auto &group : groups) updateGroup(group, G, E);
	if (inconsistentSystem){ cout << "N\n"; return ;}
	
	// Si todos los sistemas tienen solucion, el E actual me garantiza que no hay negativos y que todos los T[i] tienen el mismo delta respecto a su G[i]
	 
	ll T_0 = 0;
	int index = 0;
	forn(_, k) T_0 += E[index], index = mod(index-1, n); 
	
	if (T_0 > G[0]) { cout << "N\n"; return ;} // Tomando los minimos valores para satisfacer el sistema me excedo asi que no se puede

	// Notemos que si un grupo empieza en i puedo a llegar j sii: existe algun t tq j = i - t*k (n)
	// Y con esto llegamos a que j-i = q*n - t*k y por la identidad de Bezout llegas a que j-i son multiplos de gcd(n, k)
	// Con esto ultimo sabes que j-i = 0 (gcd(n, k)) y esto es equivalente a j = i (gcd(n, k))
	// Es decir que dos indices esten el mismo grupo implica que tienen el mismo resto en mod gcd(n, k)
	
	int d = gcd(n, k);
	// Vas a tener exactamente d grupos ya que mirando en resto vas a tener algo estilo: [x1, x1+1, ..., 0, x1, ..., 0] porque d|n lo cual implica que vas a llegar si o si a ver todos los restos
	// Sea n = d*m. Para cada resto r vas a poder hacer: r+0*d, r+d, ..., r+(m-1)*d < n ya que r < d. Luego llegas a que cada grupo tiene que tener tamanio m
	
	int sizeOfGroup = n/d;	
	// Cada ventana de k elementos va a tener k/d elementos de cada grupo. Esto es porque d|k, luego k = d*q
	// Los modulos se van a repetir cada q indices lo que implica que cada grupo va a aparecer q = k/d en cada ventana
	int q = k/d;
	
	ll needed = G[0] - T_0; // Esto es lo que necesito aumentar a todas las ventanas
	// Cuando aumento a un E[i] por x se aumentan todos los elementos del mismo grupo de i por x tambien
	// Y como se que cada ventana T[j] contiene a q elementos de este grupo va a ocurrir que: T[j] += x*q y como quiero que G[j] = T[j]
	// G[j] = T[j] + x*q sii G[j] - T[j] = q*x. Esto implica que q | G[j] - T[j] si o si
	
	P = (needed % q == 0);
	cout << (P ? "S" : "N") << "\n";
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
