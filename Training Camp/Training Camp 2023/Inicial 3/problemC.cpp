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

bool canMakeName(vector<ll> &lettersAvailable, vector<ll> &name){
    bool res = true;

    for (int i = 0; i < 26; i++){
        if (name[i] > lettersAvailable[i]){
            res = false;
        }
    }

    return res;
}

ll binarySearch(vector<vector<ll>> &arr, vector<ll> &name){
    int a = -1; // extremo izquierdo del rango de búsqueda -1
    int b = arr.size(); // extremo derecho del rango de búsqueda +1
    while(b - a > 1) { // mientras que la distancia entre las fronteras sea >1 (es decir, mientras que no estén contiguas)
        int m = (a + b) / 2; // punto medio
        if(!canMakeName(arr[m], name)) {
            a = m; // dependiendo del caso 1 o 2, vamos a intercambiar si seteamos a o b, muy fácil de razonar!
        } else {
            b = m; // acá simplemente seteamos la otra frontera!
        }
    }

    return b;
}


// ############################################################### //

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, m;
    cin >> n;

    string s;
    cin >> s;

    cin >> m;
    
    vector<vector<ll>> prefixCharacters(n, vector<ll>(26, 0));

    int firstCharIndex = s[0] - 'a';
    prefixCharacters[0][firstCharIndex]++;

    forsn(i,1,n){
        int index = s[i] - 'a';
        vector<ll> lastElement = prefixCharacters[i-1];

        lastElement[index]++;
        prefixCharacters[i] = lastElement;
    }

    forn(i, m){
        string name;
        cin >> name;

        int k = name.size();        
        vector<ll> charactersName(26, 0);

        forn(j, k){
            int index = name[j] - 'a';
            charactersName[index]++;
        }

        ll res = binarySearch(prefixCharacters, charactersName)+ 1;
        cout << res << "\n";
    }
}