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

vi children;
set<ii> res;

void build(ii u, set<ii> &used){
	//~ cout << "u is: "; DBG(u);
	int index = u.snd;
	if (children[index] == 1) return ;
	
	for (auto it = used.begin(); it != used.end() && children[index] > 1; it++){
		ii currentChild = *it;
		children[index] --;
		res.insert({index, currentChild.snd});
	}
}

void solve(ii v, set<ii> &available, set<ii> &used){
	//~ cout << "v is: "; DBG(v);
	available.erase(v);
	used.insert({abs(v.fst), v.snd});	
	int index = v.snd;
	int numberOfChild = v.fst + 1;
	int originalValue = children[index];
	
	auto p = available.lower_bound({numberOfChild, -1});
	if (p != available.end()){
		ii bestChild = *p;
		children[index] -= abs(bestChild.fst); // La cantidad de hijos de su vértice más grande
		res.insert({index, bestChild.snd});
		solve(bestChild, available, used);
	} else { return ; }
	
	p = available.lower_bound({numberOfChild, -1});
	if (p == available.end()) return ;
	if (children[index] == 1) return ;
		
	// Ahora todo lo quede disponible me va a sumar 1
	while (children[index] > 1 && !available.empty()){
		auto it = available.rbegin();
		ii currentChild = *it;
		if (abs(currentChild.fst) >= originalValue) return ;
		children[index]--;
		res.insert({index, currentChild.snd});
		build(currentChild, used); // currentChild tiene que cumplir su requerimiento con los vértices usados
		used.insert({abs(currentChild.fst), currentChild.snd});
		available.erase(currentChild);
	}
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n;
	cin >> n;
	
	children.resize(n);
	set<ii> available, used;
	
	forn(i, n){
		int c;
		cin >> c;
		children[i] = c;
		available.insert({(-1)*c, i});
	}
	
	//~ DBG(children);
	
	auto v = *available.begin();
    solve(v, available, used);
    
    while (!available.empty()){
		auto it = available.begin();
		ii currentVertex = *it;
		//~ DBG(currentVertex);
		build(currentVertex, used);
		available.erase(it);
	}
	
	//~ DBG(children);
	
	forn(i, n){
		if (children[i] == 1) continue;
		cout << "-1\n";
		return 0;
	}
	
	cout << SIZE(res) << "\n";
	for (auto [w, u] : res) cout << w+1 << " " << u+1 << "\n";
    
    return 0;
}
