#include <bits/stdc++.h>

using namespace std;

void sumMultiplo4(int k, int m, int n, int a){
    for (int i=k; i<m+1; i++){
        if (i != m){
            cout << i+a << " " << (n+1) - i << " ";
        } else{
            cout << i+a << " " << (n+1) - i << "\n";
        }
    }
}

void sumSets(int n){
    if (n%4 == 1 || n%4 == 2){
        cout << "NO" << "\n";
    }else if (n%4 == 0){
        cout << "YES" << "\n";
        cout << n/2 << "\n";
        sumMultiplo4(1, n/4, n, 0);
        cout << n/2 << "\n";
        sumMultiplo4(n/4 + 1, n/2, n, 0);
    } else{
        cout << "YES" << "\n";

        cout << (n+1)/2 << "\n";
        cout << 1 << " " << 2 << " ";
        sumMultiplo4(1, (n-3)/4, n, 3);
        cout << (n-1)/2 << "\n";
        cout << "3" << " ";
        sumMultiplo4((n-3)/4 + 1, (n-3)/2, n, 3);
    }
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    sumSets(n);
}

