#include <bits/stdc++.h>
using namespace std;

vector<long long> subarray(vector<long long> &arr, int start, int end){
    vector<long long> res;

    for (int i = start; i <= end; i++){
        res.push_back(arr[i]);
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long n, h;
    cin >> n >> h;

    vector<long long> heightBottles(n);
    for (long long &v : heightBottles) cin >> v;

    int k = 2;
    
    for (int i = 2; i < n; i++){
        vector<long long> bottles = subarray(heightBottles, 0, i);
        sort(bottles.begin(), bottles.end());

        int m = bottles.size();
        int totalHeight = 0;

        for (int j = m-1; j >= 0; j-=2){
            totalHeight += bottles[j];
        }

        if (totalHeight > h){
            break;
        } else {
            k = i+1;
        }
    }

    if (n == 1){
        cout << "1" << "\n";
    } else {
        cout << k << "\n";
    }
}
