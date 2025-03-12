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
int n, currentToken;

set<int> calculateIntervals(string &s){
	set<int> res;
	
	forn(i, SIZE(s)-1){
		if (s[i] == 'L' && s[i+1] == 'R'){
			res.insert(i);
		}
	}
	
	return res;
}

vector<ll> calculatePrefixSum(vector<int> &p){
	vector<ll> res(SIZE(p));
	res[0] = p[0];
	
	forsn(i, 1, SIZE(p)){
		res[i] = (ll) res[i-1] + p[i];
	}
	
	return res;
}

ll gaussSum(ll k){
	ll res = k*(k+1)/2;
	return res;
}

bool isGoodInterval(int indexOfLeftSide, int indexOfRightSide, vector<ll> &prefixSum){
	// Quiero chequear si la suma que hay en el rango [indexOfLeftSide, indexOfRightSide] es igual a la suma de los elementos [indexOfLeftSide+1, indexOfRightSide+1]
	ll sumOfInterval = prefixSum[indexOfRightSide];
	if (indexOfLeftSide > 0) sumOfInterval -= prefixSum[indexOfLeftSide-1];
	ll desiredSumOfInterval = gaussSum(indexOfRightSide+1) - gaussSum(indexOfLeftSide);
	
	return sumOfInterval == desiredSumOfInterval;
}


int intervalBefore(set<int> &intervals, int x){
	auto it = intervals.lower_bound(x);
	
	if (it == intervals.begin()) return 0; // Esto significa que el intervalo que forma x es [0,x]
	it--;
	
	return *it; // Este es el intervalo anterior a x en intervals
}

int intervalAfter(set<int> &intervals, int x){
	auto it = intervals.lower_bound(x);
	auto copy_it = it;
	copy_it++;
	
	if (copy_it == intervals.end()) return n-1; // Esto significa que el intervalo que forma x es [x+1, n-1]
	it++;
	
	return *it; // Este es el intervalo posterior a x en intervals
}

void eliminateInterval(set<int> &intervals, int x, int &numberOfGoodIntervals, vector<ll> &prefixSum){
	// Acá voy a fijarme de descontar los intervalos [j+1, x] y [x+1, k] en caso de que sean buenos 
	// Luego, debo sumar si el intervalo [j+1, j'] es bueno
	int j = intervalBefore(intervals, x);
	int k = intervalAfter(intervals, x);
	
	if (j != 0) j++;
	
	numberOfGoodIntervals -= isGoodInterval(j, x, prefixSum);
	numberOfGoodIntervals -= isGoodInterval(x+1, k, prefixSum);
	numberOfGoodIntervals += isGoodInterval(j, k, prefixSum);
	
	intervals.erase(x); 
}

void addInterval(set<int> &intervals, int x, int &numberOfGoodIntervals, vector<ll> &prefixSum){
	// Voy a necesitar descontar el intervalo [j+1, k] ya que lo elimino
	// Y sumar si son buenos los intervalos [j+1, x] y [x+1, k]
	intervals.insert(x);
	int j = intervalBefore(intervals, x);
	int k = intervalAfter(intervals, x);
	
	if (j != 0) j++;
	
	numberOfGoodIntervals += isGoodInterval(j, x, prefixSum);
	numberOfGoodIntervals += isGoodInterval(x+1, k, prefixSum);
	numberOfGoodIntervals -= isGoodInterval(j, k, prefixSum);
}

void solve(vector<int> &p, string &s, vector<int> &queries){
	// Voy a dividir a P en intervalos según indices de la forma: [0, intervals[0]], [intervals[0]+1, intervals[1]], ..., [intervals[k]+1, n-1] siendo k = SIZE(intervals)-1
	set<int> intervals = calculateIntervals(s);
	vector<ll> prefixSumOfP = calculatePrefixSum(p);
	
	// La idea que uso es que cuando hay un L en i y un i+1 en R, no puedo swapear nada con indice <= i a una posición >= R. Viceversa ocurre lo mismo
	// Por lo tanto, dividio a mi permutación en los intervalos que se pueden swapear libremente
	// Estos intervalos del estilo [j, k] van a ser "buenos" (ordenables) si todos los elementos entre estos indices cumple que: j+1 <= p[i] <= k+1
	// Con j <= i <= k. Notar que sumo 1 más porque indexo desde 0
	
	// Ahora calculo cuántos de estos intervalos son "buenos"
	int leftSideOfInterval = 0;
	int numberOfGoodIntervals = 0;
	
	for (int i : intervals){
		// Quiero chequear si el intervalo dado por los indices [leftSideOfInterval, ..., i] es ordenable. Esto lo hago chequeando si la suma de estos elementos es igual a la de (leftSideOfInterval+1) + ... + i+1
		numberOfGoodIntervals += isGoodInterval(leftSideOfInterval, i, prefixSumOfP); // Si el intervalo es bueno, sumo 1
		leftSideOfInterval = i+1; // Es el comienzo del siguiente intervalo
	}
	
	// Ahora chequeo que [leftSideOfInterval, n-1] es un buen intervalo
	numberOfGoodIntervals += isGoodInterval(leftSideOfInterval, n-1, prefixSumOfP);
	 
	// Proceso las queries.
	// Cada query va a poder tener 3 efectos: agregar un LR, eliminar un LR o no hacer nada
	// Va a haber casos en los que van a poder cumplirse que agrego un LR y elimino un LR al mismo tiempo
	// Voy a ver de actualizar la cantidad de intervalos "buenos" como corresponde
	 
	forn(i, SIZE(queries)){
		int x = queries[i] - 1;
		
		if (s[x] == 'R'){
			if (0 < x && s[x-1] == 'L'){ // Acá elimino un LR
				// Elimino x-1 de intervals y actualizo la cantidad de intervalos buenos
				eliminateInterval(intervals, x-1, numberOfGoodIntervals, prefixSumOfP);		
			}
			
			if (x+1 < n && s[x+1] == 'R') { // Acá agrego un LR 
				// Agrego x a intervals y actualizo la cantidad de intervalos buenos
				addInterval(intervals, x, numberOfGoodIntervals, prefixSumOfP);
			} 
			
			s[x] = 'L';
		} else { // s[x] = L
			if (x+1 < n && s[x+1] == 'R'){ // Acá elimino un LR
				// Elimino x de intervals y actualizo la cantidad de intervalos buenos
				eliminateInterval(intervals, x, numberOfGoodIntervals, prefixSumOfP);
			}
			
			if (0 < x && s[x-1] == 'L'){ // Acá agrego un LR
				// Agrego x-1 a intervals y actualizo la cantidad de intervalos buenos
				addInterval(intervals, x-1, numberOfGoodIntervals, prefixSumOfP);
			}
			
			s[x] = 'R';
		}
		
		// Veo si la cantidad de intervalos buenos es igual a SIZE(intervals) + 1
		// Esto me dice de si todos los intervalos de P son ordenables, entonces P lo es
		if (SIZE(intervals) + 1 == numberOfGoodIntervals){
			cout << "YES" << "\n";
		} else {
			cout << "NO" << "\n";
		}
	}	
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    currentToken = 0;
    
    forn(_, t){
		int q;
		cin >> n >> q;
		
		vector<int> p(n), queries(q);
		forn(i, n) cin >> p[i];
		
		string s;
		cin >> s;
		
		forn(i, q) cin >> queries[i];
		solve(p, s, queries);
	}
}
