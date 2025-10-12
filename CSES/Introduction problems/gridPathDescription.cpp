#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
//~ const int MAX_N = 1e5 + 1;
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

const int MAX_N = 7;
bool visited[MAX_N][MAX_N];
string s;

bool puedoEstar(int i, int j){ // Si puedo ir a (i, j)
	return !(i < 0 || i >= 7 || j < 0 || j >= 7 || visited[i][j]);
}

int bt(int i, int j, int pos){
	if (!puedoEstar(i, j)) return 0; // Posición invalida o ya visitada
	if (i == 6 && j == 0 && pos != 48) return 0; // Llegué antes de visitar todas las casillas
	if (i == 6 && j == 0 && pos == 48) return 1;
	
	// Si solo puedo moverme izquierda/derecha o arriba/abajo entonces termino
	if (puedoEstar(i+1, j) && puedoEstar(i-1, j) && !puedoEstar(i, j-1) && !puedoEstar(i, j+1)) return 0;
	if (!puedoEstar(i+1, j) && !puedoEstar(i-1, j) && puedoEstar(i, j-1) && puedoEstar(i, j+1)) return 0;
	
	int res = 0;
	visited[i][j] = true;
	
	if (s[pos] == '?'){
		res = bt(i+1, j, pos+1);
		res += bt(i-1, j, pos+1);
		res += bt(i, j-1, pos+1);
		res += bt(i, j+1, pos+1);
	} else if (s[pos] == 'D') res = bt(i+1, j, pos+1);
	else if (s[pos] == 'U') res = bt(i-1, j, pos+1);
	else if (s[pos] == 'L') res = bt(i, j-1, pos+1);
	else res = bt(i, j+1, pos+1);
	
	visited[i][j] = false;
	return res;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> s;
	
	//~ DBG(s);
	
	forn(i, MAX_N) {forn(j, MAX_N) visited[i][j] = false; }
	int res = bt(0, 0, 0);
	cout << res << "\n";
	
    return 0;
}
