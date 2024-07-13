#include <bits/stdc++.h>

using namespace std;

void increasingArrayMin(long long n) {
    vector<long long> array;
    long long firstNumber;
    long long movements = 0;

    cin >> firstNumber;
    array.push_back(firstNumber);

    for (int i = 1; i<n; i++) {
        long long number;
        cin >> number;
        
        if (number<array.front()){
            movements += array.front() - number;
        }else{
            array.pop_back();
            array.push_back(number);
        }
        
    }

    cout << movements << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;

    if (n == 1){
        cout << 0 << "\n";
    } else{
        increasingArrayMin(n);        
    }
}
