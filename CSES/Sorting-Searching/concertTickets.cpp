#include <bits/stdc++.h>

using namespace std;

int updateAvailable(vector<bool>& available, int j){
    int res = -1;

    while (j >=0 && !available[j]){
        if (available[j]){
            res = j;
            available[j] = false;
        }

        j--;
    }

    return res;
}

int binarySearch(vector<long long>& arr, vector<bool>& available, int start, int end, long long x){
    if (start >= end){
        if (available[end]){
            available[end] = false;
            return end;
        } else {
            return updateAvailable(available, end);
        }
    }

    int middle = (start + end)/2;

    if (arr[middle] == x){
        if (available[middle]){
            available[middle] = false;
            return middle;
        } else {
            return updateAvailable(available, middle);
        }
    } else if (x < arr[middle]){
        return binarySearch(arr, available, start, middle - 1, x);
    } else {
        return binarySearch(arr, available, middle, end, x);
    }
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<long long> tickets(n);
    vector<long long> customers(m);
    vector<bool> available(n, true);

    for (int i = 0; i < n; i++){
        long long k;
        cin >> k;
        tickets[i] = k;
    }

    for (int i = 0; i < m; i++){
        long long k;
        cin >> k;
        customers[i] = k;
    }

    sort(tickets.begin(), tickets.end());

    for (int i = 0; i < m; i++){
        int minimumPrice = binarySearch(tickets, available, 0, n-1, customers[i]);
        
        if (minimumPrice == -1){
            cout << -1 << "\n";
        } else {
            cout << tickets[minimumPrice] << "\n";
        }
    }
}
