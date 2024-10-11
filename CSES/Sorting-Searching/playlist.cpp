#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const long long NEG_INF = LLONG_MIN;

ll maximumLongestSequenceSongsFromMiddle(vector<ll> &A){
    ll res = 0;
    int n = A.size();
    int middle = n/2;
    set<ll> uniqueSongs = {A[middle]};

    for (int j = middle-1; j >= 0; j--){ 
        ll currentSong = A[j];
        if (uniqueSongs.find(currentSong) == uniqueSongs.end()){
            uniqueSongs.insert(currentSong);
        } else {
            break;
        }
    }

    for (int j = middle+1; j < n; j++){
        ll currentSong = A[j];
        if (uniqueSongs.find(currentSong) == uniqueSongs.end()){
            uniqueSongs.insert(currentSong);
        } else {
            break;
        }
    }

    return uniqueSongs.size();
}

ll longestSequenceUniqueSongs(vector<ll> &A){
    ll res = 0;
    int n = A.size();

    if (n <= 1){
        return n;
    }

    int middle = n/2;
    vector<ll> left, right;

    for (int i = 0; i < middle; i++){ // If I instead put j = middle here and in the next j = middle + 1, my function doesn't finish.
        left.push_back(A[i]);
    }

    for (int i = middle; i < n; i++){
        right.push_back(A[i]);
    }

    ll middleSum = maximumLongestSequenceSongsFromMiddle(A); 
    ll leftSequence = longestSequenceUniqueSongs(left);
    ll rightSequence = longestSequenceUniqueSongs(right);
    res = max(middleSum, max(leftSequence, rightSequence));

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<ll> arr(n);

    for (int i = 0; i < n; i++) cin >> arr[i];

    ll res = longestSequenceUniqueSongs(arr);

    cout << res << "\n";
}
