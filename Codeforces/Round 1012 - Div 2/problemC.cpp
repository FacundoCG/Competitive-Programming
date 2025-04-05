#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> celda;
typedef tuple<celda, int, int> mesa;

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

int n;

bool myMesaCmp(const mesa& a, const mesa& b) {
	int d1 = get<1>(a);
	int d2 = get<1>(b);
	
	int k1 = get<2>(a);
	int k2 = get<2>(b);
	int x1 = get<0>(a).fst;
	int y1 = get<0>(a).snd;
	int x2 = get<0>(b).fst;
	int y2 = get<0>(b).snd;
	
	
	if (k1 == 1 || k1 == 2){
		d1++;
		if (k1 == 1) y1++;
		if (k1 == 2) x1++;
	}
	
	if (k1 == 3) {
		d1 += 4;
		x1++; y1++;
	}
	
	if (k2 == 1 || k2 == 2) {
		d2++;
		if (k2 == 1) y2++;
		if (k2 == 2) x2++;
	}
	
	if (k2 == 3) {
		d2 += 4;
		x2++; y2++;
	}
	
	if (d1 > d2){
		return true;
	} else if (d1 < d2){
		return false;
	}
	
	if (x1 > x2){
		return true;
	} else if (x2 > x1){
		return false;
	}
	
	return y1 > y2;
}

struct MesaCmp {
    bool operator()(const mesa& a, const mesa& b) const {
        return myMesaCmp(a, b);
    }
};

void printQueue(priority_queue<mesa, vector<mesa>, MesaCmp> &mesasLibres){
	map<int, int> distances;
	
	while (!mesasLibres.empty()){
		mesa m = mesasLibres.top();
		mesasLibres.pop();
		distances[get<1>(m)]++;
	}
	
	for (auto p : distances){
		cout << p.fst << ": " << p.snd << "\n";
	}
}

void solve(vector<int> &A){
	priority_queue<mesa, vector<mesa>, MesaCmp> mesasLibres;
	priority_queue<mesa, vector<mesa>, MesaCmp> mesasOcupadas;
	
	int y0 = 1;
	int currentDistance = 2;
	
	while (SIZE(mesasLibres) <= n+100){
		int y1 = y0 + 3;
		int x0 = 1;
		
		while (y0 >= 1){
			celda c = make_pair(x0, y0);
			mesa m = {c, currentDistance, 0};
			mesasLibres.push(m);
			x0 += 3;
			y0 -= 3;
		}
		
		currentDistance += 3;
		y0 = y1;
	}
		
	forn(i, SIZE(A)){
		mesa m;
		
		if (A[i] == 0 || SIZE(mesasOcupadas) == 0){
			m = mesasLibres.top();
			mesasLibres.pop();
		} else {
			mesa m1 = mesasOcupadas.top();
			mesasOcupadas.pop();
			
			mesa m2 = mesasLibres.top();
			mesasLibres.pop();
			
			if (myMesaCmp(m1, m2)){
				m = m2;
				mesasOcupadas.push(m1);
			} else {
				m = m1;
				mesasLibres.push(m2);
			}
		}
		
		celda c = get<0>(m);
		int distance = get<1>(m);
		int d = get<2>(m);
		
		if (d < 3){
			int newD = d+1;
			mesa newMesa = {c, distance, newD};
			mesasOcupadas.push(newMesa);
		}
		
		if (d == 1){
			c.snd++;
		} else if (d == 2){
			c.fst++;
		} else if (d == 3){
			c.snd++;
			c.fst++;
		}
		
		cout << c.fst << " " << c.snd << "\n";
	}
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		cin >> n;
		vector<int> A(n);
		forn(i, n) cin >> A[i];
		solve(A);
	}
}
