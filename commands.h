

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <utility>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
protected:
    ofstream out;
    ifstream in;
    string fileData1;
    string fileData2;
    string correlationSettings = "1";
    HybridAnomalyDetector had;
    vector<AnomalyReport> myAr;
public:
    const vector<AnomalyReport> &getMAr() const {
        return myAr;
    }

    void setMAr(string name,long timestep) {
        AnomalyReport *An = new AnomalyReport(name,timestep);
        myAr.push_back(*An);

    }

public:
    const HybridAnomalyDetector &getHad() const {
        return had;
    }

    void setHad(const HybridAnomalyDetector &had) {
        DefaultIO::had = had;
    }

public:
    const string &getCorrelationSettings() const {
        return correlationSettings;
    }

    void setCorrelationSettings(const string &correlationSettings) {
        DefaultIO::correlationSettings = correlationSettings;
    }

public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}
	virtual void uploadFile(string path)=0;
	virtual const char * downloadFile(string path)=0;

	// you may add additional methods here
};



// you may add here helper classes

// you may edit this class
class Command{
protected:
    DefaultIO* dio;
public:
	Command(DefaultIO* dio):dio(dio){}
    virtual void execute()=0;
    virtual ~Command(){}
};

// implement here your command classes
class UploadCommand:public Command{
    ifstream in;

public:
    UploadCommand(DefaultIO *dio) : Command(dio) {}//constructor

    void execute(){
        dio->write("Please insert file path to upload train file:\n");
        dio->uploadFile("train.csv");
        dio->write("Upload complete\n");
        dio->write("Please insert file path to upload test file:\n");
        dio->uploadFile("test.csv");
        dio->write("Upload complete\n");
    }
};

class AnomalyDetectCommand:public Command{
public:
    AnomalyDetectCommand(DefaultIO *dio) : Command(dio) {}
    void execute(){
        HybridAnomalyDetector HAD;
        dio->write("Learning train file\n");
        const char* trainFile = "train.csv";
        const char* testFile = "test.csv";
        TimeSeries *trainTs = new TimeSeries(trainFile);
        HAD.setCorthresh1(dio->getCorrelationSettings());
        HAD.setCorthresh(dio->getCorrelationSettings());
        TimeSeries *testTs = new TimeSeries(testFile);
        HAD.learnNormal(*trainTs);
        for (int i = 0;i<HAD.detect(*testTs).size();i++) {
            dio->setMAr(HAD.detect(*testTs).at(i).description,HAD.detect(*testTs).at(i).timeStep);
        }
        dio->setHad(HAD);
        dio->write("Anomaly detection complete\n");
    }
};

class SettingsCommand:public Command{
public:
    SettingsCommand(DefaultIO *dio) : Command(dio) {}

    void execute(){
        dio->write("The correlation threshold is: " + dio->getCorrelationSettings() + "\n");
        dio->write("Type the new threshold \n");
        string corre = dio->read();
        float correFloat = stof(corre);
        while(correFloat > 1 || correFloat < 0){
            dio->write("Please choose a value between 0 and 1\n");
            corre = dio->read();
            correFloat = stof(corre);
        }

        dio->setCorrelationSettings(corre);
    }
};

class Anomalyreport:public Command{
public:
    Anomalyreport(DefaultIO *dio) : Command(dio) {}
    void execute(){
        dio->getMAr().size();
        for (int i = 0 ;i <dio->getMAr().size();i++){
            dio->write(dio->getMAr().at(i).timeStep);
            dio->write("\t"+dio->getMAr().at(i).description+"\n");

        }
    }
};

class AnalysR:public Command{
public:
    AnalysR(DefaultIO *dio) : Command(dio) {}
    void execute(){
//        int deletcounter = 0;
//        vector<pair<long, string>> myVec;
//        for (int i = 0 ;i<dio->getMAr().size();i++) {
//            myVec.push_back(std::make_pair(dio->getMAr().at(i).timeStep, dio->getMAr().at(i).description));
//        }
//        int sizevec=myVec.size();
//        for (int j = 0;j<myVec.size();j++){
//            if (myVec.at(j).second==myVec.at(j+1).second&& j+1<myVec.size()){
//                if (myVec.at(j+1).first-myVec.at(j).first==1&& j+1<myVec.size()){
//                    deletcounter++;
//                }
//                else{
//                    myVec.erase(myVec.begin()+j+1-deletcounter,myVec.begin()+j);
//                    deletcounter=0;
//
//                }
//
//            }
//            else{
//                deletcounter=0;
//            }
//
//        }
//
    }
};

#endif /* COMMANDS_H_ */
