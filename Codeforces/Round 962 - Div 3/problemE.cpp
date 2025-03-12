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
int rightBinarySearch(int start, int end, vector<ll> &A, ll value){
    int l = start - 1;
    int r = end + 1;

    while (r - l > 1){
        int mid = (l + r)/2;

        if (A[mid] < value){
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (l < start || l > end || !(A[l] < value)){
		l = -1; // Si l no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return l; // l es el ultimo elemento que cumple P(X)
}

ll calculate(ll index, ll desiredImage, map<ll,vector<ll>> &P, map<ll,vector<ll>> &prefixSumOfP){
	// Quiero encontrar el j más grande tal que: P[desiredImage][j] < index 
	// Luego, obtengo prefixSumOfP[desiredImage][j]
	int end  = SIZE(P[desiredImage])-1;
	int j = rightBinarySearch(0, end, P[desiredImage], index);
	if (j == UNDEFINED) return 0; // Si no existe un valor en P[desiredImage] menor a index, entonces no puedo formar substrings "buenos" que empiecen en i
	
	return prefixSumOfP[desiredImage][j];
}

vector<ll> calculatePrefixSumOf(vector<ll> &A){
	vector<ll> res (SIZE(A));
	res[0] = A[0];
	
	forsn(i, 1, SIZE(A)){
		res[i] = res[i-1] + A[i];
	}
	
	return res;
}

void solve(vector<ll> &s){
	ll res = 0;
	vector<ll> F = calculatePrefixSumOf(s);
	map<ll,vector<ll>> P;
	map<ll,vector<ll>> prefixSumsOfP;
	
	forn(i, SIZE(F)){
		P[F[i]].pb(SIZE(s)-i);
	}
	
	for (auto c : P){
		sort(all(P[c.first]));
		prefixSumsOfP[c.first] = calculatePrefixSumOf(P[c.first]);
	}
	
	forn(i, SIZE(s)){
		// Voy a buscar la cantidad de substrings "buenos" que empiezan en i y terminan en algún j. Luego cuento la cantidad de substrings que lo contienen a este
		// Si actualmente estoy parado en 1, los j que me van a formar un substring "bueno" van a ser aquellos cuya imagen sea F[i]-1
		// Si estoy en un -1, los j que me van a formar un substring "bueno" van a ser aquellos cuya imagen sea F[i]+1

		// Luego quiero saber en cuántos substrings está contenido [s[i], ..., s[j]]
		// Esto se saca calculando el tamaño de: {0, ..., i} x {j, ..., n-1}
		// Dicho tamaño es igual a multiplicar: (|{0, ..., i}|+1)*|{j, ..., n-1}|  = (i+1)*|{j, ...,n-1}| = (i+1)*(n-j)
		// Observación: me queda i+1 en lugar de i por una cuestión de que indexo desde 0
		// Dicha cuenta la necesito hacer para cada j que me forme un substring "bueno". 
		// Esto seria: res += (i+1)(n-j_1) + (i+1)(n-j_2) + ... = (i+1)*(n-j_1+n-j_2+...)
		// Y el segundo factor lo puedo calcular de una con una prefixSum sobre los valores de P una vez que tengo la imagen deseada a buscar
		ll imageToFind = F[i] + s[i]*(-1); 
		ll indexForBS = SIZE(s)-i; 
		
		res += (i+1)*calculate(indexForBS, imageToFind, P, prefixSumsOfP);
		res %= MOD;
	}
	
	cout << res << "\n";
}

//~ void solve2(vector<ll> &s){
	//~ Está incompleto. Falta arreglar los indices
	//~ ll res = 0;
	//~ vector<ll> F = calculatePrefixSumOf(s);
	//~ map<ll, ll> cantidadDeIndicesBuenosPara;
	
	//~ forn(i, SIZE(s)){
		//~ res = (res + (SIZE(s)-i+1)*(cantidadDeIndicesBuenosPara[F[i]])) % MOD;
		//~ cantidadDeIndicesBuenosPara[F[i]] += i+1;
	//~ }
	
	//~ cout << res << "\n";
//~ }

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		string s;
		cin >> s;
		
		vector<ll> alternatedS;
		forn(i, SIZE(s)){
			if (s[i] == '0'){
				alternatedS.pb(-1);
			} else {
				alternatedS.pb(1);
			}
		}
		
		solve(alternatedS);
		//~ solve2(alternatedS);
	}
}
