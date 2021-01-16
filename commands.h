

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
        ofstream ofstream1("train.csv");
        string line;
        line = dio->read();
        while(line != "done"){
            ofstream1 << line + "\n";
            line = dio->read();
        }
        ofstream1.close();
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        ofstream ofstream2("test.csv");
        string line1 = "";
        line1 = dio->read();
        while(line1 != "done"){
            ofstream2 << line1 + "\n";
            line1 = dio->read();
        }
        ofstream2.close();
        dio->write("Upload complete.\n");
    }
};

class AnomalyDetectCommand:public Command{
public:
    AnomalyDetectCommand(DefaultIO *dio) : Command(dio) {}
    HybridAnomalyDetector had;
    void execute(){
        dio->write("Learning train file\n");
        const char* trainFile = dio->downloadFile("files/train.txt");
        const char* testFile = dio->downloadFile("files/test.txt");
        TimeSeries *trainTs = new TimeSeries(trainFile);
        had.learnNormal(*trainTs);
        TimeSeries *testTs = new TimeSeries(testFile);
        had.detect(*testTs);
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


#endif /* COMMANDS_H_ */
