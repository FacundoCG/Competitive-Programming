#include <bits/stdc++.h>
using namespace std;

int main() {
    /* ios :: sync_with_stdio(0);
    cin.tie(0); */

    int n, m;
    cin >> n >> m;

    vector<vector<int>> subjects(m+1);
    map<int, int> currentSizeSubject;
    map<int, long long> sumSubject;
    long long res = 0;
    int maxSize = 0;

    for (int i = 0; i < n; i++){
        int s, r;
        cin >> s >> r;
        subjects[s].push_back(r);

        if(sumSubject.find(s) == sumSubject.end()){
            sumSubject[s] = r;
        } else {
            sumSubject[s] += r;
        }

        if(currentSizeSubject.find(s) == currentSizeSubject.end()){
            currentSizeSubject[s] = 1;
        } else {
            currentSizeSubject[s]++;
        }
    }

    for (int i = 1; i < m+1; i++){
        int m = subjects[i].size();
        maxSize = max(maxSize, m);
        sort(subjects[i].begin(), subjects[i].end());
    }

    vector<long long> sizeSubjects(n+1);
    bool flag = true;

    for (int i = maxSize; i >= 1; i--){
        //cout << "Size is: " << i << endl;
        for (int j = 1; j < m+1; j++){
            if (currentSizeSubject[j] >= i){
                /* cout << "Subject: " << j << endl;
                cout << "Sum subject: " << sumSubject[j] << endl; */
                int basura = currentSizeSubject[j] - i;
                if (basura-1 >= 0){
                    sumSubject[j] -= subjects[j][basura-1];
                }
                //cout << "Sum subject: " << sumSubject[j] << endl;
                if (sumSubject[j] > 0){
                    sizeSubjects[i] += sumSubject[j];
                }
            }
        }
    } 

    for (int i = 1; i < n+1; i++){
        res = max(res, sizeSubjects[i]);
    }

    cout << res << "\n";
}
