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

vector<int> calculate(vector<int> &answersKnown, int n){
	int i = 1;
	int j = 0;
	vector<int> res;
	
	while (i <= n && j < SIZE(answersKnown)){
		if (i < answersKnown[j]){
			res.pb(i);
			i++;
		} else if (i == answersKnown[j]){
			i++;
			j++;
		}
	}
	
	while (i <= n){
		res.pb(i);
		i++;
	}
	
	return res;
}

void solve(int n, vector<int> &missingQuestionForEachList, vector<int> &answersKnown){
	int numberOfLists = SIZE(missingQuestionForEachList);
	vector<int> answersUnknown = calculate(answersKnown, n);
	vector<int> res(numberOfLists, 0);
	
	forn(i, numberOfLists){
		if (SIZE(answersUnknown) == 0){
			res[i] = 1;
		} else if (SIZE(answersUnknown) == 1 && answersUnknown[0] == missingQuestionForEachList[i]){
			res[i] = 1;
		} 
	}
	
	forn(i, numberOfLists) cout << res[i];
	cout << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_, t){
		int n, m, k;
		cin >> n >> m >> k;
		
		vector<int> missingQuestionForEachList(m);
		forn(i, m) cin >> missingQuestionForEachList[i];
		
		vector<int> answersKnown(k);
		forn(i, k) cin >> answersKnown[i];
		
		solve(n, missingQuestionForEachList, answersKnown);
	}
}
