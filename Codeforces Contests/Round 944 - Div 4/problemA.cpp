#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;


    for (int i = 0; i < t; i++){
        int x,y;
        cin >> x >> y;

        cout << min(x,y) << " " << max(x,y) << "\n";
    }
}