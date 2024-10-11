#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> distinctBadges (n+1, 0);

    for (int j = 0; j < n; j++){
        int k;
        cin >> k;
        distinctBadges[k]++;
    }

    int cost = 0;

    for (int i = 0; i < n; i++){
        if (distinctBadges[i] > 1){
            cost += (distinctBadges[i] - 1);
            distinctBadges[i+1] += distinctBadges[i] - 1;
        }
    }

    if (distinctBadges[n] > 1){
        int k = ((distinctBadges[n] - 1) * distinctBadges[n])/2;
        cost += k;
    }

    cout << cost << "\n";
}
