#include "vector"
#include "string"
#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{
vector<string>fvector;
vector<vector<float>>database;
vector<float> myValueinLine;
public:
	TimeSeries(const char* CSVfileName);
	vector<string>getfeaturs() const {return fvector;}
	void addline();
	int sizeofdata();
	float getvalue(string fname,float time);
    vector<float> returnthepoints(string fname) const {return myValueinLine;};
    vector<vector<float>>getthetable() const {return database;}

    vector<float> getpoints(string name);

};



#endif /* TIMESERIES_H_ */
