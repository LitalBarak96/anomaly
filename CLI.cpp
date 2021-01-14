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

    dio->write("Welcome to the Anomaly Detection Server.\n");
    int input = 0;
    while (input != 6){
        dio->write("\nPlease choose an option:\n");
        dio->write("1.upload a time series csv file\n");
        dio->write("2.Algorithm settings\n");
        dio->write("3.Detect anomalies\n");
        dio->write("4.display results\n");
        dio->write("5.upload anomalies and analyze results\n");
        dio->write("6.exit\n");

        string strInput = dio->read();
        commands[stoi(strInput) - 1]->execute();

        input = stoi(strInput);

    }




}


CLI::~CLI() {
}

