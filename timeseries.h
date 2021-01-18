#include "vector"
#include "string"
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



//#ifndef TIMESERIES_H_
//#define TIMESERIES_H_
//
//#include <string>
//#include <vector>
//#include <sstream>
//
//using namespace std;
//
//class TimeSeries{
//    std::vector<std::pair<std::string, std::vector<float>>> featuresVectors;
//public:
//    ////number of features
//    int length{};
//    ////constructor
//    explicit TimeSeries (const char* CSVfileName){init(CSVfileName);}
//    explicit TimeSeries (){initEmpty();}
//    TimeSeries(TimeSeries const &other);
//    void initEmpty();
//    void init(string fileName);
//    //// return vector with the features names
//    std::vector<std::string> features();
//    //// find value of given feature at given time
//    float findValue(const string* feature, int time) const;
//    //// add new line of values to all features
//    void addLineValues(std::string valuesLine);
//    //// add line of feature names
//    void addLineFeatures(std::string titleLine);
//    //// return the featuresVectors (by value)
//    std::vector<std::pair<std::string, std::vector<float>>> getFeaturesVectors() const {return featuresVectors;}
//    //// return index of given feature
//    int featureInd(const std::string* toFind) const;
//    ////return vector of given feature
//    vector<float> featureVector(const std::string* feature) const;
//    ////split given string according to given delimiter
//    static std::vector<std::string> split(const std::string& s, char delimiter) {
//        std::vector<std::string> tokens;
//        std::string token;
//        std::istringstream tokenStream(s);
//        while (std::getline(tokenStream, token, delimiter))
//        {
//            tokens.push_back(token);
//        }
//        return tokens;
//    }
//};



//#endif /* TIMESERIES_H_ */
