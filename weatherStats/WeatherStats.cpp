#include "WeatherStats.h"
using namespace std;

WeatherStats::WeatherStats()
{
    //ctor
    LoadData();
}

WeatherStats::~WeatherStats()
{
    //dtor
}
time_t WeatherStats::GetFirstDateTime()
{
    return m_mTimeToPressure.begin()->first;
}
time_t WeatherStats::GetLastDateTime()
{
    return m_mTimeToPressure.rbegin()->first;
}
bool WeatherStats::IsValidTime(string date,string p_time)
{
    time_t time=ConvertDateTime(date,p_time);
    if(time<0)
        return 0;
    return true;
}

void WeatherStats::LoadData()
{
    for(int year=2012;year<=2015;year++)
    {
        ostringstream fileNameStream;

        fileNameStream << RESOURCE_PATH << "Environmental_Data_Deep_Moor_" << year << ".txt";


        string fileName=fileNameStream.str();
        cout << "Loading " << fileName << endl;

        fstream dataFile;
        dataFile.open(fileName.c_str());

        string line;
        getline(dataFile,line);
        while(getline(dataFile,line))
        {
            string date,time;
            double  Air_Temp,	Barometric_Press,	Dew_Point,	Relative_Humidity,	Wind_Dir,	Wind_Gust,	Wind_Speed;
            istringstream buffer(line);
            buffer>>date>>time>>Air_Temp>>Barometric_Press>>Dew_Point>>Relative_Humidity>>Wind_Dir>>Wind_Gust>>Wind_Speed;
            time_t ptime =ConvertDateTime(date,time);
            m_mTimeToPressure[ptime]=Barometric_Press;
        }
        dataFile.close();
    }

}
time_t WeatherStats::ConvertDateTime(string date,string time)
{
    int yyyy=0,mon=0,dd=0;
    if (sscanf(date.c_str(), "%d_%d_%d", &yyyy, &mon, &dd) != 3)
    {
        cerr << "ERROR: Failed to parse date string " << date << endl;
        return -1;
    }
    int hh=0,mm=0,ss=0;
    if(sscanf(time.c_str(),"%d:%d:%d",&hh,&mm,&ss)!=3)
    {
        cerr << "ERROR: Failed to parse time string " << date << endl;
        return -2;
    }

    struct tm dateTime = {};
    dateTime.tm_year = yyyy - 1900; // years since 1900
    dateTime.tm_mon = mon - 1;      // months since January
    dateTime.tm_mday = dd;          // day of the month
    dateTime.tm_hour = hh;          // hours since midnight
    dateTime.tm_min = mm;           // minutes after the hour
    dateTime.tm_sec = ss;           // seconds after the minute

    // return a time_t value representing seconds since 1970
    return mktime(&dateTime);
}

double WeatherStats::CalcCoeff(string startDate, string startTime,
	                                   string endDate, string endTime)
{
    time_t sTime = ConvertDateTime(startDate,startTime);
    time_t eTime = ConvertDateTime(endDate,endTime);
    if(sTime>eTime)
    {
        cerr << "ERROR: The start date/time must occur before the end date/time" << endl;
        return -1;
    }
    map<time_t,double> ::iterator sIt;
    map<time_t,double> ::iterator eIt;
    sIt= m_mTimeToPressure.lower_bound(sTime);
    eIt= m_mTimeToPressure.lower_bound(eTime);
    double pressueDiff= eIt->second - sIt->second;
    double timeDiff = eIt->first - sIt->first;
    return pressueDiff/timeDiff;
}
