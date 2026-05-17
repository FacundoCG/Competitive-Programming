#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using ii = pair<ll,ll>;
using vii = vector<ii>;

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

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

template <typename T>
using ordered_multiset = tree<
    pair<T, int>,
    null_type,
    less<pair<T, int>>, // NOT less_equal
    rb_tree_tag,
    tree_order_statistics_node_update
>;

struct EventoX{
	ll x; 
	ll sign;
	ii intervaloY;
	int id;
	
	EventoX(ll _x, ll _sign, ii _intervaloY, int _id) : x(_x), sign(_sign), intervaloY(_intervaloY), id(_id){}
	
	bool operator < (const EventoX &other) const {
		if (x != other.x) return x < other.x;
		return id < other.id;
	}
};

ll nOfElementsLessOrEqualThan(ll x, ordered_multiset<ll> &s){
	return (ll) s.order_of_key(make_pair(x+1, -1));
}

void solve(){
	ll n, m; cin >> n >> m;
	
	set<EventoX> eventosByX;
	vl pointsInsideRectangle(n);
	
	forn(i, n){
		ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		eventosByX.insert(EventoX(x1-1, -1, make_pair(y1, y2), i));
		eventosByX.insert(EventoX(x2, 1, make_pair(y1, y2), i));
	}
	
	vii points(m); forn(i, m) cin >> points[i].fst >> points[i].snd;
	sort(all(points));
	
	ll numRes = 0;
	int index = 0;
	
	// Necesito contar para cada rectangulo contar cuantos puntos contiene
	ordered_multiset<ll> activeYOfPoints;
	activeYOfPoints.insert(make_pair(-LINF, 0));
	activeYOfPoints.insert(make_pair(LINF, 0));
		
	for (auto E : eventosByX){
		while (index < SIZE(points) && points[index].fst <= E.x){
			activeYOfPoints.insert(make_pair(points[index].snd, index));
			index++;
		}
		
		ll y1 = E.intervaloY.fst-1, y2 = E.intervaloY.snd;
		ll nOfPointsInRange = nOfElementsLessOrEqualThan(y2, activeYOfPoints) - nOfElementsLessOrEqualThan(y1, activeYOfPoints);
		pointsInsideRectangle[E.id] += E.sign*nOfPointsInRange;
	}
	
	ll nOfPoints = (ll) SIZE(points);
	forn(i, SIZE(pointsInsideRectangle)) numRes += pointsInsideRectangle[i]*(nOfPoints-pointsInsideRectangle[i]); // Todas las veces que se tuvo que cruzar el i-esimo rectangulo
	
	ld res = (ld) 2.0 * ((ld) numRes/(ld) (nOfPoints*nOfPoints));
	cout << setprecision(numeric_limits<long double>::digits10 + 1); // Muestra con full precision para ld
	cout << res << "\n";
}


int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t = 1;
	//~ cin >> t;
	forn(_, t) solve();
	
    return 0;
}
