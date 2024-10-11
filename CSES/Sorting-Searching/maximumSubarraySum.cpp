#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const long long NEG_INF = LLONG_MIN;

ll maximumContiguosSumFromMiddle(vector<ll> &A){
    ll res = 0;
    int n = A.size();
    int middle = n/2;
    ll currentLeftSum = A[middle];
    ll currentRightSum = 0;
    ll maximumLeft = A[middle];
    ll maximumRight = 0;

    for (int j = middle-1; j >= 0; j--){ 
        currentLeftSum += (ll) A[j];
        maximumLeft = max(maximumLeft, currentLeftSum);
    }

    for (int j = middle+1; j < n; j++){
        currentRightSum += (ll) A[j];
        maximumRight = max(maximumRight, currentRightSum);
    }

    res = maximumLeft;

    if (maximumRight > 0){
        res += maximumRight;
    }

    return res;
}

ll maximumSubArraySum(vector<ll> &A){
    ll res = 0;
    int n = A.size();

    if (A.size() == 1){
        return A[0];
    } else if (A.size() == 0){
        return NEG_INF;
    }

    int middle = n/2;
    vector<ll> left, right;

    for (int i = 0; i < middle; i++){ // If I instead put j = middle here and in the next j = middle + 1, my function doesn't finish.
        left.push_back(A[i]);
    }

    for (int i = middle; i < n; i++){
        right.push_back(A[i]);
    }

    ll middleSum = maximumContiguosSumFromMiddle(A); 
    ll leftSum = maximumSubArraySum(left);
    ll rightSum = maximumSubArraySum(right);
    res = max(middleSum, max(leftSum, rightSum));

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<ll> arr(n);

    for (int i = 0; i < n; i++) cin >> arr[i];

    ll res = maximumSubArraySum(arr);

    cout << res << "\n";
}
