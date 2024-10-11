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

int h, w;
int borde_sup, borde_inf, borde_izq, borde_der;

void dfs(int i, int j, vector<string> &grid, vector<vector<bool>> &vis){
    borde_inf = max(i, borde_inf);
    borde_sup = min(i, borde_sup);

    borde_der = max(j, borde_der);
    borde_izq = min(j, borde_izq);

    vis[i][j] = true;
    if (i+1<h && grid[i+1][j] == '*' && !vis[i+1][j])   {dfs(i+1,j, grid, vis);}
    if (0<i   && grid[i-1][j] == '*' && !vis[i-1][j]) {dfs(i-1,j, grid, vis);}
    if (j+1<w && grid[i][j+1] == '*' && !vis[i][j+1]) {dfs(i,j+1, grid, vis);}
    if (0<j   && grid[i][j-1] == '*' && !vis[i][j-1]) {dfs(i,j-1, grid, vis);}
}


bool checkear(vector<string> &grid, int borde_sup, int borde_inf, int borde_der, int borde_izq){
    if (borde_der == borde_izq || borde_sup == borde_inf){
        return false;
    }

    if ((borde_der-borde_izq) % 2 != 0){
        return false;
    }

    int medio = ((borde_der-borde_izq)/2) + borde_izq;

    // Busco la altura del corazón.
    int altura_corazon = UNDEFINED;

    for(int i=borde_sup; i<=borde_inf; i++){
        if (grid[i][medio+1] == '*'){
            if (altura_corazon == UNDEFINED){
                altura_corazon = i;
            } else {  // Hay dos corazones.
                return false;
            }
        }
    }

    // No habia ningun corazon.
    if (altura_corazon == UNDEFINED){
        return false;
    }

    // Checkeo si esta desbalanceados los rayos.
    if ((altura_corazon - borde_sup != borde_der - medio) || (borde_der - medio != medio - borde_izq)){
        return false;
    }

    // Checkeo que la cruz este en '*'.
    // Miro la horizontal.
    for(int j=borde_izq; j<=borde_der; j++){
        if (grid[altura_corazon][j] != '*'){
            return false;
        }
        // Miro que los vecinos de arriba y abajo sean '.'
        if (j != medio){
            if (grid[altura_corazon+1][j] != '.' || grid[altura_corazon-1][j] != '.'){
                return false;
            }
        }
    }

    // Checkear la vértical de la cruz.
    for(int i=borde_sup; i<=borde_inf; i++){
        if (grid[i][medio] != '*'){
            return false;
        }
        // Miro que los vecinos de derecha y izquierda sean '.'
        if (i != altura_corazon){
            if (grid[i][medio+1] != '.' || grid[i][medio-1] != '.'){
                return false;
            }
        }
    }

    // Checkeo la punta de arriba.
    if (borde_inf+1 < h){  // Esta en rango.
        if (grid[borde_inf+1][medio] != '.'){
            return false;
        }
    }

    // Checkeo la punta de abajo.
    if (0 <= borde_sup-1){  // Esta en rango.
        if (grid[borde_sup-1][medio] != '.'){
            return false;
        }
    }

    // Checkeo la punta de izquierda.
    if (0 <= borde_izq-1){  // Esta en rango.
        if (grid[altura_corazon][borde_izq-1] != '.'){
            return false;
        }
    }

    // Checkeo la punta de derecha.
    if (borde_der+1 < w){  // Esta en rango.
        if (grid[altura_corazon][borde_der+1] != '.'){
            return false;
        }
    }

    if (borde_inf - altura_corazon <= medio-borde_izq){
        return false;
    }

    // Estaba todo joya.
    return true;
}


int main()
{
    cin >> h >> w;

    vector<string> grid(h);

    for(ll i=0; i<h; i++){
        cin >> grid[i];
    }

    vector<vector<bool>> vis(h, vector<bool>(w, false));

    int res = 0;

    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            if(grid[i][j] == '*' && !vis[i][j]){  // Si tiene una pieza de objeto y no fue visitado:
                borde_inf = -1; 
                borde_sup = 3000;
                borde_der = -1;
                borde_izq = 3000;
                dfs(i, j, grid, vis);
                
                if (checkear(grid, borde_sup, borde_inf, borde_der, borde_izq)){
                    /* cout << "Hago dfs en i: " << i << ", j: " << j << endl;
                    DBG(borde_inf);
                    DBG(borde_sup);
                    DBG(borde_der);
                    DBG(borde_izq); */
                    cout << "Sumo 1" << endl;
                    res++;
                }
            }
        }
    }

    cout << res << endl;

    return 0;
}