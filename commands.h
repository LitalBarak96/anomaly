

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
protected:
    ofstream out;
    ifstream in;
    string workingData;
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}
	virtual void uploadFile(string path)=0;
	virtual string downloadFile(string path)=0;


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
    UploadCommand(DefaultIO *dio) : Command(dio) {}

    void execute(){
        dio->write("Please insert file path to upload:\n");
        string path = dio->read();
        dio->uploadFile(path);
        dio->write("Upload complete");
    }
};

class AnomalyDetectCommand:public Command{
public:
    AnomalyDetectCommand(DefaultIO *dio) : Command(dio) {}

    void execute(){
        dio->write("DEDECTINGGGGG\n");
        string dataFromFile = dio->downloadFile("asdfasdf");
        cout << "THE DATA IS\n";
        cout << dataFromFile;
    }
};


#endif /* COMMANDS_H_ */
