#include <bits/stdc++.h>

using namespace std;

int pickingNumbers(vector<int> a) {
    sort(a.begin(), a.end());
    int res = 1;
    int n = a.size();
    
    for (int i = 1; i<n; i++){
        if(a[i] - a[i-1] <= 1 ){
            res += 1;
        } else {
            cout << res << endl;
            res = 1;
        }
    }
    
    return res;
}

int main(){
    vector<int> numbers = {4,6,5,3,3,1};

    cout << pickingNumbers(numbers) << endl;
}