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

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		string s;
		cin >> s;
		
		map<char, int> repeticiones;
		vector<pair<int, char>> A;
		
		forn(i, SIZE(s)) repeticiones[s[i]]++;
		for (auto p : repeticiones) A.pb({p.snd, p.fst});
		
		sort(all(A));
		
		if (SIZE(A) == 1){
			if (A[0].fst > 1) cout << "NO\n";
			else {
				cout << "YES\n";
				cout << s << "\n";
			}
		} else if (SIZE(A) == 2){
			if (A[0].fst >= 2 && A[1].fst >= 2){ 
				cout << "NO\n";
			} else {
				string res = "";
				forn(i, A[0].fst) res += A[0].snd;
				forn(i, A[1].fst) res += A[1].snd;
				cout << "YES\n";
				cout << res << "\n";
			}
		} else {
			string res = ""; // ABCDEAA
			// AAB
			
			forn(j, SIZE(s)){
				dforn(i, SIZE(A)){
					if (A[i].fst > 0){
						res += A[i].snd;
						A[i].fst--;
					}
				}
			}
			
			cout << "YES\n";
			cout << res << "\n";
		}
	}
	
	
    return 0;
}
