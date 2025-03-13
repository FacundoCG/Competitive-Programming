#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool isLeapYear(int year){
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInYear(int year){
	return isLeapYear(year) ? 366 : 365;
}

int getDaysInMonth(int month, int year) {
    if (month == 1) return 31;
    else if (month == 2) return isLeapYear(year) ? 29 : 28;
    else if (month == 3) return 31;
    else if (month == 4) return 30;
    else if (month == 5) return 31;
    else if (month == 6) return 30;
    else if (month == 7) return 31;
    else if (month == 8) return 31;
    else if (month == 9) return 30;
    else if (month == 10) return 31;
    else if (month == 11) return 30;
    else if (month == 12) return 31;
}

string getDayOfWeek(int totalDays, vector<string> &days) {
    return days[totalDays % 7];
}

void calculateDate(int n, vector<string> &days) {
    int year = 2000;
    int month = 1;
    int day = 1;
	int totalDaysFrom2000 = n;
	
    while (n > 0) {
        if (n >= getDaysInYear(year)) {
            n -= getDaysInYear(year);
            year++;
        } else if (n >= getDaysInMonth(month, year)){
			n -= getDaysInMonth(month, year);
			month++;
			if (month > 12){
				month = 1;
				year++;
			}
		} else {
			day += n;
			n = 0;
		}
    }

    cout << year << "-" << (month < 10 ? "0" : "") << month
         << "-" << (day < 10 ? "0" : "") << day << " " << getDayOfWeek(totalDaysFrom2000, days) << "\n";
}

int main(){
	int n;
	cin >> n;
	
	vector<string> days;
    days.push_back("Saturday");
    days.push_back("Sunday");
    days.push_back("Monday");
    days.push_back("Tuesday");
    days.push_back("Wednesday");
    days.push_back("Thursday");
    days.push_back("Friday"); 
	
	while (n != -1){
		calculateDate(n, days);
		cin >> n;
	}
	
	return 0;
}
