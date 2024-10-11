#include <bits/stdc++.h>

using namespace std;

void swap(vector<int> &arr, int j, int i)
{
    int oldValue = arr[i];
    arr[i] = arr[j];
    arr[j] = oldValue;
}

void insertionSort(vector<int> &arr)
{
    // Worst case: O(n^2) - Reversed order
    // Best case: O(n) - n repetions of an element
    // The algorithm is stable and in place
    int n = arr.size();

    for (int i = 1; i < n; i++)
    {
        int j = i;

        while (0 < j && arr[j - 1] > arr[j])
        {
            swap(arr, j, j - 1);
            j--;
        }
    }
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

    insertionSort(arr);

    cout << "The array sorted by the algorithm:"
         << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\n";

    return 0;
}