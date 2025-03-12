#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        long long n;
        cin >> n;

        vector<int> ans1(32, 0);
        vector<int> ans2(32, 0);
        
        int j = n;
        int k = n;

        for (int i = 31; i >= 0; i-=2){
            if (j == 0){
                break;
            } else if (j > 0){
                j -= pow(2, i);
                ans1[i] = 1;
            } else {
                j += pow(2, i);
                ans1[i] = -1;
            }
        }
    }

    
}