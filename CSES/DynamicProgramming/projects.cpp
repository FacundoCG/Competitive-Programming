#include <bits/stdc++.h>
using namespace std;

bool isGreater(tuple<long long, long long, long long>& a, tuple<long long, long long, long long>& b){
    bool res = true;

    if ()
}

vector<tuple<long long, long long, long long>> merge(vector<tuple<long long, long long, long long>>& A, vector<tuple<long long, long long, long long>>& B){
    int n = A.size();
    int m = B.size();
    int i = 0;
    int j = 0;
    int k = 0;

    vector<tuple<long long, long long, long long>> res(n+m);
    
    while (i < n || j < m){
        if (i < n && j < m){
            if (isGreater(A[i], B[j])){
                res[k] = B[j];
                k++;
                j++;
            } else {
                res[k] = A[i];
                k++;
                i++;
            }
        } else if (i < n){
            res[k] = A[i];
            k++;
            i++;
        } else {
            res[k] = B[j];
            k++;
            j++;
        }
    }

    return res;
}



vector<tuple<long long, long long, long long>> mergeSort(vector<tuple<long long, long long, long long>>& A, int i, int j){
    if (i == j){
        return A;
    }

    int middle = i/2 + j/2;

    vector<tuple<long long, long long, long long>> leftHalf = mergeSort(A, i, middle);
    vector<tuple<long long, long long, long long>> rightHalf = mergeSort(A, middle+1, j);

    return merge(leftHalf, rightHalf);
}




int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;


    vector<tuple<long long, long long, long long>> projects(n);

    for (int i = 0; i < n; i++) {
        long long s, e, r;
        cin >> s >> e >> r;
        projects[i] = {s, e, r};
    }

}