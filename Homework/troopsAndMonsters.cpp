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
using vvvl = vector<vvl>;
using ii = pair<ll,ll>;
using vii = vector<ii>;
using vvii = vector<vii>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
//~ const int MAX_N = 1e5 + 1;
int MOD = 1e9 + 7;
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

struct MonsterType{
	ll amount, time, sand;
	
	MonsterType(ll AMOUNT, ll TIME, ll SAND) : amount(AMOUNT), time(TIME), sand(SAND) {}
	bool operator <(MonsterType &other){ return time < other.time;}
};

int n;

void solve(){
	cin >> n;
	
	vector<MonsterType> A;
	forn(_, n){
		ll amount, time, sand; cin >> amount >> time >> sand;
		A.pb(MonsterType(amount, time, sand));
	}
	
	sort(all(A));
	multiset<ii> collected;
	
	ll currentTime = 0;
	forn(i, n){		
		ll time = A[i].time, totalAmount = A[i].amount, sand = A[i].sand;
		ii toInsert = {sand, min(time-currentTime, totalAmount)};
		totalAmount -= toInsert.snd;

		while (totalAmount > 0 && !collected.empty()){
			ii p = *collected.begin();			
			if (p.fst >= sand) break;
			
			collected.erase(collected.begin());			
			ll changedSand = min(totalAmount, p.snd);
			toInsert.snd += changedSand;
			totalAmount -= changedSand;
			p.snd -= changedSand;
			currentTime -= changedSand;
			if (p.snd > 0) collected.insert(p);
		}
		
		if (toInsert.snd != 0) collected.insert(toInsert);
		currentTime += toInsert.snd;
	}
		
	ll res = 0;
	for (ii p : collected) res += p.fst*p.snd;
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
