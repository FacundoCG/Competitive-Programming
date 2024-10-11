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

#include <bits/stdc++.h>
using namespace std;

ll binarySearch(vector<ll> &arr, int start, int end, ll alfajores){
    int l = start - 1; // extremo izquierdo del rango de búsqueda -1
    int r = end + 1; // extremo derecho del rango de búsqueda +1
        
    while(r - l > 1) { // mientras que la distancia entre las fronteras sea >1 (es decir, mientras que no estén contiguas)
        int mid = (l + r) / 2;
        if(!(arr[mid] <= alfajores)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return r;
}

int main()
{
    ios ::sync_with_stdio(0);
    cin.tie(0);
 
    int n, m;
 
    cin >> n >> m;
 
    vector<int> alfajores_por_viaje(n);
 
    for(int i=0; i<n; i++){
        cin >> alfajores_por_viaje[i];
    }
 
    vector<ll> empleados(m);
 
    for(int i=0; i<m; i++){
        cin >> empleados[i];
    }
 
    vector<ll> prefijoMinimos(m);
    prefijoMinimos[0] = empleados[0]; 
   
    forsn(i,1,m){
        prefijoMinimos[i] = min(empleados[i], prefijoMinimos[i-1]);
    }
 
    // Resuelvo:
    for(int i_v=0; i_v<n; i_v++){
        //cout << "Iteración i: " << i_v << endl;
        // Resuelvo un viaje.
        ll alfajores = alfajores_por_viaje[i_v];
        int toStart = binarySearch(prefijoMinimos, 0, m-1, alfajores);
        //cout << "Empiezo con alfajores:" << alfajores << endl;

        while (toStart >= 0 && toStart < m && prefijoMinimos[toStart] <= alfajores){
            //cout << "La posición correcta para ir es: " << toStart << endl;
            alfajores %= prefijoMinimos[toStart];
            toStart = binarySearch(prefijoMinimos, toStart+1, m-1, alfajores);
        }
 
        // Output, lo que le sobro en ese viaje:
        cout << alfajores << " ";
    }
 
    return 0;
}