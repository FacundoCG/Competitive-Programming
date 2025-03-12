#include <bits/stdc++.h>
using namespace std;


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int a,b,c,x,y,z;
    cin >> a >> b >> c >> x >> y >> z;

    string res = "Yes";
    int extra;

    if (a < x && b < y && c < z){ // 3 Desaprobados
        res = "No";
    } else if ((a < x && b < y && c >= z) || (a < x && c < z && b >= y) || (b < y && c < z && a >= x)){ // 2 Desaprobados
        if (a < x && b < y && c >= z){
            extra = (c-z)/2;

            if (a + b + extra < x + y){
            res = "No";
            }
        } else if (a < x && c < z && b >= y){
            extra = (b-y)/2;

            if (a + c + extra < x + z){
                res = "No";
            }
        } else {
            extra = (a-x)/2;

            if (b + c + extra < y + z){
                res = "No";
            }
        }
    } else if (a < x || b < y || c < z){ // 1 Desaprobado
        if (a < x){
            extra = (b-y)/2 + (c-z)/2;

            if (a + extra < x){
                res = "No";
            }
        } else if (b < y){
            extra = (a-x)/2 + (c-z)/2;

            if (b + extra < y){
                res = "No";
            }
        } else {
            extra = (b-y)/2 + (a-x)/2;

            if (c + extra < z){
                res = "No";
            }
        }
    }

    cout << res << "\n";
}
