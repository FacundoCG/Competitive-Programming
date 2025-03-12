#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n;
        long long k;
        cin >> n >> k;

        vector<long long> ships(n);

        for (int j = 0; j < n; j++){
            long long x;
            cin >> x;
            ships[j] = x;
        }
        
        bool attackFirstShip = true;
        int firstShip = 0;
        int lastShip = n-1;
        int shipsDestroyed = 0;

        while ((firstShip < lastShip) && k > 0){
            if (attackFirstShip){
                if (ships[firstShip] <= ships[lastShip] && k >= (2*ships[firstShip] - 1)){
                    ships[lastShip] -= (ships[firstShip] - 1);
                    k -= (2*ships[firstShip] - 1);
                    ships[firstShip] = 0;
                    firstShip++;
                    attackFirstShip = false;
                } else if (ships[firstShip] <= ships[lastShip] && k < (2*ships[firstShip] - 1)) {
                    break;
                } else {
                    ships[firstShip]--;
                    k--;
                    attackFirstShip = false;
                }
            } else {
                if (ships[lastShip] <= ships[firstShip] && k >= (2*ships[lastShip] - 1)){
                    ships[firstShip] -= (ships[lastShip] - 1);
                    k -= (2*ships[lastShip] - 1);
                    ships[lastShip] = 0;
                    lastShip--;
                    attackFirstShip = true;
                } else if (ships[lastShip] <= ships[firstShip] && k < (2*ships[lastShip] - 1)) {
                    break;
                } else {
                    ships[lastShip]--;
                    k--;
                    attackFirstShip = true;
                }
            }
        }

        if (firstShip == lastShip){
            if (ships[firstShip] <= k){
                shipsDestroyed = n;
            } else {
                shipsDestroyed = n-1;
            }
        } else {
            if (ships[firstShip] == 0){
                shipsDestroyed += firstShip+1;
            } else {
                shipsDestroyed += firstShip;
            }
            
            if (ships[lastShip] == 0){
                shipsDestroyed += (n-lastShip);
            } else {
                shipsDestroyed += (n - (lastShip + 1));
            }
        }

        cout << shipsDestroyed << "\n";
    }
}