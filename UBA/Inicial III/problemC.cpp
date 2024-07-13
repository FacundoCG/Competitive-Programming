#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n, b, p;
    cin >> n >> b >> p;

    int bottlesNeeded = (n-1)*(2*b+1);
    int towelsNeeded = n*p;

    cout << bottlesNeeded << " " << towelsNeeded << "\n";
}