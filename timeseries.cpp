#include <sstream>
#include "timeseries.h"
#include "iostream"
#include "istream"
#include "string"
#include "utility"
#include "vector"
#include "fstream"



using namespace std;
    TimeSeries::TimeSeries(const char* CSVfileName)
    {
      ifstream myFile(CSVfileName);
      string line;
      if (myFile.is_open()){
          int counter=0;
          vector<float>mytempvector;
          while(getline(myFile,line)) {//
              stringstream s_stream(line);
              if (counter == 0) {
                  while (s_stream.good()) {
                      string fstr;
                      getline(s_stream, fstr, ',');
                      fvector.push_back(fstr);

                  }
              } else {
                  while(s_stream.good()){//כל עוד לא נגמרת השורה
                      string mystr;
                      getline(s_stream,mystr,',');
                      mytempvector.push_back(stof(mystr));
                  }
                  database.push_back(mytempvector);
                  mytempvector.clear();
              }
              counter++;
          }
          myFile.close();

      }


}
void TimeSeries::addline(){
        database.resize(database.size()+1);
    }

int TimeSeries::sizeofdata() {
       return database.size();

    }


float TimeSeries:: getvalue(string fname,float time){
        int foundTimeFeatureIndex = -1;
        int foundFeatureIndex = -1;

        for (int i = 0; i < fvector.size(); ++i) {//מחפשת בפיצ'ר וקטור איפה נמצא הזמן
            if(fvector[i] == "A"){
                foundTimeFeatureIndex = i;
            }
        }

        for (int i = 0; i < fvector.size(); ++i) {// מחפשת איפה נמצא הפיצר שאני רוצה
            if(fvector[i] == fname){
                foundFeatureIndex = i;

            }
        }

        int foundTimeRow = -1;

        if(foundTimeFeatureIndex != -1 && foundFeatureIndex != -1){// מסתכלת בטור של הזמן לבדוק באיזה אינדקס הוא נמצא בטור
             vector<float> timeCol = database[foundTimeFeatureIndex];
            for (int i = 0; i < timeCol.size(); ++i) {
                if(timeCol[i] == time){
                    foundTimeRow = i;
                }
            }

            if(foundTimeRow != -1){
               return database[foundTimeRow][foundFeatureIndex];// מחזירה את המיקום שרציתי
            }
        }

}
vector<string> getfeaturs(){};




//#include "timeseries.h"
//
//using namespace std;
//
//#include <string>
//#include <fstream>
//#include <vector>
//#include <utility> // std::pair
//#include <stdexcept> // std::runtime_error
//#include <sstream> // std::stringstream
//
//// only initialize featuresVectors
//void TimeSeries::initEmpty() {
//    std::vector<std::pair<std::string, std::vector<float>>> newFeaturesVectors;
//    featuresVectors = newFeaturesVectors;
//}
//
////create std::vector<std::pair<std::string, std::vector<int>>> featuresVectors which is
////a vector of pairs, feature name and vector of all its numerical values
//void TimeSeries::init(const string fileName) {
//    // Create a vector of <string, int vector> pairs to store the result
//    std::vector<std::pair<std::string, std::vector<float>>> newFeaturesVectors;
//    // Create an input filestream
//    std::ifstream myFile(fileName);
//    // Helper vars
//    std::string line, colname;
//    float val;
//    // Read the first line - the names of the features
//    std::getline(myFile, line);
//
//    // Create a stringstream from line
//    std::stringstream ss(line);
//
//    // Extract each column name and add to newFeaturesVectors, paired with empty vector
//    while (std::getline(ss, colname, ',')) {
//        // Initialize and add <colname, int vector> pairs to result
//        newFeaturesVectors.push_back({colname, std::vector<float>{}});
//    }
//
//    // Read data, line by line
//    while (std::getline(myFile, line)) {
//        // Create a stringstream of the current line
//        std::stringstream ss(line);
//
//        // Keep track of the current column index
//        int featureInd = 0;
//
//        // Extract each integer
//        while (ss >> val) {
//
//            // Add the current integer to the 'featureInd' column's values vector
//            newFeaturesVectors.at(featureInd).second.push_back(val);
//
//            // If the next token is a comma, ignore it and
//            if (ss.peek() == ',') ss.ignore();
//
//            // Increment the column index
//            featureInd++;
//        }
//    }
//    featuresVectors = newFeaturesVectors;
//    length = newFeaturesVectors.size();
//}
//
//
////return vector with the features names
//std::vector<std::string> TimeSeries::features() {
//    std::vector<std::string> feauteresVector;
//    //iterate over the features
//    for (int i = 0; i < TimeSeries::featuresVectors.size(); i++)
//        //add each feautere name to the answer vector
//        feauteresVector.push_back(TimeSeries::featuresVectors[i].first);
//    return feauteresVector;
//}
//
//// find the value of specific feature in specific time. if not found return -9999
//float TimeSeries::findValue(const string* feature, int time) const {
//    int ind = featureInd(feature);
//    //if ind is -9999 return -9999. else return the corresponding feature at index time
//    return ind == -9999 ? -9999 : TimeSeries::featuresVectors[featureInd(feature)].second.at(time);
//}
//
////return index of given feature in our vector of pairs
//int TimeSeries::featureInd(const std::string* toFind) const {
//    for(int i = 0; i < TimeSeries::length; i++) {
//        if(TimeSeries::featuresVectors[i].first == *toFind) {
//            return i;
//        }
//    }
//    return -9999;
//}
//
////return vector of asked feature
//vector<float> TimeSeries::featureVector(const std::string* feature) const{
//    return TimeSeries::featuresVectors[TimeSeries::featureInd(feature)].second;
//}
//
//
//
////return vector of floats, according to given vector of strings
//std::vector<float> vecToFloat(std::vector<std::string> stringV) {
//    std::vector<float> ans = {};
//    for (int i = 0; i < stringV.size(); i++)
//        ans.push_back(std::stof(stringV[i]));
//    return ans;
//}
//
////add line, i.e. one numerical value to each feature. assuming the number of values equals the number of features we already have
//void TimeSeries::addLineValues(std::string valuesLine) {
//    std::vector<std::string> splitted_str = split(valuesLine, ',');
//    std::vector<float> splitted_float = vecToFloat(splitted_str);
//    for(int i = 0;  i < splitted_float.size(); i++) {
//        TimeSeries::featuresVectors[i].second.push_back(splitted_float[i]);
//    }
//}
//
////add title line
//void TimeSeries::addLineFeatures(string titleLine) {
//    std::vector<std::string> splitted = split(titleLine, ',');
//    for(int i = 0; i < splitted.size(); i++) {
//        TimeSeries::featuresVectors.push_back({splitted[i], std::vector<float>{}});
//    }
//    length = splitted.size();
//}
//
//TimeSeries::TimeSeries(const TimeSeries &other) {
//    featuresVectors = other.getFeaturesVectors();
//    length = other.length;
//}
//
//
//
