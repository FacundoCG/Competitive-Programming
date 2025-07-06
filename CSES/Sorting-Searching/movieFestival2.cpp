#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

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

typedef pair<int, int> interval;

bool finishEarlier(interval &p1, interval &p2){
    ll endingTimeP1 = p1.second, endingTimeP2 = p2.second;
    if (endingTimeP1 != endingTimeP2) return endingTimeP1 < endingTimeP2;
    ll startingTimeP1 = p1.first, startingTimeP2 = p2.first;
    return startingTimeP1 < startingTimeP2;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, k;
	cin >> n >> k;
	
	vector<interval> A(n);
	forn(i, n){
		int l, r;
		cin >> l >> r;
		A[i] = {l, r};
	}
	
	sort(all(A), finishEarlier);
	
	ll res = 1;
	multiset<int> s = {A[0].snd-1};
	
	forsn(i, 1, n){
		int startingTime = A[i].fst, endingTime = A[i].snd;
		auto it = s.lower_bound(startingTime);
		
		if (it == s.begin()){ 
			if (SIZE(s) < k){
				s.insert(endingTime-1);
				res++;
			}
		} else {
			it--;
			s.erase(it);
			s.insert(endingTime-1);
			res++;
		}
	}
	
	cout << res << "\n";
	
    return 0;
}
