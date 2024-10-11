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

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<set<ll>> adjList(n);
    vector<ll> degreeOfTheVertex(n, 0);
    vector<bool> evenDegree(n, false);
    vector<bool> oddDegree(n, false);
    vector<bool> eliminated(n, false);

    forn(i,n){
        ll p;
        cin >> p;

        if (p != 0){
            p -= 1;
            degreeOfTheVertex[i]++;
            degreeOfTheVertex[p]++;
            adjList[i].insert(p);
            adjList[p].insert(i);
        }
    }

    forn(i,n){
        int degree = degreeOfTheVertex[i];

        if (degree % 2 == 0){
            evenDegree[i] = true;
        } else {
            oddDegree[i] = true;
        }
    }

    forn(i,n){
        
    }

}