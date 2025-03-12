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


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //

bool check(map<ll, multiset<ll>> &repetitions, ll modDesiredNumber, ll desiredNumber){
    bool res = false;

    if (esta(modDesiredNumber, repetitions) && !repetitions[modDesiredNumber].empty()){
        auto it = repetitions[modDesiredNumber].lower_bound(desiredNumber);

        if (it != repetitions[modDesiredNumber].begin()){
            it--;
            repetitions[modDesiredNumber].erase(it);
            res = true;
        }
    }

    return res;
}

ll continueFindForNextNumber(map<ll, multiset<ll>> &repetitions, ll currentNumber, ll x){
    bool existsPossibilities = true;
    ll res = currentNumber;

    while (existsPossibilities) {
        ll numberToFind = (ll) ((ll) res+1) % x;

        if (check(repetitions, numberToFind, res+1)){
            res++;
        } else {
            existsPossibilities = false;
        }
    }

    return res;
}

void solve(vector<ll> &numbers, map<ll, multiset<ll>> &repetitions, ll x){
    ll m = numbers.size();
    ll currentNumber = numbers[0];
    ll i = 1;
    bool existsMoreOptions = true;

    if (currentNumber != 0){
        cout << 0 << "\n";
        return;
    }

    while (i < m){
        ll difference = (ll) numbers[i] - currentNumber;

        if (difference == 1){
            currentNumber = numbers[i];
            i++;
        } else {
            ll numberToFind = (ll) ((ll) currentNumber+1)%x;
            bool existsFollowingNumber = check(repetitions, numberToFind, currentNumber+1);

            if (!existsFollowingNumber){
                existsMoreOptions = false;
                break;
            } else {
                currentNumber++;
            }
        }
    }

    currentNumber = continueFindForNextNumber(repetitions, currentNumber, x);
    currentNumber++;

    cout << currentNumber << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_, t){
        ll n, x;
        cin >> n >> x;
        
        set<ll> numbers;
        map<ll, multiset<ll>> repetitionsOfModsX;

        forn(i,n){
            ll v;
            cin >> v;

            if (!esta(v, numbers)){
                numbers.insert(v);
            } else {
                repetitionsOfModsX[v%x].insert(v);
            }
        }

        vector<ll> arrNumbers(numbers.begin(), numbers.end());
        solve(arrNumbers, repetitionsOfModsX, x);
    }
}