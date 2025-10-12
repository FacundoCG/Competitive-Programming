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
vector<string> A;
int h, w;

int countBlacks(int i, int j){
	int res = 0;
	if (i+1 < h && A[i+1][j] == '#') res++;
	if (0 <= i-1 && A[i-1][j] == '#') res++;
	if (j+1 < w && A[i][j+1] == '#') res++;
	if (0 <= j-1 && A[i][j-1] == '#') res++;
	return res;
}

void update_position(int i, int j, set<ii> &to_paint, vector<vi> &black_neighbors){
	black_neighbors[i][j] = countBlacks(i, j);
	if (black_neighbors[i][j] == 1 && A[i][j] == '.') to_paint.insert({i, j});
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> h >> w;
	A.resize(h);
	forn(i, h) cin >> A[i];
	
	//~ DBG(A);
	vector<vi> black_neighbors(h, vi(w, 0));
	set<ii> to_paint;
	
	forn(i, h){
		forn(j, w){
			black_neighbors[i][j] = countBlacks(i, j);
			if (black_neighbors[i][j] == 1 && A[i][j] == '.') to_paint.insert({i, j});
		}
	}
		
	ll res = 0;
	while (!to_paint.empty()){
		//~ res += SIZE(to_paint);
		set<ii> new_to_paint;
		for (auto [i, j] : to_paint) A[i][j] = '#';
		for (auto [i, j] : to_paint){
			if (i+1 < h) update_position(i+1, j, new_to_paint, black_neighbors);
			if (0 <= i-1) update_position(i-1, j, new_to_paint, black_neighbors);
			if (j+1 < w) update_position(i, j+1, new_to_paint, black_neighbors);
			if (0 <= j-1) update_position(i, j-1, new_to_paint, black_neighbors);
		}
		
		to_paint = new_to_paint;
	}
	
	forn(i, h){
		forn(j, w) res += (A[i][j] == '#');
	}
	
	cout << res << "\n";
	//~ RAYA;
	
    return 0;
}
