#include <bits/stdc++.h>
using namespace std;

int binary_search(vector<long long>& A, int i, int j, int k){
    if (i >= j){
        return j;
    }

    int middle = (i/2) + (j/2);

    if (A[middle] == k){
        return middle;
    } else if (k < A[middle]){
        return binary_search(A, i, middle, k);
    } else {
        return binary_search(A, middle + 1, j, k);
    }
}

int longest_increment_subsequence(vector<long long>& A){
    int n = A.size();
    vector<long long> ans;
    ans.push_back(A[0]);

    for (int i = 1; i < n; i++){
        if (A[i] > ans.back()){
            ans.push_back(A[i]);
        } else {
            int positionElementIth = binary_search(ans, 0, ans.size()-1, A[i]);
            ans[positionElementIth] = A[i];
        }
    }

    return ans.size();
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;

    vector<long long> A(n);
    for (long long &v : A) cin >> v;

    cout << longest_increment_subsequence(A) << "\n";
}