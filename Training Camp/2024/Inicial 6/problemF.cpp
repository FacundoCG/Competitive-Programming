#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
 
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ld EPSILON = 1e-10;
 
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.


bool simulate(string camino, ll n, ll d){
	ll pos = -1;
	
	while(true){
		bool yaSalto = false;
	
		for(ll i=1; (i<=d) && (!yaSalto); i++){
			
			if (pos+i >= n){  // Llego al final.
				return true;
			}
			
			if (camino[pos+i] == 'R'){  // Saltar a una casilla R más cercana.
				pos = pos + i;
				yaSalto = true;
			}
		}
		
		if (!yaSalto){  // No llego al final y no habí casilla R en el rango, no se puede llegar con distancia d.
			return false;
		}
	}
}


void solve(){
	
	string camino;
	
	cin >> camino;
	
	//for(ll i=0; i<10; i++){
	//	cout << "d: " << i << " " << simulate(camino, camino.size(), i) << "\n";
	//}
	
	
	// Calcular extremo izquierdo que cumple P(X)
	int l = -1;
    int r = camino.size()+1; 
    while(r - l > 1) { 
        int mid = (l + r) / 2;
        if(!simulate(camino, camino.size(), mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << r << "\n";
	// r es el primer elemento que cumple P(X)
	
}




int main()
{
	ll t;
	
	cin >> t;
	
	for(ll i=0; i<t; i++){
		solve();
	}
	
    return 0;
}
