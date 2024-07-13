#include <bits/stdc++.h>
using namespace std;

int leftBinarySearch(int start, int end, long long max, long long min, int level){
    if (start > end){
        return end;
    }
    
    int middle = (start+end)/2;
    long long distanceMiddle = pow(middle, 2) + pow(level, 2);
    long long distancePrev = pow(middle-1, 2) + pow(level, 2);

    if (distanceMiddle >= min && distanceMiddle <= max && middle-1 == 0){
        return middle;
    } else if (distanceMiddle >= min && distanceMiddle < max && distancePrev < min){
        return middle;
    } else if (distanceMiddle >= max || distancePrev >= min){
        return leftBinarySearch(start, middle-1, max, min, level);
    } else {
        return leftBinarySearch(middle+1, end, max, min, level);
    }
}

int rightBinarySearch(int start, int end, long long max, long long min, int level){
    if (start > end){
        return end;
    }
    
    int middle = (start+end)/2;
    long long distanceMiddle = pow(middle, 2) + pow(level, 2);
    long long distanceNext = pow(middle+1, 2) + pow(level, 2);

    if (distanceMiddle >= min && distanceMiddle < max && distanceNext >= max){
        return middle;
    } else if (distanceMiddle >= max){
        return rightBinarySearch(start, middle-1, max, min, level);
    } else {
        return rightBinarySearch(middle+1, end, max, min, level);
    }
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        long long r;
        cin >> r;

        long long minDistance = pow(r, 2);
        long long maxDistance = pow(r+1, 2);
        int totalPoints = 1;

        for (int j = 1; j <= r; j++) {
            int leftCorner = leftBinarySearch(1, r, maxDistance, minDistance, j);
            int rightCorner = rightBinarySearch(1, r, maxDistance, minDistance, j);
            long long distanceRight = pow(rightCorner, 2) + pow(j,2);
            long long distanceLeft = pow(leftCorner, 2) + pow(j,2);
            bool validCorners = distanceRight >= minDistance && distanceRight < maxDistance && distanceLeft >= minDistance && distanceLeft < maxDistance;
            
            if (validCorners){
                totalPoints += rightCorner - leftCorner + 1;
            }
        } 

        cout << totalPoints*4 << "\n";
    }
}