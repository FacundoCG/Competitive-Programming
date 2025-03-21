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

ll solve(multiset<ll> &tickets, ll maximumPrice){
    ll res = -1;

    if (tickets.empty()) return res;
    
    // It will give me an iterator pointing to the first ticket wich is >= maximumPrice
    auto it = tickets.lower_bound(maximumPrice);
    
    if (it == tickets.end()){ // It means that there aren't any ticket >= to the maximumPrice. It points outside the multiset
        --it; // Now I points to the largest element in the multiset
    }

    if (*it <= maximumPrice) {
        res = *it;
        tickets.erase(it);
    } else if (it != tickets.begin()) { // If it isn't the first one it means that I move back one step
        it--;
        res = *it;
        tickets.erase(it);
    }

    return res;
}

// ############################################################### //
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, m;
    cin >> n >> m;

    multiset<ll> tickets;
    vector<ll> customers(m);

    forn(i, n){
        ll t;
        cin >> t;
        tickets.insert(t);
    }

    forn(i, m) cin >> customers[i];

    forn(i, m){
        ll maximumPrice = customers[i];
        ll res = solve(tickets, maximumPrice);
        cout << res << "\n";
    }
}