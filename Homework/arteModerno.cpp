
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using vvl = vector<vl>;
using ii = pair<int,int>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
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

    int n; cin >> n;
    ll k; cin >> k;

    vl A(n), B(n), C(n), prefixSumC(n);    
    ll D = 0;
    forn(i, n) cin >> A[i];
    forn(i, n) cin >> B[i];
	forn(i, n){
		C[i] = A[i] - B[i];
		prefixSumC[i] = C[i];
		if (i > 0) prefixSumC[i] += prefixSumC[i-1];
		D += C[i];
	}

    // Mi objetivo es que todas las posiciones de C sean cero (significa transformar A en B)
    // Si D > 0, necesito agregar elementos
    // Si D < 0, necesito sacar elementos
	
	// Problema original:
    // Solo puedo reacomodar cosas (prohibido sacar/agregar) requiere D = 0
    // Para todo 1 <= i < n, analizo el sentido de donde entran elementos con la barrera (i, i+1)
    // Eso define univocamente el flujo de los elementos ya que para (i, i+1) solo pueden fluir:
    // 1. i -> i+1
    // 2. i <- i+1
	// No tiene sentido que cruces en los dos sentidos la barrera porque podrias haber evitado la operacion
	
    // Analizando la flecha de (i, i+1) miro las cantidades en: B1 = [C[1], ..., C[i]] y B2 = [C[i+1], ..., C[n]]
    // Claramente B1+B2 = D = 0, es decir, B1 = -B2. 
    // -Si B1 < 0, entonces necesito traer elementos de B2 en el sentido i <- i+1
    // -Si B1 > 0, entonces necesito sacar elementos de B1, en el sentido i -> i+1
    // Luego, la cantidad de elementos que van a usar esta flecha va a ser exactamente: abs(B1) (que es = a abs(b2)) 
	
	// Problema a resolver:
    // En este caso puedo imaginarme que hay dos posiciones fantasmas 0 y n+1 que pueden agregar/eliminar elementos como quiera, el costo de usarlas es k
    // 0 1 .... n (n+1)

    // Tendria que definir las direcciones (0, 1) y (n, n+1) ahora. Y asegurarme que C[0] + D + C[n+1] = 0
    // Podria iterar por cada valor posible de C[0] y eso me fija a C[n+1] = -D - C[0]

    // C[0] y C[n+1] me dicen cuantos elementos salieron/entraron por ahi. 
    // El costo de usarlas es: (abs(C[0])+abs(C[n+1])*k
    
    // Y creo que el resto:
	// C'[1] = C[1] + C[0] 
	// C'[i] = C[i] + C'[i-1] si 1 < i < n
	// C'[n] = C[n] + C'[n-1] + C[n+1]  
	
	// Y ya ahora puedo resolver el problema con la cuenta normal de:
	// res = k*abs(C[0]) + abs(C[n+1])*k + sumatoria i=1...n-1 (abs(prefixSumC'[i]))
    
    // res = k*(abs(x1)+abs(x2)) + sumatoria i=1...n-1  max(prefixSum[i] + x1, D - prefixSum[i] + (-D-X1)))
    // res = k*(abs(x1)+abs(x2)) + sumatoria i=1...n-1 max(prefixSum[i]+x1, -prefixSum[i]-x1)
    
    // Me queda minimizar esta expresion y x1 puede tomar el valor entero que quiera mientras sea optimo
    // res = k*(abs(x1)+abs(x2)) + sumatoria i=1...n-1 max(prefixSum[i]+x1, -prefixSum[i]-x1)
    // res = k*(abs(x1)+abs(-D-x1)) + sumatoria i = 1...n-1 abs(prefixSum[i]+x1)
    
    // Y reescribiendo un poco:
    // res = k*abs(x1-0)+k*abs(x1-(-D)) + sumatoria i = 1...n-1 abs(x1 - (-prefixSum[i]))
    
    // Basicamente tengo un monton de puntos que calculan la distancia respecto a X1, y mi objetivo es minimizar la sumatoria total
    vl puntos;
    forn(i, n-1) puntos.pb(-prefixSumC[i]);
    forn(_, k){
		puntos.pb(-D);
		puntos.pb(0);
	}
	
	if (puntos.empty()){
		cout << abs(D)*k << "\n";
		return 0;
	}
	
	sort(all(puntos));
	// Agarro la mediana de punto optimo
	ll x1 = puntos[SIZE(puntos)/2], x2 = -D-x1;
    ll res = (abs(x1)+abs(x2))*k;
    vl C_prime = C;
    C_prime[0] += x1;
    forn(i, n-1) {
		res += abs(C_prime[i]);
		C_prime[i+1] += C_prime[i];
    }

    cout << res << "\n";
	return 0;
}
