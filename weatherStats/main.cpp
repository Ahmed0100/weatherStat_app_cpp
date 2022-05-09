#include <iostream>
#include "WeatherStats.cpp"
#include <string>

using namespace std;

int main()
{
    WeatherStats s;
    string sDate,sTime,eDate,eTime;
	cout << endl << "Enter START DATE as yyyy_mm_dd: ";
	cin >> sDate;
	cout << "Enter START TIME as hh:mm:ss (24-hour): ";
	cin >> sTime;

	if(!s.IsValidTime(sDate,sTime))
        return 1;

	cout << endl << "Enter END DATE as yyyy_mm_dd: ";
	cin >> eDate;
	cout << "Enter END TIME as hh:mm:ss (24-hour): ";
	cin >> eTime;

	if(!s.IsValidTime(eDate,eTime))
        return 1;

	double coeff = s.CalcCoeff(sDate, sTime,
                                      eDate, eTime);

    cout << endl << "Coefficient: " << coeff * 24 * 60 * 60 << " inHg/day" << endl;

    // determine if it's sunny or stormy
    if (coeff < 0)
    {
        cout << "Stormy conditions... Looks like you might need an umbrella!" << endl;
    }
    else
    {
        cout << "Sunny conditions... Don't forget your sunscreen!" << endl;
    }

    return 0;
}
