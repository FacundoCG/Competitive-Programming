#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;
/* 
Caso base: termino de recorrer el arreglo y devuelvo 1 porque vine de una secuencia de operaciones válidas.
Caso recursivo:
- Si la celda que estoy parado está desocupada, no haga nada y avanzo.
- Si la celda que estoy parado está ocupada tengo 3 opciones:
1. No hacer nada, es decir, moverme uno para atrás y listo.
2. Avanzar 2 y modificar el tablero. 
3. Retroceder 2 y modificar el tablero.

Tengo un problema con esta toma de decisiones: si tomo la opción 2 estando en la posición i, cuando esté parado en i+2 voy a tener la opción de tomar la opción 3. Esto me va a llevar de vuelta a la posición i con el mismo estado del tablero con el que empecé. 

Lo que se me ocurrió para evitar esto es tener una variable que me indique cuál fue mi última decisión tomada. Y si tomé 2 en la posición i, no debería poder tomar 3 en la posición i+2 para no entrar en ese loop. 

Voy a empezar con está variable en 1 y me va a permitir poder tomar cualquiera de las dos opciones.
 */


long long dp(string &s, int i, int op, vector<vector<long long>> &memo){
    cout << "Iteration: " << i << ", string: " << s << " and op: " << op << endl;
    if (i == -1){
        return 1;
    }

    if(memo[i][op] == -1){
        memo[i][op] = 0;
        int n = s.size();

        if (s[i] == '1'){ // Si la celda está ocupada, chequeo a ver si puedo modificar el estado
            if (i+2 < n && s[i+2] == '0' && s[i+1] == '1' && op != 2){ // Si cumplo las condiciones y no vengo de retroceder, entonces puedo avanzar.
                s[i] = '0';
                s[i+2] = '1';
                memo[i][op] += dp(s, i+2, 1, memo);
                s[i] = '1';
                s[i+2] = '0';
            }

            if (i-2 >= 0 && s[i-2] == '0' && s[i-1] == '1' && op != 1){ // Si cumplo las condiciones y no vengo de avanzar, entonces puedo retroceder.
                s[i-2] = '1';
                s[i] = '0';
                memo[i][op] += dp(s, i-2, 2, memo); 
                s[i] = '1';
                s[i-2] = '0';
            }
        } 

        memo[i][op] += dp(s, i-1, 0, memo);
        memo[i][op] %= MOD;
    }

    return memo[i][op];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        string s;
        cin >> n >> s;

        vector<vector<long long>> memo(n, vector<long long>(3, -1));

        cout << dp(s, n-1, 0, memo) << "\n";
    }
}
