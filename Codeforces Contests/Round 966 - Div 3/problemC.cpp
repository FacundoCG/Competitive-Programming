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

bool checkPositionsOfSameChars(map<char, vector<ll>> &positionsOfTheSameChars, vector<ll> &numbers){
    bool res = true;

    for(auto p : positionsOfTheSameChars){
        vector<ll> positionsOfAChar = p.second;

        if (positionsOfAChar.size() > 1){
            forn(k, positionsOfAChar.size()-1){
                ll index1 = positionsOfAChar[k];
                ll index2 = positionsOfAChar[k+1];

                if (numbers[index1] != numbers[index2]){
                    res = false;
                    break;
                }
            }
        }
    }

    return res;
}

bool checkPositionsOfSameNumbers(map<ll, vector<ll>> &positionsOfTheSameNumbers, string &s){
    bool res = true;

    for(auto p : positionsOfTheSameNumbers){
        vector<ll> positionsOfANumber = p.second;

        if (positionsOfANumber.size() > 1){
            forn(k, positionsOfANumber.size()-1){
                ll index1 = positionsOfANumber[k];
                ll index2 = positionsOfANumber[k+1];

                if (s[index1] != s[index2]){
                    res = false;
                    break;
                }
            }
        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(i,t){
        int n;
        cin >> n;

        vector<ll> numbers(n);
        map<ll, vector<ll>> positionsOfTheSameNumbers;
        forn(j,n){
            cin >> numbers[j];
            positionsOfTheSameNumbers[numbers[j]].pb(j);
        }

        int m;
        cin >> m;

        forn(j,m){
            string s;
            cin >> s;

            string res = "YES";
            map<char, vector<ll>> positionsOfTheSameChars;

            if (s.size() != n){
                res = "NO";
                cout << res << "\n";
                continue;
            }

            forn(k, s.size()){
                positionsOfTheSameChars[s[k]].pb(k);
            }

            bool flag1 = checkPositionsOfSameNumbers(positionsOfTheSameNumbers, s);
            bool flag2 = checkPositionsOfSameChars(positionsOfTheSameChars, numbers);

            if (!flag1 || !flag2){
                res = "NO";
            }

            cout << res << "\n";
        }
    }
}