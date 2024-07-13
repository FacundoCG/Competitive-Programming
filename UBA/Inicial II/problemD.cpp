#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<long long>& arr, int start, int end, long long v){
    if (start > end){
        return start;
    }

    int middle = (start + end)/2;

    if (arr[middle] == v){
        return middle;
    } else if (arr[middle] > v){
        return binarySearch(arr, start, middle-1, v);
    } else {
        return binarySearch(arr, middle+1, end, v);
    }
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    
    vector<long long> warriors(n);
    vector<long long> minutes(q);
    vector<long long> prefixSum(n);

    for (int i = 0; i < n; i++){
        long long w;
        cin >> w;
        warriors[i] = w;
    }
    
    int deads = 0; // Number of dead warriors
    int lastWarriorAlive = 0; // Position of the last warrior alive
    long long extraDamage = 0; // Damage of the last warrior alive

    prefixSum[0] = warriors[0];
    for (int i = 1; i < n; i++){
        prefixSum[i] = prefixSum[i-1] + warriors[i];
    }

    for (int i = 0; i < q; i++){
        long long arr;
        cin >> arr;
        minutes[i] = arr;
    }

    int newLast; // Position of the new last warrior alive

    for (int i = 0; i < q; i++){
        if (lastWarriorAlive == 0){
            newLast = binarySearch(prefixSum, lastWarriorAlive, n-1, minutes[i] + extraDamage);

            if (prefixSum[newLast] <= (minutes[i] + extraDamage)){
                extraDamage = (minutes[i] + extraDamage) - prefixSum[newLast];
                deads += (newLast - lastWarriorAlive) + 1;
                lastWarriorAlive = newLast + 1;
            } else if (prefixSum[newLast] > (minutes[i] + extraDamage)){
                int lifeWarrior = prefixSum[newLast] - (minutes[i] + extraDamage);
                extraDamage = warriors[newLast] - lifeWarrior;
                deads += (newLast - lastWarriorAlive);
                lastWarriorAlive = newLast;
            }
        } else {
            newLast = binarySearch(prefixSum, lastWarriorAlive, n-1, minutes[i] + extraDamage + prefixSum[lastWarriorAlive-1]);

            if (prefixSum[newLast] <= (minutes[i] + extraDamage + prefixSum[lastWarriorAlive-1])){
                extraDamage = (minutes[i] + extraDamage + prefixSum[lastWarriorAlive-1]) - prefixSum[newLast];
                deads += (newLast - lastWarriorAlive) + 1;
                lastWarriorAlive = newLast + 1;
            } else if (prefixSum[newLast] > (minutes[i] + extraDamage + prefixSum[lastWarriorAlive-1])){
                int lifeWarrior = prefixSum[newLast] - (minutes[i] + extraDamage + prefixSum[lastWarriorAlive-1]);
                extraDamage = warriors[newLast] - lifeWarrior;
                deads += (newLast - lastWarriorAlive);
                lastWarriorAlive = newLast;
            }
        }      

        if (deads >= n){
            deads = 0;
            extraDamage = 0;
            lastWarriorAlive = 0;
        }

        cout << n-deads << "\n";
    }

}