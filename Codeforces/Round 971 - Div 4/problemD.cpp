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

bool binarySearch(int start, int end, vector<ll> &A, ll v){
    if (start > end){
        return false;
    }

    int mid = (start + end)/2;

    if (A[mid] == v){
        return true;
    } else if (A[mid] < v){
        return binarySearch(mid+1, end, A, v);
    } else {
        return binarySearch(start, mid-1, A, v);
    }
}

ll calculateNumberOfTriangles(vector<ll> &topPoints, vector<ll> &bottomPoints){
    ll res = 0;

    forn(i, topPoints.size()){
        bool existsPairBottom = binarySearch(0, bottomPoints.size()-1, bottomPoints, topPoints[i]);

        if (existsPairBottom){
            res += topPoints.size() - 1;
            res += bottomPoints.size() - 1;
        }

        bool existsLeftPoint = binarySearch(0, bottomPoints.size()-1, bottomPoints, topPoints[i]-1);
        bool existsRightPoint = binarySearch(0, bottomPoints.size()-1, bottomPoints, topPoints[i]+1);
        
        if (existsLeftPoint && existsRightPoint){
            res++;
        }
    }

    forn(i, bottomPoints.size()){
        bool existsLeftPoint = binarySearch(0, topPoints.size()-1, topPoints, bottomPoints[i]-1);
        bool existsRightPoint = binarySearch(0, topPoints.size()-1, topPoints, bottomPoints[i]+1);
        
        if (existsLeftPoint && existsRightPoint){
            res++;
        }
    }
    
    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_,t){
        int n;
        cin >> n;

        vector<ll> topPoints;
        vector<ll> bottomPoints;
        
        forn(i,n){
            ll x,y;
            cin >> x >> y;
            
            if (y == 0){
                bottomPoints.pb(x);
            } else {
                topPoints.pb(x);
            }
        }

        sort(all(topPoints));
        sort(all(bottomPoints));

        ll res = calculateNumberOfTriangles(topPoints, bottomPoints); 
        cout << res << "\n";
    }
}