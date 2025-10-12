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
int n;
vi res;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    cin >> n;
	int M = (1 << n);
    vector<vi> adjList(M);
    
    assert(M >= 0);
    
    forn(i, M){
		forn(j, n){
			int currentNumber = i;
			if (i & (1 << j)) currentNumber &= ~(1 << j);
			else currentNumber |= (1 << j);
			adjList[i].pb(currentNumber);
		}
	}
	
	vb visited(M, false);
	int v = 0;
	
	while (SIZE(res) < M){
		res.pb(v);
		visited[v] = true;
		
		for (int j : adjList[v]){
			if (visited[j]) continue;
			v = j;
			break;
		}
	}
    
    for (int x : res){
		string s;
		
		dforn(i, n){
			if ((1 << i) & x) s += '1';
			else s += '0';
		}
		
		cout << s << "\n";
	}
}
