#include <bits/stdc++.h>

using namespace std;

void swap(vector<int> &arr, int j, int i)
{
    int oldValue = arr[i];
    arr[i] = arr[j];
    arr[j] = oldValue;
}

void bubbleSort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n - i; j++)
        {
            if (arr[j - 1] > arr[j])
            {
                swap(arr, j - 1, j);
            }
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

    bubbleSort(arr);

    cout << "The array sorted by the algorithm:"
         << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\n";

    return 0;
}