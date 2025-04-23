#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
//const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;
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

ll n, m;
const int MAX_N = 10;
const int MAX_M = 1000;
const int MAX_K = pow(2, 10) + 1;

ll memo[MAX_M][MAX_N][MAX_K];

 
ll addMod(ll a, ll b){
    ll res = ((a % MOD) + (b % MOD)) % MOD;
    return res;
}

ll dp(int i, int j, int k){ // i es la columna actual, j la fila y k la bitmask que describe la columna anterior
	if (i == m && k == 0) return 1; // Si terminé de recorrer las filas y puse cosas válidas en la fila anterior, entonces llegué a una configuración válida
	if (i == m) return 0; // Si terminé de recorrer las filas y puse cosas inválidas en la fila anterior, entonces llegué a una configuración inválida
	if (j == n) return dp(i+1, 0, k); // Si terminé la última fila, ahora me muevo a la siguiente columna
	
	if (memo[i][j][k] == UNDEFINED){
		int a = 1 << j; // I need to check what was the bit at the position j of k.
		int b = 1 << (j+1);
		
		if (k & a){ // Si estaba prendido el bit j en esta posición quiere decir que había un bloque horizontal. Luego, esta posición está ocupada y no puedo hacer nada
			memo[i][j][k] = dp(i, j+1, k & (~a)); // Apago el bit j del vector k y me voy una fila para abajo
		} else { // Si había puesto uno vertical, entonces está posición está libre así que tengo dos opciones: uno horizontal o uno vértical
			memo[i][j][k] = dp(i, j+1, k | a); // Pongo uno horizontal y me voy abajo
			// Me fijo si puedo poner uno vértical. Chequeo que el bit j+1 esté apagado
			if (j+1 < n && (k & b) == 0){ //Si está libre el bit en la posición j+1
				memo[i][j][k] = addMod(memo[i][j][k], dp(i, j+2, k));
			}
		}
	}
	
	return memo[i][j][k];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    cin >> n >> m;
    
    forn(i, m){
		forn(j, n){
			forn(k, pow(2, n)+1){
				memo[i][j][k] = UNDEFINED;
			}
		}
	}
    
    ll res = dp(0, 0, 0);
    cout << res << "\n";
}
