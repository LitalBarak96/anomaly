#include "vector"

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{
vector<string>fvector;
vector<pair<string ,vector<float>>>database;

public:

	TimeSeries(const char* CSVfileName);
	vector<string>getfeaturs(){return fvector;}
	void addline();
	void writedata();
	float getvalue(string fname,float time);
    vector<pair<string ,vector<float>>>getthetable() const {return database;}
//    void readcsv(const char* CSV);
};



#endif /* TIMESERIES_H_ */
