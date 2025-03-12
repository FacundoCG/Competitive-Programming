#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        string s;
        cin >> s;

        string firstNumbers = s.substr(0, 2);
        int firstNumbersTime = stoi(firstNumbers);
        
        if (firstNumbersTime == 0){
            string formattedTime = "12";
            formattedTime += s.substr(2, 5);
            formattedTime += " AM";

            cout << formattedTime << "\n";
        } else if (firstNumbersTime < 12){
            s += " AM";
            cout << s << "\n";
        } else if (firstNumbersTime == 12){
            s += " PM";
            cout << s << "\n";
        } else {
            int newTime = firstNumbersTime-12;
            string formattedTime = "";

            if (newTime < 10){
                formattedTime += "0";
            }

            formattedTime += to_string(newTime);
            formattedTime += s.substr(2, 5);
            formattedTime += " PM";
            cout << formattedTime << "\n";
        }
    }
}