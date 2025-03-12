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

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_,t){
        int n, k;
        cin >> n >> k;

        set<ll> cards;
        map<ll, ll> repetitionsOfCards;
        ll res = 0;

        forn(_,n){
            ll card;
            cin >> card;
            cards.insert(card);
            repetitionsOfCards[card]++;
        }

        vector<ll> vectorOfCards (cards.begin(), cards.end());
        vector<ll> prefixRepetitionsOfCards(vectorOfCards.size());
        vector<int> prefixConsecutiveCards(vectorOfCards.size());

        prefixRepetitionsOfCards[0] = repetitionsOfCards[vectorOfCards[0]];
        prefixConsecutiveCards[vectorOfCards.size()-1] = 1;
        
        forsn(i, 1, vectorOfCards.size()){
            prefixRepetitionsOfCards[i] = prefixRepetitionsOfCards[i-1] + repetitionsOfCards[vectorOfCards[i]];
        }

        dforsn(i, 0, vectorOfCards.size()-1){   
            if (vectorOfCards[i] + 1 == vectorOfCards[i+1]){
                prefixConsecutiveCards[i] = prefixConsecutiveCards[i+1] + 1;
            } else {
                prefixConsecutiveCards[i] = 1;
            }
        }


        dforn(i, vectorOfCards.size()){
            int j = min(prefixConsecutiveCards[i],k)-1;
            int until = min(i+j, (int) vectorOfCards.size()-1);
            ll newRes = 0;

            if (i != 0){
                newRes = prefixRepetitionsOfCards[until] - prefixRepetitionsOfCards[i-1];
            } else {
                newRes = prefixRepetitionsOfCards[until];
            }

            res = max(res, newRes);
        }

        cout << res << "\n";
    }
}