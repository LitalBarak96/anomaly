#include <sstream>
#include "timeseries.h"
#include "iostream"
#include "istream"
#include "string"
#include "utility"
#include "vector"
#include "fstream"
#include "algorithm"

using namespace std;
    TimeSeries::TimeSeries(const char* CSVfileName)
    {
      ifstream myFile("CSVfileName");
      string line;
      if (myFile.is_open()){
          int counter=0;
          vector<float>temp;
          while(getline(myFile,line)) {//
              stringstream s_stream(line);
              if (counter == 0) {
                  while (s_stream.good()) {
                      string substr;
                      getline(s_stream, substr, ',');
                      fvector.push_back(substr);
//                      vector<float>ntemp;
//                      database.push_back(make_pair("featur",ntemp));

                  }
              } else {
                  while(s_stream.good()){
                      string substr;
                      getline(s_stream,substr,',');
                      temp.push_back(stof(substr));
                  }
                  database.push_back(temp);
                  temp.clear();
              }
              counter++;
          }
//          for (int i =0;i<temp.size();i=i+4){
//              for(int j=0;j<fvector.size();j++){
//                  pair<string ,vector<float>> mypair;
//                  vector<float>Myvectorpair;
//                  Myvectorpair.push_back(stof(temp.at(i+j)));
//                  mypair = make_pair(fvector.at(j),Myvectorpair);//השם של הפיצ'ר
//                  database.push_back(mypair);//זה אי ועוד ג'י כי הם כולם דחוסים אחד אחרי השני
//              }
//          }
          myFile.close();

      }


}
void TimeSeries::addline(){
        database.resize(database.size()+1);
    }

void TimeSeries::writedata(){

    }
float TimeSeries:: getvalue(string fname,float time){
        int foundTimeFeatureIndex = -1;
        int foundFeatureIndex = -1;

        for (int i = 0; i < fvector.size(); ++i) {//מחפשת בפיצ'ר וקטור איפה נמצא הזמן
            if(fvector[i] == "time"){
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

//void TimeSeries::readcsv(){}
