#include <bits/stdc++.h>

using namespace std;

void permutation(long long n){
    
    for(int i=2; i<n+1; i+=2){
        cout<<i<<" ";
    }

    for(int i=1; i<n+1; i+=2){
        cout<<i<<" ";
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;

    if (n==3 or n==2){
        cout << "NO SOLUTION" << "\n";
    } else{
        permutation(n);
    }
}
