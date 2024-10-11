#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll,ll,ll> project;
const long long UNDEFINED = -1;

bool greaterProject(project A, project B){
    ll endingDayA = get<1>(A);
    ll endingDayB = get<1>(B);

    if (endingDayA > endingDayB){
        return true;
    } else if (endingDayA < endingDayB){
        return false;
    }

    ll startingDayA = get<0>(A);
    ll startingDayB = get<0>(B);

    if (startingDayA > startingDayB){
        return true;
    }

    return false;
}

vector<project> merge(vector<project> &arr1, vector<project> &arr2)
{
    int n = arr1.size();
    int m = arr2.size();
    int t = n + m;
    vector<project> res(t);

    int j = 0;
    int h = 0;

    for (int i = 0; i < t; i++)
    {
        if (j < n && h < m)
        {
            if (greaterProject(arr2[h], arr1[j]))
            {
                res[i] = arr1[j];
                j++;
            }
            else
            {
                res[i] = arr2[h];
                h++;
            }
        }

        else if (j < n)
        {
            res[i] = arr1[j];
            j++;
        }
        else
        {
            res[i] = arr2[h];
            h++;
        }
    }

    return res;
}

vector<project> mergeSort(vector<project> &arr)
{   
    // Worst and best case: O(n * log n)
    // The algorithm is stable but not in place

    int n = arr.size();

    if (n <= 1)
    {
        return arr;
    }

    int mid = n / 2;

    vector<project> leftHalf, rightHalf;

    for (int i = 0; i < mid; i++)
    {
        leftHalf.push_back(arr[i]);
    }

    for (int i = mid; i < n; i++)
    {
        rightHalf.push_back(arr[i]);
    }

    vector<project> res1 = mergeSort(leftHalf);
    vector<project> res2 = mergeSort(rightHalf);

    return merge(res1, res2);
}

int findPreviousProject(vector<project> &A, int i){
    int left = 0;
    int right = i-1;
    int startingDate = get<0>(A[i]);
    int n = A.size();

    while (left <= right){
        int middle = left/2 + right/2;
        int endingDate = get<1>(A[middle]);

        if (endingDate < startingDate){
            if (middle == right || (middle+1 < n && get<1>(A[middle+1]) >= startingDate)){
                return middle;
            }
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1; // If there aren't any valid project
}

ll maximumRewardTD(vector<project> &A, vector<ll> &memo, int i){
    if (i == -1){ // Base case: I don't have any project
        return 0;
    }

    if (memo[i] == UNDEFINED){ // Recursive case
        ll ignoreProject = maximumRewardTD(A, memo, i-1); // I don't take the project
        ll rewardOfProject = get<2>(A[i]);
        ll j = findPreviousProject(A, i);
        ll takeProject = (ll) rewardOfProject + maximumRewardTD(A, memo, j); // I take the project
        memo[i] = max(ignoreProject, takeProject);
    }

    return memo[i];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;

    vector<project> projects(n);

    for (int i = 0; i < n; i++) {
        ll s, e, r;
        cin >> s >> e >> r;
        projects[i] = {s, e, r};
    }

    vector<ll> memo(n, UNDEFINED);

    vector<project> sortedProjects = mergeSort(projects);
    ll res = maximumRewardTD(sortedProjects, memo, n-1);

    cout << res << "\n";
}