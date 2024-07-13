#include <bits/stdc++.h>
using namespace std;
 
long long removalGame(vector<long long>& A){
    int n = A.size();
    vector<vector<long long>> memo(n, vector<long long>(n, 0));
    memo[0][0] = A[0];

    
}



tuple<int, int> maxTupleV1(tuple<int, int> a, tuple<int, int> b){
    if (get<0>(a) > get<0>(b)){
        return a;
    } else {
        return b;
    }

    if (get<1>(a) > get<1>(b)){
        return b;
    } else if (get<1>(a) < get<1>(b)){
        return a;
    }
}

tuple<int, int> maxTupleV2(tuple<int, int> a, tuple<int, int> b){
    if (get<1>(a) > get<1>(b)){
        return a;
    } else if (get<1>(a) < get<1>(b)){
        return b;
    }

    if (get<0>(a) > get<0>(b)){
        return b;
    } else {
        return a;
    }
}


tuple<int, int> sumTuple(tuple<int, int> a, tuple<int,int> b){
    int c1 = get<0>(a) + get<0>(b);
    int c2 = get<1>(a) + get<1>(b);
 
    return {c1, c2};
}
 
tuple<long long, long long> optimalResults(vector<long long>& A, vector<vector<tuple<long long,long long>>>& memo, int i, int j, int p){
    if (i == j && p == 1){
        return {A[i], 0};
    }
 
    if (i == j && p == 2){
        return {0, A[i]};
    }
 
    if (get<0> (memo[i][j]) == -1){
        if (p == 1){
            memo[i][j] = maxTupleV1(sumTuple({A[i],0}, optimalResults(A, memo, i+1, j, p+1)), sumTuple({A[j],0}, optimalResults(A, memo, i, j-1, p+1)));
        } 
 
        if (p == 2){
            memo[i][j] = maxTupleV2(sumTuple({0, A[i]}, optimalResults(A, memo, i+1, j, p-1)), sumTuple({0, A[j]}, optimalResults(A, memo, i, j-1, p-1)));
        }
    }   
 
    return memo[i][j];
}
 
 
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;
 
    vector<long long> A(n);
    vector<vector<tuple<long long,long long>>> memo(n, vector<tuple<long long,long long>>(n, {-1,-1}));
 
    for (int i = 0; i < n; i++){
        long long k;
        cin >> k;
        A[i] = k;
    }
 
    cout << get<0>(optimalResults(A, memo, 0, n-1, 1)) << "\n";
}
