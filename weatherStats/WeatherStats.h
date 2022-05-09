#ifndef WEATHERSTATS_H
#define WEATHERSTATS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <ctime>

#define RESOURCE_PATH "./resources/"
using namespace std;
class WeatherStats
{
    public:
        WeatherStats();
        bool IsValidTime(string date, string time);
        double CalcCoeff(string startDate, string startTime,string endDate, string endTime);
        virtual ~WeatherStats();
    private:
        map<time_t,double> m_mTimeToPressure;
        void LoadData();
        time_t GetFirstDateTime();
        time_t GetLastDateTime();
        time_t ConvertDateTime(std::string date, std::string time);
};

#endif // WEATHERSTATS_H
