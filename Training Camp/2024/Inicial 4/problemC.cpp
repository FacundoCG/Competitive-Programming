#include <bits/stdc++.h>
using namespace std;


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> pagesOfSolutions(n);

    for (int &v : pagesOfSolutions) cin >> v;

    int days = 0;
    int pagesRead = 0;
    int newDay = 0;

    while (pagesRead != n){
        int readUntil = pagesOfSolutions[newDay]-1;

        for (int i = newDay; i <= readUntil; i++){
            if (readUntil < pagesOfSolutions[i]-1){
                readUntil = pagesOfSolutions[i]-1;
            }
        }

        newDay = readUntil+1;
        pagesRead = readUntil+1;
        days++;
    }

    cout << days << "\n";
}
