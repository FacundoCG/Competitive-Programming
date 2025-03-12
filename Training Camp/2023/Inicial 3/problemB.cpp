#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl
#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define all(c) (c).begin(),(c).end()

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
struct LexicographicalComparator {
    bool operator()(const pair<ll, ll> & a, const pair<ll, ll> & b) const {
        return a > b; // Use operator > for min-heap
    }
};

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    ll n;
    cin >> n;
    
    vector<ll> arr;
    priority_queue<ll, vector<ll>, greater<ll>> q;
    vector<pair<string, ll>> operations;

    forn(i,n){
        string operation;
        ll v;
        cin >> operation;

        if (operation == "insert"){
            cin >> v;
            operations.pb({"insert", v});
            q.push(v);
        } else if (operation == "removeMin"){
            if (!q.empty()){
                operations.pb({"removeMin", 0});
                q.pop();
            } else {
                operations.pb({"insert", 1});
                operations.pb({"removeMin", 0});
            }
        } else {
            cin >> v;
            if (!q.empty() && q.top() < v){
                while(!q.empty() && q.top() < v){
                    operations.pb({"removeMin", 0});
                    q.pop();
                }
            }

            if (q.empty() || q.top() > v){
                operations.pb({"insert", v});
                q.push(v);
            }

            operations.pb({"getMin", v});
        }
    }

    int m = operations.size();

    cout << m << "\n";

    forn(i, m){
        string operation = operations[i].first;
        ll v = operations[i].second;

        if (operation == "removeMin"){
            cout << operation << "\n";
        } else {
            cout << operation << " " << v << "\n";
        }
    }
}