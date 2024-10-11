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

void swap(vector<ll> &arr, int i, int j){
    ll oldValue = arr[i];
    arr[i] = arr[j];
    arr[j] = oldValue;
}

bool cumploProp(vector<ll> &arr, ll x){
    int n = arr.size();
    bool res = true;

    forn(i,n-1){
        ll sumamos = (ll) arr[i] + arr[i+1];
        if (sumamos == x){
            res = false;
            break;
        }
    }

    return res;
}

// Le paso un array sin repetidos y me aseguro de ordenarlo de tal forma que no sume X
void modificarArrayParaQueNoSumeX(vector<ll> &A, ll x){
    int m = A.size();

    forn(i,m-1){
        ll sumamos = (ll) A[i] + A[i+1];

        if (sumamos == x){
            if (i + 2 < m){
                swap(A, i+1, i+2);
            }
        }
    }
}

vector<ll> arrayQueNoSumaX(vector<ll> &A, ll x){
    vector<ll> res;
    modificarArrayParaQueNoSumeX(A, x);

    // Chequeo si el último y anteultimo elemento no suman x. Ese es el unico caso que la función anterior no solucionó
    int m = A.size();

    if (m >= 2){
        ll sumamos = (ll) A[m-1] + A[m-2];
        if (sumamos == x){
            res.pb(A[m-1]);
            m--;
        }
    }

    forn(i,m){
        res.pb(A[i]);
    }
    
    return res;
}

vector<ll> intercalarRepetidos1(vector<ll> &A, ll repeticiones, ll elem){
    vector<ll> res;
    int j = 0;
    
    while (j < A.size() && repeticiones > 0){
        if (A[j] != elem){
            res.pb(elem);
            res.pb(A[j]);
            j++;
            repeticiones--;
        } else {
            res.pb(A[j]);

            if (j+1 < A.size()){
                res.pb(A[j+1]);
            }

            j += 2;
        }
    }

    // Si entro a este while es porque me faltó pushear elementos del array original
    while (j < A.size()) {
        res.pb(A[j]);
        j++;
    }

    // Si entro a este while es porque me faltó pushear repeticiones
    while(repeticiones > 0){
        res.pb(elem);
        repeticiones--;
    }

    return res;
}

// Extiendo el array con repetidos (siempre y cuando no sumen x dos repetidos juntos)
vector<ll> extenderArrayConRepetidos(vector<ll> &A, map<ll, ll> &repeticiones, ll mitadDeX){
    vector<ll> res;

    forn(i, A.size()){
        res.pb(A[i]);

        while(repeticiones[A[i]] > 0 && A[i] != mitadDeX){
            res.pb(A[i]);
            repeticiones[A[i]]--;
        }
    }

    return res;
}

void imprimirVector(vector<ll> &A){
    forn(i, A.size()){
        cout << A[i] << " ";
    }

    cout << "\n";
}

int main()
{
    int n;
    ll x;
    cin >> n >> x;
    map<ll,ll> repeticiones;
    vector<ll> elementosUnicos;
	
    forn(i,n){
        ll value;
        cin >> value;

        if (!esta(value, repeticiones)){
            repeticiones[value] = 1;
        } else {
            repeticiones[value]++;
        }
    }

    for (auto p : repeticiones){
    	elementosUnicos.pb(p.first);
        repeticiones[p.first]--;
    }

    ll mitadDeX = -1;
    if (x % 2 == 0){
        mitadDeX = x/2;
    }

    vector<ll> noSumaX = arrayQueNoSumaX(elementosUnicos, x); // Me encargo de ordenar el array sin repetidos para que no suceda que sume X
    vector<ll> noSumaXConRepetidos = extenderArrayConRepetidos(noSumaX, repeticiones, mitadDeX); // Extiendo al array sin repetidos que no suma X con las repeticiones que le faltaba (exceptuando la de la mitad de X)    
    
    
    vector<ll> intercalando1 = intercalarRepetidos1(noSumaXConRepetidos, repeticiones[mitadDeX], mitadDeX);
    bool cumplePropiedad1 = cumploProp(intercalando1, x);
    
    if (cumplePropiedad1){
        imprimirVector(intercalando1);
    } else {
        cout << "*" << "\n";
    }
}

