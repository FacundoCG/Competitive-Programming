#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
//const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;
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
const ll MAX_N = pow(10, 5)*2;
ll memo[MAX_N + 1];


int rightBinarySearch(int start, int end, vector<tuple<ll, ll, ll>> &A, ll v){
    int l = start - 1;
    int r = end + 1;

    while (r - l > 1){
        int mid = (l + r)/2;
		ll x = get<1>(A[mid]);
		
        if (x < v){
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (l < start || l > end || get<1>(A[l]) >= v){
		l = -1; // Si l no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return l; // l es el ultimo elemento que cumple P(X)
}

ll dp(int i, vector<tuple<ll, ll, ll>> &A){
	if (i < 0) return 0;
	
	if (memo[i] == UNDEFINED){
		ll option2 = get<2>(A[i]) + dp(rightBinarySearch(0, i-1, A, get<0>(A[i])), A);
		memo[i] = max(dp(i-1, A), option2);
	}
	
	return memo[i];
}

bool customCompare(tuple<ll, ll, ll> p1, tuple<ll, ll, ll> p2){
	return get<1>(p1) < get<1>(p2);
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	cin >> n;
	
	vector<tuple<ll, ll, ll>> A(n);
	forn(i, n) {
		ll start, end, money;
		cin >> start >> end >> money;
		A[i] = make_tuple(start, end, money);
	}
	
	sort(all(A), customCompare);
	forn(i, n) memo[i] = UNDEFINED;
	
	cout << dp(n-1, A) << "\n";
}
