

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <utility>
#include <fstream>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

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

class StandardIO: public DefaultIO{
    virtual string read(){
        string s;
        cin>>s;
        return s;
    }
    virtual void write(string text){
        cout<<text;
    }

    virtual void write(float f){
        cout<<f;
    }

    virtual void read(float* f){
        cin>>*f;
    }
};

class SocketIO: public DefaultIO{
    int clientID;
public:
    SocketIO(int clientID){
        this->clientID = clientID;
    }
    string read(){
        string serverInput="";
        char c=0;
        ::read(this->clientID,&c,sizeof(char));
        while(c!='\n'){
            serverInput+=c;
            ::read(this->clientID,&c,sizeof(char));
        }
        return serverInput;
    }



    void write(string input) {
        ::write(this->clientID, input.c_str(), input.length());
    }


    void write(float f){
        string str;
        str = to_string(f);
        str.erase(str.find_first_not_of('0')+1,string::npos);
        ::write(this->clientID,str.c_str(),str.length());

    }

    void read(float* f){
    }
};
//class SocketIO: public DefaultIO{
//
//public:
//    int m_socket;
//    SocketIO(int socket){
//        m_socket = socket;
//    }
//
//    virtual string read(){
//        string serverInput="";
//        char c=0;
//        ::read(m_socket,&c,sizeof(char));
//        cout<<serverInput;
//        while(c!='\n'){
//            serverInput+=c;
//            ::read(m_socket,&c,sizeof(char));
//        }
//        cout<<serverInput;
//        return serverInput;
//    }
//
//    virtual void write(string text){
//        cout<<text;
//        ::write(m_socket,text.c_str(),text.length());
//        ::write(m_socket,"\n",1);
//    }
//
//
//    virtual void write(float f){
//
//    }
//
//    virtual void read(float* f){
//
//    }
//
//    ~SocketIO(){
//
//    }
//};


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
// ליצור GETTER ו SETTER ל TS
   void execute(){
        dio->write("Please upload your local train CSV file.");
        string inp = dio->read();
        while(inp != "done") {
            inp = dio->read();
        }
        dio->write("Upload complete.");
        dio->write("Please upload your local test CSV file.");
        string inp2 = dio->read();
        while(inp2!="done"){
            inp2=dio->read();
        }
        dio->write("Upload complete.");
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
	HAD.CorthreshHybrid = dio->getCorrelationSettings();
	HAD.CorthreshSimple = dio->getCorrelationSettings();
        TimeSeries *testTs = new TimeSeries(testFile);
        HAD.learnNormal(*trainTs);
        for (int i = 0;i<HAD.detect(*testTs).size();i++) {
            dio->setMAr(HAD.detect(*testTs).at(i).description,HAD.detect(*testTs).at(i).timeStep);
        }
        dio->setHad(HAD);
        dio->write("anomaly detection complete.");
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
        dio->write("Done.\n");
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
        for (int i = 0 ;i<dio->getMAr().size();i++) {

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
        dio->write("Please upload your local anomalies file.");
        string inputfrom = dio->read();
        dio->write("Upload complete.");
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
        while(((s.at(s.length()-1)=='0' || s.at(s.length()-1)=='.') && s != "0") || s.length()>5) {
            s = s.substr (0,s.length()-1);
        }
        dio->write("True Positive Rate: "+s);
        string a =to_string(Far);

        while(((a.at(a.length()-1)=='0' || a.at(a.length()-1)=='.') && a != "0") || a.length()>5) {
            a = a.substr (0,a.length()-1);
        }
        dio->write("False Positive Rate: "+a);

    }
};

#endif /* COMMANDS_H_ */
