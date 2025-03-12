#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 998244353;
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

ll complementBetween(ll i, ll j, vector<ll> &prefixSum){
	ll res = prefixSum[i];
	if (j > 0) res -= prefixSum[j-1];
	return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    ll n, m;
    cin >> n >> m;
	
	vector<ll> A(n+2);
	A[0] = 0;
	A[n+1] = m;
	forsn(i, 1, n+1) cin >> A[i];
	
	vector<ll> totalTimeTurnedOnUntil(n+2);
	totalTimeTurnedOnUntil[0] = A[0];
	
	forsn(i, 1, n+2){
		if (i % 2 == 1){ // Si apago, entonces cuento el tiempo entre el elemento anterior y el actual
			totalTimeTurnedOnUntil[i] = totalTimeTurnedOnUntil[i-1] + (A[i] - A[i-1]);
		} else { // Si prendo, no cuento nada porque estaba apagado
			totalTimeTurnedOnUntil[i] = totalTimeTurnedOnUntil[i-1];
		}
	}
	
	ll res = totalTimeTurnedOnUntil[n+1];
	
	forn(i, n+1){
		// Voy a poner un punto entre A[i] y A[i+1]
		if (A[i] + 1 == A[i+1]) continue; // Si no tengo espacio para ponerlo, lo salteo
		
		ll newRes = totalTimeTurnedOnUntil[i]; // Sumo lo que estuvo prendida hasta A[i] que todo funcionaba bien
		ll timeLeft = m - A[i+1]; // El tiempo total entre [A[i+1], ..., m]
		ll complementTime = complementBetween(n+1, i+1, totalTimeTurnedOnUntil);
		
		if (i % 2 == 0){ // Si la lampara estaba prendida, entonces la voy a apagar lo más tarde posible
			ll newPoint = A[i+1] - 1; // Lo pongo en esta posición y apago
			newRes += newPoint - A[i]; // Sumo el intervalo prendido [A[i], newPoint]
		} else { // Si la lampara estaba apagada, entonces la voy a prender lo más pronto posible
			ll newPoint = A[i] + 1; // Lo pongo en esta posición y la prendo
			newRes += A[i+1] - newPoint; // Sumo el intervalo prendido [newPoint, A[i+1]]
		}
		
		newRes += timeLeft - complementTime;
		res = max(res, newRes);
	}
	
	cout << res << "\n";
}
