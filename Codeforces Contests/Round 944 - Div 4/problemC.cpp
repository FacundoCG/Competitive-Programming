#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        int startAlice = min(a, b);
        int endAlice = max(a, b);
        int startBob = min(c, d);
        int endBob = max(c, d);

        bool firstRegion = (startAlice <= startBob && startBob <= endAlice) && (startAlice <= endBob && endBob <= endAlice);
        bool secondRegion = (startBob <= startAlice || startBob >= endAlice) && (endBob <= startAlice || endBob >= endAlice);
        if (firstRegion || secondRegion){
            cout << "NO" << "\n";
        } else {
            cout << "YES" << "\n";
        }
    }
}