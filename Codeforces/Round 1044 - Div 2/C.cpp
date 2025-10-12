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
typedef pair<int, vi> caminos;

int makeQueryStartingAtWith(int v, vi &vertexs){
	cout << "? " << v << " " << SIZE(vertexs);
	forn(i, SIZE(vertexs)) cout << " " << vertexs[i];
	cout << "\n";
	cout.flush();
	
	int res;
	cin >> res;
	return res;
}

void solve(){
	map<int, vi> lengthOfPath;
	vi allVertexs;
	forsn(i, 1, n+1) allVertexs.pb(i);
	forsn(i, 1, n+1) {
		int res = makeQueryStartingAtWith(i, allVertexs);
		lengthOfPath[res].pb(i);
	}
	
	if (SIZE(lengthOfPath) == 1){
		cout << "! 1 1\n";
	} else {
		vector<vi> A;
		int longestPath = 0;
		
		for (auto &p : lengthOfPath) {
			longestPath = max(longestPath, p.fst);
			A.pb(p.snd);
		}
		
		int currentVertex = A[SIZE(A)-1][0];
		vi path = {currentVertex};
		vi vertexsUsed; 
		 
		dforn(i, SIZE(A)-1){
			vertexsUsed.pb(currentVertex);
			
			for (int u : A[i]){
				vertexsUsed.pb(u);
				int res =  makeQueryStartingAtWith(currentVertex, vertexsUsed);
				if (res == 1){
					vertexsUsed.pop_back();
				} else {
					currentVertex = u;
					vertexsUsed.clear();
					break;
				}
			}
			
			path.pb(currentVertex);
		}
		
		cout << "! " << longestPath;
		for (int v : path) cout << " " << v;
		cout << "\n";
	}
	
	cout.flush();
}

int main()
{	
	int t;
	cin >> t;
	
	forn(_, t){
		cin >> n;
		solve();
	}
	
    return 0;
}
