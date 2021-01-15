

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <utility>
#include <fstream>
#include <iomanip>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
protected:
    int size_of_allof;
public:
    int getSizeOfAllof() const {
        return size_of_allof;
    }

    void setSizeOfAllof(int sizeOfAllof) {
        size_of_allof = sizeOfAllof;
    }

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
        dio->write("Please upload your local train CSV file.\n");
        dio->uploadFile("train.csv");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->uploadFile("test.csv");
        dio->write("Upload complete.\n");
    }
};

class AnomalyDetectCommand:public Command{
public:
    AnomalyDetectCommand(DefaultIO *dio) : Command(dio) {}
    void execute(){
        HybridAnomalyDetector HAD;
        const char* trainFile = "train.csv";
        const char* testFile = "test.csv";
        TimeSeries *trainTs = new TimeSeries(trainFile);
        int size_of_all = trainTs->getthetable().size();
        dio->setSizeOfAllof(size_of_all);
        HAD.setCorthresh1(dio->getCorrelationSettings());
        HAD.setCorthresh(dio->getCorrelationSettings());
        TimeSeries *testTs = new TimeSeries(testFile);
        HAD.learnNormal(*trainTs);
        for (int i = 0;i<HAD.detect(*testTs).size();i++) {
            dio->setMAr(HAD.detect(*testTs).at(i).description,HAD.detect(*testTs).at(i).timeStep);
        }
        dio->setHad(HAD);
        dio->write("anomaly detection complete\n");
    }
};

class SettingsCommand:public Command{
public:
    SettingsCommand(DefaultIO *dio) : Command(dio) {}

    void execute(){
        dio->write("The current correlation threshold is " + dio->getCorrelationSettings() + "\n");
        dio->write("Type a new threshold\n");
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
            dio->write("\t "+dio->getMAr().at(i).description+"\n");

        }
        dio->write("\ndone.\n");
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
        long SumofN =0;

       vector<pair<long, long>> myVec;
        for (long i = 0 ;i<dio->getMAr().size();i++) {

            if ((i + 1 < dio->getMAr().size())) {
                if ((dio->getMAr().at(i).description == dio->getMAr().at(i + 1).description)) {
                    if (dio->getMAr().at(i + 1).timeStep - dio->getMAr().at(i).timeStep == 1) {
                        innercpunter++;
                    } else {
                        SumofN=SumofN+innercpunter+1;
                        myVec.push_back(std::make_pair(dio->getMAr().at(i- innercpunter).timeStep,dio->getMAr().at(i).timeStep  ));
                        innercpunter = 0;
                    }
                } else {
                    SumofN=SumofN+innercpunter+1;
                    myVec.push_back(std::make_pair(dio->getMAr().at(i- innercpunter).timeStep, dio->getMAr().at(i).timeStep));
                    innercpunter = 0;
                }

            }
            else{
                if (dio->getMAr().at(i-1).description == dio->getMAr().at(i).description) {
                    if (dio->getMAr().at(i).timeStep - dio->getMAr().at(i - 1).timeStep == 1) {
                        SumofN=SumofN+innercpunter+1;
                        myVec.push_back(std::make_pair(dio->getMAr().at(i- innercpunter).timeStep , dio->getMAr().at(i).timeStep ));
                        innercpunter = 0;
                    }
                }
            }
        }
        float N =dio->getSizeOfAllof();
        float TP=0;
        float numberoanomly = myVec.size();
        int P = myVec.size();
        int positive = 0;
        float FP =0;
        dio->write("Please upload your local anomalies file.\n");
        string inputfrom = dio->read();
        dio->write("Upload complete.\n");
        while(inputfrom!="done"){
            positive++;
            string delimit = ",";
            long first = stol(inputfrom.substr(0, inputfrom.find(delimit)));
            long second = stol(inputfrom.substr(inputfrom.find(delimit)+1, inputfrom.length()));
            int flag = 0 ;
            for(int j=0;j<P;j++){
                if ((myVec.at(j).first <=second && myVec.at(j).first >=first)||(myVec.at(j).second>=first&&myVec.at(j).second<=second)||(first>=myVec.at(j).first&&first<=myVec.at(j).second)||(second>=myVec.at(j).first&&second<=myVec.at(j).second)){
                    TP++;
                    numberoanomly--;

                }
                else{
                    flag = 1;
                }
            }
            if (flag>0) {
                N = N - (second-first+1);
            }
            inputfrom=dio->read();
        }
        float Tpr = TP/positive;
        float Far = numberoanomly/N;
        string s =to_string(Tpr);
        dio->write("True Positive Rate: ");
        while(((s.at(s.length()-1)=='0' || s.at(s.length()-1)=='.') && s != "0") || s.length()>5) {
            s = s.substr (0,s.length()-1);
        }
        dio->write(s);
        string a =to_string(Far);
        dio->write("\nFalse Positive Rate: ");
        while(((a.at(a.length()-1)=='0' || a.at(a.length()-1)=='.') && a != "0") || a.length()>5) {
            a = a.substr (0,a.length()-1);
        }
        dio->write(a);
        dio->write("\n");

    }
};

#endif /* COMMANDS_H_ */
