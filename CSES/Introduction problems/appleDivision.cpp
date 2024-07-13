#include <bits/stdc++.h>

using namespace std;

void appleDivision(int n) {
    vector<int> apples;
    int suma1 = 0;
    int suma2 = 0;

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;

        apples.push_back(m);
    }

    sort(apples.begin(), apples.end());

    for (int i = 0; i < n; i++) {
        int k = apples.back();
        apples.pop_back();

        if (suma1>suma2){
            suma2 += k;
        } else {
            suma1 += k;
        }
    }

    int res = abs(suma1-suma2);

    cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    appleDivision(n);
}
