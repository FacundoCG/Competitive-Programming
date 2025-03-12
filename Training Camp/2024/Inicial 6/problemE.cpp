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

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl

#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)

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


int main()
{
	ll n;
	
	cin >> n;
	
	set<ll> elementos;
	
	bool hayDupla = false;
	vector<ll> dupla(2);
	
	for(ll i=0; i<n; i++){
		ll e;
		cin >> e;
		elementos.insert(e);
	}
	
	ll delta = 1;
	
	for(ll h=0; h<33; h++){
		for(const auto &e : elementos){
			
			ll e_atras = e-delta;
			ll e_adelante = e+delta;
			
			bool hayAtras = esta(e_atras, elementos);
			bool hayAdelante = esta(e_adelante, elementos);
			
			if (hayAtras && hayAdelante){
				cout << "3" << "\n";
				cout << e-delta << " " << e << " " << e+delta;
				return 0;
			}
			
			if(!hayDupla){
				
				if(hayAtras){
					dupla[0] = e_atras;
					dupla[1] = e;
					hayDupla = true;
				}
				if(hayAdelante){
					dupla[0] = e;
					dupla[1] = e_adelante;
					hayDupla = true;
				}
			}
		}
		delta *= 2;
	}

	
	if(hayDupla){
		cout << "2" << "\n";
		cout << dupla[0] << " " << dupla[1];
		return 0;
	}
	
	cout << "1" << "\n";
	cout << *elementos.begin();	
	
    return 0;
}
