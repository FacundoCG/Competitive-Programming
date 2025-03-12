#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    vector<int> numbers(n);
    vector<int> res(n);
    int sum = 0;
    int negativeOdds = 0;
    int positiveOdds = 0;

    for (int i = 0; i < n; i++){
        int m;
        cin >> m;
        numbers[i] = m;

        if (m % 2 == 0){
            res[i] = m/2;
            sum += m/2;
        } 
    }

    for (int i = 0; i < n; i++){
        if (numbers[i] % 2 == 1 && numbers[i]){

        }
    }

    
    
}
