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

const ll UNDEFINED = -2;
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

typedef pair<int, int> interval;

set<interval> buildSet(set<int> &B){
	set<interval> res;
	auto it = B.begin();
	int l = *it, r = *it;
	it++;
	
	for(auto k = it; k != B.end(); k++){
		int x = *k;
		
		if (r+1 == x) r = x;
		else {
			res.insert({l, r});
			l = r = x;
		}
	}
	
	res.insert({l, r});
	return res;
}

void getAnswer(set<interval> &s){
	interval p = *s.begin();
	if (p.fst != 0) cout << "0 ";
	else cout << p.snd + 1 << " ";
}

void deleteFrom(set<interval> &s, int x){
	auto it = s.lower_bound({x, x});
	interval toDelete;
	
	if (it == s.end()){
		it--;
		toDelete = *it;
	} else { // Sé que (*it).fst >= x
		if ((*it).fst == x){ toDelete = *it;} 
		else { it--; toDelete = (*it);}
	}
	
	s.erase(toDelete); // Ahora tengo que eliminar este intervalo y ver de como particionarlo
	if (toDelete.fst == toDelete.snd) return ; // Si tiene tamaño 1, lo elimino y listo
	
	if (toDelete.fst == x) s.insert({toDelete.fst+1, toDelete.snd});
	else if (toDelete.snd == x) s.insert({toDelete.fst, toDelete.snd-1});
	else {
		s.insert({toDelete.fst, x-1});
		s.insert({x+1, toDelete.snd});
	}
}

void addTo(set<interval> &s, int x){
	// Busco el primer intervalo que empieza después de {x, x}
	interval currentInterval = {x, x}, prevInterval = {UNDEFINED, UNDEFINED}, nextInterval = {UNDEFINED, UNDEFINED};
	auto it = s.lower_bound(currentInterval);
	
	if (it == s.end()){
		it--;
		prevInterval = {(*it).fst, (*it).snd};
	} else {
		nextInterval = {(*it).fst, (*it).snd};
		if (it != s.begin()){ it--; prevInterval = {(*it).fst, (*it).snd};}
	}
	
	if (prevInterval.snd + 1 == x && x+1 == nextInterval.fst){ // Si uno dos intervalos
		s.erase(nextInterval); s.erase(prevInterval);
		currentInterval = {prevInterval.fst, nextInterval.snd};
	} else if (prevInterval.snd + 1 == x){
		s.erase(prevInterval);
		currentInterval = {prevInterval.fst, x};
	} else if (x+1 == nextInterval.fst){
		s.erase(nextInterval);
		currentInterval = {x, nextInterval.snd};
	}
	
	s.insert(currentInterval);
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, k;
	cin >> n >> k;
	
	vi A(n);
	set<int> B;
	map<int, int> repeticiones;
	
	forn(i, n) cin >> A[i];
	forn(i, k) {
		B.insert(A[i]);
		repeticiones[A[i]]++;
	}
	
	set<interval> s = buildSet(B);
	//~ DBG(s);
	getAnswer(s);
		
	forsn(i, k, n){
		repeticiones[A[i-k]]--;
		
		if (repeticiones[A[i-k]] == 0) deleteFrom(s, A[i-k]);
		
		repeticiones[A[i]]++;
		if (repeticiones[A[i]] == 1) addTo(s, A[i]);
		
		getAnswer(s);
	}
	
	cout << "\n";
	
    return 0;
}
