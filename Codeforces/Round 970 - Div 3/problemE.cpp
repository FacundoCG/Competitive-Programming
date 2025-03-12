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

vector<vector<ll>> calculateEvenPositionsPrefix(string &s){
    int n = s.length();
    int c1 = s[0] - 'a';
    vector<vector<ll>> evenPositionsPrefix (n, vector<ll>(27));
    evenPositionsPrefix[0][c1] = 1;

    forsn(i,1,n){
        evenPositionsPrefix[i] = evenPositionsPrefix[i-1];
        
        if (i % 2 == 0){
            c1 = s[i] - 'a';
            evenPositionsPrefix[i][c1]++;
        }
    }

    return evenPositionsPrefix;
}

vector<vector<ll>> calculateOddPositionsPrefix(string &s){
    int n = s.length();
    int c1 = s[1] - 'a';
    vector<vector<ll>> oddPositionsPrefix (n, vector<ll>(27));
    oddPositionsPrefix[1][c1] = 1;

    forsn(i,2,n){
        oddPositionsPrefix[i] = oddPositionsPrefix[i-1];

        if (i % 2 == 1){
            c1 = s[i] - 'a';
            oddPositionsPrefix[i][c1]++;
        }
    }

    return oddPositionsPrefix;
}

ll calculateIndexMaxElement(vector<ll> &A){
    ll res = 0;
    
    forsn(i,1,A.size()){
        if (A[i] > A[res]){
            res = i;
        }
    }

    return res;
}

ll numberOfCharactersToModify(vector<ll> &A){
    ll indexOfMaxElement = calculateIndexMaxElement(A);
    ll res = 0;

    forn(i, A.size()){
        if (indexOfMaxElement != i){
            res += A[i]; 
        }
    } 

    return res;
}

vector<ll> sumVectors(vector<ll> &A, vector<ll> &B){
    // Asumo que: |A| = |B| o (|A| = 0 y |B| != 0)

    if (A.size() == 0){
        return B;
    } else if (B.size() == 0){
        return A;
    }

    vector<ll> res (A.size());

    forn(i,A.size()){
        res[i] = A[i] + B[i];
    }

    return res;
}

vector<ll> substractVectors(vector<ll> &A, vector<ll> &B){
    vector<ll> res(A.size());

    forn(i,A.size()){
        res[i] = A[i] - B[i];
    }

    return res;
}

vector<ll> calculateFirstEvenHalf(vector<vector<ll>> &evenPositionsPrefix, int i){
    if (i % 2 == 0){
        return evenPositionsPrefix[i-2];
    } else {
        return evenPositionsPrefix[i-1];
    }
}

vector<ll> calculateFirstOddHalf(vector<vector<ll>> &oddPositionsPrefix, int i){
    if (i % 2 == 0){
        return oddPositionsPrefix[i-1];
    } else if (i != 1) {
        return oddPositionsPrefix[i-2];
    } else {
        vector<ll> emptyVector;
        return emptyVector;
    }
}

vector<ll> calculateSecondEvenHalf (vector<vector<ll>> & oddRepetitionsPrefix, int i){
    int n = oddRepetitionsPrefix.size();
    vector<ll> secondEvenHalf;

    if ((i % 2 == 0 && i + 1 == n) || (i % 2 == 1 && i + 2 >= n)){
        return secondEvenHalf;
    } 

    secondEvenHalf = oddRepetitionsPrefix[n-1];

    if (i % 2 == 0){ // Tengo que sacarle lo de i-1
        secondEvenHalf = substractVectors(secondEvenHalf, oddRepetitionsPrefix[i-1]);
    } else{ // Tengo que sacarle lo de i
        secondEvenHalf = substractVectors(secondEvenHalf, oddRepetitionsPrefix[i]);
    }

    return secondEvenHalf;
}

vector<ll> calculateSecondOddHalf (vector<vector<ll>> & evenRepetitionsPrefix, int i){
    int n = evenRepetitionsPrefix.size();
    vector<ll> secondOddHalf;

    if ((i % 2 == 0 && i + 2 >= n) || (i % 2 == 1 && i + 1 == n)){
        return secondOddHalf;
    } 

    secondOddHalf = evenRepetitionsPrefix[n-1];

    if (i % 2 == 0){ // Tengo que sacarle lo de i
        secondOddHalf = substractVectors(secondOddHalf, evenRepetitionsPrefix[i]);
    } else{ // Tengo que sacarle lo de i-1
        secondOddHalf = substractVectors(secondOddHalf, evenRepetitionsPrefix[i-1]);
    }

    return secondOddHalf;
}

ll secondStrategy(vector<ll> &evenPositions, vector<ll> &oddPositions){
    ll res = numberOfCharactersToModify(evenPositions) + numberOfCharactersToModify(oddPositions);
    return res;
}

ll firstStrategy(string &s, vector<vector<ll>> &evenPositionsPrefix, vector<vector<ll>> &oddPositionsPrefix){
    int n = s.size();
    int c1 = s[0] - 'a';
    vector<ll> copyEvenPositionsPrefix = evenPositionsPrefix[n-1];
    copyEvenPositionsPrefix[c1]--;
    
    ll res = secondStrategy(copyEvenPositionsPrefix, oddPositionsPrefix[n-1]);

    forsn(i,1,n){
        // Elimino al elemento en la posición i-ésima
        // Todo lo que está antes de i sigue estando en posicion par e impar
        vector<ll> firstEvenHalf = calculateFirstEvenHalf(evenPositionsPrefix, i);
        vector<ll> firstOddHalf = calculateFirstOddHalf(oddPositionsPrefix, i);
        // Todo lo que está después de i y era par ahora se vuelve impar
        // Todo lo que está después de i y era impar ahora se vuelve par
        vector<ll> secondEvenHalf = calculateSecondEvenHalf(oddPositionsPrefix, i);
        vector<ll> secondOddHalf = calculateSecondOddHalf(evenPositionsPrefix, i);

        vector<ll> newEvenPositions = sumVectors(firstEvenHalf, secondEvenHalf);
        vector<ll> newOddPositions = sumVectors(firstOddHalf, secondOddHalf);

        res = min(res, secondStrategy(newEvenPositions, newOddPositions));
    }

    res++;

    return res;
}

ll solve(string &s){
    ll res = 0;
    int n = s.size();
    vector<vector<ll>> evenPositionsPrefix = calculateEvenPositionsPrefix(s);
    vector<vector<ll>> oddPositionsPrefix = calculateOddPositionsPrefix(s);

    if (s.size() % 2 == 0){
        res = secondStrategy(evenPositionsPrefix[n-1], oddPositionsPrefix[n-1]); // I can't eliminate a character
    } else {
        res = firstStrategy(s, evenPositionsPrefix, oddPositionsPrefix); // I must eliminate a character
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

        string s;
        cin >> s;

        if (n == 1){
            cout << 1 << "\n";
            continue;
        }

        ll res = solve(s);

        cout << res << "\n";
    }
};