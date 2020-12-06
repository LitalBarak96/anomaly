#include "vector"

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{
vector<string>fvector;
vector<vector<float>>database;

public:

	TimeSeries(const char* CSVfileName);
	vector<string>getfeaturs() const {return fvector;}
	void addline();
	int sizeofdata();
	float getvalue(string fname,float time);
    vector<vector<float>>getthetable() const {return database;}
};



#endif /* TIMESERIES_H_ */
