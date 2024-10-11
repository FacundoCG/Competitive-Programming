#include <bits/stdc++.h>

using namespace std;

vector<int> merge(vector<int> &arr1, vector<int> &arr2)
{
    int n = arr1.size();
    int m = arr2.size();
    int t = n + m;
    vector<int> res(t);

    int j = 0;
    int h = 0;

    for (int i = 0; i < t; i++)
    {
        if (j < n && h < m)
        {
            if (arr1[j] <= arr2[h])
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

vector<int> mergeSort(vector<int> &arr)
{   
    // Worst and best case: O(n * log n)
    // The algorithm is stable but not in place

    int n = arr.size();

    if (n <= 1)
    {
        return arr;
    }

    int mid = n / 2;

    vector<int> leftHalf, rightHalf;

    for (int i = 0; i < mid; i++)
    {
        leftHalf.push_back(arr[i]);
    }

    for (int i = mid; i < n; i++)
    {
        rightHalf.push_back(arr[i]);
    }

    vector<int> res1 = mergeSort(leftHalf);
    vector<int> res2 = mergeSort(rightHalf);

    return merge(res1, res2);
}

int main()
{
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        arr[i] = k;
    }

    vector<int> sortedArray = mergeSort(arr);

    cout << "The array sorted by the algorithm:" << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << sortedArray[i] << " ";
    }

    cout << "\n";

    return 0;
}