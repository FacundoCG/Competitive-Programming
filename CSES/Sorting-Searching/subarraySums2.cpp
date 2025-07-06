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

// Calcular extremo izquierdo que cumple P(X)
int leftBinarySearch(int start, int end, vector<int> &A, int v){
    int l = start - 1; 
    int r = end + 1; 

    while(r - l > 1) { 
        int mid = (l + r) / 2;
        if(!(A[mid] >= v)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (r < start || r > end || !(A[r] >= v)) r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1

    return r; // r es el primer elemento que cumple P(X)
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n;
	ll x;
	
	cin >> n >> x;
	
	vector<ll> A(n);
	forn(i, n) cin >> A[i];
	
	vector<ll> prefixSum(n+1, 0);
	forsn(i, 1, n+1) prefixSum[i] = prefixSum[i-1] + A[i-1];
	map<ll, vector<int>> positions;
	
	forsn(i, 1, n+1) positions[prefixSum[i]].pb(i);
	//~ DBG(A);
	//~ DBG(prefixSum);
	
	//~ for (auto p : positions){
		//~ DBG(p.fst); DBG(p.snd);
	//~ }
	
	ll res = 0;
	
	forsn(i, 1, n+1){
		ll toFind = x + prefixSum[i-1];
		int index = leftBinarySearch(0, SIZE(positions[toFind])-1, positions[toFind], i);
		//~ DBG(toFind); DBG(index);
		if (index != UNDEFINED) res += SIZE(positions[toFind]) - index;
	}
	
	cout << res << "\n";
	
	
    return 0;
}
