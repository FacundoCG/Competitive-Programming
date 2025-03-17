#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
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
#define forsn(i,s,n) for (ll i=(s);i<(ll)(n);i++)
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

bool isBadConfiguration(vector<vector<ll>> &dogsForPrimaryHouse, vector<vector<ll>> &dogsForSecondaryHouse){
	map<ll, ll> primaryHouseForDog;
	
	forsn(i, 1, SIZE(dogsForPrimaryHouse)){
		for (ll j : dogsForPrimaryHouse[i]) primaryHouseForDog[j] = i;
	}
	
	forsn(i, 1, SIZE(dogsForSecondaryHouse)){
		for (ll j : dogsForSecondaryHouse[i]){
			if (primaryHouseForDog[j] == i) return true;
		}
	}
	
	return false;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
	
	ll n, x;
	cin >> n >> x;
	
	vector<vector<ll>> dogsForPrimaryHouse(n+1);
	vector<vector<ll>> dogsForSecondaryHouse(n+1);
	
	forsn(i, 1, n+1){
		ll firstDog = (i-1)*x + 1;
		ll lastDog = i*x;
		forsn(j, firstDog, lastDog+1) dogsForPrimaryHouse[i].pb(j);
	}
	
	forsn(i, 1, n+1){
		ll houseToAsign = i+1;
		for (ll j : dogsForPrimaryHouse[i]){
			if (houseToAsign > n){
				houseToAsign %= n;
			}
			
			dogsForSecondaryHouse[houseToAsign].pb(j);
			houseToAsign++; 
		}
	}
	
	if (isBadConfiguration(dogsForPrimaryHouse, dogsForSecondaryHouse)){
		cout << -1 << "\n";
		return 0;
	}
	
	forsn(i, 1, n+1){
		for (ll dog : dogsForPrimaryHouse[i]) cout << dog << " ";
		for (ll dog : dogsForSecondaryHouse[i]) cout << dog << " ";
		cout << "\n";
	}
	
	return 0;
}
