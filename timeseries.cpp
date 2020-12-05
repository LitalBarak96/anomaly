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
      ifstream myFile("CSVfileName");
      string line;
      if (myFile.is_open()){
          int counter=0;
          vector<string>temp;
          while(getline(myFile,line)) {//
              stringstream s_stream(line);
              if (counter == 0) {
                  while (s_stream.good()) {
                      string substr;
                      getline(s_stream, substr, ',');
                      fvector.push_back(substr);
                      vector<float>ntemp;
                      database.push_back(make_pair("0",ntemp));

                  }
              } else {
                  while(s_stream.good()){
                      string substr;
                      getline(s_stream,substr,',');
                      temp.push_back(substr);
                  }
              }
              counter++;
          }
          for (int i =0;i<temp.size();i=i+4){
              for(int j=0;j<fvector.size();j++){
                  pair<string ,vector<float>> mypair;
                  vector<float>Myvectorpair;
                  Myvectorpair.push_back(stof(temp.at(i+j)));
                  mypair = make_pair(j,Myvectorpair);
                  database.push_back(mypair);//זה אי ועוד ג'י כי הם כולם דחוסים אחד אחרי השני
              }
          }
          myFile.close();

      }


}
void TimeSeries::addline(){
        database.resize(database.size()+1);
    }

void TimeSeries::writedata(){

    }
float TimeSeries:: getvalue(string fname,float time){


    }
vector<string> getfeaturs(){};

//void TimeSeries::readcsv(){}
