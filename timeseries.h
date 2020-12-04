#include "vector"

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{
vector<string>fvector;
float table[100][4]={};
int counter=0;
public:

	TimeSeries(const char* CSVfileName);
	vector<string> namefeatur(){return fvector;};
	void addline();
	void writedata();
	float getvalue(string fname,float time);
};



#endif /* TIMESERIES_H_ */
