#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

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

// Calcular extremo derecho que cumple P(X)
int rightBinarySearch(int start, int end, vector<string> &A, string &s){
    int l = start - 1;
    int r = end + 1;

    while (r - l > 1){
        int mid = (l + r)/2;

        if (A[mid] < s){
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (l < start || l > end || !(A[l] < s)){
		l = -1; // Si l no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return l+1; // l es el ultimo elemento que cumple P(X)
}

int rightBinarySearch1(int start, int end, vector<string> &A, string &s){
    int l = start - 1;
    int r = end + 1;

    while (r - l > 1){
        int mid = (l + r)/2;

        if (A[mid] <= s){
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (l < start || l > end || !(A[l] <= s)){
		l = -1; // Si l no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	}

    return l+1; // l es el ultimo elemento que cumple P(X)
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;
    
    vector<string> A(n);
    map<string, vector<string>> M;
    map<string, int> repetitions;
    
    forn(i, n) cin >> A[i];
    forn(i, n){
		repetitions[A[i]]++;
		string B = A[i];
		sort(all(B));
		M[B].pb(A[i]);
	}
	
	forn(i, n) sort(all(A[i]));
	sort(all(A));
	
	for (auto &p : M) sort(all(p.snd));
	
	int q;
	cin >> q;
	
	forn(i, q){
		string s;
		cin >> s;
		
		string t = s;
		sort(all(t));
		ll res = rightBinarySearch(0, n-1, A, t); // I calculate how many words a satisfy f(a) < f(s)
		res += rightBinarySearch1(0, SIZE(M[t])-1, M[t], s); // I calculate for the words: f(a) = f(s)
		cout << res << "\n";
	}
}
