#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<long long>& arr, int start, int end, long long value){
    if (start > end){
        return end;
    }

    int middle = (start + end)/2;

    if (arr[middle] == value){
        return middle;
    } else if (arr[middle] > value){
        return binarySearch(arr, start, middle-1, value);
    } else {
        return binarySearch(arr, middle+1, end, value);
    }
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        long long n, q, k;
        cin >> n >> k >> q;

        vector<long long> points(k+1);
        vector<long long> minutes(k+1);
        points[0] = 0;
        minutes[0] = 0;

        for (int j = 1; j <= k; j++){
            long long c;
            cin >> c;
            points[j] = c;
        }

        for (int j = 1; j <= k; j++){
            long long c;
            cin >> c;
            minutes[j] = c;
        }

        for (int j = 0; j < q; j++){
            long long d;
            cin >> d;

            int closestPointToD = binarySearch(points, 0, k, d);

            if (points[closestPointToD] == d){
                cout << minutes[closestPointToD] << " ";
            } else {
                long long timeToClosestPoint = minutes[closestPointToD];
                long long timeToNextPoint = minutes[closestPointToD+1];
                long long initialPoint = points[closestPointToD];
                long long endPoint = points[closestPointToD+1];
                long long requiredTime = timeToNextPoint - timeToClosestPoint;
                long long timeToD = requiredTime*(d-initialPoint)/(endPoint - initialPoint);
                cout << timeToD + timeToClosestPoint << " ";
            }
        }

        cout << "\n";
    }
}