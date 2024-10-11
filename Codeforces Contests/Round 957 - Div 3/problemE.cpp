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


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //

int calculateDigits(int n){
    if (n < 10){
        return 1;
    }

    return 1 + calculateDigits(n/10);
}

int prefijoNumeroConcatenado(int n, int i){
    // Suponiendo que n fue concatenado una cantidad X de veces yo quiero los digitos desde 0 a i (sin incluir)
    string res;

    if (n < 10){
        forsn(j,1,i+1){
            res += to_string(n);
        }
    } else {
        forsn(j,1,i+1){
            if (j%2 != 0){ // En las posiciones pares pongo el primer digito
                res += to_string(n/10);
            } else {
                res += to_string(n%10); // En las posiciones impares pongo el segundo digito
            }
        }
    }

    return stoi(res);
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;

    forn(_,t){
        int n;
        cin >> n;

        vector<pair<ll,ll>> goodPairs;
        ll digitsN = calculateDigits(n);

        forsn(a,1,10001){
            ll digitsString = (ll) digitsN*a;

            forsn(i,1,7){
                ll b = digitsString - i;
                ll numeroConcatenadoSinB = prefijoNumeroConcatenado(n,i);
                ll k = (ll) n*a - b;

                if (numeroConcatenadoSinB == k && b > 0){
                    goodPairs.pb({a,b});
                }
            }
        }

        cout << goodPairs.size() << "\n";

        forn(i, goodPairs.size()){
            cout << goodPairs[i].first << " " << goodPairs[i].second << "\n";
        }

    }
    
}