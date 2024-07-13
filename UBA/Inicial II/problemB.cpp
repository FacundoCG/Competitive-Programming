#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

        for (int j = 0; j < n; j++){
            if (j - 1 >= 0){
                cout << "that ";
            }

            if (j % 2 == 0){
                cout << "I hate ";
            } else {
                cout << "I love ";
            }
        }

        cout << "it" << "\n";
}