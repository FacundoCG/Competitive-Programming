#include <iostream>
#include <vector>
using namespace std;

int leftBinarySearch(int start, int end, vector<double> &distanceForCards, double c){
	int l = start-1;
	int r = end+1;
	
	while (r - l > 1){
		int mid = (r+l)/2;
		
		if (distanceForCards[mid] < c){
			l = mid; 
		} else {
			r = mid;
		}
	}
	
	return l+1;
}

int main()
{
    double c;
    cin >> c;
    
    vector<double> distanceForCards(10000);
    
    for (int i = 1; i < (int) distanceForCards.size(); i++){
		double term = 1/(double) (i+1);
		distanceForCards[i] = (double) distanceForCards[i-1] + term;
	}
        
    while (c != 0.00){
		int numberOfCard = leftBinarySearch(1, 10000, distanceForCards, c);
		cout << numberOfCard << " card(s)\n";
		cin >> c;
	}

    return 0;
}


