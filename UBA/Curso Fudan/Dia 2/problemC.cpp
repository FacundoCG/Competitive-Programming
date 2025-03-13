#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    
    while (n != -1){
		int currentTime = 0;
		int currentSpeed, currentTotalTime;
		int totalDistance = 0;
		
		for (int i = 0; i < n; i++){
			cin >> currentSpeed >> currentTotalTime;
			totalDistance += (currentTotalTime - currentTime)*currentSpeed;
			currentTime = currentTotalTime;
		}
		
		cout << totalDistance << " miles\n";
		cin >> n;
	}

    return 0;
}


