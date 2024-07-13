#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int a, b;
    cin >> a >> b;

    int winsPlayer1 = 0;
    int draws = 0;
    int winsPlayer2 = 0;

    for (int i = 1; i <= 6; i++) {
        if (abs(a-i) < abs(b-i)) {
            winsPlayer1++;
        } else if (abs(b-i) < abs(a-i)) {
            winsPlayer2++;
        } else {
            draws++;
        }
    }

    cout << winsPlayer1 << " " << draws << " " << winsPlayer2 << "\n";
}