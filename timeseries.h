#include "vector"

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{
vector<string>fvector;
public:

	TimeSeries(const char* CSVfileName);
	vector<string> namefeatur(){return fvector;};
	void addline();
	void valuejintimei();
	void writedata();
	float getvalue(string fname,float time);
};



#endif /* TIMESERIES_H_ */
