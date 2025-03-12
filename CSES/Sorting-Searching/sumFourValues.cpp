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
map<ll, ll> repetitionsOfA;
map<ll, ll> repetitionsOfPairSums;

bool existsSumOfTwoValues(ll valueToFind, ll a1, ll a2){
    if (esta(valueToFind, repetitionsOfPairSums)){ // I checked that I can get that value with the sum of two values. Let's check that the two values are different from what we have used
        ll value1 = valueToFind - a1;
        ll value2 = valueToFind - a2;
        ll value3 = a1 + a2;

        if (esta(value1, repetitionsOfA) && value1 != a2 && repetitionsOfA[a1] > 1){ // If I used a1 for this sum and not a2 and I have more than one repetition of a1, then it is true
            return true;
        } else if (esta(value2, repetitionsOfA) && value2 != a1 && repetitionsOfA[a2] > 1){ // If I used a2 for this sum and not a1 and I have more than one repetition of a2, then it is true
            return true;
        } else if (valueToFind == value3 && ((repetitionsOfA[a1] > 1 && repetitionsOfA[a2] > 1 && a1 != a2) || (repetitionsOfA[a1] > 3 && a1 == a2))){ // If I used both values for this sum and I have more than one repetition of each one, then it is true
            return true;
        } else if (!esta(value1, repetitionsOfA) && !esta(value2, repetitionsOfA)){ // If I didn't use any of the previous values for this sum, then it is true
            return true;
        }
    }

    return false;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    ll n, x;
    cin >> n >> x;

    ll x1, x2, x3, x4, lookingFor;
    bool existsSumOfFourValues = false;
    vector<ll> A(n);

    forn(i, n){
        cin >> A[i];
        repetitionsOfA[A[i]]++;
    }

    forn(i, n){
        forsn(j, i+1, n){
            ll sumOfPair = A[i] + A[j];
            repetitionsOfPairSums[sumOfPair];
        }
    }

    forn(i, n){
        forsn(j, i+1, n){
            ll valueToFind = x - A[i] - A[j];
            if (existsSumOfTwoValues(valueToFind, A[i], A[j])){
                existsSumOfFourValues = true;
                lookingFor = valueToFind;
                x1 = i;
                x2 = j;
            }
        }
    }

    if (existsSumOfFourValues){
        forn(i, n){
            forsn(j, i+1, n){
                ll currentSum = A[i] + A[j];

                if (currentSum == lookingFor && (i != x1 && i != x2 && j != x1 && j != x2)){
                    x3 = i;
                    x4 = j;
                }
            }
        }

        cout << x1+1 << " " << x2+1 << " " << x3+1 << " " << x4+1 << "\n";
        return 0;
    }

    cout << "IMPOSSIBLE" << "\n";
}