#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

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

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n;
	cin >> n;
	
	vector<pair<int, int>> A(n);
	forn(i, n){
		ll v;
		cin >> v;
		A[i] = {v, i};
	}
	
	sort(all(A));
	
	vector<int> res(n, UNDEFINED);
	set<int> s; // Guardo indices
	
	int lastElement = A[0].fst; // El valor del último elemento
	
	vector<int> toAdd = {A[0].snd};
	
	forsn(i, 1, n){
		int currentIndex = A[i].snd;
		
		if (lastElement != A[i].fst){
			while (!toAdd.empty()){
				s.insert(toAdd.back());
				toAdd.pop_back();
			}
		}
		
		if (!s.empty()){
			auto it = s.lower_bound(currentIndex); // Quiero el indice más grande tq indice < currentIndex
			if (it != s.begin()){
				it--;
				res[currentIndex] = *it;
			}
		}
		
		toAdd.pb(currentIndex);
		lastElement = A[i].fst;
	}
	
	forn(i, n) cout << res[i] + 1 << " ";
	cout << "\n";
	
    return 0;
}
