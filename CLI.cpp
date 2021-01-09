#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
}

void CLI::start(){
    Command *upCmd = new UploadCommand(dio);
    Command *detectCmd = new AnomalyDetectCommand(dio);
    Command *settingsCmd = new SettingsCommand(dio);
    commands[0] = upCmd;
    commands[1] = settingsCmd;
    commands[2] = detectCmd;

    dio->write("Welcome ya zalam\n");
    int input = 0;
    while (input != 7){
        dio->write("\nPlease choose command:\n");
        dio->write("1. Upload a time series csv file\n");
        dio->write("2. Algorithm settings\n");
        dio->write("3. Detect anomalies\n");

        string strInput = dio->read();
        commands[stoi(strInput) - 1]->execute();

        input = stoi(strInput);

    }




}


CLI::~CLI() {
}

