

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
    string correlationSettings = "0.9";
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
        dio->write("done.");
    }
};

class myexit:public Command{
public:
    myexit(DefaultIO *dio) : Command(dio) {}
    void execute(){

    }
};

class AnalysR:public Command{
public:
    AnalysR(DefaultIO *dio) : Command(dio) {}
    void execute(){
        long innercpunter=0;
        int CountofN = 0 ;


       vector<pair<long, long>> myVec;
        for (long i = 0 ;i<dio->getMAr().size();i++) {
            if ((i + 1 < dio->getMAr().size())) {
                if (dio->getMAr().at(i).description == dio->getMAr().at(i + 1).description) {
                    if (dio->getMAr().at(i + 1).timeStep - dio->getMAr().at(i).timeStep == 1) {
                        innercpunter++;
                        CountofN++;
                    } else {
                        myVec.push_back(std::make_pair(i, i + innercpunter));
                        innercpunter = 0;
                    }
                } else {
                    myVec.push_back(std::make_pair(i, i + innercpunter));
                    innercpunter = 0;
                }

            }
            else{
                if (dio->getMAr().at(i-1).description == dio->getMAr().at(i).description) {
                    if (dio->getMAr().at(i).timeStep - dio->getMAr().at(i - 1).timeStep == 1) {
                        myVec.push_back(std::make_pair(i - innercpunter + 1, i + 1));
                        innercpunter = 0;
                    }
                }
            }
        }
        int N = dio->getMAr().size() -CountofN;
        float TP=0;
        int P = myVec.size();
        float FP =0;
        string inputfrom = dio->read();
        while(inputfrom!="done"){
            string delimit = ",";
            long first = stol(inputfrom.substr(0, inputfrom.find(delimit)));
            long second = stol(inputfrom.substr(inputfrom.find(delimit)+1, inputfrom.length()));

            for(int j =0;j>P;j++){
                if ((myVec.at(j).first <=second && myVec.at(j).first >=first)||(myVec.at(j).second>=first&&myVec.at(j).second<=second)){
                    TP++;

                } else{
                    FP++;
                }
            }
            inputfrom=dio->read();
        }
        float Tpr = TP/P;
        float Far = FP/N;
        dio->write("True Positive Rate: ");
        dio->write(Tpr);
        dio->write("False Positive Rate: ");
        dio->write(Far);

    }
};

#endif /* COMMANDS_H_ */
