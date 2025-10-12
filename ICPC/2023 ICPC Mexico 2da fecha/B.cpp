#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

using vi = vector<int>;
using vvi = vector<vi>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;

#define pb push_back
#define fst first
#define snd second

#define esta(x, c) ((c).find(x) != (c).end())
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << "=" << (x) << endl;
#define RAYA cerr << "-----------" << endl;

#define forn(i, n) for(int i=0; i<(int)(n);i++)
#define forsn(i, s, n) for(int i=(s); i<(int)(n);i++)

template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v){
	os << "[";
	forn(i, SIZE(v)){
		if (i > 0) os << ",";
		os << v[i];
	}
	return os << "]";
}

// ######################## //

const int MAX_N = 1000010;

ll fact[MAX_N+10];

ll mod(ll a, ll m = MOD){
	ll res = ((a % m) + m) % m;
	return res;
}

ll addMod(ll a, ll b, ll m = MOD){
	ll res = (mod(a, m) + mod(b, m)) % m;
	return res;
}

ll mulMod(ll a, ll b, ll m = MOD){
	ll res = (mod(a, m) * mod(b, m)) % m;
	return res;
}

ll binPowMod(ll base, ll exp, ll m = MOD){
	if (exp == 0) return 1;
	ll a = binPowMod(base, exp/2, m);
	ll res = mulMod(a, a, m);
	if(exp % 2 == 1) res = mulMod(res, base, m);
	return res;
}

ll divideMod(ll a, ll b, ll m = MOD){
	ll res = mulMod(a, binPowMod(b, m-2, m), m) % m;
	return res;
}

void calcularFactorial(ll n, ll m = MOD){
	fact[0] = 1;
	forsn(i, 1, n+1) fact[i] = mulMod(fact[i-1], i, m);
}


int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	int n, k;
	cin >> n >> k;
	
	calcularFactorial(MAX_N);
	
	vi vec(n);
	map<int, int> elem2apariciones;
	
	forn(i, n){
		cin >> vec[i];
		elem2apariciones[vec[i]]++;
	}
	
	ll probabilidad = divideMod(1, fact[n]);
	
	for(auto [e, apariciones] : elem2apariciones){
		if(apariciones >= 2){
			probabilidad = mulMod(probabilidad, fact[apariciones]);
		}
	}
	
	cout << probabilidad << "\n";
	
	forn(i, k){
		int pos, nuevo_val;
		cin >> pos >> nuevo_val;
		pos--;
		
		int valor_viejo = vec[pos];
		probabilidad = divideMod(probabilidad, elem2apariciones[valor_viejo]);
		elem2apariciones[valor_viejo]--;
		elem2apariciones[nuevo_val]++;
		probabilidad = mulMod(probabilidad, elem2apariciones[nuevo_val]);
		vec[pos] = nuevo_val;
		
		cout << probabilidad << "\n";
	}
	
	
	return 0;
}
