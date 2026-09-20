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
using vvvl = vector<vvl>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvii = vector<vii>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
const int MOD = 1e9+7;
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

int radar(char c, int pos);

map<char, int> positionFor;

int ceil(int a, int b){ 
	if (b == 0) return 0;
	return (a+b-1)/b; 
}

void resolveDesdeElOeste(int filaActual, int distOeste, vi &distancias, map<char, char> &ejes){
	distancias[positionFor[ejes['O']]] = distOeste;
	distancias[positionFor[ejes['E']]] = radar(ejes['E'], filaActual);
	
	int primeraCol = 1+distOeste; // Primera columna del rectangulo desde el west
	distancias[positionFor[ejes['N']]] = radar(ejes['N'], primeraCol);
	distancias[positionFor[ejes['S']]] = radar(ejes['S'], primeraCol);
}

void resolveDesdeElNorte(int colActual, int distNorte, vi &distancias, map<char, char> &ejes){
	distancias[positionFor[ejes['N']]] = distNorte;
	distancias[positionFor[ejes['S']]] = radar(ejes['S'], colActual);
	
	int primeraFila = 1+distNorte; 
	distancias[positionFor[ejes['O']]] = radar(ejes['O'], primeraFila);
	distancias[positionFor[ejes['E']]] = radar(ejes['E'], primeraFila);
}

int MAX_MOVIMIENTOS = 190;

bool funcionoDesdeElOeste(int filaActual, vi &distancias, map<char, char> &ejes){
	int distOeste = radar(ejes['O'], filaActual);
	if (distOeste != -1) resolveDesdeElOeste(filaActual, distOeste, distancias, ejes);
	return distOeste != -1;
}

bool funcionoDesdeElNorte(int colActual, vi &distancias, map<char, char> &ejes){
	int distNorte = radar(ejes['N'], colActual);
	if (distNorte != -1) resolveDesdeElNorte(colActual, distNorte, distancias, ejes);
	return distNorte != -1;
}

void solve(int nOfRows, int nOfCols, vi &distancias, map<char, char> &ejes){
	int minMovs = 1e9, altoForMin = -1, anchoForMin = -1;
	forsn(b, 1, 11){
		int ancho = ceil(100, b-1); // (b-1)*ancho >= 100 sii ancho >= 100/(b-1)
		int movs = ceil(nOfRows, b) + ceil(nOfCols, ancho);
		if (movs < minMovs) altoForMin = b, anchoForMin = ancho;
		minMovs = min(minMovs, movs);
	}
	
	for(int k = 0; k*altoForMin + 1 <= nOfRows; k++){
		int filaActual = k*altoForMin + 1;
		if (funcionoDesdeElOeste(filaActual, distancias, ejes)) return ;
	}
	
	for(int k = 0; k*anchoForMin + 1 <= nOfCols; k++){
		int colActual = k*anchoForMin+1;
		if (funcionoDesdeElNorte(colActual, distancias, ejes)) return ;
	}
}

void tiranic(int nOfRows, int nOfCols, vi &distancias) {
	positionFor['N'] = 0;
	positionFor['E'] = 1;
	positionFor['S'] = 2;
	positionFor['O'] = 3;
	distancias.resize(4);
	
	map<char, char> ejes;
	ejes['N'] = 'N';
	ejes['E'] = 'E';
	ejes['S'] = 'S';
	ejes['O'] = 'O';
		
	if (nOfRows > nOfCols){
		ejes['N'] = 'O';
		ejes['E'] = 'S';
		ejes['O'] = 'N';
		ejes['S'] = 'E';
		swap(nOfRows, nOfCols);
	}	
		
	solve(nOfRows, nOfCols, distancias, ejes);
}
