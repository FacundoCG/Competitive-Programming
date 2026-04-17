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

template <typename T>
using vv = vector<vector<T>>;

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

void solve(){
	int n; cin >> n;
	vi in_deg(n), succ(n), culpable(n, UNDEFINED);
	vvi in_edges(n);
	
	forn(i, n){
		int v; cin >> v;
		v--;
		in_deg[v]++;
		succ[i] = v;
		in_edges[v].pb(i);
	}
		
	// Primero proceso todos los vertices que van a ser inocentes, basicamente los que no son acusados por nadie
	queue<int> q;
	forn(i, n) if (in_deg[i] == 0) q.push(i);
		
	while (!q.empty()){
		int v = q.front(); q.pop(); 
		culpable[v] = 0; // Lo marco como inocente
		
		int perpetrator = succ[v];
		if (culpable[perpetrator] == 1) continue;
		culpable[perpetrator] = 1;
		
		int w = succ[perpetrator]; // Quizas es inocente
		in_deg[w]--;
		if (in_deg[w] == 0 && culpable[w] == UNDEFINED) q.push(w);
	}
		
	int res = 0;
	forn(i, n) res += (culpable[i] == 1);
	
	forn(i, n){
		if (culpable[i] != UNDEFINED) continue; // Ya procesado
		
		int v = i; // Recorro el ciclo
		int sizeCiclo = 0;
		
		while (culpable[v] == UNDEFINED){
			culpable[v] = 1; // Lo marco como visitado
			v = succ[v];
			sizeCiclo++;
		}
		
		res += (sizeCiclo+1)/2;
	}
	
	cout << res << "\n";
}

 
int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t = 1; 
	cin >> t;
	forn(_, t) solve();
	return 0;
}
