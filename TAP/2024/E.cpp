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

vector<tuple<ll,ll,ll>> K;

ll dp(int i, ll j, vector<vector<ll>> &memo){
    if (j == 0 || i == -1){ // If I don't have more life points or I don't have more weapons to choose
        return 0;
    }

    if (memo[i][j] == UNDEFINED){
        ll restingLifeWithoutDividing = j-get<1>(K[i]);
        
        if (restingLifeWithoutDividing >= 0){
            ll restingLife = restingLifeWithoutDividing/get<0>(K[i]);
            memo[i][j] = get<2>(K[i]) + dp(i-1, restingLife, memo);
        }

        memo[i][j] = max(memo[i][j], dp(i-1, j, memo));
    }

    return memo[i][j];
}

bool customCompare(tuple<ll, ll, ll> a, tuple<ll, ll, ll> b) {
    // This function helps me to sort the weapons that leave me with increasing health points for the user.
    // Basically: If I pick weapons p1, p2 in that order and I have more health points than picking p2, p1 in the final array I will have pos(p1) > pos(p2)
	return (get<1>(b)*(1-get<0>(a)) > get<1>(a)*(1-get<0>(b)));
}

int main()
{
    int n, p;
    cin >> n >> p;

    K.resize(n);

    forn(i, n){
        int a, b, c;
        cin >> a >> b >> c;
        K[i] = {a, b, c};
    }

    sort(all(K), customCompare);
	reverse(all(K));
	
    vector<vector<ll>> memo(n, vector<ll>(p+1, UNDEFINED));
    ll res = dp(n-1, p, memo);

    cout << res << "\n";
}

