#include <bits/stdc++.h>

using namespace std;

void countingSort(vector<int> &arr, int n)
{
    // We know that: n <= arr.length, the array doesn't have negative elements and every element in the array is <= n
    // Best and worst case: O(n)
    // The algorithm is in place

    int m = arr.size();

    vector<int> repetitions(n + 1, 0), prefixSum(n + 1);

    for (int i = 0; i < m; i++)
    {
        int index = arr[i];
        repetitions[index]++;
    }

    for (int i = 0; i < n + 1; i++)
    {
        if (i == 0)
        {
            prefixSum[i] = repetitions[i];
        }
        else
        {
            prefixSum[i] = repetitions[i - 1] + repetitions[i];
        }
    }

    int j = 0;

    for (int i = 0; i < n + 1; i++)
    {
        int iterations = repetitions[i];

        for (int k = 0; k < iterations; k++)
        {
            arr[j] = i;
            j++;
        }
    }
}

int main()
{
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        arr[i] = k;
    }

    countingSort(arr, m);

    cout << "The array sorted by the algorithm:"
         << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\n";

    return 0;
}