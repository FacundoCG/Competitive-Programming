#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> merge(vector<pair<int,int>> &arr1, vector<pair<int,int>> &arr2)
{
    int n = arr1.size();
    int m = arr2.size();
    int t = n + m;
    vector<pair<int,int>> res(t);

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

vector<pair<int,int>> mergeSort(vector<pair<int,int>> &arr)
{   
    // Worst and best case: O(n * log n)
    // The algorithm is stable but not in place

    int n = arr.size();

    if (n <= 1)
    {
        return arr;
    }

    int mid = n / 2;

    vector<pair<int,int>> leftHalf, rightHalf;

    for (int i = 0; i < mid; i++)
    {
        leftHalf.push_back(arr[i]);
    }

    for (int i = mid; i < n; i++)
    {
        rightHalf.push_back(arr[i]);
    }

    vector<pair<int,int>> res1 = mergeSort(leftHalf);
    vector<pair<int,int>> res2 = mergeSort(rightHalf);

    return merge(res1, res2);
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> numbers(n);
    vector<pair<int, int>> numbersWithIndexs(n);

    for (int &m: numbers) cin >> m;

    for (int i = 0; i < n; i++){
        numbersWithIndexs[i] = {numbers[i], i+1};
    }

    vector<pair<int, int>> numbersIndexedSorted = mergeSort(numbersWithIndexs);

    pair<int,int> a = numbersIndexedSorted[0];
    pair<int,int> c = numbersIndexedSorted[n-1];
    pair<int, int> b = a;

    for (int i = 1; i < n-1; i++){
        b = numbersIndexedSorted[i];

        if (b.first != a.first && b.first != c.first){
            break;
        }
    }

    if (a.first == c.first || b.first == a.first || c.first == b.first){
        cout << -1 << " " << -1 << " " << -1 << "\n";
    } else {
        cout << a.second << " " << b.second << " " << c.second << "\n";
    }
}
