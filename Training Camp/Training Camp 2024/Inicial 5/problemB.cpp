#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    string cardOnTheTable;
    vector<string> cards;
    cin >> cardOnTheTable;
    char rank = cardOnTheTable[0];
    char suit = cardOnTheTable[1];
    string res = "NO";

    for (int i = 0; i < 5; i++){
        string card;
        cin >> card;
        if (card[0] == rank || card[1] == suit){
            res = "YES";
        }
    }

    cout << res << "\n";
}
