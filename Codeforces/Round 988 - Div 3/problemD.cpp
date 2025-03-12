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

int calculateMinimumNumberOfPowerUps(ll &currentPowerJump, priority_queue<ll> &bestPowerUps, ll distanceToJump){
    int res = 0;
    while (!bestPowerUps.empty() && distanceToJump >= currentPowerJump){
        currentPowerJump += bestPowerUps.top();
        res++;
        bestPowerUps.pop();
    }
    
    if (distanceToJump >= currentPowerJump) res = -1;
    return res;
}

void solve(vector<pair<ll,ll>> &boundOfHurdle, vector<ll> &positionOfPowerUp, vector<ll> &valueOfPowerUp){
    // For each test case, output the minimum number of power-ups she must collect to reach position L.If it is not possible, output −1
    // If she is at position x with a power jump of k, she can jump to any position in: [x, x+k]  
    ll currentPowerJump = 1;
    int j = 0; // Current powerup
    int i = 0; // Current hurdle
    int res = 0;
    priority_queue<ll> bestPowerUps;
    
    while (i < SIZE(boundOfHurdle)){        
        if (j < SIZE(positionOfPowerUp) && positionOfPowerUp[j] < boundOfHurdle[i].first){ // It means that it comes a powerup before the hurdle
            bestPowerUps.push(valueOfPowerUp[j]);
            j++;
        } else { // Now I have to check if I can a skip a hurdle
            ll distanceToJump = boundOfHurdle[i].second - boundOfHurdle[i].first + 1;
            if (distanceToJump >= currentPowerJump){ // It means that I need to use some powerups to skip the hurdle
                int numberOfPowerUpsUsed = calculateMinimumNumberOfPowerUps(currentPowerJump, bestPowerUps, distanceToJump);
                
                if (numberOfPowerUpsUsed == -1){ // If I can't skip the hurdle
                    res = -1;
                    break; // I leave the while
                } else {
                    res += numberOfPowerUpsUsed;
                }
            }
                         
            i++;
        }
    }
    
    cout << res << "\n";
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
    
    forn(_,t){
		ll n, m, L;
        cin >> n >> m >> L;
        
        vector<pair<ll,ll>> boundOfHurdle(n);
        vector<ll> positionOfPowerUp(m);
        vector<ll> valueOfPowerUp(m);
        
        forn(i, n){
            ll l, r;
            cin >> l >> r;
            boundOfHurdle[i] = {l, r};
        } 
        
        forn(i, m){
            ll x, v;
            cin >> x >> v;
            positionOfPowerUp[i] = x;
            valueOfPowerUp[i] = v;
        }
        
        
        solve(boundOfHurdle, positionOfPowerUp, valueOfPowerUp);
    }
}






