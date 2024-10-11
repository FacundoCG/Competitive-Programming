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

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()
#define pb push_back
#define RAYA cerr << "-----------------" << endl

#define DBG(x) cerr << #x << " = " << (x) << endl

# define forn(i,n) for (int i=0; i<(int)(n);i++)
# define forsn(i,s,n) for (int i=(s); i <(int)(n); i++)

template <typename T>
ostream & operator << (ostream &os, const vector<T> &v) {
    os << "[";
    forn(i, v.size()) {
        if (i > 0) os << ",";
        os << v[i];
    }
    return os << "]";
}

void borrarA(vector<string>& mapa, int a, int b){
        (mapa[a][b] = '.');
        (mapa[a][b+1] = '.');
        (mapa[a][b+2] = '.');
        (mapa[a+1][b] = '.');
        (mapa[a+2][b] = '.');
        (mapa[a+3][b] = '.');
        (mapa[a+4][b] = '.');
        (mapa[a+1][b+2] = '.');
        (mapa[a+2][b+2] = '.');
        (mapa[a+2][b+1] = '.');
        (mapa[a+3][b+2] = '.');
        (mapa[a+4][b+2] = '.');
}

void borrarP(vector<string>& mapa, int a, int b){
        (mapa[a][b] = '.');
        (mapa[a][b+1] = '.');
        (mapa[a][b+2] = '.');
        (mapa[a+1][b] = '.');
        (mapa[a+2][b] = '.');
        (mapa[a+3][b] = '.');
        (mapa[a+4][b] = '.');
        (mapa[a+1][b+2] = '.');
        (mapa[a+2][b+2] = '.');
        (mapa[a+2][b+1] = '.');
}

void borrarT(vector<string>& mapa, int a, int b){
        (mapa[a][b] = '.');
        (mapa[a][b+1] = '.');
        (mapa[a][b+2] = '.');
        (mapa[a+1][b+1] = '.');
        (mapa[a+2][b+1] = '.');
        (mapa[a+3][b+1] = '.');
        (mapa[a+4][b+1] = '.');
}

int esLetra(vector<string>& mapa, int a, int b){
    // A:
    if((mapa[a][b] == '#') && (a+4<mapa.size() && b+2<mapa[a].size()) &&
        (mapa[a][b+1] == '#') &&
        (mapa[a][b+2] == '#') &&
        (mapa[a+1][b] == '#') &&
        (mapa[a+2][b] == '#') &&
        (mapa[a+3][b] == '#') &&
        (mapa[a+4][b] == '#') &&
        (mapa[a+1][b+2] == '#') &&
        (mapa[a+2][b+2] == '#') &&
        (mapa[a+2][b+1] == '#') &&
        (mapa[a+3][b+2] == '#') &&
        (mapa[a+4][b+2] == '#')){
        return 2;
    // P:
    } else if((mapa[a][b] == '#') && (a+4<mapa.size() && b+2<mapa[a].size()) &&
        (mapa[a][b+1] == '#') &&
        (mapa[a][b+2] == '#') &&
        (mapa[a+1][b] == '#') &&
        (mapa[a+2][b] == '#') &&
        (mapa[a+3][b] == '#') &&
        (mapa[a+4][b] == '#') &&
        (mapa[a+1][b+2] == '#') &&
        (mapa[a+2][b+2] == '#') &&
        (mapa[a+2][b+1] == '#')){
        return 1;
        // T:
        }else if((mapa[a][b] == '#') && (a+4<mapa.size() && b+2<mapa[a].size()) &&
        (mapa[a][b+1] == '#') &&
        (mapa[a][b+2] == '#') &&
        (mapa[a+1][b+1] == '#') &&
        (mapa[a+2][b+1] == '#') &&
        (mapa[a+3][b+1] == '#') &&
        (mapa[a+4][b+1] == '#') &&
        (mapa[a+2][b+2] != '#')){
            return 3;
        }else{
            return 0;
        }
}


int main()
{
    int n,m,a=0,p=0,t=0;
    cin >> n >> m;
    vector<string> mapa(n);

    forn(i,n){
        cin >> mapa[i];
    }
    for(int i = n-5; i >=0; i--){
        for(int j=0; j<m; j++){
            if(mapa[i][j] == '#'){
                int letra = esLetra(mapa, i, j);
                if(letra == 1){
                    //DBG(i);
                    //DBG(j);
                    //DBG(letra);
                    p+=1;
                    borrarP(mapa, i, j);
                    //DBG(mapa);
                    //RAYA;
                }else if(letra == 2){
                    //DBG(i);
                    //DBG(j);
                    //DBG(letra);
                    a += 1;
                    borrarA(mapa, i, j);
                    //DBG(mapa);
                    //RAYA;
                }else if(letra == 3){
                    //DBG(i);
                    //DBG(j);
                    //DBG(letra);
                    t += 1;
                    borrarT(mapa, i, j);
                    //DBG(mapa);
                    //RAYA;
                }
            }
        }
    }
    cout << t << " " << a << " " << p << "\n";
}
