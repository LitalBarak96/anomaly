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

vector<float> TimeSeries:: getpoints(string fname){
    int foundFeatureIndex = -1;
    for (int i = 0; i < fvector.size(); ++i) {// מחפשת איפה נמצא הפיצר שאני רוצה
        if(fvector[i] == fname){
            foundFeatureIndex = i;

        }

    }
    if (foundFeatureIndex != -1){
        vector<float> timeCol = database[1];
        for (int i = 0; i < timeCol.size(); ++i) {
            myValueinLine.push_back(database[i][foundFeatureIndex]);
        }

    }
    }
vector<string> getfeaturs(){};



