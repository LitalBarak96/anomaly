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
          int counter =0;
          float table [100][4]={};
          int num_type_data = 0;
          while(getline(myFile,line)) {//כל עוד יש לי שורות להמשיך איתם ביחס ל stringstream
              if (counter > 0) {
                  vector<string> result;
                  stringstream s_stream(line);
                  while (s_stream.good()) {
                      string substr;
                      getline(s_stream, substr, ',');
                      result.push_back(substr);
                  }
                  for (int i = 0; i < result.size(); i++) {
                      table[counter - 1][i] = stof(result.at(i));
                  }
              } else {
                  num_type_data=line.size()/2+1;
              }
              counter++;
          }
          myFile.close();

      }


}
void addline(){


    }

void valuejintimei(){

    }
void writedata(){

    }
float getvalue(string fname,float time){

    }
vector<string> namefeatur(){

    };