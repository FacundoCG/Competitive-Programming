#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n;
        long long l;
        cin >> n >> l;

        vector<long long> flags(n);


        for (long long &j : flags) cin >> j;

        double positionC1 = 0;
        double positionC2 = (double) l;
        int speedC1 = 1;
        int speedC2 = 1;
        int closestFlagC1 = 0;
        int closestFlagC2 = n-1;
        double totalTime = 0;

        while (closestFlagC1 <= closestFlagC2){
            double timeToFlagC1 = (double) (flags[closestFlagC1] - positionC1)/speedC1;
            double timeToFlagC2 = (double) (positionC2 - flags[closestFlagC2])/speedC2;

            if (timeToFlagC1 < timeToFlagC2){
                totalTime += timeToFlagC1;
                positionC1 = flags[closestFlagC1];
                positionC2 -= speedC2 * timeToFlagC1;
                speedC1++;
                closestFlagC1++;
            } else {
                totalTime += timeToFlagC2;
                positionC1 += speedC1 * timeToFlagC2;
                positionC2 = flags[closestFlagC2];
                speedC2++;
                closestFlagC2--;
            }
        }

        totalTime += (double)(positionC2 - positionC1)/(speedC1 + speedC2);
        
        cout << fixed << setprecision(16) << totalTime << "\n";
    }
}
