#include <bits/stdc++.h>

using namespace std;

void swap(vector<int> &arr, int j, int i)
{
    int oldValue = arr[i];
    arr[i] = arr[j];
    arr[j] = oldValue;
}

int minValue(vector<int> &arr, int j)
{                       // The functions return the index of the minimum value
    int n = arr.size(); // n > 0
    int min = j;

    for (int i = j + 1; i < n; i++)
    {
        if (arr[i] < arr[min])
        {
            min = i;
        }
    }

    return min;
}

void selectionSort(vector<int> &arr)
{
    // Worst and best case: O(n^2)
    // The algorithm is stable and in place

    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        int min = minValue(arr, i);
        swap(arr, min, i);
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

    selectionSort(arr);

    cout << "The array sorted by the algorithm:" << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\n";

    return 0;
}