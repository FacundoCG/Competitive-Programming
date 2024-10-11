#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        int prod = 1;
        int zeros = 0;
        int min = 10;
        bool flag = true;
        vector<int> a (n); 

        for (int j = 0; j < n; j++) {
            int m;
            cin >> m;

            if (m == 0){
                zeros++;
            }

            if (min > m){
                min = m;
            }

            a[j] = m;
        }

        if (zeros > 1){
            prod = 0;
        } else if (zeros == 1){
            for (int j = 0; j < n; j++) {
                if (a[j] == 0){
                    prod *= (a[j] + 1);
                } else {
                    prod *= a[j];
                }
            }
        } else {
            for (int j = 0; j < n; j++) {
                if (a[j] == min && flag){
                    prod *= (a[j] + 1);
                    flag = false;
                } else {
                    prod *= a[j];
                }
            }
        }

        cout << prod << endl;
    }
}
