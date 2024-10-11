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

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl

#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)

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

ll binarySearch(vector<pair<ll,ll>> &arr, int start, int end, ll v){
    if (start > end){
        return -1;
    } 

    int middle = (start + end)/2;

    if (arr[middle].first == v){
        return middle;
    } else if (arr[middle].first < v){
        return binarySearch(arr, middle+1, end, v);
    } else {
        return binarySearch(arr, start, middle-1, v);
    }
}

ll lookForDifferentGoodIndex(vector<pair<ll,ll>> &arr, int start, int different, ll value){
    int n = arr.size();
    ll res = -1;

    if (start + 1 < n && arr[start+1].first == value && start + 1 != different){
        res = start + 1;
    } else if (start + 2 < n && arr[start+2].first == value && start + 2 != different){
        res = start + 2;
    } else if (0 <= start - 1 && arr[start-1].first == value && start - 1 != different){
        res = start - 1;
    } else if (0 <= start - 2 && arr[start-2].first == value && start - 2 != different){
        res = start - 2;
    }

    return res;
}



int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);

    ll n, x;
    cin >> n >> x;

    vector<pair<ll,ll>> arr(n);
    bool flag = false;
    ll a,b,c;

    forn(i,n){
        ll v;
        cin >> v;
        arr[i] = {v,i+1};
    }

    sort(all(arr));

    forn(i,n){
        forn(j,n){
            if (i != j){
                ll objective = (ll) x - arr[i].first - arr[j].first;
                ll goodIndex = binarySearch(arr, 0, n-1, objective); 

                if (goodIndex == i){
                    goodIndex = lookForDifferentGoodIndex(arr, i, j, objective);
                } else if (goodIndex == j){
                    goodIndex = lookForDifferentGoodIndex(arr, j, i, objective);
                } 

                if (goodIndex != -1){
                    a = arr[i].second;
                    b = arr[j].second;
                    c = arr[goodIndex].second;
                    flag = true;
                    break;
                }
            }
        }
    }

    if (!flag){
        cout << "IMPOSSIBLE" << "\n";
    } else {
        cout << a << " " << b << " " << c << "\n";
    }
}