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
// Calcular extremo izquierdo que cumple P(X)
int leftBinarySearch(int start, int end, vector<int> &C, int currentPrice){
    int l = start - 1; 
    int r = end + 1; 

    while(r - l > 1) { 
        int mid = (l + r) / 2;
        if(!(currentPrice <= C[mid])) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (r < start || r > end || !(currentPrice <= C[r])){
		r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return r; // r es el primer elemento que cumple P(X)
}

ll earningsForPrice(int currentPrice, int k, vector<int> &A, vector<int> &B){
	int n = SIZE(A);
	
	// Tengo que saber la cantidad de árboles que voy a poder comprar. Esto lo hago mirando la cantidad de elementos en B tales que currentPrice <= B[j]
	int j = leftBinarySearch(0, n-1, B, currentPrice); // Indice del elemento más chico en B que cumple la condición de arriba
	if (j == UNDEFINED) j = n; // Esto lo hago para no comprar ningún arbol
	
	int arbolesComprados = n-j; // Ya que este es el tamaño del intervalo [j, ..., n-1]
	ll currentRes = (ll) arbolesComprados*currentPrice;
		
	// Quiero saber ahora la cantidad de reseñas negativas. Esto lo puedo hacer contando la cantidad de reseñas positivas
	int h = leftBinarySearch(0, n-1, A, currentPrice); // Indice del elemento más chico en A que cumple: currentPrice <= A[h]
	if (h == UNDEFINED) h = n; // Esto lo hago para no dejar ninguna reseña
	
	int reseniasPositivas = n-h; // Ya que este es el tamaño del intervalo [h, ..., n-1]
	int reseniasNegativas = arbolesComprados - reseniasPositivas;
		
	if (j == UNDEFINED || reseniasNegativas > k) currentRes = 0;
	
	return currentRes;
}

void solve1(vector<int> &A, vector<int> &B, int k){
	sort(all(A));
	sort(all(B));
	
	ll res = 0;	
	
	// El mejor precio va a estar si o si en A o en B 
	// Pruebo con valores de A como precio actual
	forn(i, SIZE(A)){
		res = max(res, earningsForPrice(A[i], k, A, B));
	}
	
	// Pruebo con los valores de B como precio actual
	forn(i, SIZE(B)){
		res = max(res, earningsForPrice(B[i], k, A, B));
	}
	
	cout << res << "\n";
}


void solve(vector<int> &A, vector<int> &B, int k){
	sort(all(A));
	sort(all(B));
	
	ll res = 0;
	int n = SIZE(A);
	int repetitionsOfThisNumber = 0;
	
	// Comentario importante:sea p un cliente. Si su a es A[i], su b no es necesariamente B[i]. Notar que cuando ordenamos ambos vectores perdimos la relación p = {A[i], B[i]} para cada cliente
	// Observación: el mejor valor posible del árbol tiene que ser un elemento de A o B
	
	// Vamos a probar eligiendo como valor del arbol elementos de A
	forn(i, n){
		int currentPrice = A[i];
		
		if (0 <= i-1 && A[i-1] == A[i]){
			repetitionsOfThisNumber++;
		} else {
			repetitionsOfThisNumber = 0;
		}
		
		int realIndex = i - repetitionsOfThisNumber; // La gracia de esto es que si tengo valores repetidos en A, siempre haga el cálculo empezando desde la mejor posición (la más atrás)
		ll currentRes = (ll) (n-realIndex)*currentPrice; // Sé que voy a poder comprar por lo menos (n-realIndex) árboles con este precio ya que para todo j > i, currentPrice <= A[j]
		
		// Ahora tengo que chequear cuántos clientes con indice j en A tal que j < i me pueden comprar pero usando su precio en B. Si su indice en B es j', quiero que currentPrice <= B[j']
		// Los clientes con indice j en A en el intervalo [0, ..., i-1] podrían tener su indice j' asociado en B en los indices [0, ..., i-1] o en los indices [i, ..., n-1]
		// Ahora basta notar que si su indice j' pertenece a [i, ..., n-1] en B quiere decir que el B asociado a algunos de los indices [i, ..., n-1] en A está asociado con los indices [0, ..., i-1] en B. Luego, lo va a poder comprar al árbol
	
		int j = leftBinarySearch(0, realIndex-1, B, currentPrice); // j es el indice del primer elemento de B en el rango [0,...,i-1] que cumple que currentPrice <= B[j]
		int cantidadMalasResenias = 0; // Originalmente no tengo ninguna mala reseña
		
		if (j != UNDEFINED){ // Si existe algún cliente j < i que pueda comprar el arbol usando B[j], actualizo 
			cantidadMalasResenias = realIndex-j; // La cantidad de malas reseñas va a ser el tamaño del intervalo [j, ..., i-1] que es igual a: (i-1) - j + 1 = i - j
			currentRes += (ll) cantidadMalasResenias*currentPrice; // Le agrego las compras de los clientes que me dejaron una mala reseña
		}
		
		if (cantidadMalasResenias <= k){ // Si el precio me dio una configuración válida
			res = max(res, currentRes);
		}
	}
	
	// Vamos a probar eligiendo como valor del arbol elementos de B
	forn(i, n){
		int currentPrice = B[i]; // Sé que potencialmente podría comprar (n-i) árboles si cumplo con la restricción de las reseñas
			
		if (0 <= i-1 && B[i-1] == B[i]){
			repetitionsOfThisNumber++;
		} else {
			repetitionsOfThisNumber = 0;
		}
		
		int realIndex = i - repetitionsOfThisNumber;
		
		// Además, sé que los clientes con indice [0, ..., i-1] en B no van a poder comprar árboles. FALTA ARREGLAR ESTO
		ll currentRes = (ll) currentPrice*(n-realIndex); // Todos los clientes con indices [i, ..., n-1] en B van a comprar arboles
		int cantidadMalasResenias = n-realIndex; // En principio tengo las reseñas negativas de B con indices [i, ..., n-1]

		// Me falta ver cuántos clientes de indice [i+1, ..., n-1] en B van a poder comprar sin dejar reseña negativa
		int j = leftBinarySearch(realIndex+1, n-1, A, currentPrice); // j es el indice del primer elemento en A que currentPrice <= B[j]
		
		if (j != UNDEFINED){ // Si existe algún cliente j > i que pueda comprar el árbol usando A[j], actualizo
			int cantidadBuenasResenias = n - j; // La cantidad de clientes que compran con buena reseña van a ser [j, ..., n-1] que es igual a: n - j
			cantidadMalasResenias -= cantidadBuenasResenias;
		}
		
		if (cantidadMalasResenias <= k){
			res = max(res, currentRes);
		}
	}
	
	
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		int n, k;
		cin >> n >> k;
		
		vector<int> A(n), B(n);
		
		forn(i, n) cin >> A[i];
		forn(i, n) cin >> B[i];
		
		//~ solve(A, B, k);
		solve1(A, B, k);
	}
}
