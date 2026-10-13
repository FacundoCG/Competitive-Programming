
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
using vii = vector<ii>;

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

struct Nivel{
	ll oneStar, twoStars;
	int id;
	
	Nivel(ll _oneStar = -1, ll _twoStars = -1, int _id = -1)
		: oneStar(_oneStar), twoStars(_twoStars), id(_id){}

	bool operator<(const Nivel &other) const{
		if (twoStars != other.twoStars) return twoStars < other.twoStars;
		return make_pair(oneStar, id) < make_pair(other.oneStar, other.id);
	}
};

struct Opcion{
	ll cost, stars;
	int id;
	
	Opcion(ll _cost = -1, ll _stars = -1, int _id = -1)
		: cost(_cost), stars(_stars), id(_id){}

	bool operator<(const Opcion &other) const{
		if (cost != other.cost) return cost < other.cost;
		return make_pair(stars, id) < make_pair(other.stars, other.id);
	}
	
	bool operator>(const Opcion &other) const{
		return other < *this;
	}
};

bool smallerOneStar(Nivel &e1, Nivel &e2){
	return e1.oneStar < e2.oneStar;
}

int n, w; 

template <typename Comp1, typename Comp2>
void removeExtraElements(set<Opcion, Comp1> &s1, set<Opcion, Comp2> &s2, int desiredSize, ll &sumSmaller, ll c){
	desiredSize = min(desiredSize, n);
	desiredSize = max(desiredSize, 0);
	
	while (SIZE(s1) > desiredSize){
		Opcion e = *s1.rbegin();
		sumSmaller += e.cost*c;
		s1.erase(e);
		s2.insert(e);
	}
}

int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);

    cin >> n >> w;
    
    vector<Nivel> A(n);
    forn(i, n){
		ll oneStar, twoStars; cin >> oneStar >> twoStars;
		A[i] = Nivel(oneStar, twoStars, i);
	}
	
	sort(all(A));
    
    vector<Nivel> B = A;
    sort(all(B), smallerOneStar);
	
	vl prefixSumOneStar(n);
	forn(i, n){
		prefixSumOneStar[i] = A[i].oneStar;
		if (i > 0) prefixSumOneStar[i] += prefixSumOneStar[i-1];
	}
	
	ll res = LINF, opt = -1;
	
	// Agarrar los w mas chicos de 1 estrella (no agarras ninguno de dos estrellas)
    if (w <= n){
		res = 0, opt = 0;
		forn(i, w) res += B[i].oneStar;
	}
	
	set<Opcion> smaller; 
	set<Opcion, greater<Opcion>> bigger;
	ll sumSmaller = 0;
	
	forn(i, n) bigger.insert(Opcion(A[i].oneStar, 1, A[i].id));
	
	forn(i, n){
		// Quiero agarrar al i-esimo de 2 estrellas. Entonces tengo que pagar como minimo: A[0].oneStar + ... + A[i].oneStar
		int missingStars = w-(i+1); // Me interesa los w-(i+1) mas chicos

		// Sacar A[i].oneStar de los conjuntos y poner (A[i].twoStar - A[i].oneStar) en donde corresponda
		Opcion toRemove = Opcion(A[i].oneStar, 1, A[i].id);
		Opcion toAdd = Opcion(A[i].twoStars-A[i].oneStar, 2, A[i].id);
		
		// Elimino valor viejo
		bigger.erase(toRemove);
		if (esta(toRemove, smaller)) sumSmaller -= toRemove.cost; 
		smaller.erase(toRemove);
				
		// Agrego valor nuevo		
		bigger.insert(toAdd);
			
		// Necesito hacer que cada set tenga el tamanio correcto		
		removeExtraElements(smaller, bigger, missingStars, sumSmaller, -1);
		removeExtraElements(bigger, smaller, n-missingStars, sumSmaller, 1);
		
		// Ahora veo de mejorarlo siempre que pueda
		while (!smaller.empty() && !bigger.empty()){
			Opcion worst = *smaller.rbegin();
			Opcion best = *bigger.rbegin();
			if (best.cost < worst.cost){
				sumSmaller -= worst.cost;
				smaller.erase(worst);
				bigger.insert(worst);
				sumSmaller += best.cost;
				smaller.insert(best);
				bigger.erase(best);
			} else break;
		}
		
		if (missingStars > n) continue;
		
		ll currentRes = prefixSumOneStar[i] + sumSmaller;
		if (currentRes < res) opt = i+1;
		res = min(res, currentRes);
	}
	
	// Fijarse cual fue la mejor opcion
	vi decision(n);
	
	if (opt == 0) forn(i, w) decision[B[i].id] = 1;
	else {
		smaller.clear(); bigger.clear();
		sumSmaller = 0;	
		forn(i, n) bigger.insert(Opcion(A[i].oneStar, 1, A[i].id));
		
		forn(i, opt){
			// Quiero agarrar al i-esimo de 2 estrellas. Entonces tengo que pagar como minimo: A[0].oneStar + ... + A[i].oneStar
			int missingStars = w-(i+1); // Me interesa los w-(i+1) mas chicos

			// Sacar A[i].oneStar de los conjuntos y poner (A[i].twoStar - A[i].oneStar) en donde corresponda
			Opcion toRemove = Opcion(A[i].oneStar, 1, A[i].id);
			Opcion toAdd = Opcion(A[i].twoStars-A[i].oneStar, 2, A[i].id);
		
			// Elimino valor viejo
			bigger.erase(toRemove);
			if (esta(toRemove, smaller)) sumSmaller -= toRemove.cost; 
			smaller.erase(toRemove);
				
			// Agrego valor nuevo		
			bigger.insert(toAdd);
			
			// Necesito hacer que cada set tenga el tamanio correcto		
			removeExtraElements(smaller, bigger, missingStars, sumSmaller, -1);
			removeExtraElements(bigger, smaller, n-missingStars, sumSmaller, 1);
		
			// Ahora veo de mejorarlo siempre que pueda
			while (!smaller.empty() && !bigger.empty()){
				Opcion worst = *smaller.rbegin();
				Opcion best = *bigger.rbegin();
				if (best.cost < worst.cost){
					sumSmaller -= worst.cost;
					smaller.erase(worst);
					bigger.insert(worst);
					sumSmaller += best.cost;
					smaller.insert(best);
					bigger.erase(best);
				} else break;
			}
		}
					
		// Agarraste una estrella seguro de los [0, ..., opt-1] de A y luego fijate que hiciste con el resto
		forn(i, opt-1) decision[A[i].id] = 1;
		for (Opcion e : smaller) decision[e.id] = (int) e.stars;
	}
	
	cout << res << "\n";
	forn(i, n) cout << decision[i];
	cout << "\n";
    
	return 0;
}
