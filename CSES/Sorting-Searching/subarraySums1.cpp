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

int binarySearch(int start, int end, vector<ll> &A, ll target){
    if (start > end){
        return -1;
    }

    int middle = (start + end)/2;

    if (A[middle] == target){
        return 1;
    } else if (A[middle] < target){
        return binarySearch(middle+1, end, A, target);
    } else {
        return binarySearch(start, middle-1, A, target);
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    ll n, x;
    cin >> n >> x;

    vector<ll> A(n);
    vector<ll> prefixSum(n);

    forn(i, n) cin >> A[i];

    prefixSum[0] = A[0];
    forsn(i, 1, n){
        prefixSum[i] = A[i] + prefixSum[i-1];
    }

    ll res = 0;
    ll currentSum = 0;
    forn(i, n){
        int existsValue = binarySearch(i, n-1, prefixSum, x + currentSum);

        if (existsValue != -1){
            res++;
        }

        currentSum += A[i];
    }

    cout << res << "\n";
}