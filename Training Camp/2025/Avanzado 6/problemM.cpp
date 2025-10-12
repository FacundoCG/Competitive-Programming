#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

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

char intToChar(int x){ // 0 <= x <= 9
	return (char) '0' + x;
}

int sumaDigitos(string &s){
	int res = 0;
	forn(i, SIZE(s)) res += s[i] - '0';
	return res;
}

void agregar(vector<string> &A, int i, int x){	
	dforn(j, SIZE(A[i])){
		if (x == 0) break; // Ya no tengo que modificar nada más
		int d = A[i][j] - '0';
		if (d + x <= 9){
			A[i][j] = intToChar(d+x);
			x = 0;
		} else {
			A[i][j] = '9';
			x -= (9 - d);
		}
	}
}

int sumarUnoDesde(vector<string> &A, int i, int toStart){
	int res = 0;
	
	dforn(j, toStart){
		int d = A[i][j] - '0';
		
		if (d != 9){ // Le sumo 1 así que estoy ganando eso
			res--;
			A[i][j] = intToChar(d+1);
			break;
		} else {
			res += 9; // Le saco 9
			A[i][j] = '0';
		}
	}
	
	return res;
} 

void reordenar(vector<string> &A, int i, int x){
	int toStart = 0;
	
	dforn(j, SIZE(A[i])){
		if (A[i][j] != '0'){ // Lo voy a decrementar en uno al primer dígito menos significativo que sea > 0
			int d = (A[i][j] - '0') - 1;
			A[i][j] = intToChar(d);
			toStart = j;
			break;
		}
	}
	
	sumarUnoDesde(A, i, toStart);
	forsn(j, toStart, SIZE(A[i])) A[i][j] = '0';
	int valorActual = sumaDigitos(A[i]); 
	if (valorActual < x) agregar(A, i, x-valorActual);
}

void reducir(vector<string> &A, int i, int x){
	dforn(j, SIZE(A[i])){
		int valorActual = sumaDigitos(A[i]);
		if (x == valorActual) break; // Si ya A[i] tiene el valor deseado, termino
		if (A[i][j] == '0') continue; // Lo skipeo ya que no puedo hacer nada
		
		int d = A[i][j] - '0';
		
		// Voy a convertir a este digito en un 0 para achicar valor y al siguiente digito más significativo le sumo 1 para garantizarme el >
		valorActual -= sumarUnoDesde(A, i, j); // Esto es todo lo que perdí al sumarle uno al digito j-1			
		valorActual -= d; // Ya que este digito ahora se volvió 0
		A[i][j] = '0';
						
		if (valorActual < x) agregar(A, i, x-valorActual); // Hago que la suma tenga el valor correspondiente
	}
}

void imprimir(string &s){
	int start = 0;
	
	forn(i, SIZE(s)){
		if (s[i] == '0') continue;
		start = i;
		break;
	}
	
	forsn(j, start, SIZE(s)) cout << s[j];
	cout << "\n";
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n;
	cin >> n;
	
	vi B(n);
	forn(i, n) cin >> B[i];
	
	vector<string> A(n);
	A[0] = "";
	forn(i, 1000) A[0] += '0';
	agregar(A, 0, B[0]);
	
	forsn(i, 1, n){
		A[i] = A[i-1];
		
		if (B[i] > B[i-1]){
			int x = B[i] - B[i-1];
			agregar(A, i, x);
		} else if (B[i] == B[i-1]){ // Tengo que decrementar en 1 el primer número que no sea 0 e incrementar en 1 el siguiente a este que no sea 9
			reordenar(A, i, B[i]);
		} else {
			reducir(A, i, B[i]);
		}
	}
	
	forn(i, n) imprimir(A[i]);
	
    return 0;
}
