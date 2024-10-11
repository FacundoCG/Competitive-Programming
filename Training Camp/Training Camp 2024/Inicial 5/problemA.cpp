#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        long long a, b, c, x, y;
        cin >> a >> b >> c >> x >> y;

        string res = "NO";

        if (x <= a){ // La comida de perros alcanza para todos
            if (c + b >= y){ // La suma de lo universal mas lo de los gatos basta
                res = "YES";
            }
        } else {
            if (a + c >= x){ // La suma de lo universal más lo de los perros basta
                int resto = a + c - x;
                if (resto + b >= y){
                    res = "YES";
                }
            }
        }

        cout << res << "\n";
    }
}
