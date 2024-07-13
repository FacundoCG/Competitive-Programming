#include <bits/stdc++.h>
using namespace std;

typedef vector<tuple<long long, long long, long long>> triple;

vector<triple> merge(vector<triple> &arr1, vector<triple> &arr2){
    int n = arr1.size();
    int m = arr2.size();
    int t = n + m;
    vector<triple> res(t);

    int j = 0;
    int h = 0;

    for (int i = 0; i < t; i++){
        if (j < n && h < m){
            if (arr1[j] <= arr2[h]){
                res[i] = arr1[j];
                j++;
            } else {
                res[i] = arr2[h];
                h++;
            }
        } else if (j < n){
            res[i] = arr1[j];
            j++;
        } else {
            res[i] = arr2[h];
            h++;
        }
    }

    return res;
}

vector<triple> mergeSort(vector<triple> &arr){   
    int n = arr.size();

    if (n <= 1){
        return arr;
    }

    int mid = n / 2;

    vector<triple> leftHalf, rightHalf;

    for (int i = 0; i < mid; i++){
        leftHalf.push_back(arr[i]);
    }

    for (int i = mid; i < n; i++){
        rightHalf.push_back(arr[i]);
    }

    vector<triple> res1 = mergeSort(leftHalf);
    vector<triple> res2 = mergeSort(rightHalf);

    return merge(res1, res2);
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n;
        cin >> n;

        vector<long long> arr(n);
        vector<triple> triples;

        for (int j = 0; j < n; j++) {
            long long x;
            cin >> x;
            arr[j] = x;
        }

        int beautifulPairs = 0;

        for (int j = 1; j < n-1; j++){
            triple t = {arr[j-1], arr[j], arr[j+1]};
            triples.push_back(t);
        }
    }
}