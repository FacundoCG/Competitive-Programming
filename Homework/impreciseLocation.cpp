#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < (n); i++)
#define dforn(i, n) for(int i = (n-1); i >= 0; i--)
#define forsn(i, s, n) for(int i = (s); i < (n); i++)
#define SIZE(c) int((c).size())
#define pb push_back
#define all(c) (c).begin(), (c).end()
#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "---------------------" << endl

using ll = long long;
using tint = ll;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vs = vector<string>;

const tint MAX_VALUE = 3e9;

struct SegmentTreeLazy{
	int n;
	vl B, lazy;
	ll neutro = 0, apagado = -2;
	
	SegmentTreeLazy(vl &C) : n(SIZE(C)){
		B.resize(4*n, neutro);
		lazy.resize(4*n, apagado);
		build(1, 0, n-1, C);
	}
	
	void build(int v, int l, int r, vl &C){
		if (l == r) B[v] = C[l];
		else {
			int m = (l+r)/2;
			build(2*v, l, m, C);
			build(2*v+1, m+1, r, C);
			B[v] = B[2*v] + B[2*v+1];
		}
	}
	
	void apply(int v, int l, int r){
		if (lazy[v] != apagado){
			B[v] = (r-l+1ll)*lazy[v];
			if (l != r){
				lazy[2*v] = lazy[v];
				lazy[2*v+1] = lazy[v];
			}
			lazy[v] = apagado;
		}
	}
	
	ll query(int v, int tl, int tr, int l, int r){
		apply(v, tl, tr);
		if (tr < l || r < tl) return neutro;
		if (l <= tl && tr <= r) return B[v];
		int tm = (tl + tr)/2;
		return query(2*v, tl, tm, l, r) + query(2*v+1, tm+1, tr, l, r);
	}
	
	void set(int v, int tl, int tr, int l, int r, ll x){
		apply(v, tl, tr);
		if (tr < l || r < tl) return ;
		if (l <= tl && tr <= r){
			lazy[v] = x;
			apply(v, tl, tr);
			return ;
		}
		
		int tm = (tl+tr)/2;
		set(2*v, tl, tm, l, r, x);
		set(2*v+1, tm+1, tr, l, r, x);
		B[v] = B[2*v] + B[2*v+1];
	}
	
	ll makeQuery(int l, int r){ return query(1, 0, n-1, l, r); }
	
	void makeSet(int l, int r, ll x){ set(1, 0, n-1, l, r, x); }
};

enum Accion{IN, IN_VERTICE, OUT};

struct Rectangle{
	tint x1, y1, x2, y2;
	int id;
	Rectangle(tint _x1 = -1, tint _y1 = -1, tint _x2 = -1, tint _y2 = -1, int _id = -1)
		: x1(_x1), y1(_y1), x2(_x2), y2(_y2), id(_id){}
		
	bool contains(Rectangle &R){
		return (x1 <= R.x1 && R.x2 <= x2) && (y1 <= R.y1 && R.y2 <= y2);
	}
};

ostream & operator<<(ostream &os, const Rectangle &R){
	os << "(" << R.x1 << ", " << R.y1 << ") - (" << R.x2 << ", " << R.y2 << ")";
	return os;
}

vector<Rectangle> A, queries;
tint area(Rectangle &R){ return (R.x2-R.x1+1ll)*(R.y2-R.y1+1ll); }

struct Evento{
	tint pos;
	Accion action;
	int id;
	Evento (tint _pos = -1, Accion _action = IN, int _id = -1)
		: pos(_pos), action(_action), id(_id){}

	bool operator<(const Evento &other) const{
		if (pos != other.pos) return pos < other.pos;
		if (action != other.action) return action < other.action;
		if (action == IN_VERTICE) return area(queries[id]) > area(queries[other.id]);
		return area(A[id]) > area(A[other.id]);
	}
};

map<tint, int> indexOf;

void compressYCoordinates(){
	set<tint> s;
	forn(i, SIZE(A)){
		s.insert(A[i].y1);
		s.insert(A[i].y2);
	}
	
	forn(i, SIZE(queries)) s.insert(queries[i].y1);
	
	for (tint x : s){
		int index = SIZE(indexOf);
		indexOf[x] = index;
	}
}

int findRectangleWhoContains(int v, Rectangle &R, vvi &jump){
	if (A[v].contains(R)) return v;
	dforn(j, 30) if (jump[v][j] != -1 && !A[jump[v][j]].contains(R))
		v = jump[v][j];
	
	//~ DBG(v);
	//~ assert(jump[v][0] != -1 && A[jump[v][0]].contains(R));
	return jump[v][0];
}

int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	int n; cin >> n;
	
	A.resize(n+1);	
	forn(i, n){
		tint x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		A[i] = Rectangle(x1, y1, x2, y2, i);
	}
	A[n] = Rectangle(-MAX_VALUE, -MAX_VALUE, MAX_VALUE, MAX_VALUE, n);
	
	vector<Evento> q;
	forn(i, SIZE(A)){
		tint pos1 = A[i].x1, pos2 = A[i].x2;
		q.pb(Evento(pos1, IN, i));
		q.pb(Evento(pos2, OUT, i));
	}
	
	int nOfQueries; cin >> nOfQueries;
	queries.resize(nOfQueries);
	vi firstRectangleWhoContainsVertex(nOfQueries);
	
	forn(i, nOfQueries){
		tint x, y, r; cin >> x >> y >> r;
		queries[i] = Rectangle(x-r, y-r, x+r, y+r, i);
		q.pb(Evento(x-r, IN_VERTICE, i));
	}
	
	sort(all(q));
	compressYCoordinates();
		
	vl C(SIZE(indexOf), -1);
	SegmentTreeLazy T(C);
	vi parent(SIZE(A), -1);
	
	// Construyo el arbol de rectangulos
	for (auto [pos, action, id] : q){
		if (action == IN){
			int l = indexOf[A[id].y1], r = indexOf[A[id].y2];
			parent[id] = (int) T.makeQuery(l, l); // Que rectangulo activo cubre actualmente al punto l es tu padre
			T.makeSet(l, r, id); // Ahora vos sos el rectangulo activo que cubre el intervalo [l, r]
		} else if (action == OUT) {
			int l = indexOf[A[id].y1], r = indexOf[A[id].y2];
			int p = parent[id]; 
			T.makeSet(l, r, p); // Como dejas de estar activo le devolves el intervalo [l, r] a tu padre que sigue activo			
		} else { // El primer rectangulo que contiene este vertice es aquel que tenga la pos y1 ahora
			int l = indexOf[queries[id].y1];
			firstRectangleWhoContainsVertex[id] = (int) T.makeQuery(l, l);
		}
	}
	
	vvi jump(SIZE(parent), vi(30, -1));
	forn(i, SIZE(parent)) jump[i][0] = parent[i];
	forsn(j, 1, 30) forn(i, SIZE(parent)) if (jump[i][j-1] != -1)
		jump[i][j] = jump[jump[i][j-1]][j-1];
	
	//~ forn(i, n) cout << A[i] << " has parent: " << parent[i] << "\n";
	forn(i, nOfQueries){
		int start = firstRectangleWhoContainsVertex[i];
		//~ DBG(start);
		//~ DBG(queries[i]);
		int idRectangle = findRectangleWhoContains(start, queries[i], jump);
		if (idRectangle != n) cout << idRectangle+1 << "\n";
		else cout << "*\n";
	}
	
	return 0;
}
