#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
}

void CLI::start(){
    Command *upCmd = new UploadCommand(dio);
    Command *settingsCmd = new SettingsCommand(dio);
    Command *detectCmd = new AnomalyDetectCommand(dio);
    Command *Anomly = new Anomalyreport (dio);
    Command *displyanom = new AnalysR(dio);
    Command *exit = new myexit(dio);

    commands[0] = upCmd;
    commands[1] = settingsCmd;
    commands[2] = detectCmd;
    commands[3] = Anomly;
    commands[4] = displyanom;
    commands[5] = exit;


    int input = 0;
    while (input != 6){
        dio->write("Welcome to the Anomaly Detection Server.");
        dio->write("Please choose an option:");
        dio->write("1.upload a time series csv file");
        dio->write("2.algorithm settings");
        dio->write("3.detect anomalies");
        dio->write("4.display results");
        dio->write("5.upload anomalies and analyze results");
        dio->write("6.exit");

        string strInput = dio->read();
        commands[stoi(strInput) - 1]->execute();

        input = stoi(strInput);

    }




}


CLI::~CLI() {
}

