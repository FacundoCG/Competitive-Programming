#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for(int i = 0; i < (n); ++i)
#define dforn(i, n) for(int i = (n)-1; i >= 0; i--)
#define forsn(i, s, n) for(ll i = (s); i < (n); ++i)
#define repeat(n) forn(sagsdgsdhdsgs, n)
#define for1(i, n) for(int i = 1; i <= (n); ++i)
#define chmin(a, b) ((a) = min(a, b))
#define chmax(a, b) ((a) = max(a, b))
#define ALL(x) (x).begin(), (x).end()
#define dbg(x) cout << #x << "" = "" << (x) << endl;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vb = vector<bool>;

#define pb push_back
#define SIZE(c) int((c).size())
#define esta(x, c) ((c).find(x) != (c).end())
#define DBG(x) cerr << #x << "=" << (x) << endl
#define RAYA cerr << "------------------------" << endl
#define fst first
#define snd second
#define all(c) (c).begin(), (c).end()

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

struct Data{
	string s;
	vi U, D;
};

void extender(vi &A, vi &B, int elemForA){
	A.pb(elemForA);
	B.pb(0);
}

using vci = vector<pair<char, int>>;

Data comprimir(string &t){
	vci A;
	int currentBlock = 0;
	forn(i, SIZE(t)-1){
		currentBlock++;
		if (t[i] != t[i+1]){
			A.pb(make_pair(t[i], currentBlock));
			currentBlock = 0;
		} 
	}
	currentBlock++;
	A.pb(make_pair(t.back(), currentBlock));
	
	string s;
	vi U, D;
	for (auto [c, reps] : A){
		s += c;
		if (c == 'U') extender(U, D, reps);
		else extender(D, U, reps);
	}
	assert(SIZE(s) == SIZE(U) && SIZE(s) == SIZE(D));
	return Data(s, U, D);
}

ii encontrarIntervalo(int i, int j, vi &U1, vi &U2){
	int suma1 = 0, suma2 = 0;
	while (suma1 != suma2 || (suma1 == 0)){
		//~ DBG(i); DBG(j);
		//~ DBG(suma1); DBG(suma2);
		if (suma1 > suma2){
			suma2 += U2[j];
			j++;
		} else {
			suma1 += U1[i];
			i++;
		}
	}
	assert(suma1 == suma2);
	return make_pair(i-1, j-1);
}

void agregarD(int pos, string &S, vi &D, int nOfDs){
	if (nOfDs == 0) return ; // No agregues nada si no moviste una D
	if (pos == SIZE(S)){ // En caso de que el string se terminara, agrega el nuevo caracter final
		S += 'D';
		D.pb(0);
	}
	D[pos] += nOfDs;
}

int query(int l, int r, vi &D){
	assert(0 <= l && l <= r && r < SIZE(D));
	int res = 0;
	forsn(i, l, r+1) res += D[i];
	return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    string t1, t2; cin >> t1 >> t2;
    
	auto [S1, U1, D1] = comprimir(t1);
	auto [S2, U2, D2] = comprimir(t2);
    
    //~ DBG(t1); DBG(S1); DBG(U1); DBG(D1);
    //~ RAYA;
    //~ DBG(t2); DBG(S2); DBG(U2); DBG(D2);
    //~ RAYA;
	DBG(S1); DBG(U1); DBG(D1);
    RAYA;
	DBG(S2); DBG(U2); DBG(D2);
    RAYA;
    
    int res = 0;
    int i = 0, j = 0;
    int pendienteD1 = 0, pendienteD2 = 0;
    while (i < SIZE(S1) && j < SIZE(S2)){
		DBG(i); DBG(S1[i]);
		DBG(j); DBG(S2[j]);
		DBG(pendienteD1); DBG(pendienteD2); DBG(res);
		
		if (S1[i] == 'U' || S2[j] == 'U'){
			int oldI = i, oldJ = j;
		// Me interesa buscar el intervalo mas chico de s1 [i, r1] tq su suma esta en [j, r2]
			auto [nextI, nextJ] = encontrarIntervalo(i, j, U1, U2);
			DBG(nextI); DBG(nextJ);
			
			// Tengo que comprimir todo el intervalo [i, nextI] de S1 a la forma UD. Idem con S2
			int nOfD1s = query(i, nextI, D1), nOfD2s = query(j, nextJ, D2);
			res += nOfD1s + nOfD2s;
			i = nextI+1;
			j = nextJ+1;
			
			assert(pendienteD1 == 0 || pendienteD2 == 0); // Uno de los dos no es necesario mover
			res += pendienteD1 + pendienteD2;
			if (pendienteD1 > 0){
				assert(S1[oldI-1] == 'D' && S2[oldJ-1] == 'D');
				assert(pendienteD1 == (D1[oldI-1] - D2[oldJ-1]));
			}
			if (pendienteD2 > 0){
				assert(S1[oldI-1] == 'D' && S2[oldJ-1] == 'D');
				assert(pendienteD2 == (D2[oldJ-1] - D1[oldI-1]));
			}
			
			nOfD1s += pendienteD1;
			nOfD2s += pendienteD2;
			pendienteD1 = 0;
			pendienteD2 = 0;
			
			// Me interesa que en la pos i y j hayan Ds y agregar la cantidad de nOfD1s y nOfD2s movidas ahi
			agregarD(i, S1, D1, nOfD1s);
			agregarD(j, S2, D2, nOfD2s);
			if (i < SIZE(S1) || j < SIZE(S2)){
				assert(i < SIZE(S1) && j < SIZE(S2));
				assert(S1[i] == 'D' && S2[j] == 'D');
			}
		} else {
			int d1 = D1[i], d2 = D2[j], d = abs(d1-d2);
			DBG(d1); DBG(d2);
			DBG(d);
			// Tenes que mover esta cantidad a D1[i+2] pero te conviene hacerlo realmente despues de que D1[i] (U) se mergee como le convenga para pagar el d solo una vez
			if (d1 > d2) pendienteD1 = d;
			else pendienteD2 = d;
			i++;
			j++;
		}
		
		RAYA;
	}
	
	assert(pendienteD1 == 0 && pendienteD2 == 0);
	
	cout << res << "\n";
    
    return 0;
}
