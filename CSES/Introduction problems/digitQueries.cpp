#include <bits/stdc++.h>

using namespace std;

int potencia(int n){
    if (n < 10){
        return 0;
    } else {
        return 1 + potencia(n/10);
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;

    vector<long long> queries(q);
    long long maxQuery = INT_MIN;

    for (int i = 0; i < q; i++){
        long long k;
        cin >> k;
        maxQuery = max(maxQuery, k);
        queries[i] = k; 
    }

    vector<int> digitPostions();

    for (int i = 1; i < 10e8; i++){
        int potenciaI = potencia(i);
        int j = 0;

        while (j < potenciaI )
    }


}
